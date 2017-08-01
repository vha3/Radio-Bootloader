#include <msp430.h>
#include "pins.h"
#include "wiring.h"
#include "cc430flash.h"
#include "ccpacket.h"
#include "cc430f5137.h"
#include "cc430radio.h"
#include "pmm.h"
#include <stdio.h>
#include <pt.h>
#include <pt-sem.h>
#include "timer1a0.h"



#define RFCHANNEL        0       // Let's use channel 0
#define SYNCWORD1        0xFF    // Synchronization word, high byte
#define SYNCWORD0        0x00    // Synchronization word, low byte
#define SOURCE_ADDR      1       // Sender address
#define DESTINATION_ADDR 0       // Receiver address

#define BEACON_TIMEOUT   2000	 // Send thread timeout
#define BEACON_THRESHOLD 500	 // Send thread threshold

// Protothread structs
static struct pt pt_polling, pt_receiving, pt_sending;

// Signaling semaphores
static struct pt_sem signal_receipt;

uint8_t status;    //Global int to hold PKTSTATUS register value
uint8_t bytes;     //Global int to hold number of bytes in RXFIFO

CCPACKET packet;   //Declare global packet
CC430RADIO radio;  //Radio object

TIMER1A0 timer;	   //Timer object


/*
 * This protothread polls the packet status register and the RXFIFO register
 * to determine whether there is a received packet waiting to be read. If so
 * it signals the signal_receipt semaphore, which allows the receiving
 * protothread to run.
 */
static PT_THREAD (protothread_polling(struct pt *pt))
		{
			PT_BEGIN(pt);									//Begin protothread
			while(1) {
				status = ReadSingleReg(PKTSTATUS);  		//Read PKTSTATUS register
				bytes = ReadSingleReg(RXBYTES);				//Read RXBYTES register
				if((status & 0x01) && bytes){				//If a sync word has been received and there are bytes in the FIFO
					while(ReadSingleReg(PKTSTATUS) & 0x01); //Wait for end of packet
					PT_SEM_SIGNAL(pt, &signal_receipt);		//Signal protothread two
					PT_YIELD(pt);							//Yield control
				}
				PT_YIELD(pt);								//Yield control
			}												//Never leave while loop
			PT_END(pt);										//End protothread
		}


/*
 * This protothread waits on the signal_receipt semaphore, and then reads the data
 * out of the RX FIFO, verifying the checksum. Because it depends on the semaphore
 * to run, it will only run once (unless signaled again).
 */
static PT_THREAD (protothread_receiving(struct pt *pt))
		{
			PT_BEGIN(pt);											//begin protothread
			while(1) {
				PT_SEM_WAIT(pt, &signal_receipt); 				    //wait on a semaphore
				if (radio.receiveData(&packet) > 0){			    //copy data into global CCPACKET, verify nonzero length
					if (packet.crc_ok){								//verify checksum
						digitalWrite(LED_2, !digitalRead(LED_2));	//toggle LED_2
						for(uint8_t i=0; i<packet.length; i++){		//loop through received data (in global CCPACKET)
							printf("%02X", packet.data[i]);			//print data to console
						}
						printf("\n");								//print newline
					}
				}
			}														//never leave while loop
			PT_END(pt);												//end protothread
		}


/*
 * This thread sends a packet at a rate specified by BEACON_THRESHOLD
 */
static PT_THREAD (protothread_sending(struct pt *pt))
		{
			PT_BEGIN(pt);														//Begin protothread
			while(1) {
				digitalWrite(LED_1, !digitalRead(LED_1));						//Toggle LED
				packet.length = 10;												//Set data length
				packet.data[0] = DESTINATION_ADDR;								//Set destination address
				for(int i=0; i<packet.length; i++){								//Pack data
					packet.data[i]=(unsigned char)255;
				}
				radio.sendData(packet);											//Send data
				timer.start(BEACON_TIMEOUT);									//Wait for timer to exceed threshold
				PT_YIELD_UNTIL(pt, timer.time_exceeded(BEACON_THRESHOLD));		//Yield control
			}																	//Never leave while loop
			PT_END(pt);															//End protothread
		}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;					//Stop watchdog timer

    /*
     * Pin Modes and Initial Settings
     */
	pinMode(LED_2, OUTPUT);						//set LED_2 to output
	pinMode(LED_1, OUTPUT);						//set LED_1 to output
	pinMode(BUTTON_ONE, INPUT);					//set button one to input
	pinMode(BUTTON_TWO, INPUT);					//set button two to input
	digitalWrite(LED_2, LOW);					//write LED_2 low
	digitalWrite(LED_1, LOW);					//write LED_1 low

	/*
	 * Internal Voltage Setting
	 */
	SetVCore(2);								//set internal voltage level

//	CC430RADIO radio;

	/*
	 * Radio settings (radio object defined globally)
	 */
    radio.setChannel(RFCHANNEL);				//set radio channel
    radio.setSyncWord(SYNCWORD1, SYNCWORD0);	//set sync word
    radio.setDevAddress(SOURCE_ADDR);			//set source address
    radio.init();								//initialize radio
    radio.disableAddressCheck();				//disable address check
    radio.enableCCA(false);						//disable CCA

    /*
     * Protothreads initializations (threads and semaphores)
     */
	PT_INIT(&pt_polling);						//initialize polling thread
	PT_INIT(&pt_receiving);						//initialize receiving thread
	PT_INIT(&pt_sending);						//initialize sending thread
	PT_SEM_INIT(&signal_receipt, 0);    		//initialize receipt semaphore to 0

	/*
	 * Round-Robin thread scheduler.
	 * Threads can be commented in/out to make chip sender/receiver
	 */
	while(1) {
			PT_SCHEDULE(protothread_polling(&pt_polling));
			PT_SCHEDULE(protothread_receiving(&pt_receiving));
//			PT_SCHEDULE(protothread_sending(&pt_sending));
	}

	return 0;
}

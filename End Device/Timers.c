/*
 * Timers.c
 *
 *  Created on: 28 oct 2021
 *      Author: sergio_mndz
 */

#include "Timers.h"

osaEventId_t timerEvents;
/* Global Variable to store our TimerID */
tmrTimerID_t timer3sID;
/* Handler ID for task */
osaTaskId_t gTimerTaskHandler_ID;
/* Local variable to store the current state of the LEDs */
//static ledStatus_t ledsState = RED;
volatile uint8_t gLedCount = 0;

/* This is the function called by the Timer each time it expires */
static void taskTimerCallback(void *param)
{
	OSA_EventSet(timerEvents, gTimerTaskEvent1_c);

	/**este evento sera usado para incrementar el contador*/
}

void My_Task(osaTaskParam_t argument)
{

	volatile force_green_led = 0 ;
	volatile force_blue_led = 0 ;
	osaEventFlags_t customEvent;
	while(1)
	{
		OSA_EventWait(timerEvents, osaEventFlagsAll_c, FALSE, osaWaitForever_c,
				&customEvent);
		if( !gUseRtos_c && !customEvent)
		{
			break;
		}
		/* Depending on the received event */
		switch(customEvent){
		case gTimerTaskEvent1_c:
			/* 3 seconds passed so increment LED count */

			increment_LedCount();
			set_LedState();

			break;
		case gTimerTaskEvent2_c: /* Switch 3 pressed */
			set_LedCount(GREEN);
			set_LedState();

			force_green_led= 1 ;

			resetTimer();
			break;
		case gTimerTaskEvent3_c: /* Switch 4 pressed */
			set_LedCount(BLUE);
			set_LedState();

			force_blue_led = 1 ;
			resetTimer();
			break;
		case gTimerTaskEvent4_c:
			TMR_StopTimer(timer3sID);
			TMR_StartIntervalTimer(timer3sID, /*myTimerID*/
					3000, /* Timer's Timeout */
					taskTimerCallback, /* pointer to myTaskTimerCallback function */
					NULL
			);
			break;
		default:
			break;
		}

	}
}

/* OSA Task Definition*/
OSA_TASK_DEFINE(My_Task, gTimerTaskPriority_c, 1, gTimerTaskStackSize_c, FALSE );

/* Function to init the task */
void timerTask_Init(void)
{
	timerEvents = OSA_EventCreate(TRUE);
	/* The instance of the MAC is passed at task creaton */
	gTimerTaskHandler_ID = OSA_TaskCreate(OSA_TASK(My_Task), NULL);
}

void timer3s_Start(void)
{
	timer3sID = TMR_AllocateTimer();
	TMR_StartIntervalTimer(timer3sID, /*myTimerID*/
			3000, /* Timer's Timeout */
			taskTimerCallback, /* pointer to myTaskTimerCallback function */
			NULL
	);
}

void resetTimer(void)
{
	OSA_EventSet(timerEvents, gTimerTaskEvent4_c);
}

/* Public function to send an event to stop the timer */
void timer3s_Stop(void)
{
	OSA_EventSet(timerEvents, gTimerTaskEvent4_c);
}

void increment_LedCount()
{
	gLedCount++;
	if(gLedCount > WHITE )
	{
		gLedCount = RED ;
	}
}


void reset_LedCount()
{
	gLedCount = 0 ;
}

void set_LedCount(uint8_t newCount)
{
	if(newCount <= WHITE)
	{
		gLedCount = newCount;
	}
}

uint8_t get_LedCount( void )
{
	return gLedCount ;
}

void set_LedState()
{
	LED_TurnOffAllLeds();

	switch (  gLedCount )
	{
	case  0 ://RED
		LED_TurnOnLed(LED2);
		break;
	case  1  ://green
		LED_TurnOnLed(LED3);
		break;
	case  2 ://blue
		LED_TurnOnLed(LED4);
		break;
	case  3 ://white
		LED_TurnOnAllLeds();
		break;
	}
}

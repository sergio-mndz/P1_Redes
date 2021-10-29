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
static ledStatus_t ledsState = RED;

/* This is the function called by the Timer each time it expires */
static void taskTimerCallback(void *param)
{
	OSA_EventSet(timerEvents, gTimerTaskEvent2_c);
}

void timer_Task(osaTaskParam_t argument)
{
	osaEventFlags_t customEvent;
	myTimerID = TMR_AllocateTimer();
	while(1)
	{
		OSA_EventWait(mMyEvents, osaEventFlagsAll_c, FALSE, osaWaitForever_c,
				&customEvent);
		if( !gUseRtos_c && !customEvent)
		{
			break;
		}
		/* Depending on the received event */
		switch(customEvent){
		case gTimerTaskEvent1_c:
			TurnOffLeds(); /* Ensure all LEDs are turned off */
			break;
		case gTimerTaskEvent2_c: /* Event called from myTaskTimerCallback */
			if(!ledsState) {
				TurnOnLeds();
				ledsState = 1;
			}
			else {
				TurnOffLeds();
				ledsState = 0;
			}
			break;
		case gTimerTaskEvent3_c: /* Event to stop the timer */
			ledsState = 0;
			TurnOffLeds();
			TMR_StopTimer(myTimerID);
			break;
		default:
			break;
		}
	}
}

/* Function to init the task */
void timerTask_Init(void)
{
	timerEvents = OSA_EventCreate(TRUE);
	/* The instance of the MAC is passed at task creaton */
	gMyTaskHandler_ID = OSA_TaskCreate(OSA_TASK(timer_Task), NULL);
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

/* Public function to send an event to stop the timer */
void timer3s_Stop(void)
{
	OSA_EventSet(mMyEvents, gTimerTaskEvent3_c);
}




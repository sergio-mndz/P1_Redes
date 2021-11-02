/*
 * Timers.h
 *
 *  Created on: 28 oct 2021
 *      Author: sergio_mndz
 */

#ifndef TIMERS_H_
#define TIMERS_H_

/* Fwk */
#include "TimersManager.h"
#include "FunctionLib.h"
#include "LED.h"
/* KSDK */
#include "fsl_common.h"
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"
#include "Keyboard.h"

/* Define the available Task's Events */
#define gTimerTaskEvent1_c (1 << 0)
#define gTimerTaskEvent2_c (1 << 1)
#define gTimerTaskEvent3_c (1 << 2)
#define gTimerTaskEvent4_c (1 << 3)

#define gTimerTaskPriority_c 3
#define gTimerTaskStackSize_c 400

typedef enum {
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	WHITE = 3
}ledStatus_t;

void timer3s_Start(void);

void resetTimer(void);

void timer3s_Stop(void);

void timerTask_Init(void);

void increment_LedCount(void);

void set_LedCount(uint8_t newCount);

uint8_t get_LedCount( void );

void set_LedState();

void reset_LedCount();

#endif /* TIMERS_H_ */

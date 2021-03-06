#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
#include "libgpio.h"
#include "motor.h"

int		initialized = 0;

unsigned	LIMIT_PIN = 7;
unsigned	STEP_PIN = 8;
unsigned	DIR_PIN = 9;
struct timespec	lastpulse;
unsigned	PULSE_MIN_INTERVAL = 20000;

gpio_handle_t	HANDLE = 0;

void		step_motor(void);
void		initialize(void);

void 
initialize()
{
	if (!initialized) {
        lastpulse.tv_sec = 0;
        lastpulse.tv_nsec = 0;
		HANDLE = gpio_open(0);
		if (HANDLE == GPIO_INVALID_HANDLE) {
			err(EXIT_FAILURE, "gpio_open failed");
		}
		gpio_pin_input(HANDLE, LIMIT_PIN);
		//Without a pulldow resistor on the circuit the pin
		// will flicker on and off randomly.
		gpio_pin_pulldown(HANDLE, LIMIT_PIN);
		gpio_pin_output(HANDLE, STEP_PIN);
		gpio_pin_output(HANDLE, LIMIT_PIN);
		lastpulse.tv_sec = 0;
		lastpulse.tv_nsec = 0;

		initialized = 1;
	}
}

int
timespec_subtract(struct timespec *result, 
		struct timespec *x, struct timespec *y)
{
	/* Perform the carry for the later subtraction by updating y. */
	if (x->tv_nsec < y->tv_nsec) {
		long	nsec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
		y->tv_nsec -= 1000000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_nsec - y->tv_nsec > 1000000000) {
		long		nsec = (x->tv_nsec - y->tv_nsec) / 100000000;
		y->tv_nsec += 100000000 * nsec;
		y->tv_sec -= nsec;
	}
	/*
	 * Compute the time remaining to wait. tv_usec is certainly positive.
	 */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_nsec = x->tv_nsec - y->tv_nsec;

	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}

int 
motor_up()
{
	initialize();
	if (gpio_pin_get(HANDLE, LIMIT_PIN) == GPIO_VALUE_LOW) {
		step_motor();
		return 0;
	}
	return 1;
}

int 
motor_down()
{
	initialize();
	step_motor();
	return 0;
}

/** Returns 1 if there has been a long enough delay between pulses.
 * Otherwise returns 0
 */
int
motor_canstep()
{
	struct timespec now;
	struct timespec diff;
	clock_gettime(CLOCK_MONOTONIC, &now);

    timespec_subtract(&diff, &now, &lastpulse);

	if (diff.tv_sec > 0 || diff.tv_nsec > PULSE_MIN_INTERVAL) {
        printf("difference: tv_sec: %ld tv_nsec: %ld\n", diff.tv_sec, diff.tv_nsec);
		return 1;
	}

	return 0;
}

void 
step_motor()
{
	if (motor_canstep()) {
		gpio_pin_set(HANDLE, STEP_PIN, GPIO_PIN_HIGH);
		gpio_pin_set(HANDLE, STEP_PIN, GPIO_PIN_LOW);
        clock_gettime(CLOCK_MONOTONIC, &lastpulse);
	}
}



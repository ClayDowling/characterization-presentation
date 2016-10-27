#include "../motor.h"
#include "mock_gpio.h"
#include "mock_time.h"
#include <check.h>

#define LIMIT_PIN 7
#define STEP_PIN 8
#define DIR_PIN 9

START_TEST(motordown_onFirstCall_willFlickerStepPin)
{
    struct timespec ticks[] = {
        {.tv_sec = 1, .tv_nsec = 0},
        {.tv_sec = 1, .tv_nsec = 20000}
    };
    struct pinvalue first;
    struct pinvalue second;

    clock_gettime_will_return(2, &ticks);
    motor_down();

    ck_assert_int_eq(gpio_pin_set_call_count(), 2);
    first = gpio_pin_set_called_with(0);
    second = gpio_pin_set_called_with(1);

    ck_assert_int_eq(first.pin, STEP_PIN);
    ck_assert_int_eq(first.value, GPIO_PIN_HIGH);

    ck_assert_int_eq(second.pin, STEP_PIN);
    ck_assert_int_eq(second.value, GPIO_PIN_LOW);

}
END_TEST

TCase *tcase_motor(void)
{
	TCase *tc;

	tc = tcase_create("motor");
    tcase_add_test(tc, motordown_onFirstCall_willFlickerStepPin);

	return tc;
}

Suite *suite_motor(void)
{
	Suite *s;

	s = suite_create("motor-suite");

	suite_add_tcase(s, tcase_motor());

	return s;
}

int main(int argc, char **argv)
{
	Suite *s;
	SRunner *runner;
	int number_fails;

	s = suite_motor();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	number_fails = srunner_ntests_failed(runner);
	srunner_free(runner);

	return number_fails;
}

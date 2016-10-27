#include "../motor.h"

#include <check.h>


START_TEST(stub_test)
{
    ck_assert_int_eq(0, 42);
}
END_TEST

TCase *tcase_motor(void)
{
	TCase *tc;

	tc = tcase_create("motor");
	tcase_add_test(tc, stub_test);

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

#include "check.h"

#include "../src/time_calculation.h"

START_TEST(test_get_hours_string_return_correct_string)
{
  ck_assert_str_eq("one", get_hours_string(1));
  ck_assert_str_eq("two", get_hours_string(2));
}
END_TEST

START_TEST(test_get_hours_string_is_12_hours_formated)
{
  ck_assert_str_eq("one", get_hours_string(13));
}
END_TEST

START_TEST(test_at_0_hours_it_twelve)
{
  ck_assert_str_eq("twelve", get_hours_string(0));
}
END_TEST

START_TEST(test_at_24_hours_it_twelve)
{
  ck_assert_str_eq("twelve", get_hours_string(24));
}
END_TEST

START_TEST(test_get_minutes_string_return_correct_term)
{
  ck_assert_str_eq("one", get_minutes_string(1));
  ck_assert_str_eq("two", get_minutes_string(2));
  ck_assert_str_eq("ten", get_minutes_string(10));
  ck_assert_str_eq("twenty", get_minutes_string(20));
}
END_TEST

START_TEST(test_get_minutes_string_return_correct_ten_term_and_unit_one_per_line)
{
  ck_assert_str_eq("twenty\ntwo", get_minutes_string(22));
  ck_assert_str_eq("thirty\nfour", get_minutes_string(34));
  ck_assert_str_eq("fourty\ntwo", get_minutes_string(42));
}
END_TEST

START_TEST(test_get_minutes_string_return_o_clock_on_minute_0)
{
  ck_assert_str_eq("o'clock", get_minutes_string(0));
}
END_TEST

Suite *time_calculation_suite(void)
{
  Suite *s = suite_create("Time calculation");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_get_hours_string_return_correct_string);
  tcase_add_test(tc_core, test_get_hours_string_is_12_hours_formated);
  tcase_add_test(tc_core, test_at_0_hours_it_twelve);
  tcase_add_test(tc_core, test_at_24_hours_it_twelve);
  tcase_add_test(tc_core, test_get_minutes_string_return_correct_term);
  tcase_add_test(tc_core, test_get_minutes_string_return_correct_ten_term_and_unit_one_per_line);
  tcase_add_test(tc_core, test_get_minutes_string_return_o_clock_on_minute_0);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s = time_calculation_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}

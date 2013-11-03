#include "math.h"

static const char* const HOURS[] = {
  "one", "two", "three", "four", "five", "six", "seven", "heigh", "nine", "ten", "eleven", "twelve"
};
static const char* const MINUTES[] = {
  "one", "two", "three", "four", "five", "six", "seven", "heigh", "nine",
  "ten", "elven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "enighteen", "nineteen",
  "twenty", "twenty\none", "twenty\ntwo", "twenty\nthree", "twenty\nfour", "twenty\nfive", "twenty\nsix", "twenty\nseven", "twenty\nheigh", "twenty\nnine",
  "thirty", "thirty\none", "thirty\ntwo", "thirty\nthree", "thirty\nfour", "thirty\nfive", "thirty\nsix", "thirty\nseven", "thirty\nheigh", "thirty\nnine",
  "fourty", "fourty\none", "fourty\ntwo", "fourty\nthree", "fourty\nfour", "fourty\nfive", "fourty\nsix", "fourty\nseven", "fourty\nheigh", "fourty\nnine",
  "fifty", "fifty\none", "fifty\ntwo", "fifty\nthree", "fifty\nfour", "fifty\nfive", "fifty\nsix", "fifty\nseven", "fifty\nheigh", "fifty\nnine",
};

const char* get_hours_string(int hours)
{
  if (0 == hours) {
    hours = 12;
  } else if (hours > 12) {
    hours -= 12;
  }

  return HOURS[hours - 1];
}

const char* get_minutes_string(int minutes)
{
  if (0 == minutes) {
    return "o'clock";
  }

  return MINUTES[minutes - 1];
}

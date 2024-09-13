#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../include/patro/patro.h"
#define MITIBUFFERSIZE 32

const char *PATRO_START_BS = "1975-01-01";
const char *PATRO_END_BS = "2100-12-30";

/// @brief 2100 - 1975 + 1
const int PATRO_YEAR_ARRAY_SIZE = 126;
const int PATRO_MITI_FIRST_YEAR = 1975;
const int PATRO_MITI_LAST_YEAR = 2100;

const char *PATRO_START_AD = "1918-04-13";
const char *PATRO_END_AD = "2044-04-12";
const int PATRO_DATE_FIRST_YEAR = 1918;
const int PATRO_DATE_LAST_YEAR = 2044;

const char *PATRO_weekDays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

const char *PATRO_months[] = {"Baishakh", "Jetha",   "Asar",  "Saun", "Bhadau", "Asoj",
                  "Kartik",   "Mangsir", "Pusha", "Magh", "Fagun",  "Chaita"};

const char PATRO_miti_table[][12] = {
/* 1975 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 1976 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 1977 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 1978 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1979 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 1980 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 1981 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 1982 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1983 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 1984 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 1985 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 1986 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1987 */ {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 1988 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 1989 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 1990 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1991 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
/* 1992 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 1993 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1994 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1995 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
/* 1996 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 1997 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1998 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 1999 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2000 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2001 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2002 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2003 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2004 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2005 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2006 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2007 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2008 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 29, 31},
/* 2009 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2010 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2011 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2012 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 2013 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2014 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2015 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2016 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 2017 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2018 */ {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2019 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2020 */ {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2021 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2022 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
/* 2023 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2024 */ {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2025 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2026 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2027 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2028 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2029 */ {31, 31, 32, 31, 32, 30, 30, 29, 30, 29, 30, 30},
/* 2030 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2031 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2032 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2033 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2034 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2035 */ {30, 32, 31, 32, 31, 31, 29, 30, 30, 29, 29, 31},
/* 2036 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2037 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2038 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2039 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 2040 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2041 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2042 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2043 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 2044 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2045 */ {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2046 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2047 */ {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2048 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2049 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
/* 2050 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2051 */ {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2052 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2053 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
/* 2054 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2055 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2056 */ {31, 31, 32, 31, 32, 30, 30, 29, 30, 29, 30, 30},
/* 2057 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2058 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2059 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2060 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2061 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2062 */ {30, 32, 31, 32, 31, 31, 29, 30, 29, 30, 29, 31},
/* 2063 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2064 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2065 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2066 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 29, 31},
/* 2067 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2068 */ {31, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2069 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2070 */ {31, 31, 31, 32, 31, 31, 29, 30, 30, 29, 30, 30},
/* 2071 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2072 */ {31, 32, 31, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2073 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 31},
/* 2074 */ {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2075 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2076 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
/* 2077 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2078 */ {31, 31, 31, 32, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2079 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 29, 30, 30},
/* 2080 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 29, 30, 30},
/* 2081 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 29, 31},
/* 2082 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2083 */ {31, 31, 32, 31, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2084 */ {31, 31, 32, 31, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2085 */ {31, 32, 31, 32, 30, 31, 30, 30, 29, 30, 30, 30},
/* 2086 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2087 */ {31, 31, 32, 31, 31, 31, 30, 30, 29, 30, 30, 30},
/* 2088 */ {30, 31, 32, 32, 30, 31, 30, 30, 29, 30, 30, 30},
/* 2089 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2090 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2091 */ {31, 31, 32, 31, 31, 31, 30, 30, 29, 30, 30, 30},
/* 2092 */ {30, 31, 32, 32, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2093 */ {30, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2094 */ {31, 31, 32, 31, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2095 */ {31, 31, 32, 31, 31, 31, 30, 29, 30, 30, 30, 30},
/* 2096 */ {30, 31, 32, 32, 31, 30, 30, 29, 30, 29, 30, 30},
/* 2097 */ {31, 32, 31, 32, 31, 30, 30, 30, 29, 30, 30, 30},
/* 2098 */ {31, 31, 32, 31, 31, 31, 29, 30, 29, 30, 29, 31},
/* 2099 */ {31, 31, 32, 31, 31, 31, 30, 29, 29, 30, 30, 30},
/* 2100 */ {31, 32, 31, 32, 30, 31, 30, 29, 30, 29, 30, 30}};


/**
 * @brief be careful to work with dates before 1970
 * parsing date before 1970 is unreliable.
 * We have to reset (hr, min, sec) of the `struct tm` after
 * parsing date (YYYY-MM-DD, etc.) from string buffer.
 */

/**
 * @brief `given_date_tm` is converted into BS and then stored in `struct miti
 * *miti`
 *
 * @param given_date_tm
 * @param miti
 */
void date_to_miti(struct tm *given_date_tm, struct miti *miti) {
  // First day of the calendar database in `struct tm`.
  struct tm start_ad_tm;
  char buffer[MITIBUFFERSIZE];
  strptime(PATRO_START_AD, "%Y-%m-%d", &start_ad_tm);

  // strftime(buffer, MITIBUFFERSIZE, "%Y-%m-%d-%u", given_date_tm);
  // printf("inside date_to_miti(): %s\n", buffer);
  /**
   * @brief Calculation of miti;
   * First, calculate the total # of days from a FIXED start date
   * to the given date.
   * Then, add the total days to a FIXED start miti to get
   * the final miti.
   */
  int remaining_days = diff_date(given_date_tm, &start_ad_tm);
  // printf("DIFF: ")

  /// @brief Initial miti year from month array
  int INIT_MITI_YEAR;
  // printf("total days: %d\n", remaining_days);

  strpmiti(PATRO_START_BS, miti);
  miti->wday = given_date_tm->tm_wday + 1;
  INIT_MITI_YEAR = miti->year;

  int month_length;
  while (remaining_days > 0) {
    if (miti->year - INIT_MITI_YEAR >= PATRO_YEAR_ARRAY_SIZE) {
      /**
       * @brief conversion date is out of range.
       * This program supports miti upto the year 2100 BS.
       * Set the miti as 0000-00-00-00 to indicate conversion failure.
       */
      miti->year = 0;
      miti->mon = 0;
      miti->day = 0;
      miti->wday = 0;
      remaining_days = 0;
      // printf("breaked");
      break;
    }
    // printf("total_days: %d\n", remaining_days);
    month_length = PATRO_miti_table[miti->year - INIT_MITI_YEAR][miti->mon - 1];
    if (remaining_days + miti->day <= month_length) {
      /**
       * @brief add remaining few days to at most fill (but not overfill)
       * current month
       *
       */
      miti->day += remaining_days;
      remaining_days = 0;
      // printf("REM: %d, partially: %d")
    } else {
      /**
       * @brief current month filled; go to first day of next month
       *
       */
      remaining_days -= (month_length - miti->day + 1);
      miti->day = 1;
      miti->mon++;
      if (miti->mon > 12) {
        miti->mon = 1;
        miti->year++;
      }
    }
  }
}

/**
 * @brief `miti` is converted into AD and then stored in `date`
 *
 * @param date date in AD
 * @param miti miti in BS
 */
void miti_to_date(struct tm *date, struct miti *miti) {
  char buffer[32];
  // strfmiti(buffer, 32, miti, 0);
  // printf("Miti: %s\n", buffer);
  int diff_year = miti->year - PATRO_MITI_FIRST_YEAR;
  int diff_month = miti->mon;
  int total_days = 0;
  // add all the days in the year since 1975 upto given miti year.
  for (int y = 0; y < diff_year; y++) {
    for (int m = 0; m < 12; m++) {
      total_days += PATRO_miti_table[y][m];
    }
  }
  // printf("total_days: %d\n", total_days);
  // add all the days of the PATRO_months of given year upto given month
  for (int m = 0; m < miti->mon - 1; m++) {
    total_days += PATRO_miti_table[miti->year - PATRO_MITI_FIRST_YEAR][m];
  }
  // finally, add days of the given miti
  total_days += miti->day - 1;
  // printf("total_days: %d\n", total_days);

  // struct tm *date = (struct tm *)malloc(sizeof(struct tm));
  strptime(PATRO_START_AD, "%Y-%m-%d", date);
  // printf("year: %d mon: %d day: %d\n", date->tm_year, date->tm_mon,
  // date->tm_mday);
  date->tm_mday += total_days;
  /**
   * @brief
   * IMPORTANT !!!
   * Zero out the hour, min, sec of date because
   * the date is prior 1970; otherwise garbage result
   */
  date->tm_hour = 0;
  date->tm_min = 0;
  date->tm_sec = 0;
  mktime(date);
  // printf("year: %d mon: %d day: %d\n", date->tm_year, date->tm_mon,
  // date->tm_mday);
  miti->wday = date->tm_wday + 1;
  // strfmiti(buffer, 32, miti, 0);
  // printf("Miti: %s\n", buffer);
}

/**
 * @brief Returns 1 if given year is a leap year (366 days) else 0.
 *
 * @param year
 * @return int
 */
int is_leap_year(int year) {
  return year % 100 == 0 && year % 400 == 0 || year % 100 != 0 && year % 4 == 0;
}

/**
 * @brief Returns the difference of two dates (struct tm *) in days.
 *
 * @param d1 struct tm *
 * @param d2 struct tm *
 * @return int
 */
int diff_date(struct tm *d1, struct tm *d2) {
  int swap = 0;

  if (d1->tm_year == d2->tm_year) {
    swap = d1->tm_yday - d2->tm_yday;
  } else
    swap = d1->tm_year - d2->tm_year;
  if (swap < 0) {
    struct tm *temp = d2;
    d2 = d1;
    d1 = temp;
  }
  /// Here d1 = latter date, d2 = earlier date

  int total_days = 0;
  // add all the days of the years in between d1 and d2
  for (int year = d2->tm_year + 1; year < d1->tm_year; year++) {
    total_days += 365;
    if (is_leap_year(year + 1900)) total_days++;
  }
  if (d1->tm_year == d2->tm_year) {
    total_days += d1->tm_yday - d2->tm_yday;
  } else {
    total_days += 364 - d2->tm_yday;
    if (is_leap_year(d2->tm_year + 1900)) total_days++;
    total_days += d1->tm_yday + 1;
  }
  return total_days;
}

/**
 * @brief Prints a console calendar with colored saturdays
 *
 * @param mitiYear
 * @param mitiMonth
 * @param mitiDay
 * @param totalDays in a month
 * @param firstWeekDay
 */
void make_calendar(int mitiYear, int mitiMonth, int mitiDay, int totalDays,
                   int firstWeekDay) {
  char headline[20];

  // printf("first_weekday: %d\n", firstWeekDay);

  // print headline
  printf("           %d %s\n", mitiYear, PATRO_months[mitiMonth - 1]);
  printf("---------------------------------\n");
  // print weekdays
  // printf(" ");
  for (int i = 0; i < 7; i++) {
    if (i == 6) {
      printf("\033[1;31m");
    }
    printf("%s  ", PATRO_weekDays[i]);
    printf("\033[0m");
  }
  printf("\n");

  // print first week (partial)
  int currentDay = 1;
  // adding 35 (multiples of 7) is equivalent to itself (mod 7)
  // int firstWeekDay = ((todayWeekDay + 35) - (mitiDay - 1)) % 7;
  for (int i = 0; i < 7; i++) {
    if (i >= firstWeekDay) {
      if (i == 6) {
        // red foreground-color in saturday
        printf("\033[1;31m");
      }
      if (currentDay == mitiDay) {
        // yellow foreground in today
        printf("\033[1;4;33m");
      }
      if (currentDay < 10) {
        printf(" ");
      }
      printf("%d", currentDay++);
      printf("\033[0m");
      printf("   ");
    } else {
      printf("     ");
    }
  }
  printf("\n");
  // write remaining weeks
  for (int w = 1; w <= 5; w++) {
    for (int i = 0; i < 7; i++) {
      if (currentDay > totalDays) {
        if (i > 0) {
          printf("\n");
        }
        return;
      }
      if (i == 6) {
        // red foreground color in saturday
        printf("\033[1;31m");
      }
      if (currentDay == mitiDay) {
        // yellow foreground in today
        printf("\033[1;4;33m");
      }
      if (currentDay < 10) {
        printf(" ");
      }
      printf("%d", currentDay++);
      printf("\033[0m");
      printf("   ");
    }
    printf("\n");
  }
}

/**
 * @brief Parse given miti string and store in the given `struct miti *`.
 *
 * @param miti_str "2050-11-22" format
 * @param miti_tm
 */
void strpmiti(const char *miti_str, struct miti *miti_tm) {
  sscanf(miti_str, "%d-%d-%d", &miti_tm->year, &miti_tm->mon, &miti_tm->day);
}

/**
 * @brief Formats the given `struct miti *` to '%Y-%m-%d-%w'
 *
 * @param buffer
 * @param n
 * @param miti
 */
void strfmiti(char *buffer, size_t n, struct miti *miti, int enable_weekday) {
  int c = snprintf(buffer, n, "%d-%02d-%02d-%d", miti->year, miti->mon,
                   miti->day, miti->wday);
  if (enable_weekday == 0) {
    /**
     * @brief truncate the weekday from miti string.
     *
     */
    buffer[c - 2] = '\0';
  }
}

/**
 * @brief Returns 1 if given miti is valid.
 *
 * @param miti
 * @return int
 */
int test_miti_validity(struct miti *miti) {
  return miti->year >= PATRO_MITI_FIRST_YEAR &&
         miti->year <= PATRO_MITI_LAST_YEAR + miti->mon > 0 && miti->mon < 13 &&
         miti->day > 0 &&
         miti->day <= PATRO_miti_table[miti->year - PATRO_MITI_FIRST_YEAR][miti->mon - 1];
}

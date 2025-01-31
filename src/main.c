#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/patro/patro.h"
#define MITI_FIRST_YEAR ((PATRO_START_BS[0] - '0') * 1000 + (PATRO_START_BS[1] - '0') * 100 + (PATRO_START_BS[2] - '0') * 10 + (PATRO_START_BS[3] - '0'))
#define PATRO_MITI_LAST_YEAR MITI_FIRST_YEAR + PATRO_YEAR_ARRAY_SIZE - 1
#define MITIBUFFERSIZE 32

int main(int argc, char *argv[]) {
  time_t T = time(NULL);
  struct tm current_date;
  struct tm *date;
  char buffer[MITIBUFFERSIZE];
  int yr, mon, day;
  int is_valid_date = 1;
  // strptime("2010-10-23", "%Y-%m-%d", &current_date);

  // int status;
  // char *date_formats[] = {"%Y/%m/%d", "%Y-%m-%d","%Y.%m.%d"};

  struct miti *miti = (struct miti *)malloc(sizeof(struct miti));
  // printf("argc: %d\n", argc);
  // if(argc == 3) {
  //   printf("%s\n", argv[2]);
  // }
  // if (argc == 3 && strcmp(argv[2], "ad") == 0) {
  if (argc > 2 && strcmp(argv[1], "ad") == 0) {
    /**
     * @brief Taken command line argument as BS.
     *
     */
    sscanf(argv[2], "%d%*[^0-9]%d%*[^0-9]%d", &yr, &mon, &day);
    snprintf(buffer, MITIBUFFERSIZE, "%d-%d-%d", yr, mon, day);
    // printf("Buffer: %s\n", buffer);
    miti->year = yr;
    miti->mon = mon;
    miti->day = day;
    // char *ret = strptime(buffer, "%Y-%m-%d", &current_date);

    // status = test_miti_validity(miti);
    // printf("status = %d\n", status);
    if (test_miti_validity(miti) != 1) {
      fprintf(stderr, "Invalid or unsupported miti provided.\n");
      is_valid_date = 0;
    }
    // fprintf(stderr, "Invalid or unsupported")

    // if (ret == NULL) {
    //   printf("Error occured while parsing date\n");
    //   is_valid_date = 0;
    // }
    if (is_valid_date != 0) {
      date = (struct tm *)malloc(sizeof(struct tm));
      miti_to_date(date, miti);
      strftime(buffer, 32, "%Y-%m-%d", date);
      printf("AD: %s\n", buffer);
      free(date);
    }

  } else if (argc > 1 && strcmp(argv[1], "patro") == 0) {
    /**
     * @brief Show miti calendar for the given <year> <month>
     *
     */
    int current_day;
    if (argc == 4) {
      sscanf(argv[2], "%d", &miti->year);
      sscanf(argv[3], "%d", &miti->mon);
      miti->day = 1;
      current_day = 1;
    } else {
      T = time(NULL);
      localtime_r(&T, &current_date);
      // current_date = localtime_s(&T);
      // strftime(buffer, MITIBUFFERSIZE, "%Y-%m-%d-%u", &current_date);
      // printf("else date: %s\n", buffer);
      date_to_miti(&current_date, miti);
      // date = (struct tm *)malloc(sizeof(struct tm));
      current_day = miti->day;
      miti->day = 1;
      // printf("DEBUG: %d %d %d\n", miti->year, current_day, miti->wday);
      // printf(" ");
    }
    if (test_miti_validity(miti) == 1) {
      date = (struct tm *)malloc(sizeof(struct tm));
      // printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
      // strfmiti(buffer, MITIBUFFERSIZE, miti, 1);
      // printf("miti: %s\n", buffer);
      // strftime(buffer, MITIBUFFERSIZE, "%Y-%m-%d-%u", date);
      // printf("date: %s\n", buffer);
      // printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
      miti_to_date(date, miti);
      // strftime(buffer, 32, "%Y-%m-%d", date);
      make_calendar(miti->year, miti->mon, current_day,
                    PATRO_miti_table[miti->year - MITI_FIRST_YEAR][miti->mon - 1],
                    date->tm_wday);
      free(date);
    }
  } else if (argc == 2) {
    printf("Help:\n");
    printf("$ miti - Show today's miti\n");
    printf("$ miti ad <miti> - Convert given miti to AD\n");
    printf("$ miti bs <date> - Convert given date to BS\n");
    printf(
        "$ miti patro <year> <month> - Show Nepali calendar for given "
        "year/month\n");
  } else {
    if (argc == 1) {
      /**
       * @brief No cmd arguments; return today's miti
       *
       */
      T = time(NULL);
      current_date = *localtime(&T);
      // strptime("1996-09-28", "%Y-%m-%d", &current_date);
    } else if (argc > 2 && strcmp(argv[1], "bs") == 0) {
      /**
       * @brief Taken AD date from command line argument.
       * Accept dates with different types of separators
       * discard the separators with; %*[character class].
       * Any non-numeric character can be a separator.
       */
      sscanf(argv[2], "%d%*[^0-9]%d%*[^0-9]%d", &yr, &mon, &day);
      snprintf(buffer, MITIBUFFERSIZE, "%d-%d-%d", yr, mon, day);
      // printf("Buffer: %s\n", buffer);
      char *ret = strptime(buffer, "%Y-%m-%d", &current_date);
      if (ret == NULL) {
        printf("Error occured while parsing date\n");
        is_valid_date = 0;
      }
    }
    /**
     * @brief Conversion of AD to BS.
     *
     */
    if (is_valid_date != 0) {
      date_to_miti(&current_date, miti);
      strfmiti(buffer, MITIBUFFERSIZE, miti, 0);
      if (miti->year == 0) {
        fprintf(stderr, "Miti Out of Range. Cant be greater than %d BS.\n", PATRO_MITI_LAST_YEAR);
      } else {
        printf("BS: %d %s %d\n", miti->year, PATRO_months[miti->mon - 1], miti->day);
      }
    }
  }
  // struct tm *date = miti_to_date()
  // struct miti miti;
  // strpmiti("2053-06-12", &miti);
  // current_date = miti_to_date(&miti);
  // strfmiti(buffer, 32, miti);
  // printf("Date: %s\n", buffer);
  // printf("%d-%d-%d-%d\n", miti->year, miti->mon, miti->day, miti->wday);
  free(miti);
  return 0;
}
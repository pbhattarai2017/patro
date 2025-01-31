#ifndef LIBPATRO_H_
#define LIBPATRO_H_
                        
extern const char *PATRO_START_BS;

extern const int PATRO_YEAR_ARRAY_SIZE;

extern const char *PATRO_START_AD;

extern const char *PATRO_weekDays[];

extern const char *PATRO_months[];

extern const char PATRO_miti_table[][12];

/**
 * @brief be careful to work with dates before 1970
 * parsing date before 1970 is unreliable.
 * We have to reset (hr, min, sec) of the `struct tm` after
 * parsing date (YYYY-MM-DD, etc.) from string buffer.
 */

/**
 * @brief struct for miti; year[2000-2100],
 * day[1-32], month[1-12], weekday[1-7]
 *
 */
struct miti {
  int year;
  int mon;
  int day;
  int wday;
};

/**
 * @brief `given_date_tm` is converted into BS and then stored in `struct miti
 * *miti`
 *
 * @param given_date_tm
 * @param miti
 */
extern void date_to_miti(struct tm *given_date_tm, struct miti *miti);

/**
 * @brief `miti` is converted into AD and then stored in `date`
 *
 * @param date date in AD
 * @param miti miti in BS
 */
extern void miti_to_date(struct tm *date, struct miti *miti);

/**
 * @brief Returns 1 if given year is a leap year (366 days) else 0.
 *
 * @param year
 * @return int 
 */
extern int is_leap_year(int year);

/**
 * @brief Returns the difference of two dates (struct tm *) in days.
 *
 * @param d1 struct tm *
 * @param d2 struct tm *
 * @return int
 */
extern int diff_date(struct tm *d1, struct tm *d2);

/**
 * @brief Prints a console calendar with colored saturdays
 *
 * @param mitiYear
 * @param mitiMonth
 * @param mitiDay
 * @param totalDays in a month
 * @param firstWeekDay
 */
extern void make_calendar(int mitiYear, int mitiMonth, int mitiDay, int totalDays,
                   int firstWeekDay);

/**
 * @brief Parse given miti string and store in the given `struct miti *`.
 *
 * @param miti_str "2050-11-22" format
 * @param miti_tm
 */
extern void strpmiti(const char *miti_str, struct miti *miti_tm);

/**
 * @brief Formats the given `struct miti *` to '%Y-%m-%d-%w'
 *
 * @param buffer
 * @param n
 * @param miti
 */
extern void strfmiti(char *buffer, size_t n, struct miti *miti, int enable_weekday);

/**
 * @brief Returns 1 if given miti is valid.
 *
 * @param miti
 * @return int
 */
extern int test_miti_validity(struct miti *miti);
#endif
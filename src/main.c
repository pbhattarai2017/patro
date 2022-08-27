#include <stdio.h>
#include "../include/miti.h"

int main() {
  int year = 2079;
  for(int i = 0; i < 12; i ++) {
    printf("Month: %d days: %d\n", i + 1, miti_table[year - miti_start_year][i]);
  }
}
#include "test_core.h"

int main(void) {
  srand(time(NULL));
  Suite *list[] = {st_arithmetic(), st_comparison() /*, st_converters()*/,
                   st_rounding(), NULL};
  for (Suite **current_testcase = list; *current_testcase != NULL;
       current_testcase++) {
    SRunner *sr = srunner_create(*current_testcase);

    srunner_run_all(sr, CK_NORMAL);  // CK_VERBOSE - ALL | CK_ENV - ONLY FAILS
    srunner_free(sr);
  }

  return 0;
}

long long int getRandomLLD() { return rand() * rand() * rand(); }
double getRandomDouble() {
  double a = -98317124098.824;
  double b = 98110124982.483;

  return a + (rand() / (RAND_MAX / (a - b)));
}

#include "minunit.h"
#include "../include/fjk.h"

int tests_run = 0;

static char * test_tiny_encrypt() {
    mu_assert("error, encryption of '123456' is not equal to '531642'",
                strncmp(fjk_encrypt("123456", 6), "531642", 6) == 0);

    mu_assert("error, encryption of '1234567' is not equal to '7531642'",
                strncmp(fjk_encrypt("1234567", 7), "7531642", 7) == 0);

    mu_assert("error, encryption of '12345678' is not equal to '87531642'",
                strncmp(fjk_encrypt("12345678", 8), "87531642", 8) == 0);

    mu_assert("error, encryption of '123456789' is not equal to '741852963'",
                strncmp(fjk_encrypt("123456789", 9), "741852963", 9) == 0);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_tiny_encrypt);
    return 0;
}

int main(void) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}

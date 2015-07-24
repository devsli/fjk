#include "minunit.h"
#include "../include/fjk.h"

int tests_run = 0;

MU_TEST(encrypt_6) { mu_assert(strncmp(fjk_encrypt("123456", 6), "531642", 6) == 0, "encryption of '123456' is not equal to '531642'"); }
MU_TEST(encrypt_7) { mu_assert(strncmp(fjk_encrypt("1234567", 7), "7531642", 7) == 0, "encryption of '1234567' is not equal to '7531642'"); }
MU_TEST(encrypt_8) { mu_assert(strncmp(fjk_encrypt("12345678", 8), "87531642", 8) == 0, "encryption of '12345678' is not equal to '87531642'"); }
MU_TEST(encrypt_9) { mu_assert(strncmp(fjk_encrypt("123456789", 9), "741852963", 9) == 0, "encryption of '123456789' is not equal to '741852963'"); }

MU_TEST(decrypt_6) { mu_assert(strncmp(fjk_decrypt("531642", 6), "123456", 6) == 0, "decryption of '531642' is not equal to '123456'"); }
MU_TEST(decrypt_7) { mu_assert(strncmp(fjk_decrypt("7531642", 7), "1234567", 7) == 0, "decryption of '7531642' is not equal to '1234567'"); }
MU_TEST(decrypt_8) { mu_assert(strncmp(fjk_decrypt("87531642", 8), "12345678", 8) == 0, "decryption of '87531642' is not equal to '12345678'"); }
MU_TEST(decrypt_9) { mu_assert(strncmp(fjk_decrypt("741852963", 9), "123456789", 9) == 0, "decryption of '741852963' is not equal to '123456789'"); }



MU_TEST_SUITE(encryption_suite) {
    MU_RUN_TEST(encrypt_6);
    MU_RUN_TEST(encrypt_7);
    MU_RUN_TEST(encrypt_8);
    MU_RUN_TEST(encrypt_9);
}

MU_TEST_SUITE(decryption_suite) {
    MU_RUN_TEST(decrypt_6);
    MU_RUN_TEST(decrypt_7);
    MU_RUN_TEST(decrypt_8);
    MU_RUN_TEST(decrypt_9);
}

int main(void) {
	MU_RUN_SUITE(encryption_suite);
    MU_RUN_SUITE(decryption_suite);
	MU_REPORT();
	return 0;
}

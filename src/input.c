#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <slre.h>

/**
 * Description: Checks if str is a valid email
 * Note: this regexpr does not comply with RFC 822
 * Params:
 * const char* str - String to test
 * int str_len - Length of string
 * Returns: 1 if valid otherwise 0
 */
int is_email_address(const char* str, size_t str_len)
{
    return slre_match("(\\S)+@(\\S)+\\.(\\S)+", str, str_len, 0, 0, 0) == str_len;
}

/**
 * Description: Checks if string is a valid UK phone number
 * Note: This validation function is the simplest and doesn't require regex
 * Params:
 * const char* str - String to test
 * size_t str_len - Length of the string
 * Returns: 1 if valid otherwise 0
 */
int is_phone_number(const char* str, size_t str_len)
{
    return slre_match("0\\d\\d\\d\\d\\d\\d\\d\\d\\d\\d", str, str_len, 0, 0, 0) == str_len;
}

int is_postcode(const char* str, size_t str_len)
{
    return 0;
}


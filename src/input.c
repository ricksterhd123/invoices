#pragma once
#include <stdlib.h>
#include <slre.h>

/**
 * Description: Checks if str is a valid email
 * Note: this regexpr does not comply with RFC 822
 * Params:
 * const char* str - String to test
 * int str_len - Length of string
 * Returns: 1 if valid otherwise 0
 */
int is_email_address(const char* str, int str_len)
{
    return slre_match("(\\S)+@(\\S)+\\.(\\S)+", str, str_len, 0, 0, 0) == str_len;
}

/**
 * Description: Checks if string is a valid UK phone number
 * Params:
 * const char* str - String to test
 * int str_len - Length of the string
 * Returns: 1 if valid otherwise 0
 */
int is_phone_number(const char* str, int str_len)
{
    return slre_match("0\\d\\d\\d\\d\\d\\d\\d\\d\\d\\d", str, str_len, 0, 0, 0) == str_len;
}

// ^[A-Z]{1,2}[0-9][A-Z0-9]? ?[0-9][A-Z]{2}$ 
int is_postcode(const char* str, size_t str_len)
{
    return 0;
}


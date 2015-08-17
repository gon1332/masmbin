#include "convert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/* int convert_hex_bin_oct_to_dec (const char *input)
 *
 * Given a hexadecimal, binary, or octal number in string, returns it in its
 * decimal representation and as a type of integer.
 *
 * It does not handle the minus sign. It should and it will in a future update.
 *
 * In terms of security, it does not check if the digits are valid for the given
 * representation. This function is made to support the parsing so it takes for
 * granted the validity of the data the lexer passes for computation.
 */
int convert_hex_bin_oct_to_dec(const char *input)
{
	int result = 0;
	int power = 0;
	int i = 0;

	if (NULL == input) {
		fprintf(stderr, "masmbin: convert_hex_bin_oct_to_dec: error: NULL input.\n");
		exit(EXIT_FAILURE);
	}

	if ('0' == input[0]) {
		if ('B' == input[1] || 'b' == input[1]) {
			for (i = 2, power = strlen(input)-2-1; power >= 0 && input[i] != '\0'; power--, i++)
				if ('1' == input[i])
					result += pow((double) BIN_base, (double) power);
		}
		else if ('X' == input[1] || 'x' == input[1]) {
			for (i = 2, power = strlen(input)-2-1; power >= 0 && input[i] != '\0'; power--, i++) {
				if (ASCII_is_in_a_f(input[i]))
					result += (10 + input[i] - ASCII_a) * pow((double) HEX_base, (double) power);
				else if (ASCII_is_in_A_F(input[i]))
					result += (10 + input[i] - ASCII_A) * pow((double) HEX_base, (double) power);
				else if (ASCII_is_in_0_9(input[i]))
					result += (input[i] - ASCII_0) * pow((double) HEX_base, (double) power);
				else {
					fprintf(stderr, "masmbin: convert_hex_bin_oct_to_dec: \
								error: Not a hex digit.\n");
					exit(EXIT_FAILURE);
				}
			}
		} else if ('O' == input[1] || 'o' == input[1]) {
			for (i = 2, power = strlen(input)-2-1; power >= 0 && input[i] != '\0'; power--, i++)
				result += (input[i] - ASCII_0) * pow((double) OCT_base, (double) power);
		}
	} else {
		result = atoi(input);
	}
	return result;
}


char *baseconv(unsigned int num, int base)
{
	static char retbuf[33];
	char *p;

	if (base < 2 || base > 16)
		return NULL;

	p = &retbuf[sizeof(retbuf)-1];
	*p = '\0';

	do {
		*--p = "0123456789abcdef"[num % base];
		num /= base;
	} while (num != 0);

    // Sign-extent positive base-2 numbers
    if (base == 2 && p != retbuf) {
        do {
            *--p = '0';
        } while (p != retbuf);
    }

	return p;
}

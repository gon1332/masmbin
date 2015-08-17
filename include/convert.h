#ifndef CONVERT_H_ZKIX5RGT
#define CONVERT_H_ZKIX5RGT

#define ASCII_a	97
#define ASCII_A	65
#define ASCII_0	48

#define ASCII_is_in_0_9(a)	(((a) >= ASCII_0) && ((a) <= (ASCII_0 + 9)))
#define ASCII_is_in_A_F(a)	(((a) >= ASCII_A) && ((a) <= (ASCII_A + 5)))
#define ASCII_is_in_a_f(a)	(((a) >= ASCII_a) && ((a) <= (ASCII_a + 5)))

#define HEX_base	16
#define BIN_base	2
#define OCT_base	8

extern
int convert_hex_bin_oct_to_dec(const char *input);

extern
char *baseconv(unsigned int num, int base);

#endif /* CONVERT_H_ZKIX5RGT */


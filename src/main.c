#include <stdio.h>
#include <stdlib.h>

void yyparse(void);

int main(int argc, char *argv[])
{
    /* Check for argument validity.
     * */
    if (argc != 3) {
        printf("Usage: masmbin <in_file> <out_file>\n");
        exit(EXIT_FAILURE);
    }

    /* Open 1st argument for read.
     * */
    extern FILE *yyin;
    if (NULL == (yyin = fopen(argv[1], "r"))) {
        perror("masmbin: error");
        exit(EXIT_FAILURE);
    }

    /* Open 2nd argument for write.
     * */
    FILE *fout;
    if (NULL == (fout = fopen(argv[2], "w"))) {
        perror("masmbin: error");
        exit(EXIT_FAILURE);
    }

    /* Parse the input file.
     * */
    yyparse();

    return EXIT_SUCCESS;
}

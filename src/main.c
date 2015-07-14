#include <stdio.h>
#include <stdlib.h>

void yyparse(void);

int main(int argc, char *argv[])
{
    extern FILE *yyin;

    argv++, argc--;
    if (3 == argc) {
        if (NULL == (yyin = fopen(argv[0], "r"))) {
            perror("masmbin: error");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Usage: masmbin <in_file> <out_file>\n");
        exit(EXIT_FAILURE);
    }

    yyparse();

    return EXIT_SUCCESS;
}

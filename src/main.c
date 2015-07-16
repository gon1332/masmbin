#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "label_map.h"

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
    extern FILE *fout;
    if (NULL == (fout = fopen(argv[2], "w"))) {
        perror("masmbin: error");
        exit(EXIT_FAILURE);
    }

    /* Map MIPS assembly labels to addresses.
     * */
    extern map_t *lbl_map;
    lbl_map = map_init();
    if (!label_map(argv[1])) {
        printf("masmbin: label_map: Could not initialize label map.\n");
        map_free(lbl_map);
        exit(EXIT_FAILURE);
    }
    /* Result is in lbl_map */


    /* Parse the input file.
     * */
    yyparse();

    return EXIT_SUCCESS;
}

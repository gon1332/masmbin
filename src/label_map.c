#include "label_map.h"
#include "hash.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_empty(const char *s)
{
    while ( isspace(*s) && ++s );
    return !*s;
}


char *get_label(char *s)
{
    char *char_pos = strchr(s, ':');

    if (!char_pos) return NULL;

    *char_pos = '\0';

    // Check if ':' is in a comment
    while (char_pos-- != s) {
        if (*char_pos == '#') {
            return NULL;
        }
    }

    return s;
}


map_t *label_map(const char *input)
{
    FILE *fin;
    if (NULL == (fin = fopen(input, "r"))) {
        perror("masmbin: fopen");
        exit(EXIT_FAILURE);
    }


    size_t lbl_addr = 0;
    size_t line_no = 0;
    char line[80];
    while (fgets(line, 80, fin)) {
        if (ferror(fin)) {
            perror("masmbin: fgets");
            exit(EXIT_FAILURE);
        }

        if (feof(fin)) {
            break;
        }
         line_no++;

        /* ditch newline at end, if it exists */
        int len = strlen(line);
        if (line[len-1] == '\n') line[len-1] = '\0';

        if (is_empty(line)) continue;   // Omit blank lines.
#ifdef NDEBUG
        printf(">: %s\n", line);
#endif

        lbl_addr++; // Increment with every new line.

        // Find the position of the first ':'
        char *label = get_label(line);
        if (!label) continue;    // Omit labelless lines.

        lbl_addr--; // Decrement with every label met.

        // Check for duplicate or original labels.
        if (-1 == map_lookup(lbl_map, label)) {
            map_insert_pair(lbl_map, label, lbl_addr);
        } else {
            printf("@%zd: %s\n", line_no, "Double label definition."); 
            return NULL;
        }

#ifdef NDEBUG
        printf("%zd: %s\n", lbl_addr, label);
#endif
    }
    return lbl_map;
}

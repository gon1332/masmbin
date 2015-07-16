#ifndef HASH_H_0QBW1PDI
#define HASH_H_0QBW1PDI
#include <stdbool.h>

#define MERSENNE_PRIME(x)   ((2<<(x)) - 1)   // Mersenne prime
#define MAP_SIZE            (MERSENNE_PRIME(8)) // 255

typedef struct pair {
    char *string;
    int   value;

    struct pair *next;
} pair;

extern pair         *map_init       (void);
extern void          map_insert_pair(pair *map, const char *string, int val);
extern int           map_lookup     (pair *map, const char *string);
extern void          map_free       (pair *map);

#endif /* HASH_H_0QBW1PDI */

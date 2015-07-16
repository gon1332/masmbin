#include "hash.h"
#include "strdup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//==============  STATIC FUNCTIONS DEFINITIONS  ===============================
//
static pair         *_construct_pair(const char *str, int val);
static unsigned int  _hash          (const char *str);
static void          _map_free      (pair *current);


//==============  EXTERNAL FUNCTIONS DEFINITIONS  =============================

pair *map_init(void)
{
    pair *map = malloc(MAP_SIZE * sizeof(pair));
    if (!map) {
        perror("masmbin: malloc");
        exit(EXIT_FAILURE);
    }
    for (unsigned i = 0; i < MAP_SIZE; i++)
        map[i].next = NULL;

    return map;
}


void map_insert_pair(pair *map, const char *string, int val)
{
    pair *new_pair = _construct_pair(string, val);
    unsigned key = _hash(string);
    new_pair->next = map[key].next;
    map[key].next = new_pair;
}


int map_lookup(pair *map, const char *string)
{
    unsigned key = _hash(string);
    for (pair *curr = map[key].next; curr; curr = curr->next)
        if (!strcmp(curr->string, string))
            return curr->value;
    return -1;
}


void map_free(pair *map)
{
    // run through the array
    for (unsigned i = 0; i < MAP_SIZE; i++)
        // free each list has element
        if (map[i].next != NULL)
            _map_free(map[i].next);
}


//==============  STATIC FUNCTIONS DEFINITIONS  ===============================

pair *_construct_pair(const char *str, int val)
{
    pair *new_node = malloc(sizeof(pair));

    new_node->string = strdup(str);
    new_node->value  = val;
    return new_node;
}


unsigned int _hash(const char *str)
{
    unsigned long hash = MERSENNE_PRIME(13);
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % MAP_SIZE;
}


void _map_free(pair *current)
{
    // recursive call of _free_map
    if (current->next != NULL)
        _map_free(current->next);

    // free the current node
    free(current->string);
    current->string = NULL;
    free(current);
    current = NULL;
}

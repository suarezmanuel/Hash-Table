//
// Created by Manuel on 10/10/2023.
//

#ifndef HASHTABLE_HASH_TABLE_H
#define HASHTABLE_HASH_TABLE_H

#include "hash_item.h"

typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

//
// Created by Manuel on 10/10/2023.
//

#include "hash_table.h"
#include <iostream>

static int HT_PRIME1 = 53;
static int HT_PRIME2 = 59;
static const int HT_MIN_TABLE_SIZE = 0;

ht_hash_table* ht_new_hash_table ();
void ht_del_hash_table (ht_hash_table* table);

static int ht_hash (const char* s, int a, int m);
static int ht_get_hash (const char* s, int num_buckets, int attempt);

int ht_find_index (ht_hash_table* ht, const char* key);
char* ht_find_value (ht_hash_table* ht, const char* key);
void ht_insert (ht_hash_table* ht, const char* key, const char* value);
void ht_delete (ht_hash_table* ht, const char* key);

static void ht_resize (ht_hash_table*& ht, int new_size);
static void resize_up (ht_hash_table*& ht);
static void resize_down (ht_hash_table*& ht);

#endif //HASHTABLE_HASH_TABLE_H

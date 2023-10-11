//
// Created by Manuel on 10/10/2023.
//

#include "../headers/hash_table.h"
#include "../headers/prime.h"
#include <iostream>

// creates a new hash table, instantiates its pointers. The default size of table is `HT_MIN_TABLE_SIZE`
static ht_hash_table* ht_new_table (const int size = HT_MIN_TABLE_SIZE) {
    ht_hash_table* table = (ht_hash_table*) malloc(sizeof(ht_hash_table));
    if (table == nullptr) {
        exit(1);
    }
    table->size = size;
    table->count = 0;
    table->items = (ht_item**) calloc(table->size, sizeof(ht_item*));
    if (table->items == nullptr) {
        exit(1);
    }
    return table;
}

// deletes the hash table
void ht_del_hash_table (ht_hash_table* table) {
    for (int i = 0; i < table->count; ++i) {
        ht_del_item((table->items)[i]);
    }
    free(table->items);
    free(table);
}

// our beloved hash function, takes a string (the item's key),
// a prime bigger than the table's size, and the size of the table.
static int ht_hash (const char* s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; ++i) {
        hash += (long) pow(a, len_s - (i+1)) * s[i];
        hash %= m;
    }
    return (int) hash;
}

// attempts to give us a working bucket index for new item, uses double hashing.
static int ht_get_hash (const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME2, num_buckets);
    return (hash_a + attempt * (hash_b + 1)) % num_buckets;
}

// tries all possibilities of finding a bucket index for an ew item.
// won't loop endlessly (i hope), as the resize happens when adding an element at insertion.
int ht_find_index (ht_hash_table* ht, const char* key) {
    int attempt = 0, index;
    ht_item* curr;

    do {
        index = ht_get_hash(key, ht->size, attempt);
        curr = (ht->items)[index];
        if (curr != nullptr && strcmp(curr->key, key) == 0) {
            return index;
        }
        attempt++;
    } while (curr != &HT_DELETED_ITEM && curr != nullptr);

    return index;
}

// finds value of item given it's key, returns nullptr if not found.
char* ht_find_value (ht_hash_table* ht, const char* key) {
    int index = ht_find_index(ht, key);
    if ((ht->items)[index] != &HT_DELETED_ITEM && (ht->items)[index] == nullptr) {
        return nullptr;
    }
    return (ht->items)[index]->value;
}

// deletes item given it's key, does nothing if not found.
void ht_delete (ht_hash_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    // the load will in fact get bigger in the recursive call.
    if (load < 0.1) {
        resize_down(ht);
    }
    int index = ht_find_index(ht, key);
    if ((ht->items)[index] == nullptr) {
        return;
    }
    (ht->items)[index] = &HT_DELETED_ITEM;
    ht->count--;
}

// adds item to table, expands if pretty full, replaces if same item found.
void ht_insert (ht_hash_table* ht, ht_item* item) {
    const int load = ht->count * 100 / ht->size;
    // resize_up uses ht_insert, this recursion doesn't bother us as it won't loop indefinitely,
    // the load will in fact get smaller in the recursive call.
    if (load > 0.7) {
        resize_up(ht);
    }

    int attempt = 0, index;
    ht_item* curr;

    do {
        index = ht_get_hash(item->key, ht->size, attempt);
        curr = (ht->items)[index];
        // if same item found, replace it.
        if (curr != nullptr && !strcmp(curr->key, item->key)) {
            ht_del_item(curr);
            (ht->items)[index] = item;
            return;
        }
        attempt++;
    } while (curr != &HT_DELETED_ITEM && curr != nullptr);

    (ht->items)[index] = item;
    ht->count++;
}

// resizes table, either expands or shrinks (based on new_size).
static void ht_resize (ht_hash_table*& ht, const int new_size) {
    // can't resize to less than the minimum.
    if (new_size < HT_MIN_TABLE_SIZE) {
        return;
    }
    ht_hash_table* new_table = ht_new_table(new_size);

    // loop through original table, adding its items to new table.
    for (int i = 0; i < ht->size; ++i) {
        ht_item* curr = (ht->items)[i];
        if (curr != nullptr && curr != &HT_DELETED_ITEM) {
            ht_insert (new_table, curr->key, curr->value);
        }
    }

    // change original pointer to table to point to new table.
    new_table -> count = ht -> count;
    ht_hash_table* temp = ht;
    ht = new_table;

    // delete original table.
    ht_del_hash_table(temp);
}


static void resize_up (ht_hash_table*& ht) {
    const int new_size = ht->size * 2;
    ht_resize(ht, new_size);

    // update primes used in hashing funcs
    HT_PRIME1 = next_prime(ht->size);
    HT_PRIME2 = next_prime(HT_PRIME1);
}


static void resize_down (ht_hash_table*& ht) {
    const int new_size = ht->size / 2;
    ht_resize(ht, new_size);

    // update primes used in hashing funcs
    HT_PRIME1 = next_prime(ht->size);
    HT_PRIME2 = next_prime(HT_PRIME1);
}
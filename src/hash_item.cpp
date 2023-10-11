//
// Created by Manuel on 11/10/2023.
//

#include "../headers/hash_item.h"
#include <iostream>

static ht_item* ht_new_item (const char* k, const char* v) {
    ht_item* item = (ht_item*) malloc (sizeof(ht_item));
    item->key = strdup(k);
    item->value = strdup(v);
    return item;
}


static void ht_del_item (ht_item* i) {
    if (i == nullptr)
        return;
    free(i->key);
    free(i->value);
    free(i);
}
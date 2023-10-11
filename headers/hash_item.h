//
// Created by Manuel on 11/10/2023.
//

#ifndef HASHTABLE_HASH_ITEM_H
#define HASHTABLE_HASH_ITEM_H

typedef struct {
    char* key;
    char* value;
} ht_item;

static ht_item HT_DELETED_ITEM = {nullptr, nullptr};

static ht_item* ht_new_item (const char* k, const char* v);
static void ht_del_item (ht_item* i);

#endif //HASHTABLE_HASH_ITEM_H

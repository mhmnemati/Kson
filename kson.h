#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct Kson{
    char *key;
    char *value;
    struct Kson *next;
} Kson;
typedef struct Kson_Iterator{
    struct Kson *kson;
} Kson_Iterator;
typedef struct Kson_Array{
    char *value;
    struct Kson_Array *next;
} Kson_Array;

Kson *kson_new();

void kson_free(Kson *kson);

void kson_parse(char *kson_pack , struct Kson **kson);

void kson_pack(struct Kson *kson , char **kson_pack);

void kson_get(struct Kson *kson , const char *key,char **value);

void kson_put(struct Kson **kson , const char *key , const char *value);

void kson_remove(struct Kson **kson , const char *key);

Kson_Iterator* kson_iterator(struct Kson *kson);

char *kson_keys_iterate(struct Kson *kson, struct Kson_Iterator **kson_iterator);

Kson_Array *kson_array_new();

void kson_array_free(Kson_Array *kson_array);

void kson_array_parse(const char *kson_array_pack , struct Kson_Array **kson_array);

void kson_array_pack(struct Kson_Array *kson_array , char **kson_array_pack);

void kson_array_get(struct Kson_Array *kson_array , const int index , char **value);

void kson_array_add(struct Kson_Array **kson_array , const char *value);

void kson_array_set(struct Kson_Array *kson_array , const int index , const char *value);

void kson_array_remove(struct Kson_Array **kson_array , const int index);

int kson_array_length(struct Kson_Array *kson_array);
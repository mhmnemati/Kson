#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct Kson{
    char *key;
    char *value;
    struct Kson *next;
} Kson;

Kson *kson_new();

void kson_free(Kson *kson);

void kson_parse(char *kson_pack , struct Kson *kson);

void kson_pack(struct Kson *kson , char **kson_pack);

char *kson_get(struct Kson *kson , const char *key);

void kson_put(struct Kson **kson , const char *key , const char *value);

void kson_remove(struct Kson **kson , const char *key);

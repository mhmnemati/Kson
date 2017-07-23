# Kson
A simple c language json parser

this version only supports string value types

# Functions

```
Kson *kson_new(); 
        allocates new Kson struct

void kson_free(Kson *kson);
        frees Kson struct and its data

void kson_parse(char *kson_pack , struct Kson **kson);
        parses Json string into Kson struct

void kson_pack(struct Kson *kson , char **kson_pack);
        packs Kson struct into Json string
        
void kson_get(struct Kson *kson , const char *key,char **value);
        gets value by key

void kson_put(struct Kson **kson , const char *key , const char *value);
        puts key-value pair

void kson_remove(struct Kson **kson , const char *key);
        removes key-value pair

Kson_Iterator* kson_iterator(struct Kson *kson);
        return Kson keys iterator struct

char *kson_keys_iterate(struct Kson *kson, struct Kson_Iterator **kson_iterator);
        iterates kson keys

Kson_Array *kson_array_new();
        allocates new Kson Array struct

void kson_array_free(Kson_Array *kson_array);
        frees Kson Array struct and its data

void kson_array_parse(const char *kson_array_pack , struct Kson_Array **kson_array);
        parses Json Array string into Kson Array struct

void kson_array_pack(struct Kson_Array *kson_array , char **kson_array_pack);
        packs Kson Array struct into Json Array string

void kson_array_get(struct Kson_Array *kson_array , const int index , char **value);
        gets value by index number

void kson_array_add(struct Kson_Array **kson_array , const char *value);
        adds value at the start of Kson Array 

void kson_array_set(struct Kson_Array *kson_array , const int index , const char *value);
        sets value to the index if index is in Kson Array range

void kson_array_remove(struct Kson_Array **kson_array , const int index);
        removes value by index number
        
int kson_array_length(struct Kson_Array *kson_array);
        returns Kson Array length
```


# Example
```
#include <stdio.h>
#include <stdlib.h>
#include "kson.h"

int main() {

    char *json_text = R"({"Key_1":"Value_1","Key_2":"Value_2"})";

    Kson *kson = kson_new();

    kson_parse(json_text,kson);

    char *val = NULL;
    
    kson_get(kson,"Key_1",&val);
    
    printf("Key_1 = %s\n",val);

    char *json_string = NULL;

    kson_put(&kson,"Key_3","Value_3");

    kson_remove(&kson,"Key_2");

    kson_pack(kson,&json_string);

    printf("%s\n",json_string);
    
    kson_free(kson);

    return 0;
}
```

# Usage

for using this library only you need to add `kson.c` and `kson.h` files to your project



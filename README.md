# Kson
A simple c language json parser

this version only supports string value types

# Functions

```
Kson* kson_new();
        allocates heap memory for parsed json data
        
void kson_parse(Kson*);
        parse the json text and copy it's data to Kson
        
void kson_pack(Kson*,char**);
        pack the json data into json text
        
void kson_get(Kson*,char*,char**);
        find the key value if not found return NULL
        
void kson_put(Kson**,char*,char*);
        put the key value
        
void kson_remove(Kson**,char*);
        remove key
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



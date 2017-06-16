# Kson
A simple c language json parser

this version only supports string value types



# Example
```
#include <stdio.h>
#include <stdlib.h>
#include "kson.h"

int main() {

    char *json_text = R"({"Key_1":"Value_1","Key_2":"Value_2"})";

    Kson *kson = kson_new();

    kson_parse(json_text,kson);

    printf("Key_1 = %s\n",kson_get(kson,"Key_1"));

    char *json_string = NULL;

    kson_put(&kson,"Key_3","Value_3");

    kson_remove(&kson,"Key_2");

    kson_pack(kson,&json_string);

    printf("%s\n",json_string);

    return 0;
}
```

# Usage

for using this library only you need to add `kson.c` and `kson.h` files to your project



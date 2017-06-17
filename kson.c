#include "kson.h"

Kson *kson_new(){
    Kson *kson = malloc(sizeof(Kson));
    return kson;
}

void kson_free(Kson *kson){
    Kson *swap = NULL;
    do{
        swap = kson->next;
        free(kson->key);
        free(kson->value);
        free(kson);
        kson = swap;
    } while(kson->next != NULL);
}

void kson_string_parse(char **kson_string){
    int string_length = (int) strlen(*kson_string);
    int str_cursor = 0;
    char string[string_length];
    for(int cursor = 0 ; cursor < string_length ; cursor++){
        if(*(*kson_string+cursor) == '\\' && *(*kson_string+cursor+1) == '\"'){
            string[str_cursor] = '\"';
            cursor++;
        }else{
            string[str_cursor] = *(*kson_string+cursor);
        }
        str_cursor++;
    }
    string[str_cursor] = '\0';
    strcpy(*kson_string,string);
}

void kson_string_pack(char **kson_string){
    int string_length = (int) strlen(*kson_string)*2;
    int str_cursor = 0;
    char string[string_length];
    for(int cursor = 0 ; cursor < string_length ; cursor++){
        if(*(*kson_string+cursor) == '\"'){
            string[str_cursor] = '\\';
            str_cursor++;
            string[str_cursor] = '\"';
        }else{
            string[str_cursor] = *(*kson_string+cursor);
        }
        str_cursor++;
    }
    string[str_cursor] = '\0';
    strcpy(*kson_string,string);
}

void kson_parse(char *kson_pack , Kson *kson){
    Kson *next_kson = kson;
    char *key = malloc(sizeof(char)*strlen(kson_pack));
    char *value = malloc(sizeof(char)*strlen(kson_pack));
    int i_cursor = 0;
    int is_inner_key = 0; // -> 0 , 1 , 2 => 0 -> when not in block , 1 -> when getting key , 2 -> when in block but out of key
    int is_inner_value = 0; // -> 0 , 1 => 0 -> when not in value , 1 -> when in value
    for(int cursor = 0 ; cursor < strlen(kson_pack) ; cursor++){
        if(is_inner_key == 0){
            // wait until get key
            if(kson_pack[cursor] == '\"' && kson_pack[cursor-1] != '\\'){
                is_inner_key = 1;
            }
        }else if(is_inner_key == 1){
            if(kson_pack[cursor] == '\"' && kson_pack[cursor-1] != '\\'){
                is_inner_key = 2;
                *(key+i_cursor) = '\0';
                i_cursor = 0;
                // end of key
            }else{
                // in key
                *(key+i_cursor) = kson_pack[cursor];
                i_cursor++;
            }
        }else{
            if(is_inner_value == 0){
                if(kson_pack[cursor] == '\"' && kson_pack[cursor-1] != '\\'){
                    is_inner_value = 1;
                }
            }else{
                if(kson_pack[cursor] == '\"' && kson_pack[cursor-1] != '\\'){
                    *(value+i_cursor) = '\0';
                    is_inner_value = 0;
                    is_inner_key = 0;
                    i_cursor = 0;
                    // end of value
                    // add block
                    realloc(key,sizeof(char)*strlen(key));
                    realloc(value,sizeof(char)*strlen(value));
                    kson_string_parse(&key);
                    kson_string_parse(&value);
                    next_kson->key = key;
                    next_kson->value = value;
                    next_kson->next = malloc(sizeof(Kson));
                    next_kson = next_kson->next;
                    key = malloc(sizeof(char)*strlen(kson_pack));
                    value = malloc(sizeof(char)*strlen(kson_pack));
                }else{
                    // in value
                    *(value+i_cursor) = kson_pack[cursor];
                    i_cursor++;
                }
            }

        }
    }
}

void kson_pack(Kson *kson , char **kson_pack){
    *kson_pack = malloc(2048*sizeof(char));
    strcat(*kson_pack,"{");
    Kson *swap = NULL;
    do{
        kson_string_pack(&kson->key);
        kson_string_pack(&kson->value);
        swap = kson->next;
        strcat(*kson_pack,"\"");
        strcat(*kson_pack,kson->key);
        strcat(*kson_pack,"\":\"");
        strcat(*kson_pack,kson->value);
        strcat(*kson_pack,"\"");
        if(kson->next->next != NULL){
            strcat(*kson_pack,",");
        }
        kson = swap;
    } while(kson->next != NULL);
    strcat(*kson_pack,"}");
}

void kson_get(struct Kson *kson , const char *key,char **value){
    Kson *swap = NULL;
    do{
        swap = kson->next;
        if(strcmp(kson->key,key) == 0){
            (*value) = malloc(sizeof(char)*strlen(kson->value));
            strcpy(*value,kson->value);
            break;
        }
        kson = swap;
    } while(kson->next != NULL);
}

void kson_put(struct Kson **kson , const char *key , const char *value){
    Kson *first_kson = *kson;
    Kson *swap = NULL;
    int find = 0;
    do{
        swap = (*kson)->next;
        if(strcmp((*kson)->key,key) == 0){
            free((*kson)->value);
            (*kson)->value = malloc(sizeof(char)*strlen(value));
            strcpy((*kson)->value,value);
            find = 1;
            break;
        }
        *kson = swap;
    } while((*kson)->next != NULL);
    *kson = first_kson;
    if(find == 0){
        Kson *kson_item = malloc(sizeof(Kson));
        char *item_key = malloc(sizeof(char)*strlen(key));
        char *item_value = malloc(sizeof(char)*strlen(value));
        strcat(item_key,key);
        strcat(item_value,value);
        kson_item->key = item_key;
        kson_item->value = item_value;
        kson_item->next = *kson;
        *kson = kson_item;
    }
}

void kson_remove(struct Kson **kson , const char *key){
    Kson *swap = NULL;
    Kson *first_kson = *kson;
    Kson *before_kson = NULL;
    do{
        swap = (*kson)->next;
        if(strcmp((*kson)->key,key) == 0){
            if(before_kson != NULL){
                before_kson->next = swap;
                free((*kson)->key);
                free((*kson)->value);
                free((*kson));
            }else{
                first_kson = (*kson)->next;
                free((*kson)->key);
                free((*kson)->value);
                free((*kson));
            }
            break;
        }
        before_kson = (*kson);
        (*kson) = swap;
    } while((*kson)->next != NULL);
    *kson = first_kson;
}
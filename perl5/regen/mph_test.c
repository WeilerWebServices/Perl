#include <stdio.h>
#include <string.h>
#include <stdint.h>


#include "mph_algo.h"

int main(int argc, char *argv[]){
    int i;
    for (i=1; i<argc; i++) {
        unsigned char *key = (unsigned char *)argv[i];
        int key_len = strlen(argv[i]);
        printf("key: %s got: %d\n", key, mph_match((unsigned char *)key,key_len));
    }
    return 0;
}

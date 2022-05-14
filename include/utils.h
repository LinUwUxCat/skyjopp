#include <string.h>

char* spacefill(char* str, int n){
    int len = strlen(str);
    if (len >= n){
        return str;
    }
    int diff = n - len;
    for (int i = 0; i < diff; i++){
        strcat(str, " ");
    }
    return str;
}




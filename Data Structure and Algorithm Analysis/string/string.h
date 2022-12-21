#ifndef __STRING_H__
#define __STRING_H__

#include <stdbool.h>

bool isIntStr(char *str) {
    bool isInt;

    isInt = true;

    if(str[0] == '-') {
        for(int i = 1; str[i]; i++) {
            if(str[i] < '0' || str[i] > '9') {
                isInt = false;
                break;
            }
        }
    }
    else {
        for(int i = 0; str[i]; i++) {
            if(str[i] < '0' || str[i] > '9') {
                isInt = false;
                break;
            }
        }
    }

    return isInt;
}

int strToInt(char *str) {
    int num;

    num = 0;

    if(str[0] == '-') {
        for(int i = 1; str[i]; i++) {
            num = num*10 + str[i] - '0';
        }
        num *= -1;
    }
    else {
        for(int i = 0; str[i]; i++) {
            num = num*10 + str[i] - '0';
        }
    }

    return num;
}

#endif
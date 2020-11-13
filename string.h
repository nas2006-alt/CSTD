#ifndef STRING_STRING_H
#define STRING_STRING_H

#include <malloc.h>
#include <math.h>

typedef struct string {
    char* data;
    int length;
    int __cap;
} string;

string create_string(char* data);

void strlen(string* str) {
    int i = 0;
    while (str->data[i] != '\0') {
        i++;
    }
    str->length = i;
}

int strleni(const char* c) {
    int i = 0;
    while (c[i] != '\0') {
        i++;
    }
    return i;
}

string subString(string string1, int startIndex, int length) {
    string s;
    s.data = (char*)malloc(length+1);
    s.length = length;

    int i;
    for (i = startIndex; i < startIndex + length; i++) {
        s.data[i - startIndex] = string1.data[i];
    }

    s.data[i+1] = '\0';

    return s;
}

string* split(string str, char* splitter) {

    string* strArr = malloc(sizeof(string));
    string size;
    int strArrLen = 1;

    int startIndex = 0;

    for (int i = 0; i < str.length; i++) {
        for (int j = 0; j < strleni(splitter); j++) {
            if (str.data[i+j] != splitter[j]) {
                break;
            }
            if (j == strleni(splitter) - 1) {
                //printf("%d,", j);
                strArr = reallocarray(strArr, strArrLen+1, sizeof(string));
                string newS;
                newS.data = malloc(i - startIndex + 1);
                newS.length = i - startIndex;
                newS.__cap = i - startIndex;
                for (int k = startIndex; k < i; k++) {
                    newS.data[k-startIndex] = str.data[k];
                }

                newS.data[i+1] = '\0';

                strArr[strArrLen] = newS;

                strArrLen++;
                startIndex = i+j+1;
            }
        }
    }

    if (startIndex != str.length) {
        string newS;
        newS.data = malloc(str.length - startIndex + 1);
        for (int k = startIndex; k < str.length; k++) {
            newS.data[k - startIndex] = str.data[k];
        }
        newS.length = str.length - startIndex;
        newS.data[str.length] = '\0';

        strArr[strArrLen] = newS;
    } else {
        strArrLen--;
    }

    size.length = strArrLen;
    strArr[0] = size;

    return strArr;
}

void concat(string* base, string toConcat) {
    if (!base->length) {
        strlen(base);
    }
    int startIndex = base->length;
    if (!toConcat.length) {
        strlen(&toConcat);
        if (!toConcat.length) {
            return;
        }
    }
    int secondStrLen = toConcat.length;

    if (base->__cap < startIndex + secondStrLen + 1) {
        long newSize = floor(powl(base->length, 1.5)) + 1;
        base->data = (char *) reallocarray(base->data, newSize, 1);
        base->__cap = newSize;
    }

    for (int i = startIndex; i < startIndex + secondStrLen; i++) {
        base->data[i] = toConcat.data[i - startIndex];
    }

    base->data[startIndex + secondStrLen + 1] = '\0';

    base->length = base->length + secondStrLen;
}

int findFirst(string base, char* target) {
    int tstrleni = strleni(target);
    for (int i = 0; i < base.length; i++) {
        for (int j = 0; j < tstrleni; j++) {
            if (base.data[i+j] != target[j]) {
                break;
            }
            if (j == tstrleni - 1) {
                return i;
            }
        }
    }

    return -1;
}

string create_string(char* str) {
    string s;
    int slen = strleni(str);
    s.data = (char*)malloc(slen+1);
    for (int i = 0; i < slen; i++) {
        s.data[i] = str[i];
    }

    s.length = slen;
    s.__cap = slen;

    return s;
}

#endif //STRING_STRING_H

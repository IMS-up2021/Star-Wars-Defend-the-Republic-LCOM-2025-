#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    int n = 5;
    int *p = &n;

    *p = 0;
    char *cp = (char *)p;
    cp[0] = 'A';
    printf("*cp=%c\n", *cp);
    printf("*p=%d\n", *p);

    free(d);
}
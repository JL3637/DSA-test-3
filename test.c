#include<stdio.h>

int main(){
    printf("2 500000 0\n");
    for(int i = 0; i < 500000; i++){
        printf("a");
    }
    printf("\n");
    for(int i = 0; i < 500000; i++){
        printf("");
    }

    return 0;
}
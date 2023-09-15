#include <stdio.h>

int main(){
    char nombre[5][10] = {"gabriel","maria","jesus","esteban","franco"};
    
    printf("los nombres son : ");
    for (int i = 0; i < 5; i++)
    {
        printf("%s - ",nombre[i]);
    }
    return 0;
}
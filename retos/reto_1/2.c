#include <stdio.h>

int main(){
    char nombre[5][10];
    for (int i = 0; i < 5; i++)
    {
        printf("\nintroduce el un nombre: ");
        scanf("%s",nombre[i]);
    }
    printf("los nombres son : ");
    for (int j = 0; j < 5; j++)
    {
        printf("%s - ",nombre[j]);
    }
    return 0;
}
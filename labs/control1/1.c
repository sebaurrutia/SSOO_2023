#include <stdio.h>

int main(){
    int num =1;
    int i;
    //1)
    printf("primeros 100 numeros impares:\n");
    for ( i = 0; i < 100; i++)
    {
        printf("%i ",num);
        num+=2;
    }

    return 0;
}

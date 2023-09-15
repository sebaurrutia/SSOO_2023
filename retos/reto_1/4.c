#include <stdio.h>

int main(){
    int matriz1[2][2];
    int matriz2[2][2];
    int suma[2][2];

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("ingrese numero para el primer array 2x2 ");
            scanf("%d", &matriz1[i][j]);
            
        }
        
    }
    printf("\n");

 
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("ingrese numero para el segundo array 2x2 ");
            scanf("%d", &matriz2[i][j]); 
        }
    }

 
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            suma[i][j]=matriz1[i][j]+matriz2[i][j];          
        }
        
    }

    printf("suma\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", suma[i][j]);
        }
        printf("\n");
        
    }
    
    return 0 ; 
}
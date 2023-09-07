#include <stdio.h>
#include <math.h>

int main(){
    float num1,num2,num3;
    printf("ingrese 3 notas para calcular el promedio ponderado\n");
    printf("nota 1 40 porciento :");
    scanf("%f", & num1);
    printf("\nnota 2 30 porciento :");
    scanf("%f", & num2);
    printf("\nnota 3 30 porciento :");
    scanf("%f", & num3);
    
    float prom=(num1*0.4 + num2*0.3 + num3*0.3)/10;
    printf("el promedio de las cuatro notas es : %f" ,prom);
    

    return 0;
}

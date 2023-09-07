#include <stdio.h>
#include <math.h>

int main(){
    //Desarrollar un programa que solicite 4 notas en punto flotante por pantalla y se obtenga el
    //promedio simple
    float num1,num2,num3,num4;
    printf("ingrese 4 notas para calcular el promedio");
    scanf("%f", & num1);
    scanf("%f", & num2);
    scanf("%f", & num3);
    scanf("%f", & num4);
    
    float prom=(num1 + num2 + num3 + num4 )/4;
    printf("el promedio de las cuatro notas es : %f" ,prom);
    

    return 0;
}

/*Crear un programa que permita contar la cantidad de veces que se ingresan números pares
y la cantidad de números impares hasta que se ingrese un número negativo. El cero no se
cuenta.*/
#include<stdio.h>

int main(){
    int num,resultado;
    int contp=0;
    int conti=0;
    while(num>0){
        printf("ingrese un numero : ");
        scanf("%d",&num);
        resultado=num/2;
        if(resultado==1){
            contp++;
        }else{
            conti++;
        }
        
    }
    printf("la cantidad de numeros pares ingresados son : %d",contp);
    printf("la cantidad de numeros impares ingresados son : %d",conti);

    return 0;
}
#include<stdio.h>

int main(){
    int cat1, cat2 ;
    float h,A,P;

    printf("introdusca el cateto 1 : ");
    scanf("%d",&cat1);
    printf("introdusca el cateto 2 : ");
    scanf("%d",&cat2);

    h=sqrt((cat1*cat1)+(cat2*cat2));
    printf("la hipotenusa es  : %f \n", h);

    A=(cat1*cat2)/2;
    printf("el area es  : %f \n", A);

    P=h+cat1+cat2;
    printf("el perimetro es  : %d \n", P);

 return 0;
}
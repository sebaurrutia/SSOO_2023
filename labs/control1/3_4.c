#include <stdio.h>
#include <math.h>

int main(){    
    int lado1,lado2,lado3;
    printf("\ningresar primer lado de triangulo ");
    scanf("\n%d", & lado1);
    printf("\nel lado es %i",lado1);
    printf("\ningresar segundo lado de triangulo ");
    scanf("\n%d", & lado2);
    printf("\nel lado es %i",lado2);
    printf("\ningresar terce lado de triangulo ");
    scanf("\n%d", & lado3);
    printf("\nel lado es %i",lado3);
    
    if (lado1 == lado2 && lado2 ==lado3)
    {
        printf("\nes un triangulo equilatero");
    }
    else if(lado1==lado2 || lado1==lado3 || lado2==lado3){
        printf("\nes un triangulo isosceles");
    }
    else{
        printf("\nes un triangulo escaleno");
    }

    //4Tomando como base el código anterior, obtener el cálculo del perímetro, semi perímetro y
    //área del triángulo según la fórmula de Herón.
    //Donde s, es el semiperímetro del triángulo:

    int perimetro=lado1+lado2+lado3;
    float semiperimetro=perimetro/2;
    float s1=semiperimetro-lado1;
    float s2=semiperimetro-lado2;
    float s3=semiperimetro-lado3;
    float area=sqrt(semiperimetro*s1*s2*s3);
    printf("\nperimetro %i",perimetro);
    printf("\nsemiperimetro %f",semiperimetro);
    printf("\narea %f",area);

    return 0;
}

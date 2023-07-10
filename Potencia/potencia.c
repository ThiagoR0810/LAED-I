#include <stdio.h>

int mult(int base, int exp);

int main(void){
    int base, exp, resultado;

    printf("Digite a base e o expoente inteiros: ");
    scanf("%d", &base);
    scanf("%d", &exp);

    resultado = mult(base, exp);

    printf("Resultado: %d", resultado);
}

int mult(int base, int exp){
    if(exp==0){
        return 1;
    }
    else{
        return base*mult(base,exp-1);
    }
}
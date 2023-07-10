#include <stdio.h>

int Digitos(int N);

int main(void){
    int num, resultado;

    printf("Digite um numero inteiro: ");
    scanf("%d", &num);

    resultado = Digitos(num);

    printf("Resultado: %d", resultado);
    
    return 0;
}

int Digitos(int N){
    static int cont = 1;
    if(N>=10){
        cont++;
        return Digitos(N/10);
    }
    else{
        return cont;
    }
}
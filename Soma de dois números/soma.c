#include <stdio.h>

int main(void){
    int num1, num2, resultado;

    printf("Digite os dois numeros: ");
    scanf("%d", &num1);
    scanf("%d", &num2);

    resultado = num1 + num2;

    printf("Resultado = %d\n", resultado);

    return 0;
}
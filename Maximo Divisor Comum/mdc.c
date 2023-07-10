#include <stdio.h>

int mdc(int a, int b);

int main(void){
    int num1, num2, maxDivCom;

    printf("Digite dois numeros inteiros: ");
    scanf("%d", &num1);
    scanf("%d", &num2);

    maxDivCom = mdc(num1, num2);

    printf("Resultado: %d", maxDivCom);

}

int mdc(int a, int b){
    if(b==0){
        return a;
    }
    else{
        return mdc(b, a % b);
    }
}
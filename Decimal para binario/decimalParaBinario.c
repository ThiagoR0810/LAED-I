#include <stdio.h>

void dec2bin(int dec);

int main(void){
    int dec;

    printf("Digite um numero inteiro: ");
    scanf("%d", &dec);

    printf("Resultado: ");
    dec2bin(dec);
    
    return 0;
}

void dec2bin(int dec){
    int bin;
    if(dec/2 !=0){
        bin = dec%2;
        dec2bin(dec/2);
        printf("%d", bin);
    }
    else{
        printf("%d", dec%2);
    }
}
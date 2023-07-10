#include <stdio.h>

int main(void){
    int entrada;

    printf("Digite um numero inteiro: ");
    scanf("%i", &entrada);
    printf("Decomposicao:\n");

    
    return 0;
}


int LimpaVetor(int vetor[]){
    for(int i=0; i<sizeof(vetor);i++){
        vetor[i] = 0;
    }
    return vetor;
}

void Imprimir(int vetor[]){
    for(int i=0; i<sizeof(vetor);i++){
        if(i==(sizeof(vetor)-1) || vetor[i+1]==0){
            printf("%i\n", vetor[i]);
            break;
        }
        else{
            printf("%i + ", vetor[i]);
        }
    }
    return 0;
}

int PreencheVetor(int num, int vetor[]){
    vetor[0] = num;
    Imprimir(vetor);
    
}

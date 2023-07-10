#include <stdio.h>

int main(void){
    int tam;
    
    printf("Digite a quantidade de numeros: ");
    scanf("%d", &tam);

    int vet[tam];

    printf("Digite a sequencia de numeros: \n");

    for(int i=0; i<tam; i++){
        scanf("%d",&vet[i]);
    }

    int aux = vet[0];
    int cont = 1;

    for (int i=1; i<tam; i++)
    {
        if(aux!=vet[i]){
            aux = vet[i];
            vet[cont] = vet[i];
            cont++;
        }
    }
    printf("Resultado: existe(m) %d numero(s) na sequencia final\n", cont);

    printf("Sequencia final: ");

    for (int i=0; i<cont; i++)
    {
        printf("%d ", vet[i]);
    }
}
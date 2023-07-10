#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char nomeArquivo[100];
    int *ponteiro; // aponta para o primeiro numero do vetor original
    int *numDiferentes;
    int qntNumDiferente = 1;
    int cont = 0;
    int contador = 0;
    int aux;
    int aux1 = 1;
    int tamVetor = 0;
    int numSegmentos = 1;
 

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    FILE *fp;
    fp = fopen(nomeArquivo,"r");

    if(!fp) {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    };

    fscanf(fp, "%i", &tamVetor);

    ponteiro = malloc(tamVetor * sizeof(int));

    for (int i = 0; i < tamVetor; i++) {
        fscanf(fp, "%i", &*(ponteiro + i));
    }  

    fclose(fp);
    
    
    //printf("Tamnho do vetor: %i\n", tamVetor);

    /*for (int i = 0; i < tamVetor; i++) {
        printf("%i ", *(ponteiro + i));
        if (i == tamVetor -1)
            printf("\n");
    }*/

    aux = *ponteiro;

    for (int i = 0; i < tamVetor; i++) {
        if (aux != *(ponteiro + i)) {
            aux = *(ponteiro + i);
            numSegmentos++;
        }
    }

    //printf("Numero de segmentos: %i\n", numSegmentos);

    int **M;
    int m = 2;
    int n = numSegmentos;

    M = (int **) malloc (m * sizeof (int *));
    for (int i = 0; i < m; ++i)
        M[i] = (int *) malloc (n * sizeof (int));

    
    aux = *ponteiro;

    for (int i = 0; i < tamVetor; i++) {
        if (aux != *(ponteiro + i)) {
            aux = *(ponteiro + i);
            M[1][cont] = contador;
            cont++;
            contador = 0;
        }
        if (i == tamVetor - 1) {
            contador++;
            M[1][cont] = contador;
            cont++;
            contador = 0;
        } 
        contador++;
    }    

    aux = *ponteiro;
    cont = 0;

    for (int i = 0; i < tamVetor; i++) {
        if (aux != *(ponteiro + i)){
            for(int j = 0; j < i; j++) {
                if (*(ponteiro + i) == *(ponteiro + j))
                    cont++;
            }
            if(cont == 0)
                qntNumDiferente++;
            cont = 0;
        }
    }

    //printf("qntNumDiferente = %i\n", qntNumDiferente);

    numDiferentes = malloc(qntNumDiferente * sizeof(int));

    cont = 0;
    *(numDiferentes) = aux;

    for (int i = 0; i < tamVetor; i++) {
        if (aux != *(ponteiro + i)){
            for(int j = 0; j < i; j++) {
                if (*(ponteiro + i) == *(ponteiro + j))
                    cont++;
            }
            if(cont == 0) {
                *(numDiferentes + aux1) = *(ponteiro + i);
                aux1++;
            }
            cont = 0;
        }
    }

    /*for (int j = 0; j < qntNumDiferente; j++) {
        printf("%i ", *(numDiferentes + j));
        if (j == qntNumDiferente -1)
            printf("\n");
    }*/

    for (int i = 0; i < qntNumDiferente; i++) {
        for (int j = 0; j < qntNumDiferente; j++) {
            if (*(numDiferentes + j) > *(numDiferentes + i)){
                aux = *(numDiferentes + j);
                *(numDiferentes + j) = *(numDiferentes + i);
                *(numDiferentes + i) = aux;
            }
        }
    }

    /*for (int j = 0; j < qntNumDiferente; j++) {
        printf("%i ", *(numDiferentes + j));
        if (j == qntNumDiferente -1)
            printf("\n");
    }*/

    aux = *ponteiro;

    for (int k = 0; k < qntNumDiferente; k++) {
            if (*(ponteiro) == *(numDiferentes + k)){
                    M[0][0] = k + 1;
            }
    }

    for (int i = 0, j = 1; i < tamVetor; i++) {
        if (aux != *(ponteiro + i)) {
            aux = *(ponteiro + i);
            for (int k = 0; k < qntNumDiferente; k++) {
                if (*(ponteiro + i) == *(numDiferentes + k)){
                    M[0][j] = k + 1;
                    j++;
                }
            }
        }
        if (i == tamVetor - 1) {
            for (int k = 0; k < qntNumDiferente; k++) {
                if (*(ponteiro + i) == *(numDiferentes + k)){
                    M[0][j] = k + 1;
                    j++;
                }
            }
        } 
        
    }    

    printf("Matriz:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%i ", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}
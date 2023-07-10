// Projeto LAEDs Parte 1
// Dupla: Ana Clara Cunha Lopes e Thiago Ribeiro Correa

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/* ========================================================================= */

typedef int TipoChave;

typedef struct {
    int Chave;
    int Tipo;
    int NumElementos;
    int PontoMedio;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct {
    TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista) { 
    Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista) { 
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista) { 
    Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Item = x;
    Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item){ 
    /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p -> Prox == NULL) { 
        printf("Erro! Lista vazia ou posicao nao existe\n");
        return;
    }
    q = p -> Prox;
    *Item = q -> Item;
    p -> Prox = q -> Prox;
    if (p -> Prox == NULL) 
        Lista -> Ultimo = p;
    free(q);
}

void Imprime(TipoLista Lista) { 
    TipoApontador Aux;
    Aux = Lista.Primeiro -> Prox;
    while (Aux != NULL) { 
        printf("Chave: %d\n", Aux -> Item.Chave);
        printf("Tipo: %d\n", Aux -> Item.Tipo); 
        printf("NumElementos: %d\n", Aux -> Item.NumElementos); 
        printf("PontoMedio: %d\n\n", Aux -> Item.PontoMedio);
        Aux = Aux -> Prox;
    }
}

int VerificaSequencia(TipoLista Lista) {
    int sequencia[5] = {1, 3, 2, 3, 1};
    int vetor[5];
    int retorno = 0;
    TipoApontador Aux1, Aux2;
    Aux1 = Lista.Primeiro -> Prox;
    while (Aux1 != NULL) {
        if (Aux1->Item.Tipo == 1) {
            Aux2 = Aux1;
            for (int i = 0; i < 5; i++) {
                vetor[i] = Aux2->Item.Tipo;
                Aux2 = Aux2 -> Prox;
                if (Aux2 == NULL && i<4) {
                    return retorno;
                }
            }
            for (int i = 0; i < 5; i++) {
                if (sequencia[i] == vetor[i]) {
                   retorno++;
                }
            }
            if (retorno == 5) {
                return retorno;
            }
            retorno = 0;
        }
        
        Aux1 = Aux1 -> Prox;
        retorno = 0;
    }
    return retorno;
}
/* ========================================================================== */

int main(int argc, char *argv[]) {

    TipoLista lista;
    TipoItem item;
    FLVazia(&lista);

    char nomeArquivo[100];
    int N; // numero de elementos no arquivo texto
    int *ptr; //ponteiro que aponta para a primeira posicao do vetor original de elementos
    int aux; // variavel auxiliar
    int numSegmentos = 0; // numero de segmentos do vetor original

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo); 
    
    FILE *file;
    file = fopen(nomeArquivo,"r");

    if(!file) {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    };

    fscanf(file, "%i", &N);

    ptr = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        fscanf(file, "%i", &*(ptr + i));
    } 

    fclose(file);

    aux = *ptr;

    for (int i = 0; i < N; i++) { // calcula o numero de segmentos do vetor original
        if (aux != *(ptr + i)) {
            aux = *(ptr + i);
            numSegmentos++;
        }
        if (i == N -1)
            numSegmentos++;
    }
    //printf("NumSegmentos: %d\n\n", numSegmentos);

    int numElementos[numSegmentos]; // numero de elementos em cada segmento

    aux = *ptr;

    for (int i = 0, j = 0, k = 0; i < N; i++) { // calcula o numero de elementos em cada segmento
        if (aux != *(ptr + i)) {
            aux = *(ptr + i);
            numElementos[k] = j;
            k++;
            j = 0;
        }
        if (i == N - 1) {
            j++;
            numElementos[k] = j;
            k++;
            j = 0;
        } 
        j++;
    }
    /*for (int i = 0; i < numSegmentos; i++) {
        printf("Segmento %i: %i elementos\n", i+1, numElementos[i]);
    }
    printf("\n");*/

    int PontoMedio[numSegmentos];

    aux = *ptr;

    for (int i = 0, j = 0, k = 0; i < N; i++) { // calcula o ponto medio de todos os segmentos
        if (aux != *(ptr + i)) {
          aux = *(ptr + i);
          PontoMedio[k] = (int)((j + i)/ 2);
          j = i + 1;
          k++;
        }
        if (i == N - 1) {
          PontoMedio[k] = (int)((j + i)/ 2);
        }
    }
    /*for (int i = 0; i < numSegmentos; i++) {
        printf("Segmento %i: PontoMedio: %i\n", i+1, PontoMedio[i]);
    }
    printf("\n");*/

    int Tipo[numSegmentos];

    aux = *ptr;

    for (int i = 0, k = 0; i < N; i++) { // calcula o tipo de cada segmento 0->1  128->2  255->3
        if (aux != *(ptr + i)) {
            if (aux == 0)
                Tipo[k] = 1;
            else if (aux == 128)
                Tipo[k] = 2;
            else if (aux == 255)
                Tipo[k] = 3;
            k++;
            aux = *(ptr + i);
        }
        if (i == N -1) {
            if (aux == 0)
                Tipo[k] = 1;
            else if (aux == 128)
                Tipo[k] = 2;
            else if (aux == 255)
                Tipo[k] = 3;
        }
    }
    /*for (int i = 0; i < numSegmentos; i++) {
        printf("Segmento %i: Tipo: %i\n", i+1, Tipo[i]);
    }
    printf("\n");*/
    
    for (int i = 0; i < numSegmentos; i++) { 
        item.Chave = i;
        item.NumElementos = numElementos[i];
        item.PontoMedio = PontoMedio[i];
        item.Tipo = Tipo[i];
        Insere(item, &lista);
    }

    //Imprime(lista);

    int verificador = VerificaSequencia(lista);

    if (verificador == 5)
        printf("Resultado: Padrao encontrado.\n");
    else
        printf("Resultado: Padrao nao encontrado.\n");
    
    return (0);
}

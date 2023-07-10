
// ALUNOS: Ana Clara Cunha Lopes   e   Thiago Ribeiro Corrêa

/* ========================================================================= */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

typedef int TipoChave;

typedef struct
{
    int Chave;
    int TipoSegmento;
    int NumElementos;
    int PontoMedio;

} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;

} TipoCelula;

typedef struct
{
    TipoApontador Primeiro, Ultimo;

} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Imprime(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        // printf("Chave: %d, Tipo: %d, NumElementos: %d, PontoMedio: %d\n", Aux->Item.Chave, Aux->Item.TipoSegmento, Aux->Item.NumElementos, Aux->Item.PontoMedio);

        printf("Chave: %d, Tipo: %d, NumElementos: %d, PontoMedio: %d\n", Aux->Item.Chave, Aux->Item.TipoSegmento, Aux->Item.NumElementos, Aux->Item.PontoMedio);

        Aux = Aux->Prox;
    }
}

// funcao que transforma matriz em vetor com 9 sepando cada linha
int *transformador(int **matriz, int linha, int coluna)
{
    int i, j, k = 0;
    int tamanho = (linha * coluna) + linha;

    int *vetor = (int *)malloc(tamanho * sizeof(int));
    if (vetor == NULL)
    {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }
    for (i = 0; i < linha; i++)
    {
        for (j = 0; j < coluna; j++)
        {
            if (j == coluna - 1)
            {
                vetor[k] = matriz[i][j];
                vetor[k + 1] = 9; // representa a quebra de linha
                k = k + 2;
            }
            else
            {
                vetor[k] = matriz[i][j];
                k++;
            }
        }
    }
    return vetor;
}

int verificaDirecao(TipoLista Lista)
{
    TipoApontador verifica = Lista.Primeiro->Prox;
    int verifica2, a = 0;
    int *vetor = (int *)malloc(a * sizeof(int)); // *

    while (verifica != NULL)
    {
        if (verifica->Item.TipoSegmento == 1)
        {
            if (verifica->Prox != NULL && verifica->Prox->Item.TipoSegmento == 3)
            {
                if (verifica->Prox->Prox->Item.TipoSegmento == 2)
                {
                    verifica2 = verifica->Prox->Prox->Item.PontoMedio;

                    if (verifica->Prox->Prox->Prox != NULL && verifica->Prox->Prox->Prox->Item.TipoSegmento == 3)
                    {
                        if (verifica->Prox->Prox->Prox->Prox != NULL && verifica->Prox->Prox->Prox->Prox->Item.TipoSegmento == 1)
                        {
                            vetor[a] = verifica2; // sequencia encontrada
                            a++;
                        }
                    }
                }
            }
        }
        verifica = verifica->Prox;
    }

    int result = vetor[0] - vetor[a - 1];
   if (a < 5)
    {
        result = 10000;
        return result;
    }
    else
    {
        return result;
    }
}

/* ========================================================================== */

int main()
{
    FILE *arquivo;
    char texto[100];

    printf("Digite o nome do arquivo: ");
    scanf("%s", texto);

    // Abre arquivo texto para leitura
    arquivo = fopen(texto, "r");

    // Verifica se não conseguiu abrir o arquivo
    if (!arquivo)
    {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    }

    // Lê a primeira linha o valor de L
    int L;
    fscanf(arquivo, "%d", &L);

    int **segmento = (int **)malloc(L * sizeof(int *));

    // le os valores de N e as linha seguinte os N valores
    // L são as linhas e N são as colunas

    int N;
    for (int i = 0; i < L; i++)
    {
        fscanf(arquivo, "%i", &N);
        segmento[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++)
        {
            fscanf(arquivo, "%i", &segmento[i][j]);
        }
    }

    /* ========================================================================== */
    // processamento necessário com os dados lidos da linha

    // L são as linhas e N são as colunas

    // Alocando memória para a matriz
    int **vetor_segmento = (int **)malloc(L * sizeof(int *)); // Aloca memória para os segmentos
    for (int i = 0; i < L; i++)
    {
        vetor_segmento[i] = (int *)malloc(N * sizeof(int));
    }

    // Preenchendo a matriz com valores
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (segmento[i][j] == 0) // preto
            {
                vetor_segmento[i][j] = 1;
            }
            else if (segmento[i][j] == 128) // vermelho
            {
                vetor_segmento[i][j] = 2;
            }
            else if (segmento[i][j] == 255) // branco
            {
                vetor_segmento[i][j] = 3;
            }
            else
            {
                vetor_segmento[i][j] = segmento[i][j];
            }
        }
    }

    /*for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", vetor_segmento[i][j]);
        }
        printf("\n");
    }*/

    //  Inicia matriz com zero
    int matriz_qtd_elem_dif[L][1], K = 0;

    for (int i = 0; i < L; i++)
    {
        matriz_qtd_elem_dif[i][0] = 0;
    }

    //  Encontra a qtd de segmentos diferentes
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == N - 1)
            {
                if (vetor_segmento[i][j] != vetor_segmento[i][j - 1])
                {
                    K++;
                }
                matriz_qtd_elem_dif[i][0] = K;
                K = 0;
            }
            else
            {
                if (j == 0 || vetor_segmento[i][j] != vetor_segmento[i][j - 1])
                {
                    K++;
                }
            }
        }
    }

    // verifica qual linha possui o maior numero de elementos
    int maior = 0;
    for (int i = 0; i < L; i++)
    {
        if (matriz_qtd_elem_dif[i][0] > maior)
        {
            maior = matriz_qtd_elem_dif[i][0];
        }
    }

    /* ========================================================================= */

    // Alocando memória para a matriz
    int **num_elementos = (int **)malloc(L * sizeof(int *));
    int **tipo_segmento = (int **)malloc(L * sizeof(int *));
    int **ponto_medio = (int **)malloc(L * sizeof(int *));
    for (int i = 0; i < L; i++)
    {
        num_elementos[i] = (int *)malloc(maior * sizeof(int));
        tipo_segmento[i] = (int *)malloc(maior * sizeof(int));
        ponto_medio[i] = (int *)malloc(maior * sizeof(int));
    }

    // inicia as matrizes com zero
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < maior; j++)
        {
            num_elementos[i][j] = 0;
            tipo_segmento[i][j] = 0;
            ponto_medio[i][j] = 0;
        }
    }

    // Aloca os valores da matriz em tipo_segmento (um de cada bloco)
    int x = 0, y = 0;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == N - 1)
            {
                if (vetor_segmento[i][j] != vetor_segmento[i][j - 1])
                {
                    tipo_segmento[x][y] = vetor_segmento[i][j];
                }
                x++;
                y = 0;
            }
            else
            {
                if (j == 0 || vetor_segmento[i][j] != vetor_segmento[i][j - 1])
                {
                    tipo_segmento[x][y] = vetor_segmento[i][j];
                    y++;
                }
            }
        }
    }
    // ***************** OBSERVACAO: ONDE ESTIVER COM ZERO NA MATRIZ É PARA DESCONSIDERAR *****************

    // Cria MATRIZ e conta o numero de elementos
    int auxx = 0, auxy = 0;

    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == N - 1)
            {
                if (j == 0 || vetor_segmento[i][j] != vetor_segmento[i][j - 1])
                {
                    num_elementos[auxx][auxy] = 1;
                }
                else
                {
                    num_elementos[auxx][auxy - 1]++;
                }
                auxx++;
                auxy = 0;
            }
            else
            {
                if (j == 0 || vetor_segmento[i][j] != vetor_segmento[i][j - 1])
                {
                    num_elementos[auxx][auxy] = 1;
                    auxy++;
                }
                else
                {
                    num_elementos[auxx][auxy - 1]++;
                }
            }
        }
    }

    // cria matriz com o ponto médio do segmento
    int m = 0, n = 0, inicio = 0, fim = 0, pontoMedio;

    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == N - 1)
            {
                fim = j;
                pontoMedio = (inicio + fim) / 2;
                ponto_medio[m][n] = pontoMedio;
                n = 0;
                m++;
                inicio = 0;
                fim = 0;
            }
            else
            {
                if (vetor_segmento[i][j] != vetor_segmento[i][j + 1])
                {
                    fim = j;
                    pontoMedio = (inicio + fim) / 2;

                    ponto_medio[m][n] = pontoMedio;
                    n++;

                    inicio = j + 1;
                }
            }
        }
    }

    /* ========================================================================== */

    // transforma matrizes em vetores
    int tam = (L * maior) + L;
    int *aux_tipo_segmento, *aux_num_elementos, *aux_ponto_medio;

    aux_tipo_segmento = transformador(tipo_segmento, L, maior);
    aux_num_elementos = transformador(num_elementos, L, maior);
    aux_ponto_medio = transformador(ponto_medio, L, maior);

    /* ========================================================================== */
    // Verifica qual a direcao da curva

    TipoLista lista;
    TipoItem item;

    FLVazia(&lista);

    /*Insere cada chave na lista */
    for (int i = 0; i < tam; i++)
    {
        item.Chave = i;
        item.TipoSegmento = aux_tipo_segmento[i];
        item.NumElementos = aux_num_elementos[i];
        item.PontoMedio = aux_ponto_medio[i];
        Insere(item, &lista);
    }

    int result = verificaDirecao(lista);
   // printf("%d ", result);

    if (result < -90)
    {
        printf("Resultado: Curva a esquerda.");
    }
    else if (result > 90 && result < 10000)
    {
        printf("Resultado: Curva a direita.");
    }
    else if (result > -89 && result < 89)
    {
        printf("Resultado: Pista em linha reta.");
    }
    else
    {
        printf("Resultado: Formato da pista nao estimado.");
    }

    /* ========================================================================== */
    // Liberando a memória alocada
    for (int i = 0; i < L; i++)
    {
        free(segmento[i]);
        free(vetor_segmento[i]);
        free(num_elementos[i]);
        free(tipo_segmento[i]);
        free(ponto_medio[i]);
    }
    free(segmento);
    free(vetor_segmento);
    free(num_elementos);
    free(tipo_segmento);
    free(ponto_medio);

    fclose(arquivo); // Fecha o arquivo

    return 0;
}

#include <stdio.h>
#include <string.h>

int main(void){
    char nomeArquivo[100];
    int numLinhas, numColunas, num;
    int soma = 0, somaFinal = 0;
    int linhaFinal, colunaFinal;
    int aux = 0;

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivo);

    FILE *fp;
    fp = fopen(nomeArquivo,"r");
    if(!fp) {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    };

    fscanf(fp, "%i", &numLinhas);
    numColunas = numLinhas;
    //printf("\nNumero de linhas: %i\n", numLinhas);

    int matriz[numLinhas][numColunas];

    for(int i=0; i<numLinhas; i++){
        for(int j=0; j<numColunas; j++){
            if(j<=i){
                fscanf(fp, "%i", &num);
                //printf("%i ", num);
                matriz[i][j] = num;
            }
            else{
                num = 0;
                //printf("%i ", num);
                matriz[i][j] = num;
            }
        }
        //printf("\n");
    }
/*
    for(int i=0;i<numLinhas; i++){
        for(int j=0;j<numColunas; j++){
            printf("%i ", matriz[i][j]);
        }
        printf("\n");
    }
*/
    for(int l=numLinhas-1; l>=0; l--){
        for(int c=numColunas-1; c>=0; c--){
            
            for(int i=l; i>=0; i--){
                for(int j=numColunas-1; j>=0; j--){
                    if(aux==0){
                        //printf("%i + %i = ", soma, matriz[i][c]);
                        soma = matriz[i][c];
                        //printf("%i\n", soma);
                        aux = 1;
                        break;
                    }
                    else{
                        //printf("%i + %i = ", soma, matriz[i][j]);
                        soma = soma + matriz[i][j];
                        //printf("%i\n", soma);
                    }
                }
            }

            //printf("Resposta: filera %i, caixa %i\n", l+1, c+1);
            //printf("soma: %i\n", soma);
            if(soma > somaFinal){
                somaFinal = soma;
                linhaFinal = l;
                colunaFinal = c;
            }

            aux = 0;
            soma = 0;
        }
    }

    printf("Resposta: fileira %i, caixa %i.", linhaFinal+1, colunaFinal+1);

    fclose(fp);
    return 0;
}
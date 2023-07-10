// Dupla: 
// Thiago Ribeiro Correa e Marcos Alves de Castro Baker



#include <stdio.h>
#include <string.h>

int main(void){
    char nomeArquivo[100];
    int qntMochilas;

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);
    
    FILE *fp;
    fp = fopen(nomeArquivo, "r");
    if (!fp) {
        printf("Erro na abertura do arquivo.\n");
        return 0;
    };

    fscanf(fp, "%i", &qntMochilas);
    //printf("Quantidade de mochilas: %i\n", qntMochilas);

    int capacidadeMochilas[qntMochilas];

    for (int i = 0; i < qntMochilas; i++) {
        fscanf(fp, "%i", &capacidadeMochilas[i]);
    }

    for (int i = 0; i < qntMochilas; i++) {
        //printf("Capacidade mochila %i: %i\n", (i+1), capacidadeMochilas[i]);
    }

    int qntItens;

    fscanf(fp, "%i", &qntItens);

    int pesoItens[qntItens];
    int valorItens[qntItens];
    int matriz[qntItens][qntMochilas]; // representa os itens selecionados para cada mochila

    for (int i = 0; i < qntItens; i++) { // armazena o peso e o valor dos itens em vetores
        fscanf(fp, "%i", &pesoItens[i]);
        fscanf(fp, "%i", &valorItens[i]);
    }

    for (int i = 0; i < qntItens; i++) {
        //printf("Item %i: Peso %i Valor %i\n", (i+1), pesoItens[i], valorItens[i]);
    }

    for (int i = 0; i < qntItens; i++) {
        for (int j = 0; j < qntMochilas; j++) {
            fscanf(fp, "%i", &matriz[i][j]);
        }
    }

    for (int i = 0; i < qntItens; i++) {
        for (int j = 0; j < qntMochilas; j++) {
            //printf("%i ", matriz[i][j]);
        }
        //printf("\n");
    }

    int pesoNasMochilas[qntMochilas]; // peso do total de itens que estao em cada mochila
    int valorNasMochilas[qntMochilas]; // valor total dos itens que estao em cada mochila

    for (int i = 0; i < qntMochilas; i++) {
        pesoNasMochilas[i] = 0;
        valorNasMochilas[i] = 0;
    }
    
    for (int i = 0; i < qntItens; i++) {
        for (int j = 0; j < qntMochilas; j++) {
            if (matriz[i][j] == 1) {
                //printf("Mochila %i: calculando peso: %i calculando valor: %i\n", j+1, pesoNasMochilas[j], valorNasMochilas[j]);
                pesoNasMochilas[j] = pesoNasMochilas[j] + pesoItens[i];
                valorNasMochilas[j] = valorNasMochilas[j] + valorItens[i];
                //printf("Mochila %i: calculando peso: %i calculando valor: %i\n", j+1, pesoNasMochilas[j], valorNasMochilas[j]);
            }
        }
    }

    int valorItensOrdem[qntItens]; // vetor de itens ordenados do maior valor para o menor valor
    int pesoItensOrdem[qntItens];

    for (int i = 0; i < qntItens; i++) {
        valorItensOrdem[i] = valorItens[i];
        pesoItensOrdem[i] = pesoItens[i];
    }

    int auxValor = valorItensOrdem[0];
    int auxPeso = pesoItensOrdem[0];

    for (int i = 0; i < qntItens; i++) { // coloca os itens em ordem do mais valioso ao menos valioso
        for (int j = 0; j < qntItens; j++) {
            if (valorItensOrdem[j] < valorItensOrdem[i]){
                auxValor = valorItensOrdem[j];
                valorItensOrdem[j] = valorItensOrdem[i];
                valorItensOrdem[i] = auxValor;
                auxPeso = pesoItensOrdem[j];
                pesoItensOrdem[j] = pesoItensOrdem[i];
                pesoItensOrdem[i] = auxPeso;
            }
        }
    }

    for (int i = 0; i < qntItens; i++) {
        //printf("Item %i: Peso %i Valor %i\n", (i+1), pesoItensOrdem[i], valorItensOrdem[i]);
    }

    int valorMaxDasMochilas[qntMochilas];
    int pesoAtualMochilas[qntMochilas];

    for (int i = 0; i < qntMochilas; i++) {
        valorMaxDasMochilas[i] = 0;
        pesoAtualMochilas[i] = 0;
    }

    for (int i = 0; i < qntMochilas; i++) { // calcula o valor maximo de cada mochila
        for (int j = 0; j < qntItens; j++) {
            if (j == 0){
                valorMaxDasMochilas[i] = valorItensOrdem[j];
                pesoAtualMochilas[i] = pesoItensOrdem[j];
            }
            valorMaxDasMochilas[i] = valorMaxDasMochilas[i] + valorItensOrdem[j];
            pesoAtualMochilas[i] = pesoAtualMochilas[i] + pesoItensOrdem[j];
            if(pesoAtualMochilas[i] > capacidadeMochilas[i]){
                valorMaxDasMochilas[i] = valorMaxDasMochilas[i] - valorItensOrdem[j];
                pesoAtualMochilas[i] = pesoAtualMochilas[i] - pesoItensOrdem[j];
            }

        }
    }


    for (int i = 0; i < qntMochilas; i++) {
        if (pesoNasMochilas[i] > capacidadeMochilas[i]) {
            //printf("Mochila %i esta com sobrepeso! Capacidade: %i Peso atual: %i\n", (i+1), capacidadeMochilas[i], pesoNasMochilas[i]);
            printf("Solucao inviavel.\n");
            //break;
        } else if (valorNasMochilas[i] < valorMaxDasMochilas[i]) {
            //printf("Mochila %i nao esta com valor maximo! Valor Maximo: %i Valor atual: %i\n", (i+1), valorMaxDasMochilas[i], valorNasMochilas[i]);
            printf("Solucao viavel mas nao otima.\n");
            //break;
        }
        else if (i == qntMochilas -1) {
            //printf("Mochila %i esta com valor maximo! Valor Maximo: %i Valor atual: %i\n", (i+1), valorMaxDasMochilas[i], valorNasMochilas[i]);
            printf("Solucao otima.\n");
        }
    }

    
    
    return 0;
}

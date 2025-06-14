#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define TAMANHO_TABELA 10

typedef struct Aluno{
    int matricula;
    char nome[50];
    char curso[50];
    struct Aluno *prox;
} Aluno;

typedef struct {
    Aluno **buckets;
    int tamanho;
} TabelaHash;

void clearBuffer() {
    while (getchar() != '\n');
}

int hash(int matricula) {
    return matricula % TAMANHO_TABELA;
}

TabelaHash *criarTabelaHash() {
    int i;
    TabelaHash *tabela = (TabelaHash *)malloc(sizeof(TabelaHash));
    tabela->tamanho = TAMANHO_TABELA;
    tabela->buckets = (Aluno **)malloc(sizeof(Aluno *) * TAMANHO_TABELA);

    for (i = 0; i < TAMANHO_TABELA; i++) {
        tabela->buckets[i] = NULL;
    }
    return tabela;
}

Aluno *criarAluno(){
    Aluno *novo = (Aluno *)malloc(sizeof(Aluno)); 
    
    printf("Digite a matricula do aluno: ");
    scanf("%d", &novo->matricula);
    clearBuffer();
    
    printf("Digite o nome do aluno: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';
    
    printf("Digite o curso do aluno: ");
    fgets(novo->curso, sizeof(novo->curso), stdin);
    novo->curso[strcspn(novo->curso, "\n")] = '\0';
    
    novo->prox = NULL;
    
    return novo;
}

void inserir(TabelaHash *tabela){
    Aluno *novo = criarAluno();
    
    int indice = hash(novo->matricula);
    
    Aluno *aux = tabela->buckets[indice];
    while(aux != NULL){
        if (aux->matricula == novo->matricula){
            printf("A Matricula solicitada ja existe na tabela!!");
            free(novo);
            return;
        }
        aux = aux->prox;
    }
    
    novo->prox = tabela->buckets[indice];
    tabela->buckets[indice] = novo;
    printf("Aluno inserido na posicao: %d", indice);
}

void remover(TabelaHash *tabela){
    Aluno *aux1;
    Aluno *aux2;
    int procurada;
    
    printf("Informe a matricula do aluno: ");
    scanf("%d", &procurada);
    clearBuffer();
    
    int indice = hash(procurada);
    
    aux1 = tabela->buckets[indice];
    aux2 = NULL;
    
    while (aux1 != NULL && aux1->matricula != procurada){
        aux2 = aux1;
        aux1 = aux1->prox;
    }
    
    if(aux1 == NULL){
        printf("Aluno nao encontrado");
        return;
    }
    
    if (aux2 == NULL){
        tabela->buckets[indice] = aux1->prox;
    }
    else {
        aux2->prox = aux1->prox;
    }
    
    free(aux1);
}

Aluno *buscarAluno(TabelaHash *tabela){
    Aluno *aux;
    int procurada;
    
    printf("Informe a matricula do aluno: ");
    scanf("%d", &procurada);
    clearBuffer();
    
    int indice = hash(procurada);
    
    aux = tabela->buckets[indice];
    
    while (aux != NULL && aux->matricula != procurada){
        aux = aux->prox;
    }
    
    if (aux == NULL){
        printf("Matricula não esncontrada\n");
    }
    else{
        printf("\nMatricula: %d", aux->matricula);
        printf("\nNome: %s", aux->nome);
        printf("\nCurso: %s", aux->curso);
    }
    return aux;
}

void exibirTabela(TabelaHash *tabela){
    int i;
    for (i=0; i < tabela->tamanho; i++){
        Aluno *aux = tabela->buckets[i];
        
        printf("\nPosicao %d:", i);
        while (aux != NULL){
            printf("\nMatricula: %d", aux->matricula);
            printf("\nNome: %s", aux->nome);
            printf("\nCurso: %s", aux->curso);
            aux = aux->prox;
        }
    }
}

void exibirEstatistica(TabelaHash *tabela){
    float quantidadeAlunos = 0.0;
    int i;
    for (i = 0; i < tabela->tamanho; i++){
        Aluno *aux1 = tabela->buckets[i];
        while (aux1 != NULL){
            aux1 = aux1->prox;
            quantidadeAlunos++;
        }
    }
    float media = quantidadeAlunos / tabela->tamanho;
    int maxColisoes = 0;
    int bucketMaior = -1;

    printf("Total de Alunos: %.1f", quantidadeAlunos);
    printf("\nTotal de buckets: %d", tabela->tamanho);
    printf("\nTotal de alunos por bucket: %.1f", media);
    
    for (i = 0; i < tabela->tamanho; i++) {
        int contador = 0;
        Aluno *aux2 = tabela->buckets[i];
        while (aux2 != NULL) {
            contador++;
            aux2 = aux2->prox;
        }
        if (contador > maxColisoes) {
            maxColisoes = contador;
            bucketMaior = i;
        }
        
    }
    
    if (maxColisoes > 1) {
        printf("\nBucket com mais colisões: %d (%d alunos)\n", bucketMaior, maxColisoes);
    } else {
        printf("\nNenhum bucket teve colisões.\n");
    }
    
}


int main(){
    int op;
    TabelaHash *tabela = criarTabelaHash();
    
    do{
        printf("\n----MENU----");
        printf("\n 0- Sair\n 1- Inserir Aluno na Tabela\n 2- Remover Aluno da Tabela\n 3- Buscar Aluno na Tabela\n 4- Exibir Tabela Hash\n 5- Exibir Estatísticas");
        printf("\nSelecione uma opção (0-5): ");
        scanf("%d", &op);
        clearBuffer();
        
        switch(op){
            case 0:
                printf("Saindo!!!");
                break;
            case 1:
                inserir(tabela);
                break;
            case 2:
                remover(tabela);
                break;
            case 3:
                buscarAluno(tabela);
                break;
            case 4:
                exibirTabela(tabela);
                break;
            case 5:
                exibirEstatistica(tabela);
                break;
            default:
                printf("Valor Invalido!!!");
                break;
        }
    }while (op != 0);
    return 0;
}
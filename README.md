# Trabalho Avaliativo Implementação Tabela Hash 

**Curso:** Engenharia de Software  
**Disciplina:** Algoritmos e Estruturas de Dados I  
**Professor:** Prof. Alternei de Souza Brito  
**Período:** 2025.1

## Dicentes

- **Verissimo Casas**
- **Joel Carlos**

## Arquivo Principal - [AED1-Trabalho-Tabela-Hash.c](AED1-Trabalho-Tabela-hash.c)

## 1. Implementação da Função Hash

A função hash implementada utiliza o **método da divisão (módulo)**:

```c
int hash(int matricula) {
    return matricula % TAMANHO_TABELA;
}
```

**Especificações Técnicas:**
- **Algoritmo:** Divisão por módulo
- **Capacidade:** 10 buckets (TAMANHO_TABELA = 10)
- **Entrada:** Matrícula do aluno (número inteiro)
- **Saída:** Índice do bucket (0 a 9)
- **Tratamento de colisões:** Encadeamento separado (separate chaining)

**Exemplos de mapeamento baseados nos dados reais:**
- Matrícula 0 → hash(0) = 0 % 10 = **0**
- Matrícula 19552 → hash(19552) = 19552 % 10 = **2**
- Matrícula 923 → hash(923) = 923 % 10 = **3**
- Matrícula 34425 → hash(34425) = 34425 % 10 = **5**
- Matrícula 75166 → hash(75166) = 75166 % 10 = **6**

## 2. Estruturas de Dados Utilizadas

### 2.1 Estrutura do Aluno
```c
typedef struct Aluno{
    int matricula;
    char nome[50];
    char curso[50];
    struct Aluno *prox;
} Aluno;
```

### 2.2 Estrutura da Tabela Hash
```c
typedef struct {
    Aluno **buckets;
    int tamanho;
} TabelaHash;
```

### 2.3 Estado Atual da Tabela Hash

**Dados reais inseridos no sistema (Capturado em 14/06/2025 02:06:42 UTC):**

```
Posição 0: 0 (45567 - Eng. Software) -> NULL
Posição 1: NULL
Posição 2: 19552 (Sonia - Filosofia) -> NULL  
Posição 3: 923 (Hugo - Botanica) -> NULL
Posição 4: NULL
Posição 5: 34425 (lOLA - Artes) -> NULL
Posição 6: 75166 (Zico - Pedagogia) -> NULL
Posição 7: NULL
Posição 8: NULL
Posição 9: NULL
```

**Análise da distribuição atual:**
- **Buckets ocupados:** 5 de 10 (50%)
- **Buckets vazios:** 5 de 10 (50%)
- **Total de alunos:** 5
- **Distribuição:** Perfeita - sem colisões
- **Taxa de ocupação:** 5/10 = 0.5

**Observação importante:** Neste exemplo, todas as matrículas resultaram em índices únicos, demonstrando não houve colisões.

## 3. Documentação das Funções

### 3.1 Funções de Inicialização

#### `TabelaHash *criarTabelaHash()`
**Propósito:** Inicializa uma nova tabela hash vazia.

**Funcionamento:**
- Aloca memória para a estrutura TabelaHash
- Define tamanho como TAMANHO_TABELA (10)
- Cria array de ponteiros para buckets
- Inicializa todos os buckets como NULL

**Complexidade:** O(n) onde n = tamanho da tabela

#### `Aluno *criarAluno()`
**Propósito:** Cria um novo nó aluno coletando dados do usuário.

**Funcionamento:**
- Aloca memória para novo aluno
- Coleta matrícula, nome e curso via input
- Remove caracteres '\n' das strings
- Inicializa ponteiro próximo como NULL

**Complexidade:** O(1)

#### `void clearBuffer()`
**Propósito:** Limpa o buffer de entrada.

**Funcionamento:**
- Remove caracteres residuais até encontrar '\n'
- Previne problemas com scanf e fgets consecutivos

### 3.2 Operações Principais

#### `void inserir(TabelaHash *tabela)`
**Propósito:** Adiciona um novo aluno à tabela hash.

**Algoritmo:**
1. Cria novo aluno através de `criarAluno()`
2. Calcula índice usando função hash
3. Verifica se matrícula já existe no bucket
4. Se não existir, insere no início da lista encadeada
5. Exibe mensagem com posição de inserção

**Exemplo de execução:**
```
Digite a matricula do aluno: 34425
Digite o nome do aluno: lOLA
Digite o curso do aluno: Artes
Aluno inserido na posicao: 5
```

**Tratamento de duplicatas:** Rejeita inserção e libera memória

**Complexidade:** O(k) onde k = elementos no bucket

#### `void remover(TabelaHash *tabela)`
**Propósito:** Remove aluno específico da tabela.

**Algoritmo:**
1. Solicita matrícula para remoção
2. Calcula índice do bucket
3. Percorre lista com dois ponteiros (aux1, aux2)
4. Localiza elemento e reconecta lista
5. Libera memória do aluno removido

**Casos especiais tratados:**
- Remoção do primeiro elemento
- Remoção de elementos intermediários
- Elemento não encontrado

**Complexidade:** O(k) onde k = elementos no bucket

#### `Aluno *buscarAluno(TabelaHash *tabela)`
**Propósito:** Localiza e exibe dados de um aluno.

**Algoritmo:**
1. Solicita matrícula para busca
2. Calcula índice usando hash
3. Percorre lista encadeada até encontrar matrícula
4. Exibe dados completos ou mensagem de erro

**Exemplo de saída:**
```
Matricula: 19552
Nome: Sonia
Curso: Filosofia
```

**Retorno:** Ponteiro para aluno encontrado ou NULL

**Complexidade:** O(k) onde k = elementos no bucket

### 3.3 Funções de Visualização

#### `void exibirTabela(TabelaHash *tabela)`
**Propósito:** Mostra estrutura completa da tabela hash.

**Funcionamento:**
- Itera por todas as posições da tabela (0-9)
- Para cada posição, percorre lista encadeada
- Exibe matrícula, nome e curso de cada aluno
- Mostra posições vazias como apenas "Posicao X:"

**Exemplo de saída real:**
```
----MENU----
 0- Sair
 1- Inserir Aluno na Tabela
 2- Remover Aluno da Tabela
 3- Buscar Aluno na Tabela
 4- Exibir Tabela Hash
 5- Exibir Estatísticas
Selecione uma opção (0-5): 4

Posicao 0:
Matricula: 0
Nome: 45567
Curso: Eng. Software
Posicao 1:
Posicao 2:
Matricula: 19552
Nome: Sonia
Curso: Filosofia
Posicao 3:
Matricula: 923
Nome: Hugo
Curso: Botanica
Posicao 4:
Posicao 5:
Matricula: 34425
Nome: lOLA
Curso: Artes
Posicao 6:
Matricula: 75166
Nome: Zico
Curso: Pedagogia 
Posicao 7:
Posicao 8:
Posicao 9:
```

**Utilidade:** Debug e visualização da distribuição

#### `void exibirEstatistica(TabelaHash *tabela)`
**Propósito:** Calcula e exibe métricas de performance.

**Estatísticas calculadas:**
- Total de alunos na tabela
- Número total de buckets
- Média de alunos por bucket
- Bucket com maior número de colisões

**Baseado nos dados atuais, a saída seria:**
```
Total de Alunos: 5.0
Total de buckets: 10
Total de alunos por bucket: 0.5
Nenhum bucket teve colisões.
```

## 4. Interface do Sistema

### 4.1 Menu Principal
```
----MENU----
 0- Sair
 1- Inserir Aluno na Tabela
 2- Remover Aluno da Tabela
 3- Buscar Aluno na Tabela
 4- Exibir Tabela Hash
 5- Exibir Estatísticas
Selecione uma opção (0-5):
```

### 4.2 Exemplo de Inserção Completa
```
Digite a matricula do aluno: 75166
Digite o nome do aluno: Zico
Digite o curso do aluno: Pedagogia
Aluno inserido na posicao: 6
```

### 4.3 Exemplo de Busca
```
Informe a matricula do aluno: 923

Matricula: 923
Nome: Hugo
Curso: Botanica
```

## 5. Análise de Performance com Dados Reais

### Estado Atual do Sistema:

| Métrica | Valor |
|---------|-------|
| Total de alunos | 5 |
| Buckets ocupados | 5 |
| Buckets vazios | 5 |
| Taxa de ocupação | 50% |
| Colisões | 0 |
| Distribuição | Sem colisões |

### Complexidade das Operações:

| Operação | Caso Atual | Pior Caso Teórico |
|----------|------------|-------------------|
| Inserção | O(1) | O(n) |
| Busca | O(1) | O(n) |
| Remoção | O(1) | O(n) |

### Análise da Função Hash:

A distribuição atual demonstra eficiência da função hash módulo para este conjunto específico de matrículas:
- Matrícula 0 → Posição 0
- Matrícula 19552 → Posição 2  
- Matrícula 923 → Posição 3
- Matrícula 34425 → Posição 5
- Matrícula 75166 → Posição 6

**Resultado:** Distribuição uniforme sem colisões, demonstrando performance ótima.

## 6. Casos de Teste Realizados

### Dados de Entrada Testados:
1. **Aluno 1:** Matrícula 0, Nome "45567", Curso "Eng. Software"
2. **Aluno 2:** Matrícula 19552, Nome "Sonia", Curso "Filosofia"
3. **Aluno 3:** Matrícula 923, Nome "Hugo", Curso "Botanica"
4. **Aluno 4:** Matrícula 34425, Nome "lOLA", Curso "Artes"
5. **Aluno 5:** Matrícula 75166, Nome "Zico", Curso "Pedagogia"

### Verificações de Qualidade:
- ✅ Inserção bem-sucedida de todos os alunos
- ✅ Distribuição sem colisões
- ✅ Exibição correta da estrutura da tabela
- ✅ Interface do menu funcionando adequadamente

## 7. Compilação e Execução

### Comandos de Compilação
```bash
gcc -o AED1-Trabalho-Tabela-hash AED1-Trabalho-Tabela-hash.c -std=c99 -Wall
```

### Execução
```bash
./AED1-Trabalho-Tabela-hash
```

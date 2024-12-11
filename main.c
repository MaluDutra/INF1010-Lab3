// Gustavo Rocha Barros 2310505
// Maria Luiza Dutra Gonzalez de Almeida 2310509
#include <stdio.h>
#include <stdlib.h>

struct arvbin
{ // criação do struct para árvore binária, contendo as informações para os nós (chave e ponteiros para filhos)
    int info;
    int nivel;
    int altura;
    struct arvbin* esq;
    struct arvbin* dir;
    struct arvbin* pai;
};
typedef struct arvbin Arvbin;

Arvbin* cria_arvore();
Arvbin* cria_no(int info, int nivel, int altura, Arvbin* no_pai);
Arvbin* insere_alt(Arvbin* arvore);
void insere_no(Arvbin** arvore, int info);
void imprime_arvore(Arvbin* arvore);

Arvbin* cria_arvore()
{ // inicialização da árvore binária como vazia
    return NULL;
}

Arvbin* cria_no(int info, int nivel, int altura, Arvbin* no_pai)
{ // criação de um nó da árvore binária, contendo a chave e dois ponteiros para seus filhos à esquerda e direita
    Arvbin* no = (Arvbin*)malloc(sizeof(Arvbin));

    if (!no)
    {
        printf("Ocorreu um erro ao inicializar o nó!\n\n.");
        exit(1);
    }

    no->info = info;
    no->nivel = nivel;
    no->altura = altura;
    no->dir = NULL;
    no->esq = NULL;
    no->pai = no_pai;

    return no;
}

Arvbin* insere_alt(Arvbin* arvore)
{ // recebe a árvore já povoada e calcula a altura de cada nó
    if (arvore == NULL)
    { // confere se o nó está nulo, servindo como condição para terminar a recursão
        return NULL;
    }

    int aux = 0; // variável auxiliar para calcular o valor da altura
    Arvbin* pAux = arvore;
    while (pAux->esq)
    { // enquanto o nó tiver um filho à esquerda, ele incrementa a variável e segue para seu filho para continuar o cálculo
        pAux = pAux->esq;
        aux++;
    }
    arvore->altura = aux;

    arvore->esq = insere_alt(arvore->esq); // utiliza recursão para percorrer todos os nós
    arvore->dir = insere_alt(arvore->dir);
    return arvore;
}

void insere_no(Arvbin** arvore, int info)
{                                                             // inserção do nó na árvore binária
    Arvbin** fila = (Arvbin**)malloc(40 * sizeof(Arvbin*)); // criação da fila de nós (FIFO)

    if (fila == NULL)
    {
        printf("Ocorreu um erro ao criar a fila.\n");
        exit(1);
    }

    int inicio = 0;   // para marcar o início da fila
    int final = 0;    // para marcar o final da fila
    int nivel = 0;    // para começar a inserção de níveis
    int qtde_nos = 0; // para contar a quantidade de nós

    if (*arvore == NULL) // caso a árvore esteja vazia inicialmente
    {
        *arvore = cria_no(info, nivel, 0, NULL); // aqui, o nível é 0, a altura é colocada inicialmente como zero e o pai é nulo
        return;
    }

    fila[final++] = *arvore; // inserimos a raiz na fila
    qtde_nos++;              // com a raiz, há um nó na árvore no total
    nivel++;                 // o nível deixa de ser zero e passa a ser 1

    while (inicio < final)
    {
        Arvbin* no = fila[inicio++]; // nó temporário que irá percorrer a fila do início
        qtde_nos++;                  // soma-se mais um nó na contagem de nós

        if (qtde_nos > (2 * nivel))
        { // caso a quantidade de nós seja maior do que o nível vezes dois, o nível aumenta
            nivel++;
        }

        if (no->esq == NULL)
        { // caso o filho à esquerda do nó esteja vazio, é inserido o novo nó
            no->esq = cria_no(info, nivel, 0, no); // para criar um novo nó, são passados sua chave, seu nível e seu pai, passando a altura como zero por default (vai ser inserida depois)
            break;
        }
        else
        { // caso o filho à esquerda do nó não esteja vazio, ele é inserido ao final da fila
            fila[final++] = no->esq;
        }

        if (no->dir == NULL)
        { // caso o filho à direita do nó esteja vazio, é inserido o novo nó
            no->dir = cria_no(info, nivel, 0, no); // para criar um novo nó, são passados sua chave, seu nível e seu pai, passando a altura como zero por default (vai ser inserida depois)
            break;
        }
        else
        { // caso o filho à direita do nó não esteja vazio, ele é inserido ao final da fila
            fila[final++] = no->dir;
        }
    }
    free(fila);
    *arvore = insere_alt(*arvore); // aqui é onde a altura de cada nó é inserida
}

void imprime_arvore(Arvbin* arvore)
{ // impressão de todos os nós da árvore em modelo simétrico
    if (arvore != NULL)
    {
        imprime_arvore(arvore->esq); // prioridade para os nós da esquerda
        if (arvore->pai == NULL)
        {
            printf("%d -- nivel %d, altura %d\n", arvore->info, arvore->nivel, arvore->altura);
        }
        else
        {
            printf("%d -- nivel %d, altura %d, pai %d\n", arvore->info, arvore->nivel, arvore->altura, arvore->pai->info);
        }
        imprime_arvore(arvore->dir); // chamada dos nós da direita, após os da esquerda e da raiz
    }
}

int main(void)
{
    int vetor[10] = { 10, 5, 15, 3, 7, 13, 20, 1, 4, 6 };
    Arvbin* arvoreBi = cria_arvore();

    for (int i = 0; i < 10; i++)
    {
        insere_no(&arvoreBi, vetor[i]); // realiza a inserção dos nós na árvore
    }

    imprime_arvore(arvoreBi); // realiza o algoritmo de listagem dos nós
    putchar('\n');

    return 0;
}
// Gustavo Rocha Barros 2310505
// Maria Luiza Dutra Gonzalez de Almeida 2310509
#include <stdio.h>
#include <stdlib.h>

struct arvbin
{ // cria��o do struct para �rvore bin�ria, contendo as informa��es para os n�s (chave e ponteiros para filhos)
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
{ // inicializa��o da �rvore bin�ria como vazia
    return NULL;
}

Arvbin* cria_no(int info, int nivel, int altura, Arvbin* no_pai)
{ // cria��o de um n� da �rvore bin�ria, contendo a chave e dois ponteiros para seus filhos � esquerda e direita
    Arvbin* no = (Arvbin*)malloc(sizeof(Arvbin));

    if (!no)
    {
        printf("Ocorreu um erro ao inicializar o n�!\n\n.");
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
{ // recebe a �rvore j� povoada e calcula a altura de cada n�
    if (arvore == NULL)
    { // confere se o n� est� nulo, servindo como condi��o para terminar a recurs�o
        return NULL;
    }

    int aux = 0; // vari�vel auxiliar para calcular o valor da altura
    Arvbin* pAux = arvore;
    while (pAux->esq)
    { // enquanto o n� tiver um filho � esquerda, ele incrementa a vari�vel e segue para seu filho para continuar o c�lculo
        pAux = pAux->esq;
        aux++;
    }
    arvore->altura = aux;

    arvore->esq = insere_alt(arvore->esq); // utiliza recurs�o para percorrer todos os n�s
    arvore->dir = insere_alt(arvore->dir);
    return arvore;
}

void insere_no(Arvbin** arvore, int info)
{                                                             // inser��o do n� na �rvore bin�ria
    Arvbin** fila = (Arvbin**)malloc(40 * sizeof(Arvbin*)); // cria��o da fila de n�s (FIFO)

    if (fila == NULL)
    {
        printf("Ocorreu um erro ao criar a fila.\n");
        exit(1);
    }

    int inicio = 0;   // para marcar o in�cio da fila
    int final = 0;    // para marcar o final da fila
    int nivel = 0;    // para come�ar a inser��o de n�veis
    int qtde_nos = 0; // para contar a quantidade de n�s

    if (*arvore == NULL) // caso a �rvore esteja vazia inicialmente
    {
        *arvore = cria_no(info, nivel, 0, NULL); // aqui, o n�vel � 0, a altura � colocada inicialmente como zero e o pai � nulo
        return;
    }

    fila[final++] = *arvore; // inserimos a raiz na fila
    qtde_nos++;              // com a raiz, h� um n� na �rvore no total
    nivel++;                 // o n�vel deixa de ser zero e passa a ser 1

    while (inicio < final)
    {
        Arvbin* no = fila[inicio++]; // n� tempor�rio que ir� percorrer a fila do in�cio
        qtde_nos++;                  // soma-se mais um n� na contagem de n�s

        if (qtde_nos > (2 * nivel))
        { // caso a quantidade de n�s seja maior do que o n�vel vezes dois, o n�vel aumenta
            nivel++;
        }

        if (no->esq == NULL)
        { // caso o filho � esquerda do n� esteja vazio, � inserido o novo n�
            no->esq = cria_no(info, nivel, 0, no); // para criar um novo n�, s�o passados sua chave, seu n�vel e seu pai, passando a altura como zero por default (vai ser inserida depois)
            break;
        }
        else
        { // caso o filho � esquerda do n� n�o esteja vazio, ele � inserido ao final da fila
            fila[final++] = no->esq;
        }

        if (no->dir == NULL)
        { // caso o filho � direita do n� esteja vazio, � inserido o novo n�
            no->dir = cria_no(info, nivel, 0, no); // para criar um novo n�, s�o passados sua chave, seu n�vel e seu pai, passando a altura como zero por default (vai ser inserida depois)
            break;
        }
        else
        { // caso o filho � direita do n� n�o esteja vazio, ele � inserido ao final da fila
            fila[final++] = no->dir;
        }
    }
    free(fila);
    *arvore = insere_alt(*arvore); // aqui � onde a altura de cada n� � inserida
}

void imprime_arvore(Arvbin* arvore)
{ // impress�o de todos os n�s da �rvore em modelo sim�trico
    if (arvore != NULL)
    {
        imprime_arvore(arvore->esq); // prioridade para os n�s da esquerda
        if (arvore->pai == NULL)
        {
            printf("%d -- nivel %d, altura %d\n", arvore->info, arvore->nivel, arvore->altura);
        }
        else
        {
            printf("%d -- nivel %d, altura %d, pai %d\n", arvore->info, arvore->nivel, arvore->altura, arvore->pai->info);
        }
        imprime_arvore(arvore->dir); // chamada dos n�s da direita, ap�s os da esquerda e da raiz
    }
}

int main(void)
{
    int vetor[10] = { 10, 5, 15, 3, 7, 13, 20, 1, 4, 6 };
    Arvbin* arvoreBi = cria_arvore();

    for (int i = 0; i < 10; i++)
    {
        insere_no(&arvoreBi, vetor[i]); // realiza a inser��o dos n�s na �rvore
    }

    imprime_arvore(arvoreBi); // realiza o algoritmo de listagem dos n�s
    putchar('\n');

    return 0;
}
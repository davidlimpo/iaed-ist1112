#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_PROD 10000
#define NUM_CHARS 21
#define MAX_LONG_INT 2147483647

/*Inicialização das variáveis*/

char c; 	/* Variavel auxiliar */
int i; 		/* Variavel auxiliar */

/* Contadores */
double valorCarrinho = 0;
double valorTotal = 0;
int numCarrinhos = 0;
long int IdProdMaisComprado = MAX_LONG_INT;
double numComprasProdMaisComprado = 0;

/*Estruturas utilizadas no projecto*/

typedef struct prod{

	struct prod* next;

	long int id;
	double iva;
	double preco;
	char descricao[NUM_CHARS];

	double numCompras;
	double numTotalCompras;

} Produto;

typedef struct{

    Produto *first;

} Lista;

/*Protótipo das funções utilizadas*/

Lista* insertSorted(Lista* head, Produto* i);
void imprimeLista(Lista* head);
void registaCompra(Lista* head, int idComprado);
int getOrdemGrandeza(int n);
double myRound(double valor);

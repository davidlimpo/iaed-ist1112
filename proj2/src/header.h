#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHAVE 5		/* Numero de numeros da chave. */

#define EST_CHAVE 2		/* Numero de estrelas da chave. */

#define NUM_PREMIO 13		/* Numero de premios possiveis. */

#define NUM_PAISES 9		/* Numero maximo de paises. */

#define MAX_APOSTAS 1000000	/* Numero maximo de apostas. */

#define CHAR_ID 7		/* Numero de chars do ID. */



/******************** Defines usados nos algoritmos de ordenacao ********************/

#define key(A) (A)

#define less(A, B) (key(A) < key(B))

#define exch(A, B) { int t = A; A = B; B = t; }

#define compexch(A, B) if (less(B, A)) exch(A, B)



/******************** Variaveis ********************/

double montante;			/* Variavel double que guarda o montante que e dividido pelos premios. */

int numChavePremiada[NUM_CHAVE];	/* Vector que guarda destructivamente os numeros de cada aposta. */

int estChavePremiada[EST_CHAVE];	/* Vector que guarda destructivamente as estrelas de cada aposta. */

int i, j;				/* Variaveis auxiliares em ciclos. */

int pos = 0;				/* Variavel auxiliar usada para saber qual a proxima posicao a ser usada. */

int numApostas;				/* Variavel que guarda quantas apostas vao ser feitas. */

int numPedidosInf;			/* Variavel que guarda quantos pedidos de informacao foram requesitados. */



/******************** Estruturas ********************/

typedef struct{				/* Estrutura que guarda informacao acerca do sorteio */

	int premioId;
	double montantePremio;
	double numVencedores;
	double valPremio;

	}sorteio;

sorteio resultados[NUM_PREMIO];

typedef struct{				/* Estrutura que guarda num vector de 13 posicoes em que cada uma 
					representa o numero do premio o numero de pessoas que ganharam esse premio. */
	int vencedores[NUM_PREMIO];

	}Pais;

Pais contVencedores[NUM_PAISES];	/* Vector do tipo Pais com 9 posicoes, cada uma representa um pais */

typedef struct{				/* Estrutura que guarda o ID da aposta e o respectivo premio*/

	int premio;
	int id;

	}premioID;

premioID vecID[MAX_APOSTAS];		/* Vector que guarda todos os IDs vencedores e os premios respectivos. */



/******************** Funcoes ********************/

void leChave(int numSorteado[], int estSorteado[]);
void leInfPremio();
void inicializaTabela(int mon, sorteio tab[], Pais cont[]);
void leAposta(int numSorteado[], int estSorteado[], sorteio tab[], Pais contador[]);
void cmpChaveSorteada(char pais[], int numSorteado[], int estSorteado[], int num[], int est[], sorteio tab[], Pais contador[], int id);
void actualizaVectorId(int numPrem, int id, premioID vec[]);
void imprimeVectorId(premioID vec[]);
int getOrdemGrandeza(int n);
void actualizaContVencedores(char pais[], Pais cont[], int numPrem);
int devolvePais(char pais[]);
void le_e_imprime_PedidoInf();
void imprimeTabela(sorteio tab[]);
int numPaisesDifVenc(Pais cont[]);
void insertionSort(int a[], int l, int r);
void quicksortID(int l, int r);
int partitionID(int l, int r);

#define NUM_NOME 4			/*Constante com o numero de caracteres do nome de cada pais*/
#define NUM_PAISES 17			/*Constante com o numero de paises da Zona Euro*/
#define NUM_PEDIDO 3			/*Constante com o numero de caracteres necessarios para guardar o 'd '*/

int i, j, aux;				/*Variaveis auxiliares re-utilizaveis*/
float perc_ris, perc_def;		/*Variaveis que guardam os valores das percentagens*/

int pais_ris[NUM_PAISES];		/*Vector que guarda os paises que estao em risco*/
int pais_def[NUM_PAISES];		/*Vector que guarda os paises que estao em default*/	

int cont_ris = 0;			/*Contador que guarda quantos paises estao em risco*/
int cont_def = 0;			/*Contador que guarda quantos paises estao em default*/

int num_pedidos;			/*Variavel que guarda do input o numero de pedidos de informacoes */
char pedido[NUM_PEDIDO];		/*String que guarda o input 'd '*/
char pais_inf[NUM_NOME];		/*String com o pais (na qual foi pedida a informacao) que esta a ser avaliado*/

float copia_divida[NUM_PAISES];		/*Vector que guarda uma copia das dividas dos paises*/

float dividas[NUM_PAISES][NUM_PAISES];	/*Matriz do input das dividas dos paises*/

typedef struct{				/*Estrutura Zona Euro que guarda os paises e os seus dados*/
	char nome[NUM_NOME];		/*String que guarda o nome do pais*/
	float div;			/*Float que guarda o valor da divida do pais*/
	float pib;			/*Float que guarda o valor do PIB do pais*/
	int def;			/*Se estiver a 0, o pais nao esta em Default. Se estiver a 1, esta*/
	}pais;

pais ze[NUM_PAISES];			/*Vector do tipo pais onde sera guardado todo o input relativo à informacao dos paises*/



/*-*-*-*-*- Cabecalhos das funcoes -*-*-*-*-*/
void leInfEco(pais zonaEuro[]);
void leMatriz(float v[][NUM_PAISES]);
void lePedidosDef(int k, char d[], char paisInf[], pais zonaEuro[]);
void imprimeRisco(int numPaisesRisco, pais zonaEuro[]);
void imprimeDefault(int numPaisesDefault, pais zonaEuro[]);
float calculaSituacao(float perc, float pib);
int getPosicao(char a[], pais zonaEuro[]);
void contagio(float matriz[][NUM_PAISES], pais zonaEuro[], float copiaDiv[], int paisPedido);

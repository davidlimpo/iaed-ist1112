#include "header.h"

int main(){

	leInfPremio();			/* Le informacao acerca do premio */
	inicializaTabela(montante, resultados, contVencedores);	/* Inicializa a tabela com os valores correctos */

	while(numApostas != 0){		/* Le todas as apostas */
		leAposta(numChavePremiada, estChavePremiada, resultados, contVencedores);
		numApostas--;
	}

	scanf("%d", &numPedidosInf); 	/* Le o numero de pedidos de informacao */

	imprimeTabela(resultados); 	/* Imprime a tabela com o montante disponivel para cada premio, 
					o numero de vencedores de cada premio e o valor de cada premio 
					consoante o numero de vencedores */

	printf("%d\n", numPaisesDifVenc(contVencedores)); 	/*Imprime o número de paises vencedores*/

	while(numPedidosInf != 0){	/*Imprime p linhas que correspondem aos p pedidos de informação */
		le_e_imprime_PedidoInf();
		numPedidosInf--;
	}

	imprimeVectorId(vecID); 	/*Imprime a lista de vencedores por ordem de premios e IDs*/

	return 0;
}


/* Funcao que recebe como argumento dois vectores de inteiros, onde guarda uma chave (numeros e estrelas).
   Depois, ordena-os. */
void leChave(int numSorteado[], int estSorteado[]){

	for (i = 0; i < NUM_CHAVE; i++)
		scanf("%d", &numSorteado[i]);
	for (i = 0; i < EST_CHAVE; i++)
		scanf("%d", &estSorteado[i]);

	insertionSort(numSorteado, 0, NUM_CHAVE - 1);
	insertionSort(estSorteado, 0, EST_CHAVE - 1);
}

/* Funcao que guarda informacao relativa ao premio: montante disponivel para distribuir e chave premiada.
   Tambem guarda o total de apostas que foram efectuadas. */
void leInfPremio(){

	scanf("%lf", &montante);
	leChave(numChavePremiada, estChavePremiada);
	scanf("%d", &numApostas);
}

/* Funcao que inicializa a tabela dos premios e calcula os valores de cada premio. */

void inicializaTabela(int mon, sorteio tab[], Pais cont[]){
	for(i = 0; i < NUM_PREMIO; i++){
		tab[i].premioId = i+1;
		tab[i].numVencedores = 0;
		tab[i].valPremio = 0;
	}


	tab[0].montantePremio = (32 * mon)/100;
	tab[1].montantePremio = (4.8 * mon)/100;
	tab[2].montantePremio = (1.6 * mon)/100;
	tab[3].montantePremio = (0.8 * mon)/100;
	tab[4].montantePremio = (0.7 * mon)/100;
	tab[5].montantePremio = (0.7 * mon)/100;
	tab[6].montantePremio = (0.5 * mon)/100;
	tab[7].montantePremio = (2.3 * mon)/100;
	tab[8].montantePremio = (2.2 * mon)/100;
	tab[9].montantePremio = (3.7 * mon)/100;
	tab[10].montantePremio = (6.5 * mon)/100;
	tab[11].montantePremio = (17.6 * mon)/100;
	tab[12].montantePremio = (18 * mon)/100;

}

/* Funcao que recebe cada aposta e chama a funcao que vai verificar qual premio que cada chave ganhou. */

void leAposta(int numSorteado[], int estSorteado[], sorteio tab[], Pais contador[]){

	char paisAposta[4];		/* Vector que guarda o pais da aposta que está a ser tratada */
	int codigoAposta;		/* Variavel que guarda o codigo da aposta que está a ser tratada */
	int numAposta[NUM_CHAVE];	/* Vector que guarda os numeros da aposta que está a ser tratada */
	int estAposta[EST_CHAVE];	/* Vector que guarda as estrelas da aposta que está a ser tratada */

	scanf(" %s %d", paisAposta, &codigoAposta);

	leChave(numAposta, estAposta);
	cmpChaveSorteada(paisAposta, numSorteado, estSorteado, numAposta, estAposta, tab, contador, codigoAposta);
}

/* Funcao que verifica qual e o premio de cada uma das apostas. Esta funcao vai chamar a funcao que */

void cmpChaveSorteada(char pais[], int numSorteado[], int estSorteado[], int num[], int est[], sorteio tab[], Pais contador[], int id){

	int estCerto = 0, numCerto = 0, numPremio = 0;

	for(j = 0; j < NUM_CHAVE; j++){
		for(i = 0; (i < NUM_CHAVE) && (num[j] >= numSorteado[i]); i++)
			if(num[j] == numSorteado[i])
				numCerto++;
	}

	for(j = 0; j < EST_CHAVE; j++){
		for(i = 0; (i < EST_CHAVE) && (est[j] >= estSorteado[i]); i++)
			if(est[j] == estSorteado[i])
				estCerto++;
	}

	if(numCerto == 5){
		if(estCerto == 2){
			tab[0].numVencedores += 1;
			numPremio = 0;

		}else if(estCerto == 1){
			tab[1].numVencedores += 1;
			numPremio = 1;

		}else{
			tab[2].numVencedores += 1;
			numPremio = 2;
		}
	}

	if(numCerto == 4){
		if(estCerto == 2){
			tab[3].numVencedores += 1;
			numPremio = 3;

		}else if(estCerto == 1){
			tab[4].numVencedores += 1;
			numPremio = 4;

		}else{
			tab[5].numVencedores += 1;
			numPremio = 5;
		}
	}

	if(numCerto == 3){
		if(estCerto == 2){
			tab[6].numVencedores += 1;
			numPremio = 6;

		}else if(estCerto == 1){
			tab[7].numVencedores += 1;
			numPremio = 7;

		}else{
			tab[9].numVencedores += 1;
			numPremio = 9;
		}
	}

	if(numCerto == 2){
		if(estCerto == 2){
			tab[8].numVencedores += 1;
			numPremio = 8;

		}else if(estCerto == 1){
			tab[11].numVencedores += 1;
			numPremio = 11;

		}else{
			tab[12].numVencedores += 1;
			numPremio = 12;
		}
	}

	if(numCerto == 1)
		if(estCerto == 2){
			tab[10].numVencedores += 1;
			numPremio = 10;
		}


	if(numCerto >= 2 || (numCerto == 1 && estCerto == 2)){		/* Verifica se a chave foi premiada*/
		actualizaContVencedores(pais, contador, numPremio);
		actualizaVectorId(numPremio, id, vecID);
	}
}

/* Funcao que actualiza o vector da estrutura que guarda o premio e o respectivo ID das apostas. */

void actualizaVectorId(int numPrem, int id, premioID vec[]){

	vec[pos].id = id;
	vec[pos].premio = numPrem;
	pos++;

}

/* Funcao que imprime a lista de vencedores por ordem de premios e IDs. */

void imprimeVectorId(premioID vec[]){

	quicksortID(0, pos-1);

	for( j = 0; j < NUM_PREMIO; j++)
	   for( i = 0; i < pos; i ++)
		if(vec[i].premio == j){
			if(getOrdemGrandeza(vec[i].id) == 0)
				printf("00000%d\n", vec[i].id);
			else if(getOrdemGrandeza(vec[i].id) == 1)
				printf("0000%d\n", vec[i].id);
			else if(getOrdemGrandeza(vec[i].id) == 2)
				printf("000%d\n", vec[i].id);
			else if(getOrdemGrandeza(vec[i].id) == 3)
				printf("00%d\n", vec[i].id);
			else if(getOrdemGrandeza(vec[i].id) == 4)
				printf("0%d\n", vec[i].id);
			else
				printf("%d\n", vec[i].id);
		}
}

/* Funcao que ve calcula a grandeza do ID para sabermos quantos zeros sao necessarios acrescentar a esquerda no output. */

int getOrdemGrandeza(int n){
	if((n / 10) == 0) return 0; 		/* 5 zeros*/
	else if((n / 100) == 0) return 1; 	/* 4 zeros*/
	else if((n / 1000) == 0) return 2; 	/* 3 zeros*/
	else if((n / 10000) == 0) return 3; 	/* 2 zeros*/
	else if((n / 100000) == 0) return 4; 	/* 1 zeros*/
	else return 5; 				/* 0 zeros*/

}

/* Funcao que actualiza o contador de cada premio na matriz paises-premios. */

void actualizaContVencedores(char pais[], Pais cont[], int numPrem){

	cont[devolvePais(pais)].vencedores[numPrem] += 1;
}

/* Funcao que devolve qual o pais fez a aposta. */

int devolvePais(char pais[]){

	if(strcmp(pais, "AUT") == 0)
		return 0;

	else if(strcmp(pais, "BEL") == 0)
		return 1;

	else if(strcmp(pais, "ESP") == 0)
		return 2;

	else if(strcmp(pais, "FRA") == 0)
		return 3;

	else if(strcmp(pais, "IRL") == 0)
		return 4;

	else if(strcmp(pais, "LUX") == 0)
		return 5;

	else if(strcmp(pais, "POR") == 0)
		return 6;

	else if(strcmp(pais, "GBR") == 0)
		return 7;
	else 
		return 8;
}

/* Funcao que le e imprime a tabela com o numero de vencedores, o montante de cada premio e o valor que cada aposta premiada ganhou. */

void imprimeTabela(sorteio tab[]){

	for(i = 0; i < NUM_PREMIO; i++){
		if(tab[i].numVencedores != 0)		
			tab[i].valPremio = (tab[i].montantePremio / tab[i].numVencedores);
		printf("%d %.2f %.0f %.2f\n", tab[i].premioId, tab[i].montantePremio, tab[i].numVencedores, tab[i].valPremio);
	}
	
}

/* Funcao que imprime o output dos pedidos de informacao. */

void le_e_imprime_PedidoInf(){
	char p;
	char paisPedido[4];
	scanf(" %c %s", &p, paisPedido);

	for(i = 0; i < NUM_PREMIO; i++){
		printf("%d", contVencedores[devolvePais(paisPedido)].vencedores[i]);
		if(i != (NUM_PREMIO-1))		/*É preciso para nao imprimir um espaço no final */
			printf(" ");		/* e ficar diferente do output esperado */
	}
	printf("\n");

}

/* Funcao que actualiza o numero de paises diferentes que realizaram uma aposta. */

int numPaisesDifVenc(Pais cont[]){

	int numPaisesDif = 0;

	for(j = 0; j < NUM_PAISES; j++){
		for(i = 0; i < NUM_PREMIO; i++){
			if(cont[j].vencedores[i] != 0){
				numPaisesDif++;
				break;
			}
		}
	}

	return numPaisesDif;
}



/******************** Algoritmos de ordenaçao ********************/

/* Algoritmo InsertionSort */
void insertionSort(int a[], int l, int r){
	int i;
	for (i = l+1; i <= r; i++) 	/* Coloca menor na posição l */
		compexch(a[l], a[i]);
	for (i = l+2; i <= r; i++) {
		int j = i;
		int v = a[i];
		while (less(v, a[j-1])) {
			a[j] = a[j-1];
			j--;
		}
		a[j] = v;
	}
}

/* Algoritmo QuickSort adaptado ao tipo PremioID */
void quicksortID(int l, int r){
	int i;
	if (r <= l)
		return;
	i = partitionID(l, r);
	quicksortID(l, i-1);
	quicksortID(i+1, r);
}

int partitionID(int l, int r) {
	int i = l-1;
	int j = r;
	int v = vecID[r].id;

	while (i < j) {
		while (less(vecID[++i].id, v));
		while (less(v, vecID[--j].id))
			if (j == l)
				break;
			if (i < j){
				exch(vecID[i].id, vecID[j].id);
				exch(vecID[i].premio, vecID[j].premio);
			}
	}

	exch(vecID[i].id, vecID[r].id);
	exch(vecID[i].premio, vecID[r].premio);
	return i;
}

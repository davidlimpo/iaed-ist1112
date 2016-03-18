#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(){

	scanf("%f", &perc_ris);		/*Le a percentagem do PIB para um pais entrar em Risco de ser Intervencionado*/
	scanf("%f", &perc_def);		/*Le a percentagem do PIB para um pais entrar em Default*/

	leInfEco(ze);
	leMatriz(dividas); 					/*Le a matriz de input*/

	scanf("%d", &num_pedidos);				/*Le o numero de pedidos de informacao*/

	imprimeRisco(cont_ris, ze);				/*Imprime o numero e os paises em risco*/
	imprimeDefault(cont_def, ze);				/*Imprime o numero e os paises em default*/
	lePedidosDef(num_pedidos, pedido, pais_inf, ze); 	/*Le os pedidos de informacao e imprime o resultado do efeito contagio*/

	return 0;
}


/*Funcao que recebe como argumento um vector do tipo pais, onde guarda o input relativo à informacao economica: nome, divida e pib.
  Tambem e calculado quais e quantos paises estao em risco de intervencao e em default.*/
void leInfEco(pais zonaEuro[]){

	for(i = 0; i < NUM_PAISES; i++){			
	        scanf(" %s %f %f", zonaEuro[i].nome, &(zonaEuro[i].div), &(zonaEuro[i].pib));

		if(zonaEuro[i].div >= calculaSituacao(perc_ris, zonaEuro[i].pib)){		 

			if(zonaEuro[i].div >= calculaSituacao(perc_def, zonaEuro[i].pib)){	
				pais_def[cont_def] = i;				
				cont_def++;
			}
			else {
				pais_ris[cont_ris] = i;				
				cont_ris++;
			}
		}
	}
}

/*Funcao que recebe a matriz das dividas e que vai guardar os valores da matriz do input nas suas respectivas posicoes*/
void leMatriz(float v[][NUM_PAISES]){		

	for(i = 0; i < NUM_PAISES; i++){				
		for(j = 0; j < NUM_PAISES; j++){
			scanf("%f ", &(v[i][j]));
		}
	}
}

/*Funcao que recebe o inteiro com o numero de 'pedidos' de default, tres vectores, dois de chars e um do tipo pais.
  Depois de saber qual é o pais pedido, chama a funcao que calcula as consequencias desse mesmo pais ter entrado em default*/
void lePedidosDef(int k, char d[], char paisInf[], pais zonaEuro[]){

	i = 0;

	for(; k != 0; k--){
		scanf("%s%s", d, paisInf);                                      
		d[2] = '\0';
		paisInf[3] = '\0';

		contagio(dividas, ze, copia_divida, getPosicao(paisInf, zonaEuro)); 

		i++;
	}
}

/*Funcao que recebe um inteiro (contador do nº de paises em risco) e um vector do tipo pais. 
  Imprime o contador recebido e os paises em risco de intervencao*/
void imprimeRisco(int numPaisesRisco, pais zonaEuro[]){
                                                               
    printf("%d", numPaisesRisco);                               

	for(i = 0; i < numPaisesRisco; i++){                    
		printf(" %s", zonaEuro[pais_ris[i]].nome);              
	}
	printf("\n");
}

/*Funcao que recebe um inteiro (contador do nº de paises em default) e um vector do tipo pais. 
  Imprime o contador recebido e os paises em default*/
void imprimeDefault(int numPaisesDefault, pais zonaEuro[]){
	printf("%d", numPaisesDefault);                             

	for(i = 0; i < numPaisesDefault; i++){                       
		printf(" %s", zonaEuro[pais_def[i]].nome);              
	}
	printf("\n");
}

/*Funcao que calcula a situacao do pais. Ou seja, multiplica o PIB de um pais com uma 
  percentagem (risco ou default), para mais tarde ser comparada com a sua divida a fim 
  de saber se um pais esta em risco ou em default */
float calculaSituacao(float perc, float pib){
                                                            		
	return (perc*pib);						

}

/*Funcao que recebe dois vectores, um de chars (contendo um pais) e um do tipo pais.
  Devolve qual e a posicao do pais recebido */
int getPosicao(char a[], pais zonaEuro[]){

	for(j = 0; j < NUM_PAISES; j++){			
		if(strcmp(a, zonaEuro[j].nome) == 0)		
			aux = j;
	}
	return aux;
}

/*Funcao que recebe uma matriz, dois vectores, um do tipo pais, o outro para onde vai copiar a divida
 dos paises para nao perdermos a informacao previamente recebida e o pais de que foi pedida a informacao.
 Depois de calcular o efeito de contagio provocado pelos paises que ficam em default, imprime o numero total 
 dos que ficaram em risco e dos que entraram em default. */
void contagio(float matriz[][NUM_PAISES], pais zonaEuro[], float copiaDiv[], int paisPedido){	

		cont_def = 0; 									
		cont_ris = 0;									
		for(i = 0; i <	NUM_PAISES; i++){
			copiaDiv[i] = zonaEuro[i].div;		
			copiaDiv[i] += matriz[paisPedido][i];	
			zonaEuro[i].def = 0;			
		}
		zonaEuro[paisPedido].def = 1;			

		for(i = 0; i < NUM_PAISES; i++){
			if(zonaEuro[i].def == 0){						

				if(copiaDiv[i] >= calculaSituacao(perc_def, zonaEuro[i].pib)){	
					for(j = 0; j < NUM_PAISES; j++)
						copiaDiv[j] += matriz[i][j];			
					zonaEuro[i].def = 1;					
					i = -1;							
				}
			}
		}

		for(i = 0; i < NUM_PAISES; i++){

			if((copiaDiv[i] >= calculaSituacao(perc_ris, zonaEuro[i].pib)) && (zonaEuro[i].def != 1)) 
				cont_ris++;									  
			if(zonaEuro[i].def == 1)								  
				cont_def++;									  
		}
		printf("%d %d\n", cont_ris, cont_def);								  
}

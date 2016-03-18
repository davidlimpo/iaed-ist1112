#include "header.h"


int main(){

	Lista* lista;
	Produto *novo;
	long int prodComprado;
	int ordem;


	lista=(Lista*) malloc(sizeof(Lista));	/* Reserva memoria para a head da lista */

	/*Cria um novo produto, copia uma linha de informação para dentro do 
	 * novo produto e insere o produto de forma ordenada numa lista */
	while((c = getchar()) == 'p'){		
		i = 0;
		novo=(Produto*) malloc(sizeof(Produto));  /* Reserva memoria para um novo produto */

		novo->numCompras = 0;
		novo->numTotalCompras = 0;
		
		scanf(" %ld %lf %lf ", &novo->id, &novo->preco, &novo->iva);
		while((c = getchar()) != '\n'){
			novo->descricao[i] = c;
			i++;
		}
		novo->descricao[i] = '\0';

		lista = insertSorted(lista, novo);

	}
	

	while(( c == 'c')){
	getchar();									/* le o \n */
	
		while((c = getchar()) != 't'){			/*Lê e guarda os carrinhos*/
			scanf("%ld", &prodComprado);
			getchar(); 							/* le o \n */


			/*Rearranja o ID, visto que o primeiro algarismo foi "consumido" 
			 * pelo getchar que esta na condiçao do while */
			prodComprado += (c-48) * 1000000000;
			
			registaCompra(lista, prodComprado);
	
		}
		
		getchar(); 								/* le o \n */
		c = getchar();
		
		imprimeLista(lista);			/*Imprime a lista ordenada com todos produtos*/
		valorCarrinho = 0;
	}
	
	printf("%d\n%.2f\n", numCarrinhos, valorTotal);		/*Imprime o número de carrinhos e o valor total das compras*/
	
	if(numCarrinhos > 0){

		ordem = getOrdemGrandeza(IdProdMaisComprado);	/*Coloca os devidos 0's à esquerda consoante a ordem de grandeza*/


		if(ordem == 9)
			printf("000000000%ld\n", IdProdMaisComprado);

		else if(ordem == 8)
			printf("00000000%ld\n", IdProdMaisComprado);

		else if(ordem == 7)
			printf("0000000%ld\n", IdProdMaisComprado);

		else if(ordem == 6)
			printf("000000%ld\n", IdProdMaisComprado);

		else if(ordem == 5)
			printf("00000%ld\n", IdProdMaisComprado);

		else if(ordem == 4)
			printf("0000%ld\n", IdProdMaisComprado);

		else if(ordem == 3)
			printf("000%ld\n", IdProdMaisComprado);

		else if(ordem == 2)
			printf("00%ld\n", IdProdMaisComprado);

		else if(ordem == 1)
			printf("0%ld\n", IdProdMaisComprado);

		else
			printf("%ld\n", IdProdMaisComprado);
	}



	return 0;
}

/*Função que recebe uma lista e um Id de um Produto.
 * Actualiza os contadores responsaveis pelo numero 
 * de vezes que o produto foi comprado. */
void registaCompra(Lista* head, int idComprado){
							
	Produto *aux;					
	aux = head->first;				
	
	while(aux != NULL){

		if(aux->id == idComprado){
			aux->numCompras += 1;
			aux->numTotalCompras += 1;
			break;
		}
		aux = aux->next;
	}	
}

/*Função que recebe e imprime a lista de acordo com o output esperado*/
void imprimeLista(Lista* head){

	int ordemGrandeza;
	Produto *aux;	
	
	aux = head->first;


	while(aux != NULL){
		
		/* Actualiza variavel com o Id do produto mais comprado
		 * e com o num de vezes que o mesmo foi comprado */
		if(numComprasProdMaisComprado <= aux->numTotalCompras){
			if(numComprasProdMaisComprado == aux->numTotalCompras && IdProdMaisComprado < aux->id){}
			else{
				numComprasProdMaisComprado = aux->numTotalCompras;
				IdProdMaisComprado = aux->id;
			}
		}
		
		if(aux->numCompras > 0){

			ordemGrandeza = getOrdemGrandeza(aux->id);
			
			valorCarrinho += (myRound((aux->preco*aux->iva)+aux->preco)*aux->numCompras);


			if(ordemGrandeza == 9)
				printf("%.0f%% 000000000%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 8)
				printf("%.0f%% 00000000%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 7)
				printf("%.0f%% 0000000%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 6)
				printf("%.0f%% 000000%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 5)
				printf("%.0f%% 00000%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 4)
				printf("%.0f%% 0000%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 3)
				printf("%.0f%% 000%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 2)
				printf("%.0f%% 00%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else if(ordemGrandeza == 1)
				printf("%.0f%% 0%ld %s\n", aux->iva*100, aux->id, aux->descricao);

			else
				printf("%.0f%% %ld %s\n", aux->iva*100, aux->id, aux->descricao);


			printf("%.0f x %.2f %.2f\n", aux->numCompras, myRound((aux->preco*aux->iva)+aux->preco), 
										 (myRound((aux->preco*aux->iva)+aux->preco)*aux->numCompras));
										 
			aux->numCompras = 0;		/* Actualiza contador */
										 
		}
		aux = aux->next;
	}
	
	printf("%.2f\n", valorCarrinho);
	numCarrinhos += 1;
	valorTotal += valorCarrinho;
}
	

/* Função que recebe uma lista e um prodruto.
 * Introduz o Produto de forma ordenada (por IVA depois por ID) na lista */
Lista* insertSorted(Lista* head, Produto* i){

	Produto *aux;
	aux = head->first;

	/* Caso a lista esteja vazia */
	if(aux == NULL){

		head->first = i;
		i->next = NULL;

		return head;

	}else{
			while(aux->next != NULL){

				if(i->iva <= aux->next->iva){

					/* Caso seja para inserir no inicio */
					if(aux->iva > i->iva){
						i->next = head->first;
						head->first = i;
						return head;
					}
					
					/* Caso seja para inserir no inicio */
					if((aux->id > i->id) && (aux->iva == i->iva)){
						i->next = head->first;
						head->first = i;
						return head;
					}
					
					/* Caso seja para inserir a meio */
					if((i->id < aux->next->id) || (aux->next->iva > i->iva)){
						i->next = aux->next;
						aux->next = i;
						return head;						
					}
				}
				aux = aux->next;
			}

		/* Caso haja so um elemento na lista e seja depois de i */
		if(i->iva < aux->iva){
			i->next = aux;
			head->first = i;
			return head;
		}
		else{
			aux->next = i;
			i->next = NULL;
			return head;
		}
	}
}


/* Funcao que calcula a grandeza do ID para sabermos quantos zeros sao necessarios acrescentar a esquerda. */
int getOrdemGrandeza(int n){
	
	if((n / 10) == 0) return 9; 				/* 9 zeros*/
	else if((n / 100) == 0) return 8; 			/* 8 zeros*/
	else if((n / 1000) == 0) return 7; 			/* 7 zeros*/
	else if((n / 10000) == 0) return 6; 		/* 6 zeros*/
	else if((n / 100000) == 0) return 5;	 	/* 5 zeros*/
	else if((n / 1000000) == 0) return 4; 		/* 4 zeros*/
	else if((n / 10000000) == 0) return 3;	 	/* 3 zeros*/
	else if((n / 100000000) == 0) return 2; 	/* 2 zeros*/
	else if((n / 1000000000) == 0) return 1; 	/* 1 zeros*/
	else return 0; 								/* 0 zeros*/

}

/*Função que arredonda um valor aos centimos */
double myRound(double valor) {
	return floor(valor*100.0+0.5001)/100.0;
}

#include <stdio.h>
#include <stdlib.h>


/* 
*	Estrutura que define os parametros de um nó na àrvore binária 
*/
typedef struct node{
	int nh; 		 /* valor do 'next-hop' */
	struct node *lc; /* ponteiro para filho esquerdo */
	struct node *rc; /* ponteiro para filho direito */
} Node;


/* 
*	Estrutura que define uma linha da tabela de endereçamento 
*/
typedef struct line{
	char pref[9]; /* Tamanho máximo do prefixo : 8 bits + '/0' */
	int nh; /* next hop */
} Line;


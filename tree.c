                                                                                                                                                                  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

/*
* Cria e retorna um novo Node
*/
Node * NodeNew(){
	Node *new = (Node *) malloc(sizeof(Node));
	new->nh = -1;
	new->lc = NULL;
 	new->rc = NULL;
	
	return new;
}

/*
* Cria a árvore a partir da tabela de expedição
*/

void TreeInsert(Node * root, Line l){
	int i;
	Node *p = root;

	for(i = 0; i < strlen(l.pref); i++){
		if(l.pref[i] == '0'){
			if(p->lc == NULL){
				p->lc = NodeNew();
			}
			p = p->lc;
		}
		else{
			if(p->rc == NULL){
				p->rc = NodeNew();
			}
			p = p->rc;
		}
	}
	p->nh = l.nh;
	return;
}

/*
* Balanceia a árvore e propaga o nh até às folhas
*/

void TreeBalance(Node * root){
	
	if(root == NULL) return;
	if(root->lc != NULL){
		if(root->rc != NULL){
			if(root->lc->nh == -1) root->lc->nh = root->nh;
			if(root->rc->nh == -1) root->rc->nh = root->nh;
		}
		else{
			root->rc = NodeNew();
			root->rc->nh = root->nh;
		}
	}
	else{
		if(root->rc != NULL){
			root->lc = NodeNew();
			root->lc->nh = root->nh;
		}
	}

	TreeBalance(root->lc);
	TreeBalance(root->rc);

	return;
}

/*
* Balanceia a árvore. pressupõe que todos os nós têm nh 
*/

void TreeBalance2(Node * root){
	
	if(root == NULL) return;
	if(root->lc != NULL && root->rc == NULL){
		root->rc = NodeNew();
		root->rc->nh = root->nh;
	}
	else if(root->lc == NULL && root->rc != NULL){
		root->lc = NodeNew();
		root->lc->nh = root->nh;
	}

	TreeBalance(root->lc);
	TreeBalance(root->rc);

	return;
}

/*
* Comprime uma árvore balanceada
*/

void TreeCompress2(Node * root, Node * p){
	
	if(root == NULL) return;
	if(root->lc != NULL && root->lc->nh == -1)
		root->lc->nh = root->nh;
	if(root->rc != NULL && root->rc->nh == -1) 
		root->rc->nh = root->nh;

	TreeCompress2(root->lc, root);
	TreeCompress2(root->rc, root);

	if ( (root->lc != NULL) || (root->rc != NULL))
		return;

	if(root->nh == p->nh){
		printf("apaguei root->nh:%d\n",root->nh);
		if(root == p->lc)
			p->lc = NULL;
		else p->rc = NULL;
		free(root);
	}

	return;
}

/*
*Comprime e balanceia a árvore simultâneamente
*/

void TreeCompressBalance(Node * root, Node * p){
	
	if(root == NULL) return;
	if(root->lc != NULL && root->lc->nh == -1)
		root->lc->nh = root->nh;
	if(root->rc != NULL && root->rc->nh == -1) 
		root->rc->nh = root->nh;

	TreeCompressBalance(root->lc, root);
	TreeCompressBalance(root->rc, root);

	if ( (root->lc != NULL) && (root->rc != NULL))
		return;

	if(root->lc != NULL && root->rc == NULL){
		root->rc = NodeNew();
		root->rc->nh = root->nh;
	}
	else if(root->lc == NULL && root->rc != NULL){
		root->lc = NodeNew();
		root->lc->nh = root->nh;
	}

	else if(root->nh == p->nh){
		printf("apaguei root->nh:%d\n",root->nh);
		if(root == p->lc)
			p->lc = NULL;
		else p->rc = NULL;
		free(root);
	}

	return;
}

/*
*Imprime a tabela de expedição
*/
void TablePrint(Node * root, Node * p, char * str, int * index){
	
	if(root == NULL){
		(*index)--;		
		return;
	}

	if(p == NULL) printf("* -> %d\n", root->nh);

	else if(p->nh != root->nh){
		str[*index] = '\0';
		printf("%s -> %d\n", str, root->nh);
	}

	str[*index] = '0';
	++(*index);
	TablePrint(root->lc, root, str, index);

	str[*index] = '1';
	++(*index);
	TablePrint(root->rc, root, str, index);

	(*index)--;	
	
	return;
}


/*
*Devolve o nh dado um endereço de 8 bits
*/

int TreeNextHop(Node * root, char pref[9]){
	
	int i;
	Node * p = root;

	for(i = 0; i < 9; i++){
		if(p->lc == NULL) return p->nh; /*como a árvore está balanceada não é preciso verificar a existência dos dois filhos */
		if(pref[i] == '0'){			
			p = p->lc;
		}
		else p = p->rc;
	}

	return p->nh; 
}

int i = 0;

/*
* Imprime a árvore
*/

void Preorder(Node * root){
	
	if (root != NULL){
		printf("Index: %d ; NH: %d\n", i++, root->nh);
		Preorder(root->lc);
		Preorder(root->rc);
	}
	return;
}

/*void TreeCompress(Node * root, Node * p){  p - parent de root 
	if (root != NULL){
		TreeCompress(root->lc,root);
		TreeCompress(root->rc,root);

		if ( (root->lc != NULL) || (root->rc != NULL))
			return;

		if(root->nh == p->nh)
			free(root);
			printf("apaguei root->nh:%d\n",root->nh);
	}

	return;
}
*/


int main(){
	Node * root = NodeNew();
	
	/*Line linha1 = {"00",2};
	Line linha2 = {"10",2};
	Line linha3 = {"11",4};
	Line linha4 = {"110",4};
	Line linha5 = {"1101101",4};
	Line linha5 = {"*", 10};*/

	Line linha1 = {"0",1};
	Line linha2 = {"000",2};
	Line linha3 = {"01",1};
	Line linha4 = {"10",3};
	Line linha5 = {"110",4};
	Line linha6 = {"11010", 4};
	Line linha7 = {"11011",3};

	char pref[9];
	char string[9];

	int index = 0;

	root->nh = -2;
	
	TreeInsert(root,linha1);
	TreeInsert(root,linha2);
	TreeInsert(root,linha3);
	TreeInsert(root,linha4);
	TreeInsert(root,linha5);
	TreeInsert(root,linha6);
	TreeInsert(root,linha7);

	printf("árvore antes\n");
	Preorder(root);

	printf("tabela original\n");
	TablePrint(root, NULL, &string[0], &index);

	/*i = 0;
	printf("árvore depois\n");
	TreeBalance(root);
	Preorder(root);
	

	i = 0;
	printf("árvore depois comprimida\n");
	TreeCompress2(root,NULL);
	Preorder(root);

	i = 0;
	printf("árvore depois comprimida e balanceada\n");
	TreeBalance2(root);
	Preorder(root);
*/
	i = 0;
	printf("árvore depois comprimida e balanceada\n");
	TreeCompressBalance(root, NULL);
	Preorder(root);

	index = 0;
	printf("tabela comprimida\n");
	TablePrint(root, NULL, &string[0], &index);

	while(1){
		printf("Inserir prefixo: ");
		scanf("%s", pref);
		printf("Pref: %s ; Next Hop: %d\n", pref, TreeNextHop(root, pref));
	}
	return 0;
}

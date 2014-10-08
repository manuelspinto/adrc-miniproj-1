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

void Preorder(Node * root){
	
	if (root != NULL){
		printf("Index: %d ; NH: %d\n", i++, root->nh);
		Preorder(root->lc);
		Preorder(root->rc);
	}
	return;
}


int main(){
	Node * root = NodeNew();

	Line linha1 = {"01",1};
	Line linha2 = {"10",2};
	Line linha3 = {"11",3};
	Line linha4 = {"110",4};
	/*Line linha5 = {"*", 10};*/

	char pref[9];

	root->nh = 10;
	
	TreeInsert(root,linha1);
	TreeInsert(root,linha2);
	TreeInsert(root,linha3);
	TreeInsert(root,linha4);
	
	printf("árvore antes\n");
	Preorder(root);

	i = 0;
	printf("árvore depois\n");
	TreeBalance(root);
	Preorder(root);

	while(1){
		printf("Inserir prefixo: ");
		scanf("%s", pref);
		printf("Pref: %s ; Next Hop: %d\n", pref, TreeNextHop(root, pref));
	}
	return 0;
}

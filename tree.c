                                                                                                                                                                  #include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#include "tree.h"

/*
* Cria e retorna um novo Nó
*/
Node * NodeNew(){
	Node *new = (Node *) malloc(sizeof(Node));
	new->nh = -1;
	new->lc = NULL;
 	new->rc = NULL;
	
	return new;
}

/*
* Insere um novo nó na àrvore binária a partir de um elemento do tipo linha
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
*	Comprime e balanceia a árvore simultâneamente
*/

void TreeCompressBalance(Node * root, Node * p){
	

	/* Conjunto de operações responsáveis por propagar na àrvore */
	if(root == NULL) return;
	if(root->lc != NULL && root->lc->nh == -1)
		root->lc->nh = root->nh;
	if(root->rc != NULL && root->rc->nh == -1) 
		root->rc->nh = root->nh;

	TreeCompressBalance(root->lc, root);
	TreeCompressBalance(root->rc, root);


	/* Conjunto de operações de balanceamento */
	if(root->lc != NULL && root->rc == NULL){
		root->rc = NodeNew();
		root->rc->nh = root->nh;
	}
	else if(root->lc == NULL && root->rc != NULL){
		root->lc = NodeNew();
		root->lc->nh = root->nh;
	}


	/* Conjunto de operações com vista a eliminar a redundãncia permitindo comprimir a árvore */
	else if((root->lc == NULL) && (root->rc == NULL) && (root->nh == p->nh)){
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

	if(p == NULL){
	 	if(root->nh != -1) printf("* -> %d\n", root->nh);
	}
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
*Devolve o nh dado um endereço de 8 bits para uma árvore balanceada
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

/*
* Liberta a memória associada a estrutura de dados da árvore binária
*/

void TreeClean(Node * root){
	
	if (root == NULL)
		return;
	TreeClean(root->lc);
	TreeClean(root->rc);
	
	free(root);
}

/* Constroi árvore a partir de um ficheiro que contem a tabela de expedição no formato:
*
*		[prefixo][TAB][Next-Hop]
*/

void TreeBuild(Node *root, char *fname){
	FILE *fp;
	char buff[128];
	char pref[9];
	int nh;
	Line linha;

	fp = fopen(fname,"r");
	if(fp == NULL){
		printf("ERROR: Impossivel abrir o ficheiro '%s'\n",fname);
		exit(1);
	}

	while (fgets(buff, sizeof(buff), fp) != NULL ){
    	sscanf(buff,"%s\t%d",pref,&nh);
    	if(strcmp(pref,"*") == 0)	
    		root->nh = nh;
    	else{
    		strcpy(linha.pref, pref);
			linha.nh = nh;
			TreeInsert(root,linha);
    	}
    }
    fclose(fp);
    return;
}


int main(int argc, char * argv[]){
	Node * root = NodeNew();

	char pref[9];
	char string[9];

	int index = 0;
	int tnh;

	if(argc != 2){
		printf("./add2nh forwarding_table_file\n");
		exit(0);
	}

	TreeBuild(root,argv[1]);
	TreeCompressBalance(root, NULL);

	index = 0;
	printf("Tabela comprimida:\n\n");
	TablePrint(root, NULL, &string[0], &index);
	printf("\n");

	while(1){
		printf("Inserir endereço (8 bits): ");
		scanf("%s", pref);
		if(strcmp(pref,"exit") == 0){
			TreeClean(root);
			exit(0);
		}
		tnh = TreeNextHop(root, pref);
		if(tnh != -1)	
			printf("Endereço: '%s' ; Next Hop: '%d'\n", pref, tnh);
		else
			printf("Endereço: '%s' ; DROP\n", pref);

	}
	return 0;
}

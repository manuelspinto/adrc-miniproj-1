#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int nh; 
	struct node *lc;
	struct node *rc;
} Node;

typedef struct line{
	char pref[9]; /* Tamanho máximo do prefixo : 8 bits + '/0' */
	int nh; /* next hop */
} Line;


#include <stdlib.h>
#include <stdio.h>
#include <set.h> 
#include <queue>
#include <algorithm>
#include <time.h>

/* L = 0, D = 1, R = 2, U = 3 */

using namespace std;

bool moveTile(puzzle *p, int dir){

	switch(dir){
		case 0:
			if(p->col - 1 >= 0){
				p->sets[p->row][p->col] = p->sets[p->row][p->col - 1];
				p->sets[p->row][p->col - 1] = 0;
				p->col = p->col-1;
				return true;
			}
			break;
		case 1:
			if(p->row + 1 <= 3){
				p->sets[p->row][p->col] = p->sets[p->row+1][p->col];
				p->sets[p->row+1][p->col] = 0;
				p->row = p->row+1;
				return true;
			}
			break;
		case 2:
			if(p->col + 1 <= 3){
				p->sets[p->row][p->col] = p->sets[p->row][p->col + 1];
				p->sets[p->row][p->col + 1] = 0;
				p->col = p->col+1;
				return true;
			}
			break;
		case 3:
			if(p->row - 1 >= 0){
				p->sets[p->row][p->col] = p->sets[p->row - 1][p->col];
				p->sets[p->row - 1][p->col] = 0;
				p->row = p->row-1;
				return true;
			}
			break;
	}

	return false;
}

/* Calcula o custo heuristico: número de peças fora do lugar ideal */
int heuristicCost(puzzle p){
	int cost = 0;
	
	for (int i = 0; i < 4; i++){
		for(int j = 0; j < 4;j++){
			if(p.sets[i][j] != ((i*4)+j+1)) cost++;
		}
	}

	return cost-1;
}

/* Realiza todos os próximos passos */
void nextStates(puzzle p,puzzle states[4],int gn){
	if(p.col-1 >= 0){
		states[0] = p;
		states[0].di = 'L'; /* Salvando movimento tomado */
		moveTile(&states[0],0);
	}else states[0].fn = -1; /* Não pode ir nessa direção */

	if(p.row+1 <= 3){
		states[1] = p;
		states[1].di = 'D'; /* Salvando movimento tomado */
		moveTile(&states[1],1);
	}else states[1].fn = -1; /* Não pode ir nessa direção */

	if(p.col+1 <= 3){
		states[2] = p;
		states[2].di = 'R'; /* Salvando movimento tomado */
		moveTile(&states[2],2);
	}else states[2].fn = -1; /* Não pode ir nessa direção */

	if(p.row-1 >= 0){
		states[3] = p;
		states[3].di = 'U'; /* Salvando movimento tomado */
		moveTile(&states[3],3);
	}else states[3].fn = -1; /* Não pode ir nessa direção */
}

bool starSearch(puzzle p){
	int gn = 0; /* Função g(n) número de passos */
	priority_queue<puzzle> q = priority_queue<puzzle>(); /* Fila de priodridades de estados */
	puzzle states[4]; /* Os quatro possiveis estados novos */

	/* Empilhando primeiro estado */
	q.push(p);
	char sol[51] = {'\0'};

	/* Backtracking iterativo */
	while(!q.empty()){
		p = q.top(); /* Pegando o melhor caminho */
		q.pop();
		
		sol[gn] = p.di;
		
		if(gn >= 50) return false; /* Excedeu o limite de passos */	
		
		int hn = heuristicCost(p); /* Calculando o custo */
		if(!hn){
			for(int i = 1; i <= gn; i++) printf("%c", sol[i]);
			return true; /* Nenhum número fora da ordem */
		}

		p.fn = gn + hn; /* Função f(n) */
		
		gn++;

		nextStates(p,states,gn); /* Simula todos os próximos passos */
		for(int i = 0 ; i < 4 ; i++){
			if(states[i].fn != -1){
				states[i].fn = gn + heuristicCost(states[i]);
				q.push(states[i]);
			}
		}
	}
	return false;
}

int main(int argc, char const *argv[]){
	int N;
	puzzle p;

	/* N sets de puzzle */
	scanf("%d",&N);
	
	/* Lendo 4*N sets */
	for(int i = 0; i < N; i++){	
		for (int j = 0; j < 4 ; j++){
			for (int k = 0; k < 4; k++){
				/* Lendo número do piso perdido */
				scanf("%d",&p.sets[j][k]);
				
				/* Piso perdido */					
				if(p.sets[j][k] == 0){
					p.row = j;
					p.col = k;
				}
			}			
		}
		/* Calculando tempo de execução para cada busca */
		clock_t begin = clock();
		if(!starSearch(p)) printf("This puzzle is not solvable.");
		clock_t end = clock();
		
		double time = (double)(end - begin) / CLOCKS_PER_SEC;
		
		printf(" || Tempo de execução: %.4lf ||\n", time);	
	}

	return 0;
}
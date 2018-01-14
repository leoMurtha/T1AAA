#include <stdlib.h>
#include <stdio.h>
#include <set.h> 
#include <algorithm>

/* L = 0, D = 1, R = 2, U = 3 */

// verifica se a o quebra cabeça foi resolvido
bool isSolved(puzzle *p){

	for(int i=0; i< 15 ; i++)
		if(p->sets[(i/4)][i%4] != (i+1))
			return false;

	return true;			
}

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

bool search(puzzle *p,int dir,int stepNum){

	printf("%d\n",stepNum);

	if(stepNum > 50) // se estourar o numero de passos retorna insucesso
		return false;

	if(isSolved(p)){  // se o quebra cabeça foi resolvido retorna sucesso
		p->solution[stepNum] = '\0';
		return true;
	}	

	printf("AKKIII");

	if(!moveTile(p,dir)) // se nao conseguir mover o tile retorna insucesso
		return false;   // <<<<<<<<<<<<< ERRO AKI <<< TA RETORNANDO LOGO NO INCIO PQ N DA PRA MOVER <<<<<<<<< RESOLVER!
 	

	bool success = false; 
	for(int i = (dir + 1)%4; (i != dir) && !success; i = (i + 1)%4) // testas todas as possiveis direcoes
		success = search(p,i,stepNum + 1);

	if(success){
		p->solution[stepNum] = dir;// armazenar direcao	
	}else{
		moveTile(p,(dir+2)%4); // move o piso dvolta
	}

	return success;
}


int main(int argc, char const *argv[]){
	int N;
	puzzle *p = (puzzle*)malloc(sizeof(puzzle));

	/* N sets de puzzle */
	scanf("%d",&N);

	/* Lendo 4*N sets */
	for(int i = 0; i < N; i++){	
		for (int j = 0; j < 4 ; j++){
			for (int k = 0; k < 4; k++){
				/* Lendo número do piso perdido */
				scanf("%d",&p->sets[j][k]);
				
				/* Piso perdido */					
				if(p->sets[j][k] == 0){
					p->row = j;
					p->col = k;
				}
				//printf("%d ", p->sets[j][k]); 
			}
			//printf("\n");
		}
		//printf("POSIÇÃO mst (%d,%d) %d\n", p->row,p->col,p->sets[p->row][p->col]); // verificando, limpar depois
		/*if(search(p,0,0))
			printf("%s\n",p->solution);
		else
			printf("This puzzle is not solvable.\n");
		*/
	}

	return 0;
}
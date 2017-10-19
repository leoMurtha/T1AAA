#ifndef _SET_H_
#define _SET_H_

/* Struct representando um set do quebra-cabeça */
typedef struct gameset{
	int sets[4][4];/* Set de pisos */
	int row,col; /* Posição do piso faltando */
	char solution[51];
	char di;
	int fn;
	bool operator<(const gameset &a) const{
		return fn > a.fn;
	}
}puzzle;

#endif
/* Programa principal */ 
# include "Definiciones.h"
# include "Funciones.c"

# include <stdio.h>
int main(){
	
	init_curses();
	pintarFondo();
	int key; 
	//printw("ESC para salir."); 
	int x = 12;
	int y = 20;
	dibujarHumano(x,y); //Dibujo al humano en su posicion inicial
	refresh();

	do{
	key=getch();
	if(key == IZQUIERDA){	//Si presiona la tecla "a"
			deleteln();	//Elimino toda la linea en donde esta el humano, esto es importante
			y--;		//Esto hace el movimiento a la izquierda
			dibujarHumano(x,y);	//Imprimo la nueva posicion
			refresh();
		}
		else if(key == DERECHA){	//Si presiona la tecla "d"
			deleteln();	//Elimino toda la linea en donde esta el humano, esto es importante
			y++;		//Esto hace el movimiento a la derecha
			dibujarHumano(x,y); //Imprimo la nueva posicion
			refresh();
		}
		else{	//Si no se mueve a la derecha o izquierda imprime lo siguiente, esto se puede cambiar para que no imprima nada o no se mueva
				//Lo hice para ver que el movimiento se haga correctamente
			printw("Error al mover");
		}
	}while(key != ESCAPE);   //Si presiona 2 veces ESQ se termina el programa
	endwin();     
	return 0;
}

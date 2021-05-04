/* Funciones usadas por el programa principal y otras funciones */

# include "Definiciones.h"

/* c�digo implementaci�n de todas las funciones */
void pintarFondo(){
    juego = initscr();
   // printw("Hola mundo");
    refresh();
    getch();
    endwin();
}

void dibujarHumano(float x, float y){
	int key;
	move(x,y);
	printw("*");
}

void init_curses() {     
	initscr();     
	start_color();     
	init_pair(1,COLOR_WHITE,COLOR_BLUE);     
	init_pair(2,COLOR_BLUE,COLOR_WHITE);     
	init_pair(3,COLOR_RED,COLOR_WHITE);     
	curs_set(0);     
	noecho();     
	keypad(stdscr,TRUE); 
}
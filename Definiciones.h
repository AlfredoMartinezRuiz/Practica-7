/* Programa con las declaraciones usadas en el resto del sistema */ 

# ifndef DECS
# define DECS
# include <ncurses.h>
# include <stdio.h>
# include <stdlib.h>
/* Declaracion de las vars principales */
WINDOW *juego; 
int posX, posY; // Variables para controlar al monito

/* Declaracion de las funciones principales*/
void pintarFondo(); // Función que se va encargar de generar el fondo
void mover(float x, float y); //se encarga de que el monito se mueva
void dibujarBloque(float x, float y); // genera los bloques 
void moverBloques(); //se encarga de que los bloques se muevan 
int comprobarCoindicencia(float x, float y); //determina si el bloque tocó al monito
void tiempo(); //contador de cada partida
int menu(); 
void salir();
void dibujarHumano(float x, float y); //genera al monito
void escucharTeclas();

# endif

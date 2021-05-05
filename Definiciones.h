/* Programa con las declaraciones usadas en el resto del sistema */ 

# ifndef DECS
# define DECS
# include <ncurses.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h> 
# include <unistd.h> 
# include <time.h>
# include<sys/ipc.h>
# include<sys/shm.h>
#include <signal.h> 

# define NBLOQUES 30



/* Teclas para controlar al mono*/
# define ESCAPE 27
# define ENTER 10
# define IZQUIERDA 97
# define DERECHA 100

/* Velociad de los bloques(frames) */
# define KINDER 160000
# define TEST 120000
# define BAJA 90000
# define MEDIA 60000
# define ALTA 40000
# define IMPOSIBLE 20000

/* Para obtener tamaño de ventanas*/
int maxX;
int maxY;
int seg = 0; 
int puntaje = 0;
int velocidad;

/* Declaracion de las vars principales */
WINDOW *juego;  
int posX, posY; // Variables para controlar al humano
int direccionesBloques[NBLOQUES][2]; // [filas][columnas]          

/* Declaracion de las funciones principales*/
void crearVentana(); // Función que se va encargar de generar el fondo
void menuInicio(); // Función que se va encargar de generar el fondo
void mover(int alteracion); // Alteracion para mover al mono:  (-1, 1 a la izquierda) y (1, 1 a la derecha)
void moverBloquesY(); // Función que mueve los bloques un renglon abajo
void generadorBloque(int bloque); // Genera las posiciones aleatorias de los bloques
int comprobarCoincidencia(); // Comprueba si chocan o no algún bloque
void crearVentana2();

# endif

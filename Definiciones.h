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

# define NBLOQUES 11

/* Teclas para controlar al mono*/
# define ESCAPE 27
# define ENTER 114
# define IZQUIERDA 97
# define DERECHA 100

/* Velociad de los bloques(frames) */
# define TEST 120000
# define BAJA 90000
# define MEDIA 60000
# define ALTA 40000

/* Para obtener tamaño de ventanas*/
int maxX;
int maxY;
int contador_local = 0;

/* Declaracion de las vars principales */
WINDOW *juego; 
int posX = 60, posY = 31; // Variables para controlar al humano
int direccionesBloques[NBLOQUES][2] = {{2, 0}, // {espacio, renglon}
                                {12, 0},
                                {22, 0},
                                {32, 0},
                                {42, 0},
                                {52, 0},
                                {62, 0},
                                {72, 0},
                                {82, 0},
                                {92, 0},
                                {102, 0}
                            }; // [filas][columnas]          

/* Declaracion de las funciones principales*/
void crearVentana(); // Función que se va encargar de generar el fondo
void mover(int alteracion); // Alteracion para mover al mono:  (-1, 1 a la izquierda) y (1, 1 a la derecha)
void moverBloquesY(); // Función que mueve los bloques un renglon abajo
void generadorBloque(int bloque); // Genera las posiciones aleatorias de los bloques
int comprobarCoincidencia(); // Comprueba si chocan o no algún bloque
void dibujar(int c);

# endif
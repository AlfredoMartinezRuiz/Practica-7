/* Programa principal */ 
# include "Definiciones.h"
# include "Funciones.c"
//# include "allegro.h"
int puntaje = 0;

void finalizar(int snum){
		//printf("finalisechion");
		exit(0);
}
int main(){	
	/* c�digo principal de ejecuci�n */
	
	crearVentana(); // Creamos la ventana
	
	/*Compartiendo las coordeanadas del mono entre los procesos*/
	int *xM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
	int *yM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
	*xM = posX;
	*yM = posY;

	for(int i=0; i<NBLOQUES; i++) // Generamos la posicion aleatoria en y de los bloques
		generadorBloque(i);
	
	pid_t pid;
	pid = fork();
	if(pid == 0){ // Proceso encargado de dibujar 
		while (1){
			posX = *xM;
			moverBloquesY(); // Dezplaza de forma vertical los bloques 
			
			for(int i = 0; i<NBLOQUES; i++){ // Comprueba que el mono no se coche con algun bloque
				
				if(comprobarCoincidencia(i) == 1){ // Si llegaran a chocar
					clear();
					printw("Perdiste :c");
					printw("\npuntaje: %d", puntaje);
					printw("\nDesea continuar: \nPresione ESC para salir \nPresione ENTER para continuar");
					refresh();
					int key = getch();
					if(key == ESCAPE){	//Si presiona la tecla "esc"
						endwin();
						kill(getppid(), SIGTERM); //Manda la señal a su padre de que termine
						exit(1); //Se termina el proceso hijo
					}
					else if(key == ENTER){	//Si presiona la tecla "enter"
						puntaje = 0;
						//Se necesita convertir en funcion los procesos para volver a empezarlo 
					}
					
					fflush(stdin);

					
	
				}
				else{ //Contar el puntaje
					puntaje=puntaje+i;
					printw("puntaje: %d", puntaje);
				}
				
				
			}
			dibujar(); // Dibuja (representa un frame)
			usleep(MEDIA); // Velocidad de los frames
						
		}
		
	exit(0);	
	}
	
	else{ // Proceso encargado de detectar movimiento del mono
		while(1){
			posX = *xM;
			noecho();        
    		cbreak();
    		signal(SIGTERM,finalizar);
			int key = getch();
			
			if(key == IZQUIERDA){	//Si presiona la tecla "a"
				mover(-2);
			}
			else if(key == DERECHA){	//Si presiona la tecla "d"
				mover(2);
			}
			else if(key == ESCAPE){	//Si presiona la tecla "esc"
				
			}
			else if(key == ENTER){	//Si presiona la tecla "enter"
				
			}
			else{	//Si no se mueve a la derecha o izquierda imprime lo siguiente, esto se puede cambiar para que no imprima nada o no se mueva
					//Lo hice para ver que el movimiento se haga correctamente
				printw("Error al mover");
			}
			*xM = posX;
		} 
		sleep(5);
			
			
	}
		
	return 0;
}

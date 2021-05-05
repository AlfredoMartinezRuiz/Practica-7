/* Programa principal */ 
# include "Definiciones.h"
# include "Funciones.c"

void finalizar(int snum){
		exit(0);
}
int main(){	
	/* c�digo principal de ejecuci�n */
	
	crearVentana(); // Creamos la ventana
	menuInicio();  // Hacemos el menu para escoger dificultad

	
	/*Compartiendo las coordeanadas del mono entre los procesos*/
	int *xM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
	int *yM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
	int contador =0;

	for(int i=0; i<NBLOQUES; i++) // Generamos la posicion aleatoria en y de los bloques
		generadorBloque(i);
	
	pid_t pid;
	pid = fork();
	if(pid == 0){ // Proceso encargado de dibujar 
		*xM = posX;
		*yM = posY;
		while (1){
			posX = *xM;
			moverBloquesY(); // Dezplaza de forma vertical los bloques 
			
			for(int i = 0; i<NBLOQUES; i++){ // Comprueba que el mono no se coche con algun bloque
				if(comprobarCoincidencia(i) == 1){ // Si llegaran a chocar
					clear();
					
					gameOver(); //Imprime puntaje, segundos, y si deseamos continuar
					
					int key = getch();
					if(key == ESCAPE){	//Si presiona la tecla "esc"
						endwin();
						kill(getppid(), SIGTERM); //Manda la señal a su padre de que termine
						exit(1); //Se termina el proceso hijo
					}
					else if(key == ENTER){	//Si presiona la tecla "enter"
						puntaje = 0;
						seg = 0;
						*xM = (maxX/2)-2;
						posX = (maxX/2)-2;
						//Volvemos a generar los bloques desde el arriba de forma aleatoria otra vez
						for(int i=0; i<NBLOQUES; i++) // Generamos la posicion aleatoria en y de los bloques
							generadorBloque(i);
						break;
					}
					else{
						printw("Error al elegir");
					}
					
					fflush(stdin);
				}
				else{ //Contar el puntaje
					puntaje=puntaje+i;
				}			
				
			}
			dibujar(); // Dibuja (representa un frame)
			contador++;
			usleep(velocidad); // Velocidad de los frames
			int frames_por_sec = 1000000/velocidad; /* Calula cuandos frames hay por segundo 
			-> n_microsegundos en un segundo/microsegundos por cada frame */
			if(contador == frames_por_sec){ // Verifica si ya concurrió un segundo
				contador = 0;
				seg++;
			}						
		}		
	exit(0);	
	}
	
	else{ // Proceso encargado de detectar movimiento del mono
		while(1){
			
			noecho();        
    		cbreak();
    		signal(SIGTERM, finalizar);
			int key = getch();
			
			if(key == IZQUIERDA){	//Si presiona la tecla "a"
				posX = *xM;
				mover(-2);
			}
			else if(key == DERECHA){	//Si presiona la tecla "d"
				posX = *xM;
				mover(2);
			}
			else{	//Si no se mueve a la derecha o izquierda imprime lo siguiente, esto se puede cambiar para que no imprima nada o no se mueva
					//Lo hice para ver que el movimiento se haga correctamente
				printw(".");
			}
			*xM = posX;
		}			
	}		
	return 0;
}

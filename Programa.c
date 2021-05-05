/* Programa principal */ 
# include "Definiciones.h"
# include "Funciones.c"
//# include "allegro.h"
//int puntaje = 0;

void finalizar(int snum){
		//printf("finalisechion");
		exit(0);
}
int main(){	
	/* c�digo principal de ejecuci�n */
	
	crearVentana(); // Creamos la ventana
	menuInicio(); 

	
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
					//clear();
					printw("Perdiste %d, %d:c", posX, posY);
					printw("\npuntaje: %d", puntaje);
					printw("\nTiempo: %d", seg);
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
						seg = 0;
						*xM = (maxX/2)-2;
						posX = (maxX/2)-2;
						//*xM = posX;
						//Volvemos a generar los bloques desde el arriba
						for(int i=0; i<NBLOQUES; i++) // Generamos la posicion aleatoria en y de los bloques
						generadorBloque(i);
						break;
						//Se necesita convertir en funcion los procesos para volver a empezarlo 
					}
					else{
						printw("Error al elegir");
					}
					
					fflush(stdin);
				}
				else{ //Contar el puntaje
					puntaje=puntaje+i;
					//printw("puntaje: %d", puntaje);
				//	refresh();
				}
				
				
			}
			dibujar(); // Dibuja (representa un frame)
			contador++;
			if(contador == 15){
				contador = 0;
				seg++;
			}
			usleep(velocidad); // Velocidad de los frames
						
		}
		
	exit(0);	
	}
	
	else{ // Proceso encargado de detectar movimiento del mono
		while(1){
			
			noecho();        
    		cbreak();
    		signal(SIGTERM,finalizar);
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

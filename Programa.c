/* Programa principal */ 
# include "Definiciones.h"
# include "Funciones.c"
//# include "allegro.h"

int main(){	
	/* c�digo principal de ejecuci�n */
	crearVentana(); // Creamos la ventana
	
	
	/*Compartiendo las coordeanadas del mono entre los procesos*/
	int *xM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
	int *yM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
	int *contador_compartido = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);

	
	*xM = posX;
	*yM = posY;


	for(int i=0; i<NBLOQUES; i++) // Generamos la posicion aleatoria en y de los bloques
		generadorBloque(i);

	pid_t pid;
	pid = fork();
	int bandera = 1;
	int bandera2 = 1;

	do{

	if(pid == 0){ // Proceso encargado de dibujar 
		while (bandera){
			posX = *xM;
			contador_local = *contador_compartido;
			moverBloquesY(); // Dezplaza de forma vertical los bloques 
			for(int i = 0; i<NBLOQUES; i++){ // Comprueba que el mono no se coche con algun bloque
				if(comprobarCoincidencia(i) == 1){ // Si llegaran a chocar
				
				//	refresh();
					// end = time(NULL);
					bandera = 0;
					//endwin();
					//exit(0);
					//return 0;
				}
			}
			dibujar(contador_local); // Dibuja (representa un frame)
			usleep(MEDIA); // Velocidad de los frames	
					
		}
	}	
	else{ // Proceso encargado de detectar movimiento del mono
		
		//contador_local = *contador_compartido;
		while(1){
			posX = *xM;
			contador_local = *contador_compartido;
			noecho();        
    		cbreak();
			int key = getch();
			if(key == IZQUIERDA){	//Si presiona la tecla "a"
				mover(-2);
			refresh();
			}
			else if(key == DERECHA){	//Si presiona la tecla "d"
				mover(2);
			refresh();
			}
			else if(key == ESCAPE){	//Si presiona la tecla "esc"
				bandera2 = 0;
			refresh();
					printw("Choque");
					float segundos = (contador_local*MEDIA)/1000000;
					printw("Tiempo = %f",segundos);
					refresh();
					sleep(4);
					endwin(); 
					return 0;
			}
			else if(key == ENTER){	//Si presiona la tecla "enter"
				bandera = 1;
				bandera2 = 1;
				//printw("Soy el enter");
			}
			else{	//Si no se mueve a la derecha o izquierda imprime lo siguiente, esto se puede cambiar para que no imprima nada o no se mueva
					//Lo hice para ver que el movimiento se haga correctamente
				printw("Error al mover");
			}
			*xM = posX;
			*contador_compartido = contador_local;
		} 	
	}
}while(bandera2 != 0);


	return 0;
}

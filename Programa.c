/* Programa principal */ 
# include "Definiciones.h"
# include "Funciones.c"
//# include "allegro.h"

int main(){	
	/* c�digo principal de ejecuci�n */

//	time_t start;
	//time_t end;
//	time_t diferencia;
//	time_t referencia = clock();
	int contador;
	//double time_total;
	crearVentana(contador); // Creamos la ventana
	
//	start = time(NULL);
	//clock_t inicio = clock();
	
	/*Compartiendo las coordeanadas del mono entre los procesos*/
	int *xM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
	int *yM = shmat(shmget(ftok("Prac7",'k'), sizeof(int),IPC_CREAT|0600), 0, 0);
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
			moverBloquesY(); // Dezplaza de forma vertical los bloques 
			for(int i = 0; i<NBLOQUES; i++){ // Comprueba que el mono no se coche con algun bloque
				if(comprobarCoincidencia(i) == 1){ // Si llegaran a chocar
					//clock_t fin = clock();
					//double time_total = (double)((fin - inicio)/CLOCKS_PER_SEC);
				//	printw("Tiempo = %3.f", time_total);
					//refresh();
				//	printw("Choque");
				//	refresh();
					// end = time(NULL);
					bandera = 0;
					//endwin();
					//exit(0);
					//return 0;
				}
			}
			dibujar(contador); // Dibuja (representa un frame)
			usleep(MEDIA); // Velocidad de los frames	
					
		}
	}	
	else{ // Proceso encargado de detectar movimiento del mono
		while(1){
			posX = *xM;
			noecho();        
    		cbreak();
			int key = getch();
			if(key == IZQUIERDA){	//Si presiona la tecla "a"
				mover(-2);
			}
			else if(key == DERECHA){	//Si presiona la tecla "d"
				mover(2);
			}
			else if(key == ESCAPE){	//Si presiona la tecla "esc"
				bandera2 = 0;
			refresh();
					printw("Choque");
					//clock_t fin = clock();

					//double time_total = (double)((fin - inicio)/CLOCKS_PER_SEC);
					//double time_total =(double)((fin - inicio)/CLOCKS_PER_SEC);
				//	printw("Tiempo = %u", (double)(fin - inicio)/CLOCKS_PER_SEC);
				// diferencia = difftime(end,start);
				//	printw("Tiempo = %ld", diferencia/referencia);

					
					int segundos = (contador*MEDIA)/1000000;
					printw("Tiempo = %d",segundos);
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
		} 	
	}
}while(bandera2 != 0);


	return 0;
}

/* Programa principal */ 
# include "Definiciones.h"
# include "Funciones.c"

int main(){	
	/* c�digo principal de ejecuci�n */
	/* Codigo del bloque */
	WINDOW *debug = initscr();
	juego = subwin(debug, 38, 104, 0, 0);
	//juego = initscr(); // Crea la ventana   
    start_color(); // Inicia los colores
    init_pair(1, COLOR_BLACK, COLOR_BLUE); // Colores para el fondo
    bkgd(COLOR_PAIR(1));
	maxX = getmaxx(juego);
	maxY = getmaxy(juego);
	printf("asAS");
	for(int i = 0; i < NBLOQUES; i++)
		generadorBloque(i);
	
	int flag = 1;
	for(int i = 0; i < 600; i++){
		for(int i = 0; i < NBLOQUES; i++)
			flag = comprobarCoincidencia(i);		

		if(flag == 0){
			dibujar(); 
			usleep(100000);
			moverBloquesY();
			//mover(-1);		
			dibujar();
		}		
	}
	

    getch();	   
    endwin();        
    exit(1);

	/*
	pid_t pid;
	pid= fork();
	if(pid==0){
		while (1)
		{
			dibujar();
		}
	}
	
	else
	{
		while(1)
		{
			pintarFondo();
		}
	}*/

	return 0;
}

/* Funciones usadas por el programa principal y otras funciones */

# include "Definiciones.h"

/* c�digo implementaci�n de todas las funciones */
void crearVentana(){
    juego = initscr(); // Crea la ventana   
    start_color(); // Inicia los colores
    init_pair(1, COLOR_BLACK, COLOR_BLUE); // Colores para el fondo
    bkgd(COLOR_PAIR(1)); // Pone color al fondo
    // Obtenemos resolución en espacios y renglones
	maxX = getmaxx(juego); 
	maxY = getmaxy(juego);

}

void dibujar(int c){
    
    clear();
    /* Pintura del monito */    
    move(posY, posX);
    printw("  O");   
    move(posY+2, posX);
    printw("/ | \\"); 
    move(posY+4, posX);
    printw(" / \\");  

    /* Pintura del piso */
    move(posY+5, 0);
    for(int i=0; i < maxX; i++)
        printw("-");
    

    /* Pintura de los bloques */
    int x, y;
    for(int i = 0; i < NBLOQUES; i++){
        x = direccionesBloques[i][0];
        y = direccionesBloques[i][1];

        if(y > maxY - 5){ // Detecta si los bloques bajaron demasiado
            generadorBloque(i);
        }
        if(x+1 < maxX){ // Detecta que los bloques quepan en el margen
            move(y, x);
            if(y >= 0){
                printw("**");
            }
            if(y+1 >= 0){
                move(y+1, x);
                printw("**");
            }
        }  
    }
    c++;
    refresh();
}

void mover(int posicion){
    posX = posX + posicion; // Mueve la posicion en n espacios dados
}

void moverBloquesY(){ // Mueve la dirección de los bloques un renglón abajo
    for(int i = 0; i < NBLOQUES; i++){
        direccionesBloques[i][1] = direccionesBloques[i][1] + 1;
    }
}

void generadorBloque(int bloque){ // Genera de manera aleatoria la posicion en y de los bloques para que aparezcan nuevamente
    int renglonRandom = rand() % 30;
    direccionesBloques[bloque][1] = -renglonRandom;
}

int comprobarCoincidencia (int bloque){
    // Posicion del primer caracter del bloque a comparar 
    int bX = direccionesBloques[bloque][0];
    int bY = direccionesBloques[bloque][1]; 

    // Posicion del caracter la cabeza - 2 espacios
    int mX = posX;
    int mY = posY;
    //move(0, 0);
    //printw("bX: %d, bY: %d \n", bX, bY);
    //printw("mX: %d, mY: %d \n", mX, mY);    
    //refresh();
    // Algoritmo de comprobación de coincidencia (recomendado no mover)
    for(int f_bloque = bY; f_bloque < bY+2; f_bloque++){ // Recorre los dos renglones del bloque        
        for(int e_bloque = bX; e_bloque < bX+2; e_bloque++){ // Recorre los dos espacios del bloque
            for(int f_mono = mY; f_mono < mY+5; f_mono++){
                int e_mono = mX;
                if(f_mono == mY ){ // La cabeza
                    if(f_bloque == f_mono && e_bloque == e_mono+2)
                        return 1;
                }
                else if(f_mono == mY+1){ // Espacio en blanco
                    if(f_bloque == f_mono && (e_bloque >= e_mono && e_bloque <= e_mono+4))
                        return 1;
                }
                else if(f_mono == mY+2){ // Brazos
                    if(f_bloque == f_mono && (e_bloque >= e_mono && e_bloque <= e_mono+4))
                        return 1;
                }
                else if(f_mono == mY+3){ // Espacio en blanco
                    if(f_bloque == f_mono && (e_bloque >= e_mono && e_bloque <= e_mono+4))
                        return 1;
                }
                else if(f_mono == mY+4){ // Pies
                    if(f_bloque == f_mono && (e_bloque >= e_mono+1 && e_bloque <= e_mono+3))
                        return 1;
                }
            }
        }                     
    }
    return 0;
}


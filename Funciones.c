/* Funciones usadas por el programa principal y otras funciones */

# include "Definiciones.h"

/* c�digo implementaci�n de todas las funciones */
void crearVentana(){
    initscr(); // Crea la ventana   
    juego = newwin(0,0,0,0);
    start_color(); // Inicia los colores
    init_pair(1, COLOR_BLACK, COLOR_BLUE); // Colores para el fondo
    bkgd(COLOR_PAIR(1)); // Pone color al fondo
    // Obtenemos resolución en espacios y renglones
	maxX = getmaxx(juego); 
	maxY = getmaxy(juego);
    posX = (maxX/2)-2;
    posY = maxY-6;
}

void menuInicio(){
    move(maxY/2-7, maxX/2);
    printw("Bienvenido a Metoro, escoja la dificultad: ");
    move(maxY/2-6, maxX/2);
    printw("1. KINDER:");
    move(maxY/2-5, maxX/2);
    printw("2. BAJA ");
    move(maxY/2-4, maxX/2);
    printw("3. MEDIA: ");
    move(maxY/2-3, maxX/2);
    printw("4. ALTA: ");
    move(maxY/2-2, maxX/2);
    printw("5. ESTO ES IMPOSIBLE: ");
    int opcion;
    scanw("%d", &opcion);
    switch (opcion)
    {
    case 1:
        velocidad = KINDER;
        break;
    case 2:
        velocidad= BAJA;
        break;
    case 3:
        velocidad = MEDIA;
        break;
    case 4:
        velocidad = ALTA;
        break;
    case 5:
        velocidad = IMPOSIBLE;
        break;    
    }
}


void dibujar(){
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
    move(0,0);
    printw("Puntaje: %d\n",puntaje);
    printw("Time: %d\n",seg);
    refresh();
}

void mover(int posicion){
    if((posX + posicion >= 0) && (posX + posicion <= maxX-5)) // limita el movimiento del mono para que no se salga del borde 
        posX = posX + posicion; // Mueve la posicion en n espacios dados
}

void moverBloquesY(){ // Mueve la dirección de los bloques un renglón abajo
    for(int i = 0; i < NBLOQUES; i++){
        direccionesBloques[i][1] = direccionesBloques[i][1] + 1;
    }
}

void generadorBloque(int bloque){ // Genera de manera aleatoria la posicion en y de los bloques para que aparezcan nuevamente
    int renglonRandom = rand() % 30;
    int espacioRandom = rand() % 105;
    direccionesBloques[bloque][1] = -renglonRandom;
    direccionesBloques[bloque][0] = espacioRandom;

}

int comprobarCoincidencia (int bloque){
    // Posicion del primer caracter del bloque a comparar 
    int bX = direccionesBloques[bloque][0];
    int bY = direccionesBloques[bloque][1]; 

    // Posicion del caracter la cabeza - 2 espacios
    int mX = posX;
    int mY = posY;
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




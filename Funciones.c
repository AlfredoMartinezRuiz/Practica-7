/* Funciones usadas por el programa principal y otras funciones */

# include "Definiciones.h"

/* c�digo implementaci�n de todas las funciones */

void dibujar(){
    //clear();
    /* Pintura del monito */    
    move(posY, posX);
    printw("  O", maxX, maxY);   
    move(posY+2, posX);
    printw("/ | \\"); 
    move(posY+4, posX);
    printw(" / \\");  
    

    /* Pintura de los bloques */
    int x, y;
    for(int i = 0; i < NBLOQUES; i++){
        x = direccionesBloques[i][0];
        y = direccionesBloques[i][1];

        if(y > maxY - 3){
            generadorBloque(i);
        }
        if(x+1 < maxX){
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
    
    refresh(); 

    /*
    int x, y;    
    
    printw("A jugar");        
    int o = 0;
    for(int i = 0; i<10; i++){
        
        sleep(1);
        o++;             
        move(o, 30); // renglon, espacio
        x = getcurx(juego);      
        y = getcury(juego);
        printw("**");          
        o++;
        move(o, 30); 
        printw("**");
        noecho();        
        cbreak();
        keypad(juego, TRUE);     
        refresh();   
    }  
    
    getch();
    clear();
    refresh(); // Actualiza la ventana con los cambios     
    noecho();        
    cbreak();        
    keypad(juego, TRUE);
    refresh(); */  
}

void mover(int posicion){
    posX = posX + posicion;
}

void moverBloquesY(){
    for(int i = 0; i < NBLOQUES; i++){
        direccionesBloques[i][1] = direccionesBloques[i][1] + 1;
    }
}

void generadorBloque(int bloque){
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
    for(int f_bloque = bY; f_bloque < bY+2; f_bloque++){ // Recorre los dos renglones del bloque
        
        for(int e_bloque = bX; e_bloque < bX+2; e_bloque++){ // Recorre los dos espacios del bloque
            for(int f_mono = mY; f_mono < mY+5; f_mono++){
                int e_mono = mX;
                if(f_mono == mY ){ // La cabeza
                move(0, 0);
		        printw("Cabeza %d\n",  f_bloque);
                    if(f_bloque == f_mono && e_bloque == e_mono+2)
                        return 1;
                }
                else if(f_mono == mY+1){ // Espacio en blanco
                move(0, 0);
		        printw("EB %d\n",  f_bloque);
                    if(f_bloque == f_mono && (e_bloque >= e_mono && e_bloque <= e_mono+4))
                        return 1;
                }
                else if(f_mono == mY+2){ // Brazos
                move(0, 0);
		        printw("Brazos %d\n",  f_bloque);
                    if(f_bloque == f_mono && (e_bloque >= e_mono && e_bloque <= e_mono+4))
                        return 1;
                }
                else if(f_mono == mY+3){ // Espacio en blanco
                move(0, 0);
		        printw("EB %d\n",  f_bloque);
                    if(f_bloque == f_mono && (e_bloque >= e_mono && e_bloque <= e_mono+4))
                        return 1;
                }
                else if(f_mono == mY+4){ // Pies
                move(0, 0);
		        printw("Pies %d\n",  f_bloque);
                    if(f_bloque == f_mono && (e_bloque >= e_mono+1 && e_bloque <= e_mono+3))
                        return 1;
                }

            }

        }     
                
    }
    return 0;
}

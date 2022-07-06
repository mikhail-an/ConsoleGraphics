//
//  main.c
//  ConsoleGraphics
//
//  Created by Mike An on 06.07.2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <sys/ioctl.h>
#include <unistd.h>

int consoleSize = 0;
int consoleWidth = 0;
int consoleHeight = 0;

int getScreenSize(void) {
    int size = 0;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if(w.ws_col * w.ws_row != 0){
        consoleWidth = w.ws_col;
        consoleHeight = w.ws_row;
    }else{
        consoleWidth = 80;  // standart console resolution for my mac m1
        consoleHeight = 24; // -----------------------------------------
    }
    size = consoleWidth * consoleHeight;
    return size;
}

int main() {
    consoleSize = getScreenSize();
    char screen[consoleSize+1];
    float aspect = (float)consoleWidth/consoleHeight;
    const float rescale = 22.0f/42.0f;  //on my mac m1 in console is it standart resolution of symbol sprite

    
    for(int a = 0; /*a < 500*/ ; a++){
    
        for(int i = 0; i<consoleWidth; i++){
            for(int j = 0; j<consoleHeight; j++){
                
                float x = (float) i/consoleWidth*2.0f-1.0f;
                float y = (float) j/consoleHeight*2.0f-1.0f;
                
                x *= aspect * rescale;
                x += sin(a*0.001);
                
                char pixel = ' ';
/*pifagor func*/if(x*x+y*y<0.5) pixel = '.';
                
                screen[i + j * consoleWidth] = pixel;
            }
        }
        screen[consoleSize]='\0';
        puts(screen);  // [printf] unable to display characters "frame by frame", but [puts] can do it better!
        usleep(1000);  // little stopper for normal frames per second
    }

    return 0;
}

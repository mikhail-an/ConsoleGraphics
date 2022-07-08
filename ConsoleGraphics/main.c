//
//  main.c
//  ConsoleGraphics
//
//  Created by Mike An on 06.07.2022.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <sys/ioctl.h>
#include <unistd.h>

int consoleSize = 0;
int consoleWidth = 0;
int consoleHeight = 0;
float rescale = 22.0f/42.0f;  //on my mac m1 in console is it standart resolution of symbol sprite
float aspect = 1.0f;

struct d2 {
    float x;
    float y;
};


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

char pifa(struct d2 a, struct d2 b, int len) {
    char cc[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. "; // 0 - 69
    char c[]  = "@%#*+=-:. "; // 0 - 9
    float pifalen = sqrt((a.x-b.x)*(a.x-b.x)/aspect/rescale + (a.y-b.y)*(a.y-b.y)/rescale);
    
    if(pifalen > (float)len) return c[9]; // do not draw anythink
                                            /* else draw gradient */
    float step = (float)len/9.0f;
    int index = (int)round(pifalen/step);
    return c[index] ;
}

int main() {
    struct d2 c, cursor;
    consoleSize = getScreenSize();
    char screen[consoleSize+1];
    aspect = (float)consoleWidth/consoleHeight;
    

    c.x = (float)consoleWidth/2;
    c.y = (float)consoleHeight/2;
    
    for(int a = 0; /*a < 500*/ ; a++){
    
        for(int i = 0; i<consoleWidth; i++){
            for(int j = 0; j<consoleHeight; j++){
                
                cursor.x = i + 10 * sin(a*0.001);
                cursor.y = j + 2 * cos(a*0.002);


                screen[i + j * consoleWidth] = pifa(cursor,c,20);
            }
        }
        screen[consoleSize]='\0';
        puts(screen);  // [printf] unable to display characters "frame by frame", but [puts] can do it better!
        usleep(1000);  // little stopper for normal frames per second
    }

    return 0;
}

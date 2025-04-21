#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

float A, B, C;
float x, y, z;
float ooz;
int idx;
int xp, yp;
int k1 = 40;
const int cubeWidth = 30;
float distanceFromCam = 100;
#define screenWidth 80
#define screenHeight 50
char buffer[screenHeight * screenWidth];
float zBuffer[screenHeight * screenWidth];
char backgroundChar = ' ';

float findX(float i, float j, float k){
    return i * cos(B) * cos(C) - j * sin(C) * cos(B)
    + k * sin(B);
}

float findY(float i, float j, float k){
    return i * (sin(A) * sin(B) * cos(C) + sin(C) * cos(A)) +
           j * (-sin(A) * sin(B) * sin(C) + cos(A) * cos(C)) -
           k * sin(A) * cos(B);
}

float findZ(float i, float j, float k){
    return i * (-sin(B) * cos(A) * cos(C) + sin(A) * sin(C)) +
           j * (sin(B) * cos(A) * sin(C) + sin(A) * cos(C)) +
           k * cos(B) * cos(A);
}

void findPoint(float i, float j, float k, char ch){
    x = findX(i, j, k);
    y = findY(i, j, k);
    z = findZ(i, j, k) + distanceFromCam;

    ooz = 1 / z;
    xp = (int)(screenWidth / 2 + k1 * ooz * x * 2);
    yp = (int)(screenHeight / 2 + k1 * ooz * y);
    idx = xp + yp * screenWidth;
    
    if(idx >= 0 && idx < screenWidth * screenHeight){
        if(ooz > zBuffer[idx]){
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main(){

    printf("\x1b[2J");

    while(1){
        memset(buffer, backgroundChar, screenWidth * screenHeight);
        memset(zBuffer, 0, screenWidth * screenHeight * 4);
        for(float i = -cubeWidth / 2; i < cubeWidth / 2; i += 0.12){
            for(float j = -cubeWidth / 2; j < cubeWidth / 2; j += 0.12){
                findPoint(i, j, -cubeWidth / 2, '@');
                findPoint(i, cubeWidth / 2, j, '$');
                findPoint(i, -cubeWidth / 2, -j, '~');
                findPoint(-i, j, cubeWidth / 2, '#');
                findPoint(cubeWidth / 2, j, i, '%');
                findPoint(-cubeWidth / 2, j, -i, '!');
            }
        }

        printf("\x1b[H");
        for(int k = 0; k < screenWidth * screenHeight; k++){
            if(buffer[k] == '@'){
                printf("\x1b[31m");
            }

            else if(buffer[k] == '$'){
                printf("\x1b[32m");
            }

            else if(buffer[k] == '~'){
                printf("\x1b[33m");
            }

            else if(buffer[k] == '#'){
                printf("\x1b[34m");
            }

            else if(buffer[k] == '%'){
                printf("\x1b[35m");
            }

            else if(buffer[k] == '!'){
                printf("\x1b[36m");
            }

            else{
                printf("\x1b[37m");
            }

            putchar(k % screenWidth ? buffer[k] : 10);
        }
        A += 0.03;
        B += 0.05;
        C += 0.02;
        usleep(10000);
    }

    return 0;
}

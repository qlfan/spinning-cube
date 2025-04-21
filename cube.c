#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd>

float A, B, C;
float x, y, z;
float ooz;
int idx;
int xp, yp;
float distanceFromCam = 100;
int screenWidth = 80;
int screenHeight = 50;
char buffer[height * width];
float zBuffer[height * width];

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
        memset(buffer, backgroundChar, width * height);
        memset(zBuffer, 0, width * height * 4);
        for(float i = -screenWidth / 2; i < screenWidth / 2; i += 0.12){
            for(float j = -screenWidth / 2; j < screenWidth / 2; j++){
                findPoint(i, j, distanceFromCam, '@');
            }
        }

        printf("\x1b[H");
        for(int k = 0; k < width * height; k++){
            putchar(k % width ? buffer[k] : 10);
        }
        A += 0.03;
        B += 0.07;
        C += 0.02;
        usleep(8000);
    }

    return 0;
}

#include "char_letras.h"


const char* letraA[FONT_HEIGHT] = {
    "01110","01110","10001","10001","10001","10001",
    "11111","11111","10001","10001","10001","10001","10001","10001"
};
const char* letraB[FONT_HEIGHT] = {
    "11110","11110","10001","10001","10001","10001",
    "11110","11110","10001","10001","10001","10001","11110","11110"
};
const char* letraC[FONT_HEIGHT] = {
    "01111","01111","10000","10000","10000","10000",
    "10000","10000","10000","10000","10000","10000","01111","01111"
};
const char* letraD[FONT_HEIGHT] = {
    "11110","11110","10001","10001","10001","10001",
    "10001","10001","10001","10001","10001","10001","11110","11110"
};
const char* letraE[FONT_HEIGHT] = {
    "11111","11111","10000","10000","10000","10000",
    "11110","11110","10000","10000","10000","10000","11111","11111"
};
const char* letraF[FONT_HEIGHT] = {
    "11111","11111","10000","10000","10000","10000",
    "11110","11110","10000","10000","10000","10000","10000","10000"
};
const char* letraG[FONT_HEIGHT] = {
    "01111","01111","10000","10000","10000","10000",
    "10011","10011","10001","10001","10001","10001","01110","01110"
};
const char* letraH[FONT_HEIGHT] = {
    "10001","10001","10001","10001","10001","10001",
    "11111","11111","10001","10001","10001","10001","10001","10001"
};
const char* letraI[FONT_HEIGHT] = {
    "11111","11111","00100","00100","00100","00100",
    "00100","00100","00100","00100","00100","00100","11111","11111"
};
const char* letraJ[FONT_HEIGHT] = {
    "00111","00111","00010","00010","00010","00010",
    "00010","00010","00010","00010","10010","10010","01100","01100"
};
const char* letraK[FONT_HEIGHT] = {
    "10001","10001","10010","10010","10100","10100",
    "11000","11000","10100","10100","10010","10010","10001","10001"
};
const char* letraL[FONT_HEIGHT] = {
    "10000","10000","10000","10000","10000","10000",
    "10000","10000","10000","10000","10000","10000","11111","11111"
};
const char* letraM[FONT_HEIGHT] = {
    "10001","10001","11011","11011","10101","10101",
    "10101","10101","10001","10001","10001","10001","10001","10001"
};
const char* letraN[FONT_HEIGHT] = {
    "10001","10001","11001","11001","10101","10101",
    "10101","10101","10011","10011","10001","10001","10001","10001"
};
const char* letraO[FONT_HEIGHT] = {
    "01110","01110","10001","10001","10001","10001",
    "10001","10001","10001","10001","10001","10001","01110","01110"
};
const char* letraP[FONT_HEIGHT] = {
    "11110","11110","10001","10001","10001","10001",
    "11110","11110","10000","10000","10000","10000","10000","10000"
};
const char* letraQ[FONT_HEIGHT] = {
    "01110","01110","10001","10001","10001","10001",
    "10001","10001","10101","10101","10010","10010","01101","01101"
};
const char* letraR[FONT_HEIGHT] = {
    "11110","11110","10001","10001","10001","10001",
    "11110","11110","10100","10100","10010","10010","10001","10001"
};
const char* letraS[FONT_HEIGHT] = {
    "01111","01111","10000","10000","10000","10000",
    "01110","01110","00001","00001","00001","00001","11110","11110"
};
const char* letraT[FONT_HEIGHT] = {
    "11111","11111","00100","00100","00100","00100",
    "00100","00100","00100","00100","00100","00100","00100","00100"
};
const char* letraU[FONT_HEIGHT] = {
    "10001","10001","10001","10001","10001","10001",
    "10001","10001","10001","10001","10001","10001","01110","01110"
};
const char* letraV[FONT_HEIGHT] = {
    "10001","10001","10001","10001","10001","10001",
    "10001","10001","10001","10001","01010","01010","00100","00100"
};
const char* letraW[FONT_HEIGHT] = {
    "10001","10001","10001","10001","10001","10001",
    "10101","10101","10101","10101","10101","10101","01010","01010"
};
const char* letraX[FONT_HEIGHT] = {
    "10001","10001","10001","10001","01010","01010",
    "00100","00100","01010","01010","10001","10001","10001","10001"
};
const char* letraY[FONT_HEIGHT] = {
    "10001","10001","10001","10001","01010","01010",
    "00100","00100","00100","00100","00100","00100","00100","00100"
};
const char* letraZ[FONT_HEIGHT] = {
    "11111","11111","00001","00001","00010","00010",
    "00100","00100","01000","01000","10000","10000","11111","11111"
};

// espacio y punto
const char* letraSpace[FONT_HEIGHT] = {
    "00000","00000","00000","00000","00000","00000",
    "00000","00000","00000","00000","00000","00000","00000","00000"
};

const char* letraPunto[FONT_HEIGHT] = {
    "00000","00000","00000","00000","00000","00000",
    "00000","00000","00000","00000","00000","00000","01100","01100"
};

const char** alfabeto[26] = {
    letraA, letraB, letraC, letraD, letraE, letraF, letraG,
    letraH, letraI, letraJ, letraK, letraL, letraM, letraN,
    letraO, letraP, letraQ, letraR, letraS, letraT, letraU,
    letraV, letraW, letraX, letraY, letraZ
};

const char** getLetraMayuscula(char c)
{
    if(c == ' ') return letraSpace;
    if(c == '.') return letraPunto;
    return alfabeto[c - 'A'];
};


void drawChar(SDL_Renderer* renderer, char c, Position pos, int pixelSize, SDL_Color color)
{
    const char** letters = getLetraMayuscula(c);
    SDL_Rect letter;
    for (int row = 0; row < FONT_HEIGHT; row++)
    {
        for (int column = 0; column < FONT_WIDTH; column++)
        {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    
            char pixel = letters[row][column];

            if(pixel == '1')
            {
                letter.x = pos.x + (column * pixelSize);
                letter.y = pos.y +  (row * pixelSize);
                letter.w = pixelSize;
                letter.h = pixelSize;
                SDL_RenderFillRect(renderer, &letter);
            }
        }
        
    }
    
};

void drawText(SDL_Renderer* renderer, const char* text, Position pos, int pixelSize, int spacing, SDL_Color color)
{
    int offsetX = 0;
    for(int i = 0; text[i] != '\0'; i++)
    {
        Position charPos = { pos.x + offsetX, pos.y };
        drawChar(renderer, text[i], charPos, pixelSize, color);
        offsetX += (FONT_WIDTH * pixelSize) + spacing;
    }
};
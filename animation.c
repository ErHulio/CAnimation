#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int width = 140;
int height = 40;

void printAt(char character, int row,int column, char *buffer);
void printSpriteAt(char **sprite,int row,int column, char *buffer);
void printScreen(char *buffer, char *clean);

char *sprite2[8][13] = {{
    "     ***",
    "   **+++**",
    "  *+++++++*",
    " *+++++++++*",
    " *+++++++++*",
    "*++++* *++++*",
    "*****   *****",
    "*    * *    *",
    " *         *",
    " *         *",
    "  *       *",
    "   **   **",
    "     ***"
},{
    "     ***",
    "   **+++**",
    "  *+++++++*",
    " * *+++++++*",
    " *  *++++++*",
    "*    * *++++*",
    "*   *   *+++*",
    "*    * *++++*",
    " *      *++*",
    " *       *+*",
    "  *       *",
    "   **   **",
    "     ***"
},{
    "     ***",
    "   ** *+**",
    "  *   *+++*",
    " *    *++++*",
    " *    *++++*",
    "*    * *++++*",
    "*   *   *+++*",
    "*    * *++++*",
    " *    *++++*",
    " *    *++++*",
    "  *   *+++*",
    "   ** *+**",
    "     ***"
},{
    "     ***",
    "   **   **",
    "  *       *",
    " *       *+*",
    " *      *++*",
    "*    * *++++*",
    "*   *   *+++*",
    "*    * *++++*",
    " *  *++++++*",
    " * *+++++++*",
    "  *+++++++*",
    "   **+++**",
    "     ***"
},{
    "     ***",
    "   **   **",
    "  *       *",
    " *         *",
    " *         *",
    "*    * *    *",
    "*****   *****",
    "*++++* *++++*",
    " *+++++++++*",
    " *+++++++++*",
    "  *+++++++*",
    "   **+++**",
    "     ***"
},{
    "     ***",
    "   **   **",
    "  *       *",
    " *+*       *",
    " *++*      *",
    "*++++* *    *",
    "*+++*   *   *",
    "*++++* *    *",
    " *++++++*  *",
    " *+++++++*+*",
    "  *+++++++*",
    "   **+++**",
    "     ***"
},{
    "     ***",
    "   **+* **",
    "  *+++*   *",
    " *++++*    *",
    " *++++*    *",
    "*++++* *    *",
    "*+++*   *   *",
    "*++++* *    *",
    " *++++*    *",
    " *++++*    *",
    "  *+++*   *",
    "   **+* **",
    "     ***"
},{
    "     ***",
    "   **+++**",
    "  *+++++++*",
    " *+++++++* *",
    " *++++++*  *",
    "*++++* *    *",
    "*+++*   *   *",
    "*++++* *    *",
    " *++*      *",
    " *+*       *",
    "  *       *",
    "   **   **",
    "     ***"
}};

int main(){
    char *screenBuffer = malloc((height * width + 1) * sizeof(char));
    memset(screenBuffer,' ',height* width * sizeof(char));
    screenBuffer[height * width] = '\0';
    char *screenBufferClean = malloc((height * width + 1) * sizeof(char));
    strcpy(screenBufferClean,screenBuffer);
    system("cls");
    system("mode 140,40");
    printf("%c]0;Animacion%c%c",27,27,'\\');

    for(int i = -40, j = 0; i < 100; i+=2, j++){
        printSpriteAt(sprite2[(j)%8],15,i,screenBuffer);
        usleep(50000);
        printScreen(screenBuffer,screenBufferClean);
    }

    getchar();

    free(screenBuffer);
    free(screenBufferClean);
    return 0;
}

void printAt(char character, int row, int column, char *buffer){
    int uLimitRow = 0;
    int dLimitRow = height;
    int lLimitColumn = 0;
    int rLimitColumn = width;
    if(row < 0){
        return;
    }
    if(column < 0){
        return;
    }
    buffer[width * row + column] = character;
}

void printSpriteAt(char **sprite, int row, int column, char *buffer){
    char *spriteRow;
    char spriteElement;
    int uLimitRow = 0;
    int dLimitRow = height;
    int lLimitColumn = 0;
    int rLimitColumn = width;
    if(row < 0){
        uLimitRow = (-1) * row;
    }
    if(column < 0){
        lLimitColumn = (-1) * column;
    }
    for(int i = uLimitRow; i < 13 && (spriteRow = sprite[i]); i++){
        for(int j = lLimitColumn; j < 13 && (spriteElement = spriteRow[j]); j++){
            buffer[width * (row + i) + column + j] = spriteElement;
        }
    }
}

void printScreen(char *buffer, char *clean){
    write(1,buffer,height*width);
    strcpy(buffer,clean);
}
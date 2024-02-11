#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>

typedef struct User{
    char name[50];
    int ID;
    int Level;
    boolean Status; // 0 if it finished and 1 if it could restore.
    int username;
    char password[30];
    struct User* pNext;
    char FileName[30];
}USER;
typedef struct Pacman{
    int x;
    int y;
} PACMAN;

char** LoadMap(char* filename){
    char** Mat;
    FILE* fp;
    int m, n, i;

    fp = fopen(filename, "r");
    fscanf(fp,"%d %d", &m, &n);
    Mat = (char**)malloc(sizeof(char*)*m);
    for(i=0; i<m; i++){
        Mat[i] = (char*)malloc(sizeof(char)*n);
    }
    for(i=0; i<m; i++){
        for(int j=0; j<n; j++){
            fscanf(fp," %c", &Mat[i][j]);
        }
    }
    fclose(fp);


    for( i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if (Mat[i][j]=='|' || Mat[i][j] == '-')
                Mat[i][j] = '#';
            else{
                if(Mat[i][j]=='.')
                    Mat[i][j] = ' ';
            }
        }
    }


    return Mat;
}
char** Import_Mat2Map(char** mat, int rows, int cols) {
    char** NewMat = (char**)malloc(4 * rows * sizeof(char*));
    for (int i = 0; i < 4 * rows; i++) {
        NewMat[i] = (char*)malloc(6 * cols * sizeof(char));
    }
    int k, l;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(mat[i][j]=='#'){
                for(k=i*4; k<4*i+4; k++){
                    for(l=j*6; l<6*j+6; l++)
                        NewMat[k][l] = '#';
                }
            }
            else{
                if(mat[i][j]=='@'){
                    for(k=i*4+1; k<6*i+4; k+=2){
                        for(l=j*6; l<j*6+6; l++){
                            if (l%6==0)
                                NewMat[k][l]=' ';
                            else{
                                if(l%6==1||l%6==5)
                                    NewMat[k][l]='.';
                                else
                                    NewMat[k][l]='`';
                            }
                        }
                    }
                    for(k=0; k<6; k++){
                        switch (k){
                            case 0:
                                NewMat[4*i+2][6*j+k]= '(';
                                break;
                            case 1:
                                NewMat[4*i+2][6*j+k]= ' ';
                                break;                        
                            case 2:
                                NewMat[4*i+2][6*j+k]= ' ';
                                break;
                            case 3:
                                NewMat[4*i+2][6*j+k]= 'o';
                                break;
                            case 4:
                                NewMat[4*i+2][6*j+k]= 'O';
                                break;
                            case 5:
                                NewMat[4*i+2][6*j+k]= '<';
                                break;
                        }
                    }

                    for(k=0; k<6; k++)
                        NewMat[4*i][6*j+k] =' ';
                    NewMat[4*i+3][6*j+2] = '_';
                    NewMat[4*i+3][6*j+3] = '_';
                    NewMat[4*i+3][6*j+4] = '_';                        
                }
                else{
                    if (mat[i][j]=='P'){
                        for(k=0; k<4; k++){
                            for(l=0; l<6; l++){
                                NewMat[4*i+k][6*j+l]= ' ';
                            }
                        }
                        NewMat[4*i+1][6*j+2] = '/';
                        NewMat[4*i+1][6*j+3] = '\\';
                        NewMat[4*i+2][6*j+1] = '#';
                        NewMat[4*i+2][6*j+4] = '#';
                    }
                    else{
                        if(mat[i][j]=='G'){
                            for(k=4*i; k<4*i+4; k++){
                                for(l=6*j; l<6*j+6; l++)
                                    NewMat[k][l] =' ';
                            }                          
                            for(k=1; k<3; k++){
                                for(l=1; l<6; l+=4){
                                    NewMat[4*i+k][6*j+l]= '|';
                                }
                            }                    
                            for(k=2; k<5; k++){
                                NewMat[4*i+3][6*j+k]= '^';
                            }
                            //.
                            NewMat[4*i][6*j+2]= '.';
                            NewMat[4*i][6*j+3]= '-';
                            NewMat[4*i][6*j+4]= '.';
                            NewMat[4*i+1][6*j+3]= 'o';
                            NewMat[4*i+1][6*j+4]= 'O';
                            NewMat[4*i+3][6*j+1]= '.';
                            NewMat[4*i+3][6*j+5]= '.';
                        }
                        else{
                            for(k=i*4; k<4*i+4; k++){
                                for(l=j*6; l<6*j+6; l++)
                                    NewMat[k][l] = ' ';
                            } 
                        }
                    }
                }
            }
        }
    }
    return NewMat;
}
void draw(char** mat, int m, int n){
    int i, j;
    for (i=0; i<m; i++){
        for (j=0; j<n; j++){
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }
}
int Play(USER* User, char**mat, int m, int n){
    //EatenPoints;
    int Eaten = 0, i, j, numOfpnt = 0, random, numOfG = 0, G_x[4], G_y[4];
    boolean End = FALSE;
    PACMAN Pacy;
    char input, tmp, **map, inp, res; //res == 0 : loose/ res==1 : win/ res == 2: non-coplete game
     
    //find loc of @  loc and No of  G & No of P: 
    for(i=0;i<m;i++){
        for (j=0; j<n; j++){
            if(mat[i][j]=='@'){
                Pacy.x = i;
                Pacy.y = j;
            }
            if(mat[i][j] == 'P')
                numOfpnt++;
            if(mat[i][j] == 'G'){
                G_x[numOfG] = i;
                G_y[numOfG] = j;
                numOfG++;
            }
        }
    }
    printf ("Use the Arrow Keys to move Pacman\n");

    system("cls");
    printf("Name: %s \t Lv: %d \n Score: %d \t Remain: %d\n",User->name, User->Level, Eaten, numOfpnt-Eaten);
    map = Import_Mat2Map(mat, m, n);
    draw(map, 4*m, 6*n);
    printf("\nPress E to EXIT\n");    

    while (1){    

        //if kbhit>0 move pacman
        input = getch();

        //Random Ghost moving:
        for(i=0; i<numOfG; i++){
            random = rand() % 4;
            
            switch (random) {
                case 0: //U
                    if (mat[G_x[i]-1][G_y[i]] != '#' && mat[G_x[i]-1][G_y[i]] != 'P') {
                        if(mat[G_x[i]-1][G_y[i]] == '@'){
                            mat[G_x[i]-1][G_y[i]] = 'G';
                            mat[G_x[i]][G_y[i]] = ' ';
                            ////fail game
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if (mat[G_x[i]-1][G_y[i]] == 'P'){
                                mat[G_x[i]][G_y[i]] = ' ';
                            }
                            else{ // ' ' or 'G'
                                mat[G_x[i]-1][G_y[i]] = 'G';
                                mat[G_x[i]][G_y[i]] = ' ';                                
                            }
                        }
                        G_x[i]-=1;
                    }
                    break;
                case 1://D
                    if (mat[G_x[i]+1][G_y[i]] != '#' && mat[G_x[i]+1][G_y[i]] != 'P') {
                        if(mat[G_x[i]+1][G_y[i]] == '@'){
                            mat[G_x[i]+1][G_y[i]] = 'G';
                            mat[G_x[i]][G_y[i]] = ' ';
                            ////fail game
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if (mat[G_x[i]+1][G_y[i]] == 'P'){
                                mat[G_x[i]][G_y[i]] = ' ';
                            }
                            else{ // ' ' or 'G'
                                mat[G_x[i]+1][G_y[i]] = 'G';
                                mat[G_x[i]][G_y[i]] = ' ';                                
                            }
                        }
                        G_x[i]+=1;
                    } 
                    break;
                case 2://L
                    if (mat[G_x[i]][G_y[i]-1] != '#' && mat[G_x[i]][G_y[i]-1] != 'P') {
                        if(mat[G_x[i]][G_y[i]-1] == '@'){
                            mat[G_x[i]][G_y[i]-1] = 'G';
                            mat[G_x[i]][G_y[i]] = ' ';
                            ////fail game
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if (mat[G_x[i]][G_y[i]-1] == 'P'){
                                mat[G_x[i]][G_y[i]] = ' ';
                            }
                            else{ // ' ' or 'G'
                                mat[G_x[i]][G_y[i]-1] = 'G';
                                mat[G_x[i]][G_y[i]] = ' ';                                
                            }
                        }
                        G_y[i]-=1;
                    }
                    break;
                case 3://R
                    if (mat[G_x[i]][G_y[i]+1] != '#' && mat[G_x[i]][G_y[i]+1] != 'P') {
                        if(mat[G_x[i]][G_y[i]+1] == '@'){
                            mat[G_x[i]][G_y[i]+1] = 'G';
                            mat[G_x[i]][G_y[i]] = ' ';
                            ////fail game
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if (mat[G_x[i]][G_y[i]+1] == 'P'){
                                mat[G_x[i]][G_y[i]] = ' ';
                            }
                            else{ // ' ' or 'G'
                                mat[G_x[i]][G_y[i]+1] = 'G';
                                mat[G_x[i]][G_y[i]] = ' ';                                
                            }
                        }
                        G_y[i]+=1;
                    }
                    break;
                default:
                    break;
            } 
        }                
        
        //move pacman:
        switch (input){
            case 72://UP
                if(mat[Pacy.x-1][Pacy.y] != '#'){
                    if(mat[Pacy.x-1][Pacy.y]=='G'){
                        res = 0;
                        End = TRUE;
                    }
                    else{
                        if(mat[Pacy.x-1][Pacy.y]=='P'){
                            Eaten++;
                        }
                        mat[Pacy.x-1][Pacy.y]='@';
                        mat[Pacy.x][Pacy.y] = '\0';
                        Pacy.x -= 1;
                    }
                }
                break;
            case 80://D
                if(mat[Pacy.x+1][Pacy.y] != '#'){
                    if(mat[Pacy.x+1][Pacy.y]=='G'){
                        res = 0;
                        End = TRUE;
                    }
                    else{
                        if(mat[Pacy.x+1][Pacy.y]=='P'){
                            Eaten++;
                        }
                        mat[Pacy.x+1][Pacy.y]='@';
                        mat[Pacy.x][Pacy.y] = '\0';
                        Pacy.x += 1;
                    }
                }
                break;
            case 75://L
                if(mat[Pacy.x][Pacy.y-1] != '#'){
                    if(mat[Pacy.x][Pacy.y-1]=='G'){
                        res = 0;
                        End = TRUE;
                    }
                    else{
                        if(mat[Pacy.x][Pacy.y-1]=='P'){
                            Eaten++;
                        }
                        mat[Pacy.x][Pacy.y-1]='@';
                        mat[Pacy.x][Pacy.y] = '\0';
                        Pacy.y -= 1;
                    }
                }
                break;
            case 77://R
                if(mat[Pacy.x][Pacy.y+1] != '#'){
                    if(mat[Pacy.x][Pacy.y+1]=='G'){
                        res = 0;
                        End = TRUE;
                    }
                    else{
                        if(mat[Pacy.x][Pacy.y+1]=='P'){
                            Eaten++;
                        }
                        mat[Pacy.x][Pacy.y+1]='@';
                        mat[Pacy.x][Pacy.y] = '\0';
                        Pacy.y += 1;
                    }
                }
                break;
            case 'e':
            case 'E':
                system("cls");
                printf("\n\n\n\t\t Do you want to save game? (y/n)\n");
                scanf ("%c", &inp);
                if(inp == 'Y' || inp == 'y'){
                    User->Status = TRUE;
                    //save board:
                    /*
                    if (SaveGame(User, mat, m, n) == FALSE)
                        printf("The Game is not saved!");
                    else */
                    printf("Saved.");
                    //sleeeeeeeeeeeeeeep/////////////
                    sleep(3);
                }
                res = 2;
                break;
            default:
                break;
        }

        system("cls");
        printf("Name: %s \t Lv: %d \n Score: %d \t Remain: %d\n",User->name, User->Level, Eaten, numOfpnt-Eaten);
        map = Import_Mat2Map(mat, m, n);
        draw(map, 4*m, 6*n);
        printf("\nPress E to EXIT\n");   

        if (res == 2)
            return 0;//End playing
        if(numOfpnt-Eaten == 0){
            res = 1;
            End = TRUE;
        }            
        if(End==TRUE)
            break;

    }
    if(res==0){
        printf("YOOOOOOOOOU FAIL :(");
        sleep (10);
        return -1;
    }
    else{
        if (res == 1){
            printf("YOOOOOOOOOU WIN!");
            sleep(5);
            return 3;
        }
    }        

}

int main(){
    char** Mat;
    Mat = (char**)malloc(sizeof(char*)*5);
    for(int i=0; i<5; i++){
        Mat[i] = (char*)malloc(sizeof(char)*10);
    }
    Mat = LoadMap("mapA.txt");
    USER* user1;
    user1 = (USER*)malloc(sizeof(USER));
    user1->Status = FALSE;
    Play(user1,Mat, 5, 10);
    return 0;
}

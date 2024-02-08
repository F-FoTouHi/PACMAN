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

//Functions:
void StartInitialize(void);
USER* Un_Logged_Menu(USER*, int);
void Logged_In_Menu(USER*, USER*);
void Win(void); //just display
void GameOver(void); //just display
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
USER* Login(unsigned long long int, char*,  USER*); //return 0 if operation unsuccessful and 1 for success.
USER* CreatAccount(unsigned long long int, char*, USER*, int); //...
void DeleteAccount(USER*, int, int);
char** LoadMap(char*); //It load information from file and save to an array
char** RestoreGame(USER *Head, int id); //a game of a person
boolean SaveGame(USER* user, char** Map, int m, int n);
USER* LoadAll(char*);
boolean SaveAll(char*, USER*);
void draw(char**, int, int);
int Play(USER*, char**, char ); //it recieve user information and Map then give the score.
char** Import_Mat2Map(char**, int, int);
void gotoxy(short x, short y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Global variables:
unsigned long long int username;
int cmd, Num;
char password[50];


int main(){
    USER* pHead = NULL, *pUser, *ptmp;
    int i, Num = 0;
    boolean login = FALSE;
    FILE *fp1, *fp2, *fp3;
    char *Matrix, c, *tmpMat;
    char filename[19] = "Pacman_History.bin";

    pHead = LoadAll(filename); 

    //updating num:
    ptmp = pHead;
    while (ptmp){
        Num++;
        ptmp = ptmp->pNext;
    }
    
    StartInitialize();
    if(pHead)
        pUser = Un_Logged_Menu(pHead, Num);
    else    
        pUser = pHead = Un_Logged_Menu(pHead, Num);
    Logged_In_Menu(pUser, pHead);
    return 0;
}

void Win(void){
    system("cls");
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\n\n\n\n\n");
    printf("			 *     *       ****       *       *\n");
    printf("			  *   *      *      *     *       *\n");
    printf("			   * *      *        *    *       *\n");
    printf("			    *       *        *    *       *\n");
    printf("			    *	     *      *     *       *\n");
    printf("			    *          ****	       *     *\n");
    printf(" 			    *    	                 * *\n");
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("\n\n\n\n");
    printf("            #                   #     #####      #           #      #\n");
    printf("             #                 #        #        # #         #      #\n");
    printf("              #       #       #         #        #   #       #      #\n");
    printf("               #     # #     #          #        #     #     #      #\n");
    printf("                #   #   #   #           #        #       #   #      #\n");
    printf("                 # #     # #            #        #         # #\n");
    printf("                  #       #           #####      #           #      #\n");
    //play audio
    //score, information
    //sleep
    sleep(10);
    system("cls");
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
} //just display
void GameOver(void){
    system("cls");
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf("\n\n\n\n\n");
    printf("                             *****\n");
    printf("                           *                  *                *     *         *******\n");
    printf("                         *                   * *              * *   * *        * \n");
    printf("                        *                   *   *            *   * *   *       *\n");
    printf("                        *      *******     *******          *     *     *      *******\n");
    printf("                         *          *     *       *        *             *     *\n");
    printf("                           *      *      *         *      *               *    *\n");
    printf("                             ***        *           *    *                 *   *******\n");
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("\n\n\n");
    printf("                            ######      #             #   #######     ######\n");
    printf("                          #        #     #           #    #          #      #\n");
    printf("                         #          #     #         #     #          #       #\n");
    printf("                        #            #     #       #      #          #      #\n");
    printf("                        #            #      #     #       #######    #######\n");
    printf("                         #          #        #   #        #          #  #\n");
    printf("                          #        #          # #         #          #   #\n");
    printf("                            ######             #          #          #    # \n");
    printf("                                                          #######    #     #\n");
    //play audio
    sleep(7);
    system("cls");
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    //back to menu
} //just display
void StartInitialize(void){
    //No changes
    //print welcom in white:
    printf("O           O   OOOOO   O         OOO      OOO          O   O          *******  ***\n");
    printf(" O         O    O       O       O        O     O       O O O O            *   *     *\n");
    printf("  O   O   O     OOOOO   O      O        O       O     O   O   O           *  *       *\n");
    printf("   O O O O      O       O       O        O     O     O         O          *   *     *\n");
    printf("    O   O       OOOOO   OOOOO     OOO      OOO      O           O         *     ***\n");

    //wait 3sec
    sleep(3);
    //set color to red:
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

    printf("\n\n\n\n\n\n\n\n\n");
    //system("cls");
    printf("                      ##### #           #               #######\n");
    printf("                      #       #        # #             #       \n");
    printf("                      #        #      #   #           #        \n");
    printf("                      #        #     #     #         #         \n");
    printf("                      #       #     #       #       #          \n");
    printf("                      ##### #      ###########     #           \n");
    printf("                      #           #           #     #          \n");
    printf("                      #          #             #     #         \n");
    printf("                      #         #               #     #        \n");
    printf("                      #        #                 #     #       \n");
    printf("                      #       #                   #     #######\n");

    //play AUDIO 
    //change color to green
    //set cursor position:
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("                #         #                       #             #         #\n");
    printf("               # #       # #                     # #            ##        #\n");
    printf("              #   #     #   #                   #   #           # #       #\n");
    printf("             #     #   #     #                 #     #          #  #      #\n");
    printf("            #       # #       #               #       #         #   #     #\n");
    printf("           #         #         #             ###########        #    #    #\n");
    printf("          #                     #           #           #       #     #   #\n");
    printf("         #                       #         #             #      #      #  #\n");
    printf("        #                         #       #               #     #       # #\n");
    printf("       #                           #     #                 #    #        ##\n");
    printf("      #                             #   #                   #   #         #\n");

    setColor(FOREGROUND_INTENSITY | FOREGROUND_INTENSITY);
    sleep(4);
    printf("Press any key to continue...");
    while (1) {
        int x = rand() % 80; // مختصات تصادفی برای x
        int y = rand() % 25; // مختصات تصادفی برای y
        
        gotoxy(x, y);
        printf("X");

        Sleep(300); // توقف نیم ثانیه
        if(kbhit()>0){
            //stop audio
            //next page
            system("cls");
            break;
        }
    }
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}//just display

void Logged_In_Menu(USER* pUser, USER* Head){
    system("cls");

    boolean login = TRUE;
    char dif;
    int m, n, cmd2, cmd3, cmd1;
    char **tmpMatrix = NULL;
    
    while(login){
        printf("\nPlay  (1)\nLogout  (2)\nDelete Account  (3)\nExit  (0)\n");
        scanf ("%d", &cmd1);        
        switch (cmd1){
            case 0:
                exit(0);
            case 1:
                system("cls");
                if(pUser->Status){
                    while(!tmpMatrix){
                        system("cls");
                        printf("You have an unfinished game!\n\nResume last game (1)\nStart new Game (2)\nBack (0)\n");
                        scanf ("%d", &cmd2);
                        switch(cmd2){
                            case 0:
                                break;
                            case 1:
                                //resume game
                                FILE* filep;
                                filep = fopen(pUser->FileName, "r");
                                fread(&m, sizeof(int), 1, filep);
                                fread(&n, sizeof(int), 1, filep);
                                fread(tmpMatrix, sizeof(char), m*n, filep);
                            case 2:
                                //start new game
                                //ask for difficultly
                                printf("Enter your desired difficulty:\n Easy(1)\n Medium(2)\n Hard(3)\n");
                                scanf("%d", &cmd3);
                                
                                while(tmpMatrix==NULL){
                                    switch (cmd3){
                                        case 1:
                                            //read map a
                                            tmpMatrix = LoadMap("mapA.txt");
                                            dif = 'A';
                                            break;
                                        case 2:
                                            //read map b
                                            tmpMatrix = LoadMap("mapB.txt");
                                            dif = 'B';
                                            break;
                                        case 3:
                                            //read map c
                                            tmpMatrix = LoadMap("mapC.txt");
                                            dif = 'C';
                                            break;
                                        default:
                                            printf("Pleas enter from given numbers.\n");
                                            system("cls");
                                            break;
                                    }
                                }
                                system("cls");
                                break;
                            default:
                                printf("Pleas enter from given numbers...");
                                sleep(3);
                                system("cls");
                                break;
                        }
                    }
                    //now tmpMat is ready
                }
                else{
                    while(!tmpMatrix){
                        system("cls");
                        printf("\nStart new Game (1)\nBack (0)\n");
                        scanf ("%d", &cmd2);
                        switch(cmd2){
                            case 0:
                                break;
                            case 1:
                                //start new game
                                //ask for difficultly
                                printf("Enter your desired difficulty:\n Easy(1)\n Medium(2)\n Hard(3)\n");
                                scanf("%d", &cmd3);
                                
                                while(tmpMatrix==NULL){
                                    switch (cmd3){
                                        case 1:
                                            //read map a
                                            tmpMatrix = LoadMap("mapA.txt");
                                            dif = 'A';
                                            break;
                                        case 2:
                                            //read map b
                                            tmpMatrix = LoadMap("mapB.txt");
                                            dif = 'B';
                                            break;
                                        case 3:
                                            //read map c
                                            tmpMatrix = LoadMap("mapC.txt");
                                            dif = 'C';
                                            break;
                                        default:
                                            printf("Pleas enter from given numbers.\n");
                                            sleep(3);
                                            system("cls");
                                            break;
                                    }
                                }
                                system("cls");
                                break;
                            default:
                                printf("Pleas enter from given numbers...");
                                sleep (3);
                                system("cls");
                                break;
                        }
                    }
                    //now tmpMat is ready
                }
                ////////////////*********PLAY********////////////
                break;
            case 2:
                login = FALSE;
                Un_Logged_Menu(Head, Num);
                break;
            case 3:
                DeleteAccount(Head, pUser->ID, Num);
                Num--;
                Un_Logged_Menu(Head, Num);
                break;
            default:
                printf ("Pleas enter from given numbers.");
                sleep(3);
                system("cls");
                break;
        }
    }
    Un_Logged_Menu(Head,Num);
}
USER* Un_Logged_Menu(USER* Head, int num){
    system("cls");
    boolean login = FALSE;
    USER *pUser;
    while (login == FALSE){
        printf("\n Creat Account (1)\n Login (2)\n Exit (0)\n");
        scanf("%d",&cmd);
        switch (cmd){      
            case 0:
                exit(0);    
            case 1:
                Num++;
                printf("\nUsername must be numberic!\n");
                printf("\nUsername: ");
                scanf("%s", &username);
                printf("\nPassword: ");
                scanf("%s", password);

                if (Head)
                    pUser = CreatAccount(username, password, Head, Num);
                else
                    pUser = Head = CreatAccount(username, password, Head, Num);
                if (pUser){
                    login = TRUE;
                    printf("\nCreating account is done successfully\n");
                    sleep(4);
                }
                else {
                    printf("\n Username is duplicated!\n Pleas try again.\n");
                    sleep(5);
                    system("cls");
                }
                break;
            case 2:
                printf("\nUsername: ");
                scanf("%d", &username);
                printf("\nPassword: ");
                scanf("%s", &password);

                pUser = Login(username, password, Head);
                if (pUser){
                    login = TRUE;
                    printf("\nLogin is done successfully\n");
                    sleep(4);
                }   
                else {
                    printf("\n Username or password is incorrect!\n Pleas try again.\n");
                    sleep(5);
                    system("cls");
                }    
                break;
            default:
                printf ("Pleas enter from given numbers.");
                sleep(4);
                system("cls");
                break;
        }
    }
    system("cls");
    //here login is true and we can start the game, logout or delete account:
    return pUser;
}

USER* Login(unsigned long long int user, char* pass, USER* phead){
    USER *p1, *ptmp;
    ptmp = phead;
    while(ptmp){
        if((ptmp->username == user) && strcpy(ptmp->password, pass)!=0 )
            ptmp = ptmp ->pNext;
    }
    if(ptmp->pNext == NULL) { //fail
        return NULL;
    }
    else    return ptmp;

}
USER* CreatAccount(unsigned long long int user, char* pass, USER* phead, int ID){
    USER *p1 = NULL, *ptmp;
    ptmp = phead;
    char* Name;
    int tmpid;
    while(ptmp){
        if((char)(ptmp->username) == user)
            break;
        if(ptmp->pNext!=NULL)   
            ptmp = ptmp->pNext;
        else
            break; 
    }
    
    if(phead!= NULL && ptmp->pNext != NULL){// duplicate Error
        return NULL;
    }    
    else{
        ptmp = phead;
        if (phead){
            while (ptmp->pNext)
                ptmp = ptmp -> pNext;
        }
        p1 = (USER*)malloc(sizeof(USER));
        p1->pNext= NULL;
        if(phead == NULL)
            phead = p1;
        else
            ptmp->pNext = p1;
        p1->username = user;
        strcpy(p1->password, pass);
        scanf ("\nWhat is your name? %s", Name);
        strcpy(p1->name, Name);
        tmpid = ID;
        for(int i=7; i>=0; i--){
            p1->FileName[i] =  tmpid%10 + '0';
        }
        p1->FileName[8] = '.';
        p1->FileName[9] = 't';
        p1->FileName[10] = 't';
        p1->FileName[11] = 't';
        p1->ID = ID;
        p1->Level = 0;
        p1->Status = FALSE;
        if (phead)
            return p1;
        else    
            return phead;
    }
        
} //...
void DeleteAccount(USER* phead, int id, int No){
    USER* ptmp;
    ptmp = phead;
    for(int i=0; i<id-2; i++)
        ptmp = ptmp->pNext;
    if (id<No)
        ptmp->pNext = ptmp ->pNext ->pNext;
    else
        ptmp ->pNext = NULL;
}

char** LoadMap(char* filename){
    char** Mat;
    FILE* fp;
    int m, n;
    fp = fopen(filename, "r");
    fscanf(fp,"%d %d", &m, &n);
    Mat = (char**)malloc(m);
    *Mat = (char*)malloc(n);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            fscanf(fp,"%c", Mat[i][j]); //????????????
        }
    }
    fclose(fp);
    for(int i=0; i<m; i++){
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
} //It load information from file and save to an array

void draw(char** mat, int m, int n){
    int i, j;
    for (i=0; i<m; i++){
        for (j=0; j<n; j++){
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }
}
int Play(USER* User, char**mat, char dif){
    //EatenPoints;
    int Eaten = 0, m = 0, n = 0, i, j, numOfpnt = 0;
    boolean End = FALSE, res = FALSE;
    PACMAN Pacy;
    char input, tmp, **map, inp;
     
    //find row & coloumn in m & n
    if(dif == 'A'){
        m = 5;
        n = 10;
    }
    else{
        if(dif=='B'){
            m = 8;
            n = 10;
        }
        else{
            if(dif=='C'){
                m = 10;
                n = 11;
            }
        }
    }

    //find loc of @ & No of P: 
    for(i=0;i<m;i++){
        for (j=0; j<n; j++){
            if(map[i][j]=='@'){
                Pacy.x = i;
                Pacy.y = j;
                break;
            }
            if(map[i][j] == 'P')
                numOfpnt++;
        }
    }
    printf ("Use the Arrow Keys to move Pacman\n");

    while (1){    
        printf("Name: %s \t Lv: %d \n Score: %d \t Remain: %d\n",User->name, User->Level, Eaten, numOfpnt-Eaten);
    
        map = Import_Mat2Map(mat, m, n);
        draw(map, 4*m, 6*n);
        printf("\nPress E to EXIT\n");
        input= getch();
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
            case 'E':
                system("cls");
                printf("\n\n\n\n\t\t Do you want to save game? (y/n)\n");
                scanf ("%c", &inp);
                if(inp == 'Y' || inp == 'y'){
                    User->Status = TRUE;
                    //save board:
                    if (SaveGame(User, mat, m, n) == FALSE);
                        printf("The Game is not saved!");
                    //sleeeeeeeeeeeeeeep/////////////
                    exit(0);
                }
                break;
            default:
                break;
        }
        if(numOfpnt-Eaten == 0){
            res = 1;
            End = TRUE;
        }            
        if(End==TRUE)
            break;
        else
            input = getch();
    }

    if(res==0){
        User->Level -= 1;
        GameOver();
    }
    else{
        User->Level += 3;
        Win();
    }
    return User->Level;
    
}

boolean SaveAll(char *fileName, USER *Head){
    FILE* fp;
    fp = fopen(fileName, "wb");
    if (fp==NULL)
        return FALSE;
    while (Head){
        fwrite(Head, sizeof(USER), 1, fp);
        Head = Head->pNext;
    }
    fclose(fp);
    return TRUE;
}
USER* LoadAll(char* fileName){
    int No, i;
    FILE *fp;
    USER *Head = NULL, *pNew, *pLast;
    fp = fopen(fileName, "rb");
    if (fp == NULL){
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    Num = No = ftell(fp)/sizeof(USER);
    pNew = pLast = Head;
    for(i=0; i<No; i++){ //is this work to?
        pNew = (USER*)malloc(sizeof(USER));
        pNew->pNext = NULL;
        fread(pNew,sizeof(USER),1,fp);
        
        if (Head == NULL)
            pLast = Head = pNew;
        else{
            pLast->pNext = pNew;
            pLast = pNew;
        }
        pNew = pNew->pNext;
    }
    fclose(fp);
    return Head;

}
boolean SaveGame(USER* user, char** Map, int m, int n){
    FILE *fp;
    USER *tmp;
    int i;

    fwrite(&m,sizeof(int), 1, fp);
    fwrite(&n,sizeof(int), 1, fp);

    tmp = user;
    //here tmp point to user:
    fp = fopen(tmp->FileName, "wb");
    if(fp==NULL)
        return 0;
    
    for(i=0; i<m; i++){
        for (int j=0; j<n; j++){
            fwrite(&Map[i][j],sizeof(char),1,fp);
        }
    }
    fclose(fp);

    return TRUE;

}
char** RestoreGame(USER *Head, int id){
    FILE *fp;
    USER *tmp;
    int i, m, n;
    char **Mat;

    fp = fopen(tmp->FileName, "rb");
    tmp = Head;
    for(i=0; i<id-1; i++)
        tmp = tmp->pNext;
    if (tmp->Status == FALSE || fp == NULL)
        return 0;
    fread(&m,sizeof(int),1,fp);
    fread(&n,sizeof(int),1,fp);
    for(i=0; i<m; i++){
        for (int j=0; j<n; j++){
            fread(&Mat[i][j],sizeof(char),1,fp);
        }
    }
    fclose(fp);
    return Mat;
}

char** Import_Mat2Map(char** mat, int m, int n){
    int i, j, k, l;
    char **NewMat;
    NewMat = (char **)malloc(m*4);
    *NewMat = (char*)malloc(n*6);
    for (i=0; i<m; i++){
        for(j=0; j<n; j++){
            switch (mat[i][j]){
                case '#':
                    for(k=i*4; k<4*i+4; k++){
                        for(l=j*6; l<6*j+6; l++)
                            NewMat[k][l] = '#';
                    }
                    break;
                case ' ':
                    for(k=i*4; k<4*i+4; k++){
                        for(l=j*6; l<6*j+6; l++)
                            NewMat[k][l] = ' ';
                    }
                    break;
                case '@':
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
                        switch (k)
                        {
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
                    break; 
                case 'P':
                    for(k=0; k<4; k++){
                        for(l=0; l<6; l++){
                            NewMat[4*i+k][6*j+l]= ' ';
                        }
                    }
                    NewMat[4*i+1][6*j+2] = '\\';
                    NewMat[4*i+1][6*j+3] = '/';
                    NewMat[4*i+2][6*j+1] = '#';
                    NewMat[4*i+2][6*j+4] = '#';
                    break;
                case 'G':
                    for(k=0; k<6; k++)
                        NewMat[4*i][6*j+k] =' ';
                    for(k=1; k<3; k++){
                        for(l=1; k<6; k+=4){
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
                default:
                    break;
            }
        }
    }
    return NewMat;
}

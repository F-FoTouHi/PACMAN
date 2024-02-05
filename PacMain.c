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
char* RestoreGame(FILE*); //a game of a person
boolean SaveGame( USER*, int, char**, char);
USER* LoadAll(char*);
boolean SaveAll(char*, USER*);

int Play(USER*, char**, char ); //it recieve user information and Map then give the score.

FILE* Import_Mat2Map(char*);
char* Import_Map2Mat (FILE*);


unsigned long long int username;
int cmd, Num;
char password[50];


int main(){
    USER* pHead = NULL, *pUser;
    int i, Num = 0;
    boolean login = FALSE;
    FILE *fp1, *fp2, *fp3;
    char *Matrix, c, *tmpMat;
    pHead = LoadAll(); //******************
    //updating num**************
    StartInitialize();


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

    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    //system("cls");
    printf("##### #           #               #######\n");
    printf("#       #        # #             #       \n");
    printf("#        #      #   #           #        \n");
    printf("#        #     #     #         #         \n");
    printf("#       #     #       #       #          \n");
    printf("##### #      ###########     #           \n");
    printf("#           #           #     #          \n");
    printf("#          #             #     #         \n");
    printf("#         #               #     #        \n");
    printf("#        #                 #     #       \n");
    printf("#       #                   #     #######\n");

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
    printf("Press any key to continue...");
    if(kbhit>0){
        //stop audio
        //next page
        system("cls");
    }
}//just display

void Logged_In_Menu(USER* pUser, USER* Head){
    system("cls");

    boolean login = FALSE;
    char dif;
    int m, n;
    char **tmpMatrix = NULL;
    
    while(login){
        printf("\nPlay  (1)\nLogout  (2)\nDelete Account  (3)\nExit  (0)\n");
        scanf ("%d", &cmd);        
        switch (cmd){
            case 0:
                exit(0);
            case 1:
                system("cls");
                if(pUser->Status){
                    while(!tmpMatrix){
                        system("cls");
                        printf("You have an unfinished game!\n\nResume last game (1)\nStart new Game (2)\nBack (0)\n");
                        scanf ("%d", &cmd);
                        switch(cmd){
                            case 0:
                                break;
                            case 1:
                                //resume game
                                FILE* filep;
                                filep = fopen(pUser->FileName, "rb");
                                fread(&m, sizeof(int), 1, filep);
                                fread(&n, sizeof(int), 1, filep);
                                fread(tmpMatrix, sizeof(char), m*n, filep);
                            case 2:
                                //start new game
                                //ask for difficultly
                                printf("Enter your desired difficulty:\n Easy(1)\n Medium(2)\n Hard(3)\n");
                                scanf("%d", &cmd);
                                
                                while(tmpMatrix==NULL){
                                    switch (cmd){
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
                        scanf ("%d", &cmd);
                        switch(cmd){
                            case 0:
                                break;
                            case 1:
                                //start new game
                                //ask for difficultly
                                printf("Enter your desired difficulty:\n Easy(1)\n Medium(2)\n Hard(3)\n");
                                scanf("%d", &cmd);
                                
                                while(tmpMatrix==NULL){
                                    switch (cmd){
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
                system("cls");
                break;
        }
        printf("\nEnter 1 to Play\n Enter 2 to logout\nEnter 3 to delete account\n Enter 0 to Exit\n");
        scanf ("%d", &cmd);
    }
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
                printf("\nUsername: ");
                scanf("%s", &username);
                printf("\nPassword: ");
                scanf("%s", password);

                pUser = CreatAccount(username, password, Head, Num);
                if (pUser){
                    login = TRUE;

                }
                else 
                    printf("\n Username is duplicated!\n Pleas try again.\n");
                    system("cls");
                break;
            case 2:
                printf("\nUsername: ");
                scanf("%d", &username);
                printf("\nPassword: ");
                scanf("%s", &password);

                pUser = Login(username, password, Head);
                if (pUser)
                    login = TRUE;
                else 
                    printf("\n Username or password is incorrect!\n Pleas try again.\n");
                    system("cls");
                break;
            default:
                printf ("Pleas enter from given numbers.");
                system("cls");
                break;
        }
    }
    system("cls");
    //here login is true and we can start the game, logout or delete account:
    Logged_In_Menu(pUser, Head);
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
        if(phead)
            phead = p1;
        else
            ptmp->pNext = p1;
        p1->username = user;
        strcpy(p1->password, pass);
        scanf ("\nWhat is your name? %s", Name);
        strcpy(p1->name, Name);
        tmpid = ID;
        for(int i=8; i>0; i--){
            p1->FileName[i] =  tmpid%10 + '0';
        }
        p1->ID = ID;
        p1->Level = 0;
        p1->Status = FALSE;
        return p1;
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

int Play(USER* User, char**map, char dif){
    //User->name
    //EatenPoints;
    //Exit...
    //Remain points
    int Eaten = 0, m = 0, n = 0, i, j;
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
    boolean Exit = FALSE, End = FALSE, res;
    PACMAN Pacy;
    char inp, tmp;
    //find loc of pacman
    for(i=0;i<m;i++){
        for (j=0; j<n; j++){
            if(map[i][j]=='@'){
                Pacy.x = i;
                Pacy.y = j;
                break;
            }
        }
    }
    while (Exit==FALSE && End == FALSE){
        for(i=0;i<m;i++){
            for (j=0; j<n; j++){
                printf("%c", map[i][j]);
            }
        }
        scanf("%c", &inp);
        while (inp){
            switch (inp){
                case 72://UP
                    if(map[Pacy.x-1][Pacy.y] != '#'){
                        if(map[Pacy.x-1][Pacy.y]=='G'){
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if(map[Pacy.x-1][Pacy.y]=='P'){
                                Eaten++;
                            }
                            map[Pacy.x-1][Pacy.y]='@';
                            map[Pacy.x][Pacy.y] = '\0';
                            Pacy.x -= 1;
                        }
                    }
                    break;
                case 80://D
                    if(map[Pacy.x+1][Pacy.y] != '#'){
                        if(map[Pacy.x+1][Pacy.y]=='G'){
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if(map[Pacy.x+1][Pacy.y]=='P'){
                                Eaten++;
                            }
                            map[Pacy.x+1][Pacy.y]='@';
                            map[Pacy.x][Pacy.y] = '\0';
                            Pacy.x += 1;
                        }
                    }
                    break;
                case 75://L
                    if(map[Pacy.x][Pacy.y-1] != '#'){
                        if(map[Pacy.x][Pacy.y-1]=='G'){
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if(map[Pacy.x][Pacy.y-1]=='P'){
                                Eaten++;
                            }
                            map[Pacy.x][Pacy.y-1]='@';
                            map[Pacy.x][Pacy.y] = '\0';
                            Pacy.y -= 1;
                        }
                    }
                    break;
                case 77://R
                    if(map[Pacy.x][Pacy.y+1] != '#'){
                        if(map[Pacy.x-1][Pacy.y]=='G'){
                            res = 0;
                            End = TRUE;
                        }
                        else{
                            if(map[Pacy.x][Pacy.y+1]=='P'){
                                Eaten++;
                            }
                            map[Pacy.x][Pacy.y+1]='@';
                            map[Pacy.x][Pacy.y] = '\0';
                            Pacy.y += 1;
                        }
                    }
                    break;
                default:
                    break;
            }
            if(End==TRUE)
                break;
            scanf("%c", &inp);
        }
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

bool SaveAll(char* fileName, USER* Head){
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
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    No = ftell(fp)/sizeof(USER);
    Num = No;
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

boolean SaveGame(USER* Head, int id, char** Map, char Dif){
    FILE *fp;
    USER *tmp;
    int i, m = 0, n = 0;

    switch (Dif){
        case 'A':
            m = 5;
            n = 10;
            break;
        case 'B':
            m = 8;
            n = 10;
            break;
        case 'C':
            m = 10;
            n = 11;
            break;
        default:
            break;
    }
    fwrite(&m,sizeof(int), 1, fp);
    fwrite(&n,sizeof(int), 1, fp);
    tmp = Head;
    for(i=0; i<id-1; i++){
        tmp = tmp->pNext;
    }
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
char* RestoreGame(USER* Head, int id, ){}

FILE* Import_Mat2Map(char*){}
char* Import_Map2Mat (FILE*){}

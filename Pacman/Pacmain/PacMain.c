#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <graphic.h>

typedef struct Pacman{
    char name[50];
    int ID;
    int Level;
    bool Status; // 0 if it finished and 1 if it could restore.
    int user;
    char password[30];
}PACMAN;

//Functions:
void StartInitialize(void);
bool Login(int user, char pass[30]); //return 0 if operation unsuccessful and 1 for success.
bool CreatAccount(int user, char pass); //...
int SetSpeed(char); //Fast, Medium, Slow : F, M, S
char* LoadMap(FILE*); //It load information from file and save to an array
char* RestoreGame(FILE*)
FILE* Import_Mat2Map(char*);
char* Import_Map2Mat (FILE*);
FILE* SaveGame(char*);
MoveGhost
Eat
void Win(void); //just display
void GameOver(void); //just display

int main(){
    int i, cmd;
    StartInitialize();
    cin >> cmd;
    while(cmd){
        switch cmd{
            case 1:
            case 2:

        }
        cin >> cmd;
    }    
}

void StartInitialize(void){}//just display
bool Login(int user, char pass[30]){} //return 0 if operation unsuccessful and 1 for success.
bool CreatAccount(int user, char pass){} //...
int SetSpeed(char){} //Fast, Medium, Slow : F, M, S
char* LoadMap(FILE*){} //It load information from file and save to an array
char* RestoreGame(FILE*){}
FILE* Import_Mat2Map(char*){}
char* Import_Map2Mat (FILE*){}
FILE* SaveGame(char*){}
void Win(void){} //just display
void GameOver(void){} //just display
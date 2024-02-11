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
int Logged_In_Menu(USER*, USER*);
void Win(void); //just display
void GameOver(void); //just display
void setColor(int color);
USER* Login(unsigned long long int, char*,  USER*); //return 0 if operation unsuccessful and 1 for success.
USER* CreatAccount(unsigned long long int, char*, USER*, int); //...
void DeleteAccount(USER*, int, int);
char** LoadMap(char*); //It load information from file and save to an array
char** RestoreGame(USER *Head, int id); //a game of a person
boolean SaveGame(USER* user, char** Map, int m, int n);
USER* LoadAll(char*);
boolean SaveAll(char*, USER*);
void draw(char**, int, int);
int Play(USER* , char**, int, int); //it recieve user information and Map then give the score.
char** Import_Mat2Map(char**, int, int);
void gotoxy(short x, short y);
char** allocate (char**, int, int);

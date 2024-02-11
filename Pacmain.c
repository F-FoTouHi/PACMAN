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

#include <Header.h>



int main(){
    USER* pHead = NULL, *pUser, *ptmp;
    int i, Num = 0, A;
    boolean login = FALSE;
    FILE *fp1, *fp2, *fp3;
    char *Matrix, c, *tmpMat;
    

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

    while (pUser!=NULL){ //loop continous for ever!
        login = TRUE;
        while (login == TRUE){
            A = Logged_In_Menu(pUser, pHead);
            if (A == 0)
                login = FALSE;
        }
        pUser = Un_Logged_Menu(pHead, Num);
    }
    

    return 0;
}

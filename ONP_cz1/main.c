#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "stack.h" //biblioteka z internetu dol¹czona do folderu obsluguj¹ca stos

    char prior0[11] = {'0','1','2','3','4','5','6','7','8','9',','}; // ka¿da grupa znakow ma swoj 'numer' aby latwo bylo je pogrupowac
    char prior1[1] = {'('};
    char prior2[2] = {'+','-'};
    char prior3[2] = {'*','/'};
    char prior4[1] = {'^'};
    char closingBrace5[1] = {')'};
    char equal6[1] = {'='};

    int findSourceTab(char sign, char tab[],int tabLength); //ponizej funkcje rozpisane pod main, lecz tu trzeba je zadeklaarowac(przed main)
    int findTabLength(char expr[]);
    int getPriority (char sign);

int main()
{
    char insertedExpr[20];                                     //tab na wpisane wyrazenie
    printf("Podaj wyrazenie do obliczenia ");
    scanf("%s",&insertedExpr);                                 //wczytywanie do tablicy wyrazenia

    char exitTab[20];                                          // tablica wyjscie wypisujaca znaki w kolejnosci ONP
    struct stack *st = newStack(20);                           // stos przetrzymujacy znaki i dodajacy do tablcy wyjscie

    int exprLength = findTabLength(insertedExpr);              //dlugosc wprowadzonego wyrazenia
    printf("final expr length %d\n", exprLength);

    int j = 0;                                                 // indeks tablicy wyjscie
    for (int i=0; i<exprLength; i++){
       char sign = insertedExpr[i];                            //dany element tablicy o indeksie i
       switch(getPriority(sign))                               // getPriority(sign) zwraca priorytet-cyfre charakterysyczna dla danego znaku
       {
        case 5:                                                //gdy priorytet == 5..
            while(!isEmpty(st) && peek(st) != '('){            // dopoki stos nie jest pusty i znak na jego wierzchu nie jest '('.. , funkcja 'isEmpty' jest w osobnym pliku 'stack.h'
                    exitTab[j] = pop(st);                      // to wyrzuc ten znak ze stosu i dodaj do tablicy wyjscie
                    j++;                                       // zwieksz indeks tablicy wyjscie o 1
            }
            pop(st);                                            //wyrzuc '(' ze stosu
            break;
        case 4:                                                 // podobnie jak wyzej
             while(!isEmpty(st) && getPriority(peek(st))!=4){
                    exitTab[j] = pop(st);
                    j++;
             }
             push(st, sign);
             break;
        case 3:
            while(!isEmpty(st) && getPriority(peek(st))>=3){
                exitTab[j] = pop(st);
                j++;
            }
             push(st, sign);
             break;
        case 2:
            while(!isEmpty(st) && getPriority(peek(st))>=2){
                exitTab[j] = pop(st);
                j++;
            }
            push(st, sign);
            break;
        case 1:
            push(st, sign);
            break;
        case 0:
            exitTab[j] = sign;
            j++;
            break;
        case 6:
            while(!isEmpty(st)){
                exitTab[j] = pop(st);
                j++;
            }
            break;
        }
    }

    printf("Wyrazenie w ONP: ");               //drukuje wyrazenie w ONP
    for (int i=0; i<j; i++){                   // i-indeks aktualnego elementu tablicy
       printf(" %c ", exitTab[i]);
    }
    return 0;
}

int findSourceTab(char sign, char tab[], int tabLength){     // funkcja wykorzystywana w getPriority(nizej), szuka czy podany znak 'sign' jest w podanej tablicy 'tab', sign, tab -argumenty

    for(int i=0; i<tabLength; i++){
        if(sign == tab[i]){
            return 1;                                        // jesli jest w tej tablicy zwroc 1
        }
    }
    return 0;
}

int getPriority (char sign){                                 //zwraca priorytet-cyfre charaktrystyczna dla grupy znakow ,w ktorej jest rozpatrywany znak

     if(findSourceTab(sign, closingBrace5, 1)==1)            // jesli findSourceTab() zwroci 1 tzn,ze znak jest w grupie closingBrace5 i ma priorytet 5
        return 5;
     if(findSourceTab(sign, prior4, 1)==1)                   //itd.
        return 4;
     if(findSourceTab(sign, prior3, 2)==1)
        return 3;
     if(findSourceTab(sign, prior2, 2)==1)
        return 2;
     if(findSourceTab(sign, prior1, 1)==1)
        return 1;
     if(findSourceTab(sign, prior0, 11)==1)
        return 0;
     if(findSourceTab(sign, equal6, 1)==1)
        return 6;
}

int findTabLength(char expr[]){ // oblicza dlugosc tablicy
     int i = 0;
     do{
        i++;
     }while (expr[i] != '='); // oblicza indeks do napotkania znaku '='
     return i+1;                   // zwraca ostatni indeks tablicy bez'=' i dodaje 1 doliczajac '=';
}




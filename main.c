#include <stdlib.h>
#include <stdio.h>
#include "gamelib.h"
#include <time.h>

/* Questo file contiene solo la stampa del menu principale e poi richiama una delle
 tre funzioni possibili: crea_mappa(), gioca(), termina_gioco(). */


int main (void) {
    system("clear");
    short uscita = 0;
    time_t t;
    srand((unsigned) time(&t));
    
    printf("È venerdì 13 giugno 1980 ed un gruppo di studenti universitari del Corso di Laurea in Informatica"
           " si trasferiscono in vacanza al “Campeggio Lake Trasymeno”, che sta per riaprire.  Ventitre anni prima, infatti,"
           " nello stesso campeggio, un ragazzino di nome Gieson era annegato per colpa della negligenza di un programmatore:"
           " a causa di un segmentation fault nel suo programma di noleggio delle barche, alla famiglia di Gieson"
           "era stata affidata una barca con un motore difettoso. Gieson però infesta ancora il campeggio, e nutre vendetta"
           " nei confronti degli informatici poco attenti che hanno seguito il corso di Programmazione I giocando a League"
           " of Legends... Giacomo e Marzia, entrambi studenti del primo anno, rimangono isolati dagli altri quando...\n");
    printf("\n[1] Continua\n");
    pause();
    
    do
    {
        system("clear");
        char userChoice;
        
        printf("  ________.__\n" 
               " /  _____/|__| ____   __________   ____\n" 
               "/   \\  ___|  |/ __ \\ /  ___/  _ \\ /    \\ \n"
               "\\    \\_\\  \\  \\  ___/ \\___ (  <_> )   |  \\ \n"
               " \\______  /__|\\___  >____  >____/|___|  / \n"
               "        \\/        \\/     \\/           \\/ \n");
        
        printf("\n\n");
        printf("[1] Crea mappa\n");
        printf("[2] Gioca\n");
        printf("[3] Termina gioco\n");

        do
        {
            printf("\n>");
            scanf(" %c", &userChoice);
            if((userChoice!='1' && userChoice !='2' && userChoice!='3') || getchar()!='\n')
            {
                int ch;
                while((ch = getchar()) != '\n' && ch != EOF); //pulisce il buffer in caso ci fosse più di un carattere
                userChoice = '0';
                printf("Inserisci un comando valido --> (1,2,3)\n");
            }
        }while(userChoice == '0' /*|| getchar() != '\n'*/);

        switch(userChoice)
        {
            case '1':
                crea_mappa();
                break;
            case '2':
                gioca();
                break;
            case '3':
                uscita = termina_gioco();
                break;
            default:
                printf("Errore stampa main");
        }
    }while(uscita != 1);
}

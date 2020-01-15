#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"


static struct Zona* prima_zona = NULL;
static struct Zona* ultima_zona = NULL;

static int contatoreZone = 0;
static short mappa = 0; //1 mappa creata | 0 non creata

static struct Giocatore giacomo;
static struct Giocatore marzia;

//dichiarazione funzioni di crea_mappa()
static void ins_zona();
static void canc_zona();
static void stampa_mappa();
static int chiudi_mappa();
static void free_mappa();

//dichiarazine funzioni di gioca()
static void avanza();
static void mostra_oggetto();
static void prendi_oggetto();
static void cura();
static int usa_adrenalina();
static int gieson();
static void turno();


//******CREA MAPPA e FUNZIONI******
int crea_mappa()
{
    system("clear");
    
    short uscita = 0;
    char userChoice = 0;
    
    if(mappa == 1)
    {
        printf("Esiste già una mappa creata... Rimuoverla per crearne una nuova?\n");
        printf("[1] Torna indietro\n");
        printf("[2] Crea nuova mappa\n");
        do
        {
            printf("\n>");
            scanf(" %c", &userChoice); 
            if((userChoice!='1' && userChoice !='2') || getchar()!='\n')
            {
                int ch;
                while((ch = getchar()) != '\n' && ch != EOF); //pulisce il buffer in caso ci fosse più di un carattere
                userChoice = '0';
                printf("Inserisci un comando valido --> (1,2)\n");
            }
        }while(userChoice!='1' && userChoice !='2');
        
        if(userChoice == '1')
            return 0;
        else
        {
            free_mappa();
            mappa = 0;
        }
    }
    
    do
    {
        system("clear");
        userChoice = '0';

        printf("--Menù creazione mappa--\n");
        printf("\nInserire comando:\n");
        printf("[1] Inserisci una zona\n");
        printf("[2] Elimina una zona\n");
        printf("[3] Stampa la mappa\n");
        printf("[4] Chiudi mappa\n");

        do
        {
            printf("\n>");
            scanf(" %c", &userChoice);
            if((userChoice!='1' && userChoice !='2' && userChoice!='3' && userChoice!='4') || getchar()!='\n')
            {
                int ch;
                while((ch = getchar()) != '\n' && ch != EOF); //pulisce il buffer in caso ci fosse più di un carattere
                userChoice = '0';
                printf("Inserisci un comando valido --> (1,2,3,4)\n");
            }
        }while(userChoice == '0');
        
        switch(userChoice)
        {
            case '1':
                ins_zona();
                break;
            case '2':
                canc_zona();
                break;
            case '3':
                stampa_mappa();
                break;
            case '4':
                uscita = chiudi_mappa();
                break;
            default:
                printf("Errore azione menù crea mappa\n");
        }
    }while(uscita != 1);
    return 0;
}

static void ins_zona() //aggiunge in coda
{
    system("clear");
    struct Zona *new_zona = (struct Zona*) malloc(sizeof(struct Zona));
    short objectProb = 0;
    
    //Scelta tipo zona
    char userChoice = '0';
    printf("Inserire tipo di zona:\n");
    printf("[1] Cucina\n");
    printf("[2] Soggiorno\n");
    printf("[3] Rimessa\n");
    printf("[4] Strada\n");
    printf("[5] Lungo lago\n");
    printf("[6] Uscita campeggio\n");
    do
    {
        printf("\n>");
        scanf(" %c", &userChoice);
        if((userChoice!='1' && userChoice !='2' && userChoice!='3' && userChoice!='4' &&userChoice!='5' && userChoice!='6') || getchar()!='\n')
        {
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF); //pulisce il buffer in caso ci fosse più di un carattere
            userChoice = '0';
            printf("Inserisci un comando valido --> (1,2,3,4,5,6)\n");
        }
    }while(userChoice == '0');
    
    objectProb = rand()%101;
    switch(userChoice)
    {
        case '1':
            new_zona->t_zona = cucina;
            if(objectProb < 30)                           //30%
                new_zona->oggetto = cianfrusaglia;
            else if(objectProb > 30 && objectProb < 50)   //20%
                new_zona->oggetto = bende;
            else if(objectProb > 50 && objectProb < 90)   //40%
                new_zona->oggetto = coltello;
            else                                          //10%
                new_zona->oggetto = adrenalina;
            break;
            
        case '2':
            new_zona->t_zona = soggiorno;
            if(objectProb < 20)                           //20%
                new_zona->oggetto = cianfrusaglia;
            else if(objectProb > 20 && objectProb < 30)   //10%
                new_zona->oggetto = bende;
            else if(objectProb > 30 && objectProb < 40)   //10%
                new_zona->oggetto = coltello;
            else if(objectProb > 40 && objectProb < 70)   //30%
                new_zona->oggetto = pistola;
            else                                          //30%
                new_zona->oggetto = adrenalina;
            break;
            
        case '3':
            new_zona->t_zona = rimessa;
            if(objectProb < 20)                           //20%
                new_zona->oggetto = cianfrusaglia;
            else if(objectProb > 20 && objectProb < 30)   //10%
                new_zona->oggetto = bende;
            else if(objectProb > 30 && objectProb < 60)   //30%
                new_zona->oggetto = coltello;
            else if(objectProb > 60 && objectProb < 90)   //30%
                new_zona->oggetto = benzina;
            else                                          //10%
                new_zona->oggetto = adrenalina;
            break;
            
        case '4':
            new_zona->t_zona = strada;
            if(objectProb < 80)                           //80%
                new_zona->oggetto = cianfrusaglia;
            else if(objectProb > 80 && objectProb < 90)   //10%
                new_zona->oggetto = coltello;
            else                                          //10%
                new_zona->oggetto = benzina;
            break;
            
        case '5':
            new_zona->t_zona = lungo_lago;
            if(objectProb < 70)                           //70%
                new_zona->oggetto = cianfrusaglia;
            else if(objectProb > 70 && objectProb < 80)   //10%
                new_zona->oggetto = coltello;
            else                                          //20%
                new_zona->oggetto = benzina;
            break;
            
        case '6':
            new_zona->t_zona = uscita_campeggio;
            if(objectProb < 90)                           //90%
                new_zona->oggetto = cianfrusaglia;
            else                                          //10%
                new_zona->oggetto = coltello;
            break;
        default:
            printf("Errore calcolo oggetto");
    }
     
    
    new_zona->zona_successiva = NULL;

    if(prima_zona == NULL)
    {
        prima_zona = new_zona;
        ultima_zona = new_zona;
    }
    else
    {
        ultima_zona->zona_successiva = new_zona;
        ultima_zona = new_zona;
    }
    
    contatoreZone++;
    return;
}

static void canc_zona() //elimina ultima zona in coda
{
    system("clear");
    
    if(prima_zona == NULL)
    {
        printf("--Nessuna zona creata da eliminare--\n");
    }
    else
    {
        struct Zona* zona_precedente = NULL;
        struct Zona* scan_zona = prima_zona;
        
        if(scan_zona->zona_successiva == NULL) //nel caso ci fosse solo una zona
        {
            free(scan_zona);
            prima_zona = NULL;
            ultima_zona = NULL;
        }
        else
        {
            do //rimango nel ciclo finche non mi trovo nella zona precedente all'ultima
            {
                if(scan_zona->zona_successiva == ultima_zona)
                {
                    zona_precedente = scan_zona;
                    break;
                }
                else
                    scan_zona = scan_zona->zona_successiva;
            }while(scan_zona->zona_successiva != NULL);
            
            free(zona_precedente->zona_successiva); //libero la memoria dell'ultima zona
            zona_precedente->zona_successiva = NULL;
            ultima_zona = zona_precedente; //assegno la nuova ultima zona
        }
        printf("L'ultima zona inserita nella mappa è stata eliminata.\n");
        contatoreZone--;
    }
    printf("\n[1] Per tornare indietro\n");      
    pause();
    
    return;
}

static void stampa_mappa()
{ 
    system("clear");
    
    if(prima_zona == NULL)
    {
        printf("--Nessuna mappa creata--\n");
    }
    else
    {
        short k = 0;
        struct Zona* scan_zona = prima_zona;
        printf("**Mappa**\n");
        do
        {
            k++;
            printf("\nZona %d:\n", k);
            switch(scan_zona->t_zona)
            {
                case cucina:
                    printf("-Tipo: Cucina\n");
                    break;
                case soggiorno:
                    printf("-Tipo: Soggiorno\n");
                    break;
                case rimessa:
                    printf("-Tipo: Rimessa\n");
                    break;
                case strada:
                    printf("-Tipo: Strada\n");
                    break;
                case lungo_lago:
                    printf("-Tipo: Lungo lago\n");
                    break;
                case uscita_campeggio:
                    printf("-Tipo: Uscita campeggio\n");
                    break;
                default:
                    printf("Errore stampa zona");
            }
            
            switch(scan_zona->oggetto)
            {
                case cianfrusaglia:
                    printf("-Oggetto: Cianfrusaglia\n");
                    break;
                case bende:
                    printf("-Oggetto: Bende\n");
                    break;
                case coltello:
                    printf("-Oggetto: Coltello\n");
                    break;
                case pistola:
                    printf("-Oggetto: Pistola\n");
                    break;
                case benzina:
                    printf("-Oggetto: Benzina\n");
                    break;
                case adrenalina:
                    printf("-Oggetto: Adrenalina\n");
                    break;
                default:
                    printf("Errore stampa oggetto");
            }
            
            scan_zona = scan_zona->zona_successiva;
        }while(scan_zona!= NULL);
    }
    
    printf("\n[1] Per tornare indietro\n");      
    pause();
    return;
}

static int chiudi_mappa()
{
    system("clear");
    
    if(ultima_zona != NULL && contatoreZone>=8 && ultima_zona->t_zona == uscita_campeggio)
    {
        mappa = 1;
        return 1;  
    }   
    else
    {
        printf("Per terminare la creazione della mappa devi:\n");
        printf("-Aver creato almeno 8 zone\n");
        printf("-L'ultima zona deve essere di tipo 'Uscita campeggio'\n");
    }

    printf("\n[1] Per tornare indietro\n");      
    pause();
    
    return 0;
}

static void free_mappa() //dealloca tutte le zone della mappa
{
    if(prima_zona != NULL)
    {
        struct Zona* scan_zona = prima_zona;
        struct Zona* k_zona = NULL;

        do
        {
            k_zona = scan_zona->zona_successiva;
            free(scan_zona);
            scan_zona = k_zona;
        }while(scan_zona != NULL);
        
        prima_zona = NULL;
        ultima_zona = NULL;
    }
    return;
}


//******GIOCA e FUNZIONI******
void gioca()
{
    system("clear");
    
    if(mappa == 0)
    {
        printf("Non esiste nessuna mappa. Creane una!\n");
        printf("[1] Torna indietro\n");
        pause();
        return;        
    }
    
    
    /* 
    Azzero lo zaino di marzia e giacomo per evitare che rinascano nella prossima partita con gli   
    oggetti precendenti inutilizzati. 
    */
    for(short k=0; k<6; k++)                                   
    {
        giacomo.zaino[k] = 0;
        marzia.zaino[k] = 0;
    }
    
    giacomo.stato = vivo;
    giacomo.posizione = prima_zona;
    giacomo.zaino[coltello] = 1;
    
    marzia.stato = vivo;
    marzia.posizione = prima_zona;
    marzia.zaino[adrenalina] = 2;
    
    short rand_turno = -1;
    
    do
    {
        if((giacomo.stato != morto && giacomo.stato != uscito) && (marzia.stato != morto && marzia.stato != uscito))
        {
            rand_turno = rand()%2;
            //NOTA: turno(0)=giacomo // turno(1)=marzia
            if(rand_turno == 0)
            {
                    turno(0);
                    turno(1);
            }
            else
            {
                    turno(1);
                    turno(0);
            }
        }
        if((giacomo.stato == morto || giacomo.stato == uscito) && (marzia.stato != morto && marzia.stato != uscito))
        {
            turno(1);
        }
        if((giacomo.stato != morto && giacomo.stato != uscito) && (marzia.stato == morto || marzia.stato == uscito))
        {
            turno(0);
        }
        
        if(giacomo.stato == morto && marzia.stato == uscito)
        {
            system("clear");
            printf("Solo Marzia è riuscita a salvarsi!\n");
            break;
        }
        if(giacomo.stato == uscito && marzia.stato == morto)
        {
            system("clear");
            printf("Solo Giacomo è riuscito a salvarsi!\n");
            break;
        }
        if(giacomo.stato == morto && marzia.stato == morto)
        {
            system("clear");
            printf("**Game Over**\n");
            break;
        } 
        if(giacomo.stato == uscito && marzia.stato == uscito)
        {
            system("clear");
            printf("**Hai vinto**");
            break;
        }
    }while(1);
    
    printf("\n\n[1] Torna al menù principale\n");
    pause();
    return;
    
    
}

static void turno(int id)
{   

    struct Giocatore* player;
    char userChoice = 0;
    
    short turni_adrenalina = 0;
    short giesonAppear = 0;
    short giesonProb = 30;
    static short benzina = 0;
    
    static int gPrendiOggetto = 0; //var per determinare se un personaggio
    static int mPrendiOggetto = 0; //può prendere l'oggetto nella zona in cui si trova
    
    do
    {
        system("clear");
        
        //scelta del turno
        if(id == 0)
        {
            printf("Turno di Giacomo:\n");
            player = &giacomo;

        }
        else
        {
            printf("Turno di Marzia:\n");
            player = &marzia;
        }

        
        if(player->stato == morto)  //controllo stato salute in caso di uso di adrenalina
        {
            return;
        }
        
        
        //Riepilogo stats player
        struct Zona* scan_zona = player->posizione;
        printf("    *Salute:");
        switch(player->stato)
        {
            case ferito:
                printf(" Ferito\n");
                break;
            case vivo:
                printf(" Vivo\n");
                break;
            default:
                printf("Errore stampa salute giocatore");
        }
        printf("    *Zona attuale:");
        switch(scan_zona->t_zona)
        {
            case cucina:
                printf(" Cucina\n");
                break;
            case soggiorno:
                printf(" Soggiorno\n");
                break;
            case rimessa:
                printf(" Rimessa\n");
                break;
            case strada:
                printf(" Strada\n");
                break;
            case lungo_lago:
                printf(" Lungo lago\n");
                break;
            case uscita_campeggio:
                printf(" Uscita campeggio\n");
                break;
            default:
                printf("Errore stampa zona");
        }
        printf("    *Zaino:\n");
        for(short k=0; k<6; k++)
        {
            if(player->zaino[k] != 0)
            {
                switch(k)
                {
                    case 0:
                        printf("      - %d unità di cianfrusaglia\n", player->zaino[k]);
                        break;
                    case 1:
                        printf("      - %d unità di bende\n", player->zaino[k]);
                        break;
                    case 2:
                        printf("      - %d unità di coltello\n", player->zaino[k]);
                        break;
                    case 3:
                        printf("      - %d unità di pistola\n", player->zaino[k]);
                        break;
                    case 4:
                        printf("      - %d unità di benzina\n", player->zaino[k]);
                        break;
                    case 5:
                        printf("      - %d unità di adrenalina\n", player->zaino[k]);
                        break;
                    default:
                        printf("Errore stampa zaino");
                }
            }   
        }

        if(turni_adrenalina>0)
            turni_adrenalina--;

        //stampa lista azioni player
        printf("\nCosa vuoi fare?\n");
        printf("[1] Avanza nella prossima zona\n");
        if((id == 0 && gPrendiOggetto == 0) || (id == 1 && mPrendiOggetto == 0))
            printf("[2] Mostra oggetto\n");
        else if((id == 0 && gPrendiOggetto == 1) || (id == 1 && mPrendiOggetto == 1))
            printf("[2] Prendi oggetto\n");
        printf("[3] Cura\n");
        printf("[4] Utilizza adrenalina\n");

        do
        {
            printf("\n>");
            scanf(" %c", &userChoice);
            if((userChoice!='1' && userChoice !='2' && userChoice!='3' && userChoice!='4') || getchar()!='\n')
            {
                int ch;
                while((ch = getchar()) != '\n' && ch != EOF); //pulisce il buffer in caso ci fosse più di un carattere
                userChoice = '0';
                printf("Inserisci un comando valido --> (1,2,3,4)\n");
            }
        }while(userChoice == '0');

        switch(userChoice)
        {
            case '1':
                avanza(player);

                if(id == 0)
                    gPrendiOggetto = 0;
                else
                    mPrendiOggetto = 0;
                break;

            case '2':
                if((id == 0 && gPrendiOggetto == 0) || (id == 1 && mPrendiOggetto == 0))
                    mostra_oggetto(player, id, &gPrendiOggetto, &mPrendiOggetto);
                 else if((id == 0 && gPrendiOggetto == 1) || (id == 1 && mPrendiOggetto == 1))
                    prendi_oggetto(player, id, &gPrendiOggetto, &mPrendiOggetto);
                break;

            case '3':
                cura(player);
                break;

            case '4':
                turni_adrenalina = usa_adrenalina(player);
                break;

            default:
                printf("Errore scelta azioni giocatore");
            }

        //Apparizione Gieson
        if(player->stato != uscito && benzina == 0)
        {
            //calcolo apparizione gieson
            giesonAppear = rand()%101;
            if(giacomo.stato == morto || giacomo.stato == uscito || marzia.stato == morto || marzia.stato == uscito)      
                giesonProb = 50;

            if(player->posizione == ultima_zona)
                giesonProb = 75;

            if(giesonAppear < giesonProb)
            {
                benzina = gieson(player, id, &gPrendiOggetto, &mPrendiOggetto);
            }
        }
        
        if(benzina > 0)
            benzina--;
           
    }while(turni_adrenalina != 0);
    
    return;
}

static void avanza(struct Giocatore* player)
{
    struct Zona* zona_attuale;
    if(player->posizione == ultima_zona)
    {
        printf("\nSei uscito dal campeggio!\n");
        printf("[1] Continua");
        player->stato = uscito;
        pause();
        return;  
    }
    zona_attuale = player->posizione;
    player->posizione = zona_attuale->zona_successiva;
    return;
}

static void mostra_oggetto(struct Giocatore* player, int id, int* g, int* m)
{
    struct Zona* scan_zona = player->posizione;
    
    printf("\nIn questa zona c'è un'");
    switch(scan_zona->oggetto)
    {
        case 0:
            printf(" unità di cianfrusaglia\n");
            break;
        case 1:
            printf(" unità di bende\n");
            break;
        case 2:
            printf(" unità di coltello\n");
            break;
        case 3:
            printf(" unità di pistola\n");
            break;
        case 4:
            printf(" unità di benzina\n");
            break;
        case 5:
            printf(" unità di adrenalina\n");
            break;
        default:
            printf("Errore mostra oggetto");
    }
    
    if(id == 0)
        *g = 1;
    else
        *m = 1; 
    
    printf("[1] Ok!");
    pause();
    return;
}

static void prendi_oggetto(struct Giocatore* player, int id, int* g, int* m)
{
    struct Zona* scan_zona = player->posizione;
    
    switch(scan_zona->oggetto)
    {
        case 0:
            player->zaino[0]++;
            break;
        case 1:
            player->zaino[1]++;
            break;
        case 2:
            player->zaino[2]++;
            break;
        case 3:
            player->zaino[3]++;
            break;
        case 4:
            player->zaino[4]++;
            break;
        case 5:
            player->zaino[5]++;
            break;
        default:
            printf("Errore fun_prendi oggetto");
    }
    scan_zona->oggetto = cianfrusaglia;
    if(id == 0)
        *g = 0;
    else
        *m = 0;
    
    printf("\nOggetto preso!\n");
    printf("[1] Ok!\n");
    pause();
}

static void cura(struct Giocatore* player)
{
    if(player->zaino[1])
    {
        if(player->stato == vivo)
            printf("\nNon hai bisogno di cure!\n");
        else
        {
            player->stato++;
            player->zaino[1]--;
            printf("\nHai utilizzato un' unità di bende per curarti!\n");
        }           
    }
    else
        printf("\nNon hai delle bende per curarti!\n");
    
    printf("[1] Ok!\n");
    pause();
    return;
}

static int usa_adrenalina(struct Giocatore* player)
{
    short k = 0;
    if(player->zaino[5])
    {
        player->zaino[5]--;
        printf("\nHai utilizzato un' unità di adrenalina!\n"
               "Hai altri due turni a disposizione.\n");
        k = 2;
    }
    else
        printf("\nNon possiedi nessuna unità di adrenalina\n");
    
    printf("[1] Ok!\n");
    pause();
    return k;
}

static int gieson(struct Giocatore* player, int id, int* g, int* m)
{
    short nDifesa = 0;
    short usaBenzina = 0;
    
    system("clear");
    printf("AAARGH! Sono gieson!\n");
    printf("E tu adesso morirai!\n");
    
    if(player->zaino[coltello] > 0 || player->zaino[pistola] > 0 || player->zaino[benzina] > 0)
    {
        nDifesa++;
    }
    
    if(nDifesa > 0)
    {
        short sceltaSbagliata = 0;
        char userChoice = '0';
        
        printf("\nPuoi difenderti:\n");
        printf("[1] Usa coltello\n");
        printf("[2] Usa pistola\n");
        printf("[3] Usa benzina\n");
        
        do
        {
            printf("\n>");
            scanf(" %c", &userChoice);
            if((userChoice!='1' && userChoice !='2' && userChoice !='3') || getchar()!='\n')
            {
                int ch;
                while((ch = getchar()) != '\n' && ch != EOF); //pulisce il buffer in caso ci fosse più di un carattere
                userChoice = '0';
                printf("Inserisci un comando valido --> (1,2)\n");
            }
        }while(userChoice == '0');

        switch(userChoice)
        {
            case '1':
                if(player->zaino[coltello] > 0)
                {
                    player->stato--;
                    player->zaino[coltello]--;
                    printf("Hai scacciato Gieson utilizzando un coltello ma sei rimasto ferito!\n");
                }
                else
                {
                    sceltaSbagliata = 1;
                }
                break;
                
            case '2':
                if(player->zaino[pistola] > 0)
                {
                    player->zaino[pistola]--;
                    printf("Hai scacciato Gieson utilizzando una pistola, ben fatto!\n");
                }
                else
                {
                    sceltaSbagliata = 1;
                }
                break;
                
            case '3':
                if(player->zaino[benzina] > 0)
                {
                    player->zaino[benzina]--;
                    printf("Hai scacciato Gieson utilizzando la benzina, per 4 turni dovrebbe starsene lontano...\n");
                    usaBenzina = 5;
                }
                else
                {
                    sceltaSbagliata = 1;
                }
                break;
            default:
                printf("ERRORE Menu difesa");
        }
        if(sceltaSbagliata == 1)
        {
            printf("Per la paura hai sbagliato tasca dello zaino e Gieson ha avuto la meglio!\n");
            player->stato = morto;
            if(id == 0)
                *g = 0;
            else
                *m = 0;
        }
    }
    
    else
    {
        player->stato = morto;
        if(id == 0)
            *g = 0;
        else
            *m = 0;
    }
    
    printf("\n[1] Prossimo turno\n");
    pause();
    
    return usaBenzina;
}


//******TERMINA GIOCO e funzioni aggiuntive*****
int termina_gioco()
{
    system("clear");
    free_mappa();
    printf("  ________                        ________\n"
           " /  _____/_____    _____   ____   \\_____  \\___  __ ___________\n"
           "/   \\  ___\\__  \\  /     \\_/ __ \\   /   |   \\  \\/ // __ \\_  __ \\\n"
           "\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  /    |    \\   /\\  ___/|  | \\/\n"
           " \\______  (____  /__|_|  /\\___  > \\_______  /\\_/  \\___  >__|\n"
           "        \\/     \\/      \\/     \\/          \\/          \\/\n\n\n");
    return 1;
}

void pause() //attende che il giocatore prema 1 in modo da far visualizzare un messaggio
{
    char userChoice = '0';
    do
    {
        printf("\n>");
        scanf(" %c", &userChoice);
        if(userChoice !='1' || getchar()!='\n')
        {
            int ch;
            while((ch = getchar()) != '\n' && ch != EOF); //pulisce il buffer in caso ci fosse più di un carattere
            printf("*Comando non valido*\n");
            userChoice = '0';
        }
            
    }while(userChoice != '1');
    return;
}







/* Questo file contiene le dichiarazioni delle funzioni crea_mappa(), gioca(), termina_gioco().
 Continene anche le definizioni dei tipi utilizzati in gamelib.c:
 struct Giocatore, struct Zona, enum Stato_giocatore, enum Tipo_zona, enum Tipo_oggetto. */

//dichiarazione funzioni chiamate nel main
int crea_mappa();
void gioca();
int termina_gioco();

//dichiarazione funzioni aggiuntive
void pause();

//dichiarazioni enum
typedef enum{morto, ferito, vivo, uscito} Stato_giocatore;
typedef enum{cianfrusaglia, bende, coltello, pistola, benzina, adrenalina} Tipo_oggetto;
typedef enum{cucina, soggiorno, rimessa, strada, lungo_lago, uscita_campeggio} Tipo_zona;
   
struct Zona
{
    Tipo_zona t_zona;
    Tipo_oggetto oggetto;
    struct Zona* zona_successiva;
};

struct Giocatore
{
    Stato_giocatore stato;
    struct Zona* posizione;
    unsigned short zaino[6];
};







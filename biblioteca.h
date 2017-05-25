#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// Buffer dei dati
#define MAX_GIORNO 3
#define MAX_MESE 3
#define MAX_ANNO 5

// Dati cliente
#define MAX_LEN_CLIENTE 50
#define MAX_LEN_ISBN 4
#define MAX_LEN_LIBRO 60
#define MAX_LEN_AUTORI 3

// Codici relativi al menu principale
#define USCITA '0'
#define NUOVO_CLIENTE '1'
#define NUOVO_LIBRO '2'
#define PRESTITO_LIBRO '3'
#define RIENTRO_LIBRO '4'
#define SCHEDA_CLIENTE '5'
#define GESTIONE_LISTE '6'
#define CARICA_LISTA '7'
#define ABILITA_DISABILITA '8'

// Codici debug
#define LISTA_LIBRI 'q'
#define LISTA_CLIENTI 'w'

// Codici debug Uppercase
#define U_LISTA_LIBRI 'Q'
#define U_LISTA_CLIENTI 'W'

// Codici sottomenu
#define MENU_0 0
#define MENU_1 1

// Codici relativi al menu Liste
#define RIMUOVI_CLIENTE '1'
#define RIMUOVI_LIBRO '2'

// Codici d' errore
#define OK 0
#define MEMORY_FULL -1
#define NOT_FOUND -2
#define FILE_NOT_FOUND -3

// Macro Booleane
#define FALSE 0
#define TRUE 1

typedef struct{
    char giorno[MAX_GIORNO];
    char mese[MAX_MESE];
    char anno[MAX_ANNO];
}data;

typedef struct{
    char nome[MAX_LEN_CLIENTE];
    char cognome[MAX_LEN_CLIENTE];
    data data;
    int id;
    int libri_posseduti;
}cliente;

typedef struct{
    cliente clienti;
    int size;
}archivio_clienti;

typedef struct {
    char nome[MAX_LEN_CLIENTE];
    char cognome[MAX_LEN_CLIENTE];
}autore;

typedef struct{
    char isbn[MAX_LEN_ISBN];
    char titolo[MAX_LEN_LIBRO];
    int num_copie;
    int num_autori;
    autore autori[MAX_LEN_AUTORI];
}libro;

typedef struct{
    libro libri;
    int size;
}archivio_libri;

typedef struct{
    char isbn[MAX_LEN_ISBN];
    int codice_cliente;
    int isReturned;
    data data_prestito;
    data data_consegna;
    data data_rientro;
}prestito;

typedef struct{
    prestito prestito;
    int size;
}archivio_prestiti;

typedef struct nodo_clienti {
    archivio_clienti val;
    struct nodo_clienti * next;
} lista_clienti;

typedef struct nodo_libri {
    archivio_libri val;
    struct nodo_libri* next;
}lista_libri;

typedef struct nodo_prestiti {
    archivio_prestiti val;
    struct nodo_prestiti* next;
}lista_prestiti;

// Funzione gestione del cliente
cliente inserimento_nuovo_cliente();
void stampa_dati_cliente(lista_clienti*, int);
int crea_elemento(lista_clienti**, cliente);
int cerca_se_cliente_ha_libro(int, char[], lista_prestiti*);

// Funzioni gestione libri
libro inserimento_nuovo_libro(char[]);
int inserimento_libro_in_lista(lista_libri**, libro);
void stampa_dati_libro(char[], lista_libri*, int);

// Funzioni di ricerca
lista_libri* cerca_isbn_in_archivio(lista_libri*, char[]);
lista_clienti* cerca_cliente_da_id(int, lista_clienti*);
int ricerca_libri_in_possesso(int, lista_libri*);

// Funzioni di gestione archivio_prestiti
int inserimento_prestiti_in_lista(char[], int, lista_prestiti**);
void inserimento_rientro_libro(lista_prestiti**);
lista_prestiti* incrocia_dati(char[], int, lista_prestiti*);
void riepilogoPrestiti(lista_clienti*, lista_libri*);
void stampa_libro_in_prestito(int, int, lista_prestiti*, lista_libri*);
int controlla_se_libro_in_prestito(char[], lista_prestiti*);

// Funzioni gestione Liste
int rimuovi_cliente_da_lista(lista_clienti*, lista_clienti**);
int rimuovi_libro_da_lista(lista_libri*, lista_libri**);
int rimuovi_libro_da_cliente(int, char[], lista_prestiti**);

// Gestione stampa errori
void scelta_non_consentita(int);
void cliente_non_trovato();
void libro_non_trovato();
void cliente_non_in_possesso_del_libro();
void data_rientro_non_consentita();
void impossibile_eliminare_cliente();
void impossibile_eliminare_libro(int);
void caricamento_fallito();
void caricamento_ok();
void warning();

// Gestione stampa successi
void rimozione_avvenuta();

// Funzioni helper
void ricarica_schermata();
void pulizia_tabella();

// Funzioni di debug
void stampa_lista_clienti(lista_clienti*);
void stampa_lista_libri(lista_libri*);

// Funzioni gestione file su disco
void salva_lista_clienti(lista_clienti*);
void salva_lista_prestiti(lista_prestiti*);
void salva_lista_libri(lista_libri*);

int carica_lista_clienti(lista_clienti**);
int carica_lista_libri(lista_libri**);
int carica_lista_prestiti(lista_prestiti**);

#endif
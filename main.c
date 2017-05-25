#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "utils.h"

int main(int argc, char* argv[]) {
    cliente cliente;
    libro libro;

    int risultato, id, clientId, saveToFile = TRUE;
    int carica_libri, carica_clienti, carica_prestiti;
    char scelta[20], _scelta[20];
    int errore_scelta = FALSE;
    int warning_generico = FALSE;
    char isbn[MAX_LEN_ISBN];

    // Testa della lista clienti
    lista_clienti *head_clienti = NULL;

    // Testa della lista libri
    lista_libri *head_libri = NULL;

    // Testa della lista prestiti
    lista_prestiti *head_prestiti = NULL;

    lista_libri *tmp_lista_libri;
    lista_clienti *tmp_lista_clienti;
    lista_prestiti *tmp_lista_prestiti;

    do {
        // Se TRUE allora è stata fatta la scelta abagliata e il messaggio
        // apparirà nella stessa schermata senza ripulirla
        if(errore_scelta == FALSE && warning_generico == FALSE)
            cls();

        box(1, 2, 20, 80); // Grafica tabella generale
        box(16, 2, 20, 20); // Riquadro scelta
        box(16,20,20,80); // Riquadro messaggi di errore
        separator(5,2,80);
        printStrAt(3, 32, "Gestione BIBLIOTECA");
        printStrAt(17,45,"Messaggi:");
        printStrAt(6, 4, "[1]. Inserimento nuovo cliente.");
        printStrAt(7, 4, "[2]. Inserimento nuovo libro.");
        printStrAt(8, 4, "[3]. Prestito Libro.");
        printStrAt(9, 4, "[4]. Rientro Libro.");
        printStrAt(10, 4, "[5]. Stampa Scheda Cliente.");
        printStrAt(11, 4, "[6]. Gestione Liste...");
        printStrAt(12, 4, "[7]. Carica Lista da File.");
        printStrAt(13, 4, "[8]. Abilita/Disabilita Salvataggio.");
        printStrAt(15, 4, "[0]. Esci dal programma.");
        if(saveToFile == TRUE)
            printStrAt(22, 55, "[X] Salva Dati in Uscita");
        else
            printStrAt(22, 55, "[ ] Salva Dati in Uscita");
        printStrAt(18, 4, "Scelta:");
        inputStrAt(18, 12, scelta);

        // Se la scelta è un numero di più cifre forzo il valore ad un char che non utilizzo
        // In questo modo lo switch andrà nal case di Default
        if(scelta[1] >= '0')
            scelta[0] = 'f';

        switch(scelta[0]) {
            case NUOVO_CLIENTE:
                cls();
                warning_generico = FALSE;
                cliente = inserimento_nuovo_cliente();
                risultato = crea_elemento(&head_clienti, cliente);
                switch(risultato) {
                    case OK:
                        printStrAt(16, 20, "Cliente inserito correttamente in archivio");
                        break;
                    case MEMORY_FULL:
                        printStrAt(16, 19, "Memoria piena: impossibile creare nuovo cliente");
                        break;
                }
                ricarica_schermata();
                errore_scelta = FALSE;
                break;
            case NUOVO_LIBRO:
                warning_generico = FALSE;
                printStrAt(22,2,"Inserisci il codice ISBN relativo al libro:");
                getchar();
                inputStrAt(22, 47, isbn);
                tmp_lista_libri = cerca_isbn_in_archivio(head_libri, isbn);
                if(tmp_lista_libri == NULL) {
                    libro = inserimento_nuovo_libro(isbn);
                    inserimento_libro_in_lista(&head_libri, libro);
                } else {
                    // Visualizzare dati del libro
                    stampa_dati_libro(isbn, tmp_lista_libri, TRUE);
                }
                errore_scelta = FALSE;
                break;
            case PRESTITO_LIBRO:
                warning_generico = FALSE;
                printStrAt(22,2,"Inserire ID cliente:");
                getchar();
                inputIntAt(22,24,&id);
                tmp_lista_clienti = cerca_cliente_da_id(id, head_clienti);
                if(tmp_lista_clienti != NULL) {
                    printStrAt(22,2,"Inserire codice isbn del libro:");
                    inputStrAt(22,34,isbn);
                    tmp_lista_libri = cerca_isbn_in_archivio(head_libri, isbn);
                    if (tmp_lista_libri != NULL) {
                        tmp_lista_clienti->val.clienti.libri_posseduti++;
                        clientId = tmp_lista_clienti->val.clienti.id;
                        stampa_dati_libro(isbn, tmp_lista_libri, FALSE);
                        stampa_dati_cliente(tmp_lista_clienti, FALSE);
                        risultato = inserimento_prestiti_in_lista(isbn, clientId, &head_prestiti);
                        if(risultato == OK)
                            printStrAt(16, 28, "Dati inseriti in archivio");
                        else
                            printStrAt(16, 19, "Memoria piena: impossibile inserire le date.");
                        ricarica_schermata();
                    } else {
                        libro_non_trovato();
                        warning_generico = TRUE;
                    }
                } else {
                    cliente_non_trovato();
                    warning_generico = TRUE;
                }
                errore_scelta = FALSE;
                break;
            case RIENTRO_LIBRO:
                warning_generico = FALSE;
                printStrAt(22,2,"Inserire ID cliente:");
                getchar();
                inputIntAt(22,24,&id);
                tmp_lista_clienti = cerca_cliente_da_id(id, head_clienti);
                if(tmp_lista_clienti != NULL) {
                    printStrAt(22,2,"Inserire codice isbn del libro:");
                    inputStrAt(22,34,isbn);
                    tmp_lista_libri = cerca_isbn_in_archivio(head_libri, isbn);
                    if (tmp_lista_libri != NULL) {
                        clientId = tmp_lista_clienti->val.clienti.id;
                        tmp_lista_prestiti = incrocia_dati(isbn, clientId, head_prestiti);
                        if(tmp_lista_prestiti != NULL) {
                            riepilogoPrestiti(tmp_lista_clienti, tmp_lista_libri);
                            inserimento_rientro_libro(&tmp_lista_prestiti);
                        } else {
                            data_rientro_non_consentita();
                            warning_generico = TRUE;
                        }
                    } else {
                        libro_non_trovato();
                        warning_generico = TRUE;
                    }
                } else {
                    cliente_non_trovato();
                    warning_generico = TRUE;
                }
                errore_scelta = FALSE;
                break;
            case SCHEDA_CLIENTE:
                warning_generico = FALSE;
                printStrAt(22,2,"Inserire ID cliente:");
                getchar();
                inputIntAt(22,22,&id);
                tmp_lista_clienti = cerca_cliente_da_id(id, head_clienti);
                if(tmp_lista_clienti != NULL) {
                    int numero_libri_posseduti = tmp_lista_clienti->val.clienti.libri_posseduti;
                    stampa_dati_cliente(tmp_lista_clienti, TRUE);
                    stampa_libro_in_prestito(numero_libri_posseduti, id, head_prestiti, head_libri);
                } else {
                    cliente_non_trovato();
                    warning_generico = TRUE;
                }
                errore_scelta = FALSE;
                break;
            case GESTIONE_LISTE:
                warning_generico = FALSE;
                errore_scelta = FALSE;
                do {
                    // Se TRUE allora è stata fatta la scelta abagliata e il messaggio
                    // apparirà nella stessa schermata senza ripulirla
                    if(errore_scelta == FALSE && warning_generico == FALSE)
                        cls();
                    box(1, 2, 20, 80); // Grafica tabella generale
                    box(16, 2, 20, 20); // Riquadro scelta
                    box(16,20,20,80); // Riquadro messaggi di errore
                    separator(5,2,80);
                    printStrAt(3, 32, "Gestione LISTE");
                    printStrAt(17,45,"Messaggi:");
                    printStrAt(7, 4, "[1]. Rimuovi Cliente Da Archivio.");
                    printStrAt(8, 4, "[2]. Rimuovi Libro Da Archivio.");
                    printStrAt(9, 4, "[3]. Rimuovi Libro Da Cliente.");
                    printStrAt(11, 4, "[0]. <- Torna al Menu Precedente.");
                    printStrAt(18, 4, "Scelta:");
                    inputStrAt(18, 12, _scelta);

                    if(scelta[1] >= '0')
                        scelta[0] = 'f';

                    switch(_scelta[0]) {
                        case USCITA:
                            warning_generico = FALSE;
                            errore_scelta = FALSE;
                            break;
                        case RIMUOVI_CLIENTE:
                            warning_generico = FALSE;
                            printStrAt(22,2,"Inserire ID cliente:");
                            getchar();
                            inputIntAt(22,25,&id);
                            tmp_lista_clienti = cerca_cliente_da_id(id, head_clienti);
                            if(tmp_lista_clienti != NULL) {

                                // Se il cliente risulta in archivio controllo che non abbia libri in prestito
                                if(tmp_lista_clienti->val.clienti.libri_posseduti > 0) {
                                    impossibile_eliminare_cliente();
                                    warning_generico = TRUE;
                                }
                                else {
                                    /// Rimozione cliente da lista
                                    rimuovi_cliente_da_lista(tmp_lista_clienti, &head_clienti);
                                    rimozione_avvenuta() ;
                                    warning_generico = TRUE;
                                }
                            } else {
                                cliente_non_trovato();
                                warning_generico = TRUE;
                            }
                            errore_scelta = FALSE;
                            break;
                        case RIMUOVI_LIBRO:
                            warning_generico = FALSE;
                            printStrAt(22,2,"Inserire codice isbn del libro:");
                            getchar();
                            inputStrAt(22,34,isbn);
                            tmp_lista_libri = cerca_isbn_in_archivio(head_libri, isbn);
                            if(tmp_lista_libri != NULL) {
                                // Se il libro risulta in archivio controllo che non sia stato prestato
                                risultato = controlla_se_libro_in_prestito(isbn, head_prestiti);
                                if(risultato > 0) {
                                    impossibile_eliminare_libro(risultato);
                                    warning_generico = TRUE;
                                } else {
                                    /// Rimozione libro da lista
                                    rimuovi_libro_da_lista(tmp_lista_libri, &head_libri);
                                    rimozione_avvenuta() ;
                                    warning_generico = TRUE;
                                }

                            } else {
                                libro_non_trovato();
                                warning_generico = TRUE;
                            }
                            errore_scelta = FALSE;
                            break;
                        case '3':
                            warning_generico = FALSE;
                            errore_scelta = FALSE;
                            // Ricerca esistenza cliente
                            printStrAt(22,2,"Inserire ID cliente:");
                            getchar();
                            inputIntAt(22,24,&id);
                            tmp_lista_clienti = cerca_cliente_da_id(id, head_clienti);
                            if(tmp_lista_clienti == NULL) {
                                cliente_non_trovato();
                                warning_generico = TRUE;
                                break;
                            }
                            // Ricerca esistenza libro
                            printStrAt(22,2,"Inserire codice isbn del libro:");
                            getchar();
                            inputStrAt(22,34,isbn);
                            tmp_lista_libri = cerca_isbn_in_archivio(head_libri, isbn);
                            if(tmp_lista_libri == NULL) {
                                libro_non_trovato();
                                warning_generico = TRUE;
                                break;
                            }
                            // Se il cliente esiste e il libro è in archivio controlliamo se il cliente
                            // è in possesso del libro in questione
                            risultato = cerca_se_cliente_ha_libro(id, isbn, head_prestiti);
                            if(risultato == OK) {
                                // Se il cliente è in possesso del libro, lo stesso verrà eliminato
                                rimuovi_libro_da_cliente(id, isbn, &head_prestiti);
                                rimozione_avvenuta() ;

                                // Aggiornamento libri posseduti dal cliente dopo la rimozione
                                tmp_lista_clienti->val.clienti.libri_posseduti--;
                                warning_generico = TRUE;

                            } else if (risultato == NOT_FOUND) {
                                // Il cliente nn è in possesso del libo
                                cliente_non_in_possesso_del_libro();
                                warning_generico = TRUE;
                            }

                            errore_scelta = FALSE;
                            break;
                        default:
                            warning_generico = FALSE;
                            // In caso di scelta sbagliata facciamo apparire un messaggio di errore
                            scelta_non_consentita(MENU_1);
                            printStrAt(18, 12, "   ");
                            errore_scelta = TRUE;
                            break;
                    }
                }while(_scelta[0] != '0');
                break;
            case CARICA_LISTA:
                warning_generico = FALSE;
                errore_scelta = FALSE;
                carica_clienti = carica_lista_clienti(&head_clienti);
                carica_libri = carica_lista_libri(&head_libri);
                carica_prestiti = carica_lista_prestiti(&head_prestiti);
                if(carica_clienti == FILE_NOT_FOUND || carica_libri == FILE_NOT_FOUND || carica_prestiti == FILE_NOT_FOUND) {
                    caricamento_fallito();
                    warning_generico = TRUE;
                } else {
                    caricamento_ok();
                    warning_generico = TRUE;
                }
                break;
            case ABILITA_DISABILITA:
                warning_generico = FALSE;
                errore_scelta = FALSE;
                if(saveToFile == TRUE)
                    saveToFile = FALSE;
                else
                    saveToFile = TRUE;
                break;
            case USCITA:
                //Messaggio uscita dal programma
                if(saveToFile == TRUE) {
                    salva_lista_clienti(head_clienti);
                    salva_lista_prestiti(head_prestiti);
                    salva_lista_libri(head_libri);
                }
                cursorAt(1,1);
                cls();
                break;
                // funzioni nascoste per debuggare le liste
            case LISTA_CLIENTI:
            case U_LISTA_CLIENTI:
                warning_generico = FALSE;
                errore_scelta = FALSE;
                // Il case 100 stampa la lista dei clienti
                stampa_lista_clienti(head_clienti);
                break;
            case LISTA_LIBRI:
            case U_LISTA_LIBRI:
                warning_generico = FALSE;
                errore_scelta = FALSE;
                // Il case 200 stampa la lista libri
                stampa_lista_libri(head_libri);
                break;
            default:
                warning_generico = FALSE;
                // In caso di scelta sbagliata facciamo apparire un messaggio di errore
                scelta_non_consentita(MENU_0);
                printStrAt(18, 12, "   ");
                errore_scelta = TRUE;

                break;
        }
    }while(scelta[0] != '0');

    return 0;
}
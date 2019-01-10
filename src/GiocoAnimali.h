//
//  GiocoAnimali.h
//  Akinator(Animal)
//
//  Created by Axel Fleureau on 22/12/2018.
//  Copyright © 2018 AxNL. All rights reserved.
//

#ifndef GiocoAnimali_h
#define GiocoAnimali_h

#pragma once

#include "Albero.h"
#include "Albero.cpp"
#include "NodoAlbero.h"
#include "NodoAlbero.cpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class GiocoAnimali
{
private:
    bool contr;     //variabile di controllo.
    bool sx;        //variabile di controllo: controlla se si sta analizzando il sottoalbero di sinistra o di destra.
    void RicFile(NodoAlbero<string> *, fstream &);      //procedura ricorsiva utile al salvataggio dell'albero su file.
    void AggiungiNodi(Albero<string> &, NodoAlbero<string> *);      //aggiunta nodi durante l'esecuzione del gioco.
	void Split_Aggiunta_file(string, Albero<string> &);     //procedura principale per la gestione del ripristino da file.
	void RicSplit(string, int &, Albero<string> &, NodoAlbero<string> *);       //procedura ricorsiva utile alla analisi del file e ripristino dell'albero.
    int NextChar(string, const char, int);      //funzione: ritorna la posizione, nella stringa passata come primo paramero, del carattere indicato più vicino posto successivamente all'indice messo come ultimo parametro.
public:
    GiocoAnimali();         //costruttore: si occupa del set dei controllori.
    void Salvataggio(Albero<string> &);
    void Caricamento_file(Albero<string> &);
    void Caricamento_base(Albero<string> &);
    void Gioca(Albero<string> &, NodoAlbero<string> *);
};

#endif /* GiocoAnimali_h */

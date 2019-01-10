//
//  Albero.h
//  Akinator(Animal)
//
//  Created by Axel Fleureau on 22/12/2018.
//  Copyright © 2018 AxNL. All rights reserved.
//

#pragma once

#include "NodoAlbero.h"
#include "NodoAlbero.cpp"
#include<iostream>

using namespace std;

template <class tipo>
class Albero
{
    
private:
    //Puntatore al nodo padre
    NodoAlbero<tipo>* T;
    
    //Inserimento del nodo in maniera ricorsiva
    NodoAlbero<tipo>* InserisciR(tipo, NodoAlbero<tipo>*);
    
    //Stampa l'albero in vari ordini
    void Preorder(NodoAlbero<tipo>*);
    void Inorder(NodoAlbero<tipo>*);
    void Postorder(NodoAlbero<tipo>*);
    
    //Conta il numero di nodi
    //Restituisce il numero di nodi
    int ContaNodi(int&, NodoAlbero<tipo>*);
    int ContaNodiFoglia(int&, NodoAlbero<tipo>*);
    
public:
    
    //Costruttore
    Albero();
    Albero(tipo);
    
    NodoAlbero<tipo>* GetT();
    
    void InserisciDx(tipo, NodoAlbero<tipo>*);
    void InserisciSx(tipo, NodoAlbero<tipo>*);
    
    //Chiamate alle stampe nei diversi ordini
    void StampaPreorder();
    void StampaInorder();
    void StampaPostorder();
    
    //Inserimenti di nodi
    void InserisciIterativo(tipo);
    void InserisciRicorsivo(tipo);
    
    //Chiamata alla ContaNodi
    int ContaNodi();
    int ContaNodiFoglia();
    
    //Distruttore
    ~Albero();
};

//implementazione inline per MacOS, guarda il file .cpp

//Costruttore
template <class tipo>
inline Albero<tipo>::Albero()
{
    T = nullptr;
}

template <class tipo>
inline Albero<tipo>::Albero(tipo x)
{
    
    T = new NodoAlbero<tipo>(x);
}

//------------------------------------------------
//                        Stampe
//------------------------------------------------

//-------------------- Private -------------------

//Stampa in Preorder
template <class tipo>
inline void Albero<tipo>::Preorder(NodoAlbero<tipo>* T) {
    if (T != nullptr) {
        cout << T->GetInfo()<<endl;
        Preorder(T->GetLeftLink());
        Preorder(T->GetRightLink());
    }
}

//Stampa in inOrder
template <class tipo>
inline void Albero<tipo>::Inorder(NodoAlbero<tipo>* T) {
    if (T != nullptr) {
        Preorder(T->GetLeftLink());
        cout << T->GetInfo() << endl;
        Preorder(T->GetRightLink());
    }
}

//Stampa in Postorder
template <class tipo>
inline void Albero<tipo>::Postorder(NodoAlbero<tipo>* T) {
    if (T != nullptr) {
        Preorder(T->GetLeftLink());
        Preorder(T->GetRightLink());
        cout << T->GetInfo() << endl;
    }
}


//-------------------- Public -------------------

template <class tipo>
inline void Albero<tipo>::StampaPreorder() {
    Preorder(T);
}

template <class tipo>
inline void Albero<tipo>::StampaInorder() {
    Inorder(T);
}

template <class tipo>
inline void Albero<tipo>::StampaPostorder() {
    Postorder(T);
}

template <class tipo>
inline NodoAlbero<tipo>* Albero<tipo>::GetT()
{
    return T;
}

//------------------------------------------------
//                      Inserimenti
//------------------------------------------------

//-------------------- Public -------------------

template <class tipo>
inline void Albero<tipo>::InserisciSx(tipo x, NodoAlbero<tipo>*rif)
{
    NodoAlbero<tipo>* q = new NodoAlbero<string>(x);
    rif->SetLeftLink(q);
}

template <class tipo>
inline void Albero<tipo>::InserisciDx(tipo x, NodoAlbero<tipo>*rif)
{
    NodoAlbero<tipo>* q = new NodoAlbero<string>(x);
    rif->SetRightLink(q);
}

template <class tipo>
inline void Albero<tipo>::InserisciIterativo(tipo x) {
    NodoAlbero<tipo>* q = T;
    while (q != nullptr) {
        if (x > q->GetInfo()) {
            q = q->GetRightLink();
        }
        else {
            q = q->GetLeftLink();
        }
    }
    T = new NodoAlbero<tipo>(x);
}

template <class tipo>
inline void Albero<tipo>::InserisciRicorsivo(tipo x){
    T = InserisciRicorsivo(x, T);
}

//-------------------- Private ------------------

template <class tipo>
inline NodoAlbero<tipo>* Albero<tipo>::InserisciR(tipo x, NodoAlbero<tipo>* q){
    if (q == 0){
        q = new NodoAlbero<tipo>(x);
    }
    else{
        if(x > q->GetInfo()){
            q->SetRightLink(InserisciRicorsivo(x, q->GetRightLink()));
        }
        else{
            q->SetLeftLink(InserisciRicorsivo(x, q->GetLeftLink()));
        }
    }
    return q;
}



template <class tipo>
inline int Albero<tipo>::ContaNodi() {
    int nNodi = 0;
    ContaNodi(nNodi, T);
    return nNodi;
}

template <class tipo>
inline int Albero<tipo>::ContaNodi(int &nNodi, NodoAlbero<tipo>* T) {
    if (T != nullptr) {
        nNodi++;
        ContaNodi(nNodi, T->GetLeftLink());
        ContaNodi(nNodi, T->GetRightLink());
        return nNodi;
    }
}

template <class tipo>
inline int Albero<tipo>::ContaNodiFoglia() {
    int nNodiFoglia = 0;
    ContaNodiFoglia(nNodiFoglia, T);
    return nNodiFoglia;
}

template <class tipo>
inline int Albero<tipo>::ContaNodiFoglia(int &nNodiFoglia, NodoAlbero<tipo>* T) {
    if (T != nullptr) {
        ContaNodiFoglia(nNodiFoglia, T->GetLeftLink());
        ContaNodiFoglia(nNodiFoglia, T->GetRightLink());
    }
    if (T == nullptr) {
        nNodiFoglia++;
    }
    return nNodiFoglia;
}

template <class tipo>
inline Albero<tipo>::~Albero() {}

/* Albero_h */

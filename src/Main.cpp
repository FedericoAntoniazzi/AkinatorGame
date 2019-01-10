//
//  main.cpp
//  AkinAnimal
//
//  Created by Axel Fleureau on 22/12/2018.
//  Copyright © 2018 AxNL. All rights reserved.
//

#include "Albero.h"
#include "Albero.cpp"
#include "NodoAlbero.h"
#include "NodoAlbero.cpp"
#include "GiocoAnimali.h"
#include <iostream>
#include <locale.h>
#include <string>

using namespace std;

int Menu()
{
    int sc;
    
    cout << "1 --> Caricamento base dell'albero (serve per iniziare a giocare se il file di gioco e' vuoto)\n";
    cout << "2 --> Caricamento da file dei nodi dell'albero\n";
    cout << "3 --> Salva su file i nodi dell'albero\n";
    cout << "4 --> Gioca\n";
    
    cin >> sc;
    return sc;
}

int main()
{
	setlocale(LC_ALL, "");

    string init = "L'animale scelto e' un mammifero?";
    int scelta = 0;
    //Inizializzazione dell'albero.
    Albero<string> tree(init);		//costruisco l'albero con la radice uguale ad Init.
    NodoAlbero<string> * p = tree.GetT();
    
    //inizializzazione classe gioco.
    GiocoAnimali game;
    
    do{
        
        cout << "NOTE D'AUTORE: rispondi alle domande che ti verranno poste in questo modo:\n si -> 's' | 'S', oppure no -> 'n' | 'N'\n\n\n\n";
        
        scelta = Menu();
        switch(scelta)
        {
            case 1:
                game.Caricamento_base(tree);	//caricamento base dell'albero: radice e 2 nodi foglia.
                break;
            case 2:
                game.Caricamento_file(tree);    //configurazione albero da file.
                break;
            case 3:
                game.Salvataggio(tree);	//salvataggio su file dell'albero.
                break;
            case 4:
                game.Gioca(tree, p);	//avvio del gioco.
				game.Salvataggio(tree);	//ho deciso di fare un salvataggio automatico ad ogni sessione di gioco.
                break;
        }
        system("clear");
    }while(scelta != 0);
    
    return 0;
}

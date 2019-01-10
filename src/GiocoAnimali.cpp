//
//  GiocoAlbero.cpp
//  Akinator(Animal)
//
//  Created by Axel Fleureau on 22/12/2018.
//  Copyright © 2018 AxNL. All rights reserved.
//

#include "GiocoAnimali.h"

using namespace std;

GiocoAnimali::GiocoAnimali()
{
    //costruttore, inizializza le variabili di controllo.
    contr = false;
    sx = true;
}

void GiocoAnimali::RicFile(NodoAlbero<string> * p, fstream & myfile)
{
    //procedura debita al salvataggio su file dei dati di gioco, analizza ricorsivamente il sottoalbero sinistro e destro.
    if(p->GetLeftLink() == 0 && p->GetRightLink() == 0)
        return;
    
    if (p->GetLeftLink() != 0 && ( p->GetLeftLink()->GetLeftLink() != 0 || p->GetLeftLink()->GetRightLink() != 0) )
    {
        //controllo: se il nodo a sinistra di quello puntato da "p" non è un nodo foglia, allora:
        myfile << "(" << p->GetLeftLink()->GetInfo();       //scrivo nel file: apro parentesi tonda e scrivo l'informazione relativa al nodo a sinistra di p.
        RicFile(p->GetLeftLink(), myfile);      //analisi del sottoalbero sinistro.
    }
    
    else if (p->GetLeftLink() != 0)
    {
        //controllo: altrimenti, se esiste un nodo a sinistra di quello puntato, allora:
        myfile << "(" << p->GetLeftLink()->GetInfo();       //scrivo nel file: apro parentesi tonda e scrivo l'informazione relativa al nodo a sinistra di p.
    }
    
    else if (p->GetLeftLink() == 0 && p->GetRightLink() != 0)
    //controllo: altrimenti, se non esiste un nodo a sinistra di quello puntato, ma esiste un nodo a destra, allora:
        myfile << "(";      //scrivo nel file: apro parentesi tonda e continuo con l'analisi del nodo destro [ (,infoDx) ].
    
    if (p->GetRightLink() != 0 && (p->GetRightLink()->GetRightLink() != 0 || p->GetRightLink()->GetLeftLink() != 0))
    {
        //controllo: se esiste un nodo (non foglia) a destra di quello puntato da p, allora:
        myfile << "," << p->GetRightLink()->GetInfo();      //scrivo nel file: scrivo la virgola (carattere separatore) e l'informazione relativa al nodo a destra di p.
        RicFile(p->GetRightLink(), myfile);     //analisi del sottoalbero destro.
        myfile << ")";                      //scrivo nel file: scrivo la parentesi chiusa.
    }
    
    else if (p->GetRightLink() != 0)
    {
        //controllo: altrimenti, se esiste un nodo (foglia) a destra di quello puntato da p, allora:
        myfile << "," << p->GetRightLink()->GetInfo() << ")";       //scrivo nel file: scrivo la virgola (carattere separatore), l'informazione relativa al nodo a destra di p e la parentesi chiusa.
    }
    else if ( p->GetRightLink() == 0 )
    //controllo: altrimenti, se non esiste un nodo di destra, allora:
        myfile << "," << ")";                   //scrivo nel file: scrivo la virgola (carattere separatore) e la parentesi chiusa.

    
    cout << "   loading...  ";      //feedback - annuncia che un sottoalbero è stato scritto su file.
    return;
}

void GiocoAnimali::Salvataggio(Albero<string> & tree)
{
    //procedura principale debita al salvataggio su file dei dati di gioco.
    NodoAlbero<string> * node = tree.GetT();        //salvo il puntatore a nodo radice dell'albero in un puntatore a nodo "node".
    
    fstream myfile("Animali.txt", ios::in|ios::out|ios::trunc);     //apro (se esiste) il file (o lo creo), mi metto nella codizione di scrivere sul file ed eventualmente sovrascrivo ciò che era scritto nel file con quanto segue.
    if(myfile.good())
    {
        //controllo lo stato del file, std::ios::good() ritorna "true" se il flag di stato di errore dello stream è negativo.
        myfile<<node->GetInfo()<<"(";       //scrivo nel file il campo informazioni del nodo root dell'albero e apro la parentesi relativa.
        
        if (node->GetLeftLink() != 0 && node->GetRightLink() != 0)      //controllo se il nodo root è un nodo foglia...
        {//...se non lo è:
            myfile << node->GetLeftLink()->GetInfo();       //scrivo nel file l'informazione del nodo a sinistra del nodo root.
            RicFile(node->GetLeftLink(), myfile);           //analizzo ricorsivamente il sottoalbero sinistro.
            
            sx = false;                                     //ho già analizzato il sottoalbero sinistro e passo a quello destro, quindi la variabile di controllo "sx" viene set tata a "false".
            
            myfile << "," << node->GetRightLink()->GetInfo(); //scrivo la virgola, la quale separa il sottoalbero sinistro da quello destro, dopodichè scrivo nel file la prima informazione del sottoalbero destro e lo analizzo.
            RicFile(node->GetRightLink(), myfile);            //analizzo ricorsivamente il sottoalbero destro.
        }
        myfile << ")";                                      //chiudo la parentesi relativa al contenuto del nodo radice
    }
	else
	{
        //si esegue se lo stato del flag di errore dello stream è positivo.
		cout << "\nProblema col file del gioco... (isBad)\n";
		return;
	}

	myfile.close();     //chiudo il file.
    cout << "............. Ok!\n";      //feedback - annuncia che la procedura è terminata con successo e quindi che il file è stato scritto.
	contr = false;      //variabile di controllo che ritorna al suo stato iniziale.
    return;
    
}

void GiocoAnimali::Caricamento_base(Albero<string>& a)
{
    //caricamento dei dati base dell'albero, il quale è stato inizializzato con il nodo radice "L'animale scelto e' un mammifero?".
    a.InserisciSx("cane", a.GetT());               //inserisco "cane" a sinistra del nodo radice dell'albero.
    a.InserisciDx("pitone", a.GetT());              //inserisco "pitone" a destra del nodo radice dell'albero,
    
    cout << "............. Ok!\n";      //feedback - annuncia che la procedura è terminata con successo e quindi che l'albero è stato configurato.
    return;
}

void GiocoAnimali::Caricamento_file(Albero<string> & a)
{
    //caricamento dei dati relativi all'albero del gioco.
    fstream myfile("Animali.txt", ios::in);     //apro (se esiste) il file "Animali.txt";
	string data;        //variabile destinata a contenere la riga relativa alla struttura dell'albero.
	if (myfile.good())
	{
        //controllo lo stato del file, std::ios::good() ritorna "true" se il flag di stato di errore dello stream è negativo.
		if (!myfile.eof())
		{
            //controllo se  non ci troviamo alla fine del file (il file è vuoto).
            cin.ignore();       //siccome utilizzo "getline()" utilizzo std::istream::ignore, poichè, se è stato utilizzato un "cin" precedentemente i caratteri di delimitazione dell'input sono lo spazio e '\n' (invio): per ottenere in input una riga, il carattere di delimitazione dele essere '\n', quindi scarto un carattere che eventualmente è quello di delimitazione del "cin".
			getline(myfile, data);       //scrivo la riga del file nella stringa "data".
		}
        else
        {
            cout << "\nProblema col file del gioco... (isEmpty!)\n";        //se il file è in buono stato, ma vuoto, segnalo l'errore e termino la procedura.
            system("PAUSE");
            return;
        }
		Split_Aggiunta_file(data, a);       //analizzo la stringa acquisita da file per configurare l'albero.
	}
	else
	{
		cout << "\nProblema col file del gioco... (!stream.good())\n";       //se lo stream presenta errori, allora segnalo l'errore e termino la procedura.
		system("PAUSE");
		return;
	}

	myfile.close();                     //chiusura del file.
	cout << "............. Ok!\n";      //feedback - annuncia che la procedura è terminata senza errori sui file e quindi che il caricamento da file è avvenuto.
    return;
}

void GiocoAnimali::Split_Aggiunta_file(string riga, Albero<string> & a)
{
    //funzione debita alla gestione della configurazione dell'albero data una riga da file.
	int ini_pos = 0;
	int end_pos, len_info;
	char chSep = '(';
	size_t found = riga.find(chSep);

    if (found != string::npos)      //string::npos è un valore costante pari al più grande valore possibile per un elemento di tipo "size_t".
	{
        //se non il chSep non è alla fine della riga, allora:
		end_pos = riga.find(chSep, ini_pos);        //end_pos assume il valore della posizione in cui si trova il primo carattere separatore dopo ini_pos.
		len_info = end_pos - ini_pos;               //len_info assume il valore della lunghezza dell'informazione delimitata da ini_pos e end_pos.
		a.GetT()->SetInfo(riga.substr(ini_pos, len_info));      //inserisco nel campo informazioni del nodo radice la prima sotto stringa dato il carattere separatore '('.

		ini_pos = end_pos + 1;      //ini_pos assume il valore della posizione successiva a quella dell'ultimo carattere significativo individuato.

		RicSplit(riga, ini_pos, a, a.GetT());       //analisi sottoalbero sinistro.
        sx = true;      //riporto sx allo stato iniziale;
		contr = true;   // settando questa variabile di controllo a true, la prima operazione della procedura "RicSplit()" inserirà la prossima informazione a destra del nodo radice e proseguirà ripristinando il sottoalbero destro.
        
        while ( ini_pos == NextChar(riga, ')', ini_pos) )   //se ci sono diverse parentesi tonde chiuse, la procedura RicSplit potrebbe terminare prima di scartarle tutte (le scarta perchè tra un carattere separatore e l'altro c'è un sottoriga vuoto).
            ini_pos ++;
        if ( ini_pos == NextChar(riga, ',', ini_pos) )  //se rimane una virgola dopo la fine della procedura RicSplit, la ignoro per evitare di incontrare una sottoriga vuota nella prossima chiamata e far terminare prematuramente la chiamata qui sottostante.
            ini_pos ++;
		RicSplit(riga, ini_pos, a, a.GetT());       //analisi sottoalbero destro.
		contr = false;     //riporto contr allo stato iniziale.
	}

}

int GiocoAnimali::NextChar(string riga, const char chSep, int ini_pos)
{
    int n = riga.find(chSep, ini_pos);  //n assume il valore della posizione in cui si trova il primo carattere separatore dopo ini_pos.
    if (n < 0) n = 999999;      //quando il carattere significativo non viene trovato, n assume un valore negativo (-1).
    return n;                   //ritorno del valore di n.
}

void GiocoAnimali::RicSplit(string riga, int & ini_pos, Albero<string> & a, NodoAlbero<string> * p)
{
    //procedura privata chiamata per suddividere la stringa passata come parametro ricercando dei caratteri separatori in sottostringhe in modo da inserirle nell'albero di gioco di conseguenza.
	int len_info;
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
    
    n1 = NextChar(riga, '(', ini_pos);      //n1 assume il valore della posizione in cui si trova il primo carattere significativo dopo ini_pos.
    n2 = NextChar(riga, ',', ini_pos);      //n2 assume il valore della posizione in cui si trova il primo carattere significativo dopo ini_pos.
    n3 = NextChar(riga, ')', ini_pos);      //n3 assume il valore della posizione in cui si trova il primo carattere significativo dopo ini_pos.

    //DEBUG:
	cout << "\nn1 = " << n1 << "\nn2 = " << n2 << "\nn3 = " << n3 << "\nini_pos = " << ini_pos << "\np punta a " << p->GetInfo() << endl;
	//system("pause");
    
    if (!sx)
    {
        //se non stiamo trattando un sottoalbero sinistro, allora:
        if (n2 < n1 && n2 < n3) //se la virgola è il carattere più vicino al nostro indice "ini_pos", allora:
            ini_pos = n2 + 1;   //faccio avanzare di uno l'indice "ini_pos".
        return;
    }
    
	 
	if (n1 < n2 && n1 < n3)
	{
        //se il carattere separatore più vicino all'indice ini_pos è la parentesi aperta, allora:
        len_info = n1 - ini_pos;       //len_info assume il valore della lunghezza dell'informazione che ci interessa (numero carattere di fine informazione - numero carattere di inizio informazione;

		if (!contr)
		{
            a.InserisciSx(riga.substr(ini_pos, len_info), p);       //inserisco a sinistra di p la sotto stringa. std::string::substr ha come parametri la posizione di inizio della sotto stringa e il numero di caratteri della sotto stringa.
			cout << "\n" << riga.substr(ini_pos, len_info) << endl; //DEBUG
            contr = true;       //variabile di controllo cambia valore in modo da indicare quale operazione è stata fatta per ultima.
			ini_pos = n1 + 1;   //faccio avanzare di uno l'indice "ini_pos".
			RicSplit(riga, ini_pos, a, p->GetLeftLink());       //richiamo ricorsivamente la procedura spostando il puntatore verso sinistra.
		}

		else if (contr)
		{
			a.InserisciDx(riga.substr(ini_pos, len_info), p);       //inserisco a destra di p la sotto stringa. std::string::substr ha come parametri la posizione di inizio della sotto stringa e il numero di caratteri della sotto stringa.
			cout << "\n" << riga.substr(ini_pos, len_info) << endl; //DEBUG
			contr = false;      //variabile di controllo cambia valore in modo da indicare quale operazione è stata fatta per ultima.
			ini_pos = n1 + 1;   //faccio avanzare di uno l'indice "ini_pos".
			RicSplit(riga, ini_pos, a, p->GetRightLink());      //richiamo ricorsivamente la procedura spostando il puntatore verso destra.
		}
        if(!sx && contr)
        {
            n1 = NextChar(riga, '(', ini_pos);      //n1 assume il valore della posizione in cui si trova il primo carattere significativo dopo ini_pos.
            n2 = NextChar(riga, ',', ini_pos);      //n2 assume il valore della posizione in cui si trova il primo carattere significativo dopo ini_pos.
            n3 = NextChar(riga, ')', ini_pos);      //n3 assume il valore della posizione in cui si trova il primo carattere significativo dopo ini_pos.
            
            if (n3 < n1 && n3 < n2)
            {
                len_info = n3 - ini_pos;       //len_info assume il valore della lunghezza dell'informazione che ci interessa (numero carattere di fine informazione - numero carattere di inizio informazione;
                if(riga.substr(ini_pos, len_info) == "")
                {
                    //se viene rilevato un sottostringa vuoto, allora:
                    ini_pos = n3 + 1;   //faccio avanzare di uno l'indice "ini_pos".
                    return;
                }
            }
            if (n2 < n1 && n2 < n3)
            {
                len_info = n2 - ini_pos;       //len_info assume il valore della lunghezza dell'informazione che ci interessa (numero carattere di fine informazione - numero carattere di inizio informazione;
                if(riga.substr(ini_pos, len_info) == "")
                {
                    //se viene rilevato un sottostringa vuoto, allora:
                    ini_pos = n2 + 1;   //faccio avanzare di uno l'indice "ini_pos".
                    sx = true;      //variabile di controllo indica che si sta trattando un sottoalbero sinistro.
                    return;
                }
            }
            sx = true;      //variabile di controllo indica che si sta trattando un sottoalbero sinistro.
            RicSplit(riga, ini_pos, a, p);      //richiamo ricorsivamente la procedura mantenendo il puntatore fisso.
        }
	}
    
	else if (n2 < n1 && n2 < n3)
	{
		len_info = n2 - ini_pos;       //len_info assume il valore della lunghezza dell'informazione che ci interessa (numero carattere di fine informazione - numero carattere di inizio informazione;
		if(riga.substr(ini_pos, len_info) != "")    //se viene rilevato un sottostringa vuoto, allora:
			a.InserisciSx(riga.substr(ini_pos, len_info), p);       //inserisco a sinistra di p la sotto stringa. std::string::substr ha come parametri la posizione di inizio della sotto stringa e il numero di caratteri della sotto stringa.
		else {
			//cout << "##sottoriga vuoto##"; //DEBUG
            sx = false;     //variabile di controllo indica che non si sta trattando un sottoalbero sinistro.
		}
        contr = true;       //variabile di controllo cambia valore in modo da indicare quale operazione è stata fatta per ultima.
		cout << "\n" << riga.substr(ini_pos, len_info) << endl; //DEBUG
		ini_pos = n2 + 1;   //faccio avanzare di uno l'indice "ini_pos".
		RicSplit(riga, ini_pos, a, p);      //richiamo ricorsivamente la procedura mantenendo il puntatore fisso.
	}
    
	else if (n3 < n1 && n3 < n2)
	{
		len_info = n3 - ini_pos;       //len_info assume il valore della lunghezza dell'informazione che ci interessa (numero carattere di fine informazione - numero carattere di inizio informazione;
		if (riga.substr(ini_pos, len_info) != "")   //se viene rilevato un sottostringa vuoto, allora:
			a.InserisciDx(riga.substr(ini_pos, len_info), p);       //inserisco a destra di p la sotto stringa. std::string::substr ha come parametri la posizione di inizio della sotto stringa e il numero di caratteri della sotto stringa.
		else {
			//cout << "##sottoriga vuoto##"; //DEBUG
			sx = false;     //variabile di controllo indica che non si sta trattando un sottoalbero sinistro.
		}
		contr = false;      //variabile di controllo cambia valore in modo da indicare quale operazione è stata fatta per ultima.
		cout << "\n" << riga.substr(ini_pos, len_info) << endl; //DEBUG
		ini_pos = n3 + 1;   //faccio avanzare di uno l'indice "ini_pos".
		RicSplit(riga, ini_pos, a, p);      //richiamo ricorsivamente la procedura mantenendo il puntatore fisso.
	}

    return;
}

void GiocoAnimali::AggiungiNodi(Albero<string>& a, NodoAlbero<string> * p)
{
    //procedura privata chiamata solo nel caso in cui il gioco non riesca ad indovinare il personaggio.
    string data;        //stringa destinata alla memorizzazione dei campi informazione da aggiungere/aggiornare.
    cout << "\nOh... beh, potresti aiutarmi scrivendo una domanda che identifichi il tuo animale... \nInserisci: ";
    cin.ignore();
    getline(cin, data);     //input domanda relativa.
    
    string tmp = p->GetInfo();      //salvo in una strings temporanea il campo informazioni attuale del nodo soggetto a modifica.
    p->SetInfo(data);               //sovrascrivo il campo informazioni attuale del nodo soggetto a modifica.
    
    cout << "\nAggiungero' il tuo animale al mio database se lo inserisci di seguito...\nInserisci: ";
    getline(cin, data);             //input animale pensato dall'utente.
    
	a.InserisciDx(tmp, p);          //inserisco a destra l'animale che il gioco ha suggerito, sbagliando.
	a.InserisciSx(data, p);         //inserisco a sinistra l'animale che l'utente ha pensato.
    
    return;
}

void GiocoAnimali::Gioca(Albero<string>& a, NodoAlbero<string> * p)
{
    //procedura principale del gioco, essa controlla le risposte inserite dall'utente ed esegue altre procedure di conseguenza.
    char r;     //variabile destinata alla memorizzazione delle eventuali risposte dell'utente.
    
    if (contr)
    {
        //se la variabile di controllo contr è uguale a "true", allora:
        cout << "\nMi andrà meglio la prossima volta. Mettimi alla prova!\n";
        contr = false;      //riporto la variabile di controllo al suo stato iniziale.
        return;
    }
    
    cout << p->GetInfo();      //stampa i nodi contenenti domande o animali.
    
    if ((p->GetLeftLink() == 0 && p->GetRightLink() == 0))
        //se il nodo puntato da p è un nodo foglia (quindi un animale), allora:
        cout << "! l'animale a cui stavi pensando e' questo, vero? \n";
    else
        //se il nodo puntato da p non è foglia (quindi è una domanda), allora:
        cout << "\n";
    
    cin >> r;       //input risposta;
    
    if ((p->GetLeftLink() == 0 && p->GetRightLink() == 0) && (r == 'n' || r == 'N'))
    {
        //se il nodo puntato da p è un nodo foglia e la risposta data dall'utente è negativa, allora:
        AggiungiNodi(a, p);     //il programma si arrende perchè ha sbagliato e aggiunge l'animale pensato dal giocatore con una domanda relativa ad esso.
		contr = true;           //variabile di controllo che determina se il gioco si è rassegnato o meno.
        Gioca(a, p->GetLeftLink());     //chiamata ricorsiva spostandosi sul nodo a sinistra di quello puntato da p.
    }
    
    else if (r == 'n' || r == 'N')
        //se il nodo puntato da p non è un nodo foglia e la risposta dell'utente è negativa, allora:
        Gioca(a, p->GetRightLink());        //chiamata ricorsiva spostandosi sul nodo a destra di quello puntato da p.
    
	else if ((p->GetLeftLink() == 0 && p->GetRightLink() == 0) && (r == 's' || r == 'S'))
	{
        //se il nodo puntato da p è un nodo foglia e la risposta data dall'utente è positiva, allora:
		if (!contr)
            //se la variabile di controllo contr è uguale a "false", allora:
			cout << "\nHO VINTO!\n";
		contr = false;          //variabile di controllo che determina se il gioco si è rassegnato o meno.
	}
    
    else if (r == 's' || r == 'S' )
        //se il nodo puntato da p non è un nodo foglia e la risposta dell'utente è negativa, allora:
        Gioca(a, p->GetLeftLink());     //chiamata ricorsiva spostandosi sul nodo a sinistra di quello puntato da p.
 
    return;
}

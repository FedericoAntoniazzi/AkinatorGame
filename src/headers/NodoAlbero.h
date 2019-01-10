//
//  NodoAlbero.h
//  Akinator(Animal)
//
//  Created by Axel Fleureau on 22/12/2018.
//  Copyright © 2018 AxNL. All rights reserved.
//

#pragma once

template<class tipo>
class NodoAlbero
{
private:
    tipo info;
    NodoAlbero<tipo>* leftLink, *rightLink;
    
public:
    
    NodoAlbero();
    NodoAlbero(tipo);
    
    tipo GetInfo();
    
    NodoAlbero<tipo>* GetLeftLink();
    NodoAlbero<tipo>* GetRightLink();
    
    void SetInfo(tipo);
    void SetLeftLink(NodoAlbero<tipo>*);
    void SetRightLink(NodoAlbero<tipo>*);
    
    ~NodoAlbero();
};

//implementazione inline per MacOS, guarda il file .cpp

template <class tipo>
inline NodoAlbero<tipo>::NodoAlbero()
{
    leftLink = rightLink = 0;
}

template <class tipo>
inline NodoAlbero<tipo>::NodoAlbero(tipo x)
{
    info = x;
    leftLink = rightLink = 0;
}

template <class tipo>
inline tipo NodoAlbero<tipo>::GetInfo()
{
    return info;
}

template <class tipo>
inline NodoAlbero<tipo>* NodoAlbero<tipo>::GetLeftLink()
{
    return leftLink;
}

template <class tipo>
inline NodoAlbero<tipo>* NodoAlbero<tipo>::GetRightLink()
{
    return rightLink;
}

template <class tipo>
inline void NodoAlbero<tipo>::SetInfo(tipo x)
{
    info = x;
}

template <class tipo>
inline void NodoAlbero<tipo>::SetLeftLink(NodoAlbero<tipo>* x)
{
    leftLink = x;
}

template <class tipo>
inline void NodoAlbero<tipo>::SetRightLink(NodoAlbero<tipo>* x)
{
    rightLink = x;
}

template <class tipo>
inline NodoAlbero<tipo>::~NodoAlbero(){}

/* NodoAlbero_h */

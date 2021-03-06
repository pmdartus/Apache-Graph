﻿/*************************************************************************
                cIndex  -  gère les index pour les pages
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Interface de la classe <cIndex> (fichier cIndex.h) ------
#if ! defined ( cIndex_H )
#define cIndex_H


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
#include <map>
using namespace std;

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
typedef map <string, int> mIndex; // Établie un lien d’id entre une adresse URL et un entier


//------------------------------------------------------------------------ 
// Rôle de la classe <cJournal>
// Stocker les ID correspondant à chaque URL contenue dans le .log.
// Permet d'alléger l'espace mémoire et de limiter l'information redondante.
//------------------------------------------------------------------------ 

class cIndex
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    
	
	int addUrl (string aUrl);
    // Mode d'emploi :
	// Ajout d'un Url à la liste -> retourne le numero de l'index.
	// Fonctionne également si l'url existe déjà dans la liste.
    // Contrat :
    //

	string findUrl (int aNumIndex);
    // Mode d'emploi :
	// Recherche d'une Url à partir de son index
	// Renvoie une ERROR+aNumIndex s'il ne l'a pas trouvé.
    // Contrat :
    //

	void disp ();
    // Mode d'emploi :
	// Affichage à l'écran des différentes valeurs stockées dans l'index
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur

    cIndex ( );
    // Mode d'emploi :
    // 

	  
    virtual ~cIndex ( );
    // Mode d'emploi :
    // 


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	mIndex Index;
	mIndex::iterator it;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <cChargement>

#endif // cIndex_H

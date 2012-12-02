/*************************************************************************
                    cJournal  -  gère les données à importer
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Interface de la classe <cJournal> (fichier cJournal.h) ------
#if ! defined ( cJournal_H )
#define cJournal_H


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#include "cIndex.h"

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
typedef int tableauHorraire[25];
typedef map <int, int*> mapReferer;
typedef map <int, mapReferer *> mapCible;

struct sReq
{
    int key;
    int nbHit;

    sReq(int k, int nb) : key(k), nbHit(nb) {}

    bool operator < (const sReq& str) const
    {
		return (nbHit < str.nbHit);
    }
};
typedef vector <sReq> vReqOrdered; 


//------------------------------------------------------------------------ 
// Rôle de la classe <cJournal>
//
//
//------------------------------------------------------------------------ 

class cJournal
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
	void optionNbVisite(int iNbVisite);
    // Mode d'emploi :
	// Affichage des différentes sources et cibles avec le nombre de Hits associés à charque accés
    // Contrat :
    //

    
	int dispLogs(int maxHits);
    // Mode d'emploi :
    //
    // Contrat :
    // maxHits = 0 si pas de limite d'affichage

    
	int dispIndex();
    // Mode d'emploi :
	// Affichage de l'index du Journal
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur

    cJournal ( string cFic, bool html, int heure, string aGraphizFile );
    // Mode d'emploi :
    // 

	 
    virtual ~cJournal ( );
    // Mode d'emploi :
    // 


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    
	void addReq(string sCible, string sReferer, int aHeure);
    // Mode d'emploi :
	// Ajout des requetes dans le journal
    // Contrat :
    //

    void fromFile (string cFic);
    // Mode d'emploi :
    // Lis le .log ligne par ligne
    // Contrat :
    //

    string splitLog(string aLigne, int &aDate, string &aRequete, string &aReferer, string &aStatut);
    // Mode d'emploi :
    // Récupère les informations importantes depuis une ligne de .log
    // Contrat :
    //

    void traiterReq(int heure, string referer,  string url, string statut);
    // Mode d'emploi :
    // Ajout des requetes dans la struture de donnée depuis des données traités
    // Contrat :
    // date fait 21 caractères
	// referer fait au moins 3 caractères

	vReqOrdered orderLogs();
    // Mode d'emploi :
    //
    // Contrat :
    //

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés
	mapCible mCible;
	cIndex Index;
	mapReferer::iterator itReferer;
	mapCible::iterator itCible;
	bool bOptionHtml;
	int iOptionHeure;
	string sGraphizFile;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <cChargement>

#endif // cJournal_H
/*************************************************************************
                           cChargement  -  description
                             -------------------
    d�but                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Interface de la classe <cChargement> (fichier cChargement.h) ------
#if ! defined ( XXX_H )
#define XXX_H

//--------------------------------------------------- Interfaces utilis�es
#include <string>
#include <map>
#include "cIndex.h"
#include "cJournal.h"

using namespace std;

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <cChargement>
//
//
//------------------------------------------------------------------------ 

class cChargement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques
    void AddReq (string cFic);
    // Mode d'emploi :
    // AJout d'une requete sur le serveur dans la struture de donnée
    // Contrat :
    //

    void Disp ();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void Graph (string cFic);
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'op�rateurs
    cChargement & operator = ( const cChargement & uncChargement );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur

    cChargement (  bool html, int heure );
    // Mode d'emploi :
    // Création de la structure de donnée pour stocker les informations de connection

	 
    virtual ~cChargement ( );
    // Mode d'emploi :
    // Destruction des différentes structures de donnée


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

private:
//------------------------------------------------------- M�thodes priv�es

protected:
//----------------------------------------------------- Attributs prot�g�s

private:
//------------------------------------------------------- Attributs priv�s
	bool bOptionHtml;
	int iOptionHeure;
	cIndex Index;
	cJournal Journal;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <cChargement>

#endif // XXX_H

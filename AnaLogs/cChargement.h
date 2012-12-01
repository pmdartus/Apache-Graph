/*************************************************************************
			cChargement  -  récupère les infos depuis le .log
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Interface de la classe <cChargement> (fichier cChargement.h) ------
#if ! defined ( cChargement_H )
#define cChargement_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <map>
#include "cJournal.h"

using namespace std;

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <cChargement>
//
//
//------------------------------------------------------------------------ 

class cChargement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void FromFile (string cFic);
    // Mode d'emploi :
    // Ajout d'une requete sur le serveur dans la struture de donnée
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur

    cChargement ( );
    // Mode d'emploi :
    // Création de la structure de donnée pour stocker les informations de connexion

	 
    virtual ~cChargement ( );
    // Mode d'emploi :
    // Destruction des différentes structures de données


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <cChargement>

#endif // cChargement_H

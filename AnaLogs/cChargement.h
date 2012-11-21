/*************************************************************************
                           cChargement  -  description
                             -------------------
    d�but                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Interface de la classe <cChargement> (fichier cChargement.h) ------
#if ! defined ( cChargement_H )
#define cChargement_H

//--------------------------------------------------- Interfaces utilis�es
using namespace std;
#include <map>
#include <string>

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
typedef map<int,string> mIdUrl; // Établit un lien d’id entre une adresse et un numero
typedef int aNbHits[23]; //Le tableau correspond aux nombre de hits par créneau horraire
typedef multimap<int, aNbHits> mLogs; // réquète réalisée : clé l'id du réfrer.
typedef map<int, mLogs> mArcs; // Liens entre referer et cible : clé l'id de la cible


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
    // Ajout, dans la classe, d'un fichier .log repéré par son chemin absolu cFic.
    // Contrat :
    //

	
    void Disp ();
    // Mode d'emploi :
    // Affiche le contenu de la classe à l'écran, le tout trié par nombre de hits.
    // Contrat :
    //

	
    void Graph (string cFic);
    // Mode d'emploi :
    // Insère le contenu de la classe dans un fichier .dot, en respectant les convention de la norme.
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur

    cChargement ( bool html, int heure );
    // Mode d'emploi :
    // Fixe les variables correspondant aux options, avec les valeurs envoyés en paramètres.
    // Contrat :
    //

    virtual ~cChargement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es

private:
//------------------------------------------------------- M�thodes priv�es

    void AddReq (int idRef, int idDest, int idHeure);
    // Mode d'emploi :
    // Ajout d'une seule ligne dans la classe.
    // Contrat :
    //

protected:
//----------------------------------------------------- Attributs prot�g�s

private:
//------------------------------------------------------- Attributs priv�s
	mIdUrl IdUrl;
	mArcs Arcs;
	mLogs Logs;
	bool bOptionHtml; // si TRUE ne prend en compte que les .HTML
	int iOptionHeure; // si = -1 on pend tout en compte
//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <cChargement>

#endif // cChargement_H

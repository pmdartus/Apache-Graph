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
using namespace std;

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 
typedef map <int,string> mIdUrl; // Établis un lien d’id entre une adresse et un numero
typedef int tableauHorraire[25];
typedef map <int, tableauHorraire> mLogs; // réquete réalisée : clé réfrer. Le tableau correspond aux nombre de hits par créneau horraire
typedef map <int, mLogs> mArcs; // Liens entre referer et cible : clé la cible


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
    //
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
    //
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
	
    //
    void AddReq (int idRef, int idDest, int idHeure);
    // Mode d'emploi :
    //
    // Contrat :
    //

protected:
//----------------------------------------------------- Attributs prot�g�s

private:
//------------------------------------------------------- Attributs priv�s
	mIdUrl IdUrl;
	mArcs Arcs;
	mLogs Logs;
	bool bOptionHtml;
	int iOptionHeure;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <cChargement>

#endif // XXX_H

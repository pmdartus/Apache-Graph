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

//--------------------Structures pour récuperer les données brut depuis le .log ------------------
typedef int tableauHorraire[25];
typedef map <int, int*> mapReferer;
typedef map <int, mapReferer *> mapCible;

//------------------------ Structures pour la sortie des infos récupérées ------------------------
//Sortie à l'écran
struct sReqScreen
{
    int url, nbHits;
	

    sReqScreen(int aUrl, int aNbHits) : url(aUrl), nbHits(aNbHits) {}

    bool operator < (const sReqScreen& sReqCompare) const
    {
		return (nbHits < sReqCompare.nbHits);
    }
};
typedef vector <sReqScreen> vReqScreenOrd; 
//Sortie dans un fichier graphViz
struct sReqGraph
{
    int url, referer, nbHits;

    sReqGraph(int aUrl, int aRef, int aNbHits) : url(aUrl), referer(aRef), nbHits(aNbHits) {}

    bool operator < (const sReqGraph& sReqCompare) const
    {
		return (nbHits < sReqCompare.nbHits);
    }
};
typedef vector <sReqGraph> vReqGraphOrd; 
typedef map <int, bool> mapNodes;


//------------------------------------------------------------------------ 
// Rôle de la classe <cJournal>
// cJournal est un peu le chef d'orchestre de l'exécution de notre commande.
// Une fois que la partition à été lue par cCommande, cJournal jongle entre les différentes structures de données définis dans la spec.
// Son but est de récupérer et trier si besoin est, les informations contenues dans le .log.
// Elle va par la suite s'assurer d'une sortie à l'écran, voir dans un fichier graphViz
//------------------------------------------------------------------------ 

class cJournal
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    
	int dispLogs();
    // Mode d'emploi :
    // Affichage des différentes sources et cibles avec le nombre de Hits associés à charque accés
    // Contrat :
	//

    
	int dispIndex();
    // Mode d'emploi :
	// Affichage de l'index du Journal
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur

    cJournal ( string cFic, int aNbHits = 0, string aGraphizFile = "", bool html = false, int heure = -1 );
    // Mode d'emploi :
    // 
    // Contrat :
    // maxHits = 0 si pas de limite d'affichage

	 
    virtual ~cJournal ( );
    // Mode d'emploi :
    // 


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
    
	void addReq(string sCible, string sReferer, int aHeure);
    // Mode d'emploi :
	// Ajout des requetes dans le journal (les maps de stockage des logs)
    // Contrat :
    //

    void traiterReq(int heure, string referer,  string url, string statut);
    // Mode d'emploi :
    // Traite et ajoute des requetes dans la struture de donnée à partir d'informations extraites d'un .log
    // Contrat :
	// referer fait au moins 3 caractères
	// le parametre -l exclut les extentions : .jpg, .jpeg, .png, .gif, .ico .css, .js

    string splitLog(string aLigne, int &aDate, string &aRequete, string &aReferer, string &aStatut);
    // Mode d'emploi :
    // Récupère les informations importantes depuis une ligne de .log
    // Contrat :
    //

    void fromFile (string cFic);
    // Mode d'emploi :
    // Lis le .log ligne par ligne
    // Contrat :
    //

    void screenOutput(vReqScreenOrd aReqS);
    // Mode d'emploi :
    // Affiche à l'écran
    // Contrat :
	//

    void graphVizOutput(vReqGraphOrd aReqG, vReqScreenOrd aReqS, string aDot);
    // Mode d'emploi :
    // Ecrit dans le gichier GraphViz
    // Contrat :
	// Le fichier passé en paramètre doit être valide.
	// Il sera effacé, il faut donc que l'utilisateur ait été avertit auparavant.

	int orderLogs(vReqScreenOrd &aReqS, vReqGraphOrd &aReqG);
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

	//-------------------Structures de données -------------------
	mapCible mCible; //contient toutes les cibles des requètes.
	cIndex Index; //L'index des couples ID/URL
	mapReferer::iterator itReferer;
	mapCible::iterator itCible;

	//------------------- Options de la commande -------------------
	bool bOptionHtml;
	int iOptionHeure, iNbHits;
	string sGraphizFile;

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <cChargement>

#endif // cJournal_H
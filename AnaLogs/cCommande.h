/*************************************************************************
                cCommande -  lecture des commandes
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Interface de la classe <cIndex> (fichier cIndex.h) ------
#if ! defined ( cCommande_H )
#define cCommande_H


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;
 
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <cCommande>
//
//
//------------------------------------------------------------------------ 

class cCommande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


//-------------------------------------------- Constructeurs - destructeur

	cCommande(int aNbArg,char ** aCommande);
    // Mode d'emploi :
    // 

	 
	~cCommande(void);
    // Mode d'emploi :
    // 


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	bool isaNumber (string str);
	bool parameterT (string aParameter);
	bool parameterL (string aParameter);
	bool parameterG (string aFileName);
	void gestionErreur (string aParameter);
	bool exploitCmd();
	void cRCmd ();


private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
	int nbArg;
	char ** cmd;
	bool bSyntaxError; //indique la propreté de la syntaxe de la commande
	bool bOptionHtml; //booleen qui indique la nécessité de ne considérer que le HTML
	int iOptionHeure; //integer qui indique la présence d'une tranche horaire
	int iNbHit; //integer qui représente le nb de hit minimum
	string aLogFile; //nom du fichier log
	string aGraphizFile; // nom du fichier graphiz

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <cChargement>

#endif // cIndex_H



/*************************************************************************
                cCommande -  lecture des commandes
    d�but                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Interface de la classe <cIndex> (fichier cIndex.h) ------
#if ! defined ( cCommande_H )
#define cCommande_H


//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <string>
using namespace std;
 
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// R�le de la classe <cCommande>
//
//
//------------------------------------------------------------------------ 

class cCommande
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- M�thodes publiques


//-------------------------------------------- Constructeurs - destructeur

	cCommande(int aNbArg,char ** aCommande);
    // Mode d'emploi :
    // 

	 
	~cCommande(void);
    // Mode d'emploi :
    // 


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es
	bool isaNumber (string str);
	bool parameterT (string aParameter);
	bool parameterL (string aParameter);
	bool parameterG (string aFileName);
	void gestionErreur (string aParameter);
	bool exploitCmd();
	void cRCmd ();


private:
//------------------------------------------------------- M�thodes priv�es

protected:
//----------------------------------------------------- Attributs prot�g�s
	int nbArg;
	char ** cmd;
	bool bSyntaxError; //indique la propret� de la syntaxe de la commande
	bool bOptionHtml; //booleen qui indique la n�cessit� de ne consid�rer que le HTML
	int iOptionHeure; //integer qui indique la pr�sence d'une tranche horaire
	int iNbHit; //integer qui repr�sente le nb de hit minimum
	string aLogFile; //nom du fichier log
	string aGraphizFile; // nom du fichier graphiz

private:
//------------------------------------------------------- Attributs priv�s

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes priv�es

//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <cChargement>

#endif // cIndex_H



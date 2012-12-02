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
    // Instanciation d'un objet cCommande
	// Avec en param�tre le nombre d'options de la commande ( aNbArg ) et un pointeur vers un tableau de char *
	// qui contient le diff�rents arguments de la commande

	 
	~cCommande(void);
    // Mode d'emploi :
    // Destructeur du tableau de commande


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es
	bool isaNumber (string str);
	// Mode d'emploi :
	// V�rifier que la string que l'on entre est bien un nombre 
	// Si OUI la fonction retourne TRUE
    // Contrat :
    //

	bool parameterT (string aParameter);
	// Mode d'emploi :
	// Gestion de l'option -t
    // Contrat :
    //

	bool parameterL (string aParameter);
    // Mode d'emploi :
	// Gestion de l'option -l
    // Contrat :
    //

	bool parameterG (string aFileName);
    // Mode d'emploi :
	// Gestion de l'option -g
    // Contrat :
    //

	void gestionErreur (string aParameter);
	// Mode d'emploi :
	// Gestion intelligente des erreure de syntaxe en proposant � l'utilisateur des syntaxes correctes gr�ce � la recherhce de caract�re
    // Contrat :
    //

	bool exploitCmd();
	// Mode d'emploi :
	// Fonction qui decoupe / execute la commande demand�e par l'utilisateur
    // Contrat :
    //

	void cRCmd ();
	// Mode d'emploi :
	// Compte rendu de commande qui permet en mode MAP d'affiche le r�sultat comment le programme comprend la commande entr�e par l'utilisateur
    // Contrat :
    //

	bool verifyDotFile ();
	// Mode d'emploi :
	// Verifier le fichier .dot
    // Contrat :
    //

private:
//------------------------------------------------------- M�thodes priv�es

protected:
//----------------------------------------------------- Attributs prot�g�s
	int nbArg; // Nombre d'argument de la commande
	char ** cmd; // Pointeur vers un tableur de commande entr�e par l'utilisateur
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



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
    // Instanciation d'un objet cCommande
	// Avec en paramètre le nombre d'options de la commande ( aNbArg ) et un pointeur vers un tableau de char *
	// qui contient le différents arguments de la commande

	 
	~cCommande(void);
    // Mode d'emploi :
    // Destructeur du tableau de commande


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	bool isaNumber (string str);
	// Mode d'emploi :
	// Vérifier que la string que l'on entre est bien un nombre 
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
	// Gestion intelligente des erreure de syntaxe en proposant à l'utilisateur des syntaxes correctes grâce à la recherhce de caractère
    // Contrat :
    //

	bool exploitCmd();
	// Mode d'emploi :
	// Fonction qui decoupe / execute la commande demandée par l'utilisateur
    // Contrat :
    //

	void cRCmd ();
	// Mode d'emploi :
	// Compte rendu de commande qui permet en mode MAP d'affiche le résultat comment le programme comprend la commande entrée par l'utilisateur
    // Contrat :
    //

	bool verifyDotFile ();
	// Mode d'emploi :
	// Verifier le fichier .dot
    // Contrat :
    //

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
	int nbArg; // Nombre d'argument de la commande
	char ** cmd; // Pointeur vers un tableur de commande entrée par l'utilisateur
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



/*************************************************************************
                cCommande -  lecture des commandes
                             -------------------
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
// Chargé de la lecture de la commande, et de la prise en compte de tous les paramètres.
// Instancie par la suite cJournal avec les bons paramètres, elle se chargera du travail demandé par la commande.
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
	// qui contient les différents arguments de la commande

	 
	~cCommande(void);
    // Mode d'emploi :
    // Destructeur du tableau commande


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Méthodes protégées
	bool isaNumber (string str);
    // Mode d'emploi :
	// Vérifier que la string que l'on entre est bien un nombre 
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

	bool parameterH ();
    // Mode d'emploi :
	// Gestion de l'option -h pour l'affichage de l'aide.
    // Contrat :
	//

	void gestionErreur (string aParameter);
    // Mode d'emploi :
	// Gestion intelligente des erreurs de syntaxe en proposant à l'utilisateur des syntaxes correctes.
    // Contrat :
	//

	void cRCmd ();
    // Mode d'emploi :
	// Compte rendu de commande qui permet, en mode MAP, d'afficher le résultat du découpage.
	// C'est à dire comment le programme comprend la commande entrée par l'utilisateur
    // Contrat :
	//

	bool verifyDotFile ();
    // Mode d'emploi :
	// Verifier le fichier .dot : supprimer ou non le contenu du dot s'il existe en fonction de ce que l'utilisateur à demandé. 
	// Renvoyer true signifie que le fichier existe et que l'utilisateur ne veut pas le supprimer.
    // Contrat :
	//

	bool exploitCmd();
    // Mode d'emploi :
	// Fonction qui decoupe / execute la commande demandée par l'utilisateur
    // Contrat :
	//


private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
	int nbArg; // Nombre d'arguments de la commande
	char ** cmd; // Pointeur vers un tableur des commandes entrées par l'utilisateur
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



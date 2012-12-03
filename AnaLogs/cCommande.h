/*************************************************************************
                cCommande -  lecture des commandes
                             -------------------
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
// Charg� de la lecture de la commande, et de la prise en compte de tous les param�tres.
// Instancie par la suite cJournal avec les bons param�tres, elle se chargera du travail demand� par la commande.
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
	// qui contient les diff�rents arguments de la commande

	 
	~cCommande(void);
    // Mode d'emploi :
    // Destructeur du tableau commande


//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- M�thodes prot�g�es
	bool isaNumber (string str);
    // Mode d'emploi :
	// V�rifier que la string que l'on entre est bien un nombre 
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
	// Gestion intelligente des erreurs de syntaxe en proposant � l'utilisateur des syntaxes correctes.
    // Contrat :
	//

	void cRCmd ();
    // Mode d'emploi :
	// Compte rendu de commande qui permet, en mode MAP, d'afficher le r�sultat du d�coupage.
	// C'est � dire comment le programme comprend la commande entr�e par l'utilisateur
    // Contrat :
	//

	bool verifyDotFile ();
    // Mode d'emploi :
	// Verifier le fichier .dot : supprimer ou non le contenu du dot s'il existe en fonction de ce que l'utilisateur � demand�. 
	// Renvoyer true signifie que le fichier existe et que l'utilisateur ne veut pas le supprimer.
    // Contrat :
	//

	bool exploitCmd();
    // Mode d'emploi :
	// Fonction qui decoupe / execute la commande demand�e par l'utilisateur
    // Contrat :
	//


private:
//------------------------------------------------------- M�thodes priv�es

protected:
//----------------------------------------------------- Attributs prot�g�s
	int nbArg; // Nombre d'arguments de la commande
	char ** cmd; // Pointeur vers un tableur des commandes entr�es par l'utilisateur
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



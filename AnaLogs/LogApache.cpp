//#define MAP
#include <iostream>
#include "cChargement.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {

	// ------------------ Variable contenant les options d'exec. ------------------
	int i = 1;	// numero du paramêtre actuel
	bool bOptionHtml = false; //booleen qui indique la nécessité de ne considérer que le HTML
	int iOptionHeure = -1; //integer qui indique la présence d'une tranche horaire
	int iNbHit=0; //integer qui représente le nb de hit minimum
	string aLogFile; //nom du fichier log
	string aGraphizFile; // nom du fichier graphiz
	bool bSyntaxError = false; // Indique une erreur de syntaxe dans l'appel

	#ifdef MAP
	cout<<"Nombre de parametre :"<<argc-1<<endl;
	#endif


	// ------------------ Utilisation des paramêtres ------------------
	/* Parcour de la liste des arguments avec argc arguments
	 * Le parcourt s'arrète au moment ou il trouve une erreur
	 */
	while (i<(argc) && bSyntaxError== false)
	{
		#ifdef MAP
		cout << "Parametre courant :"<<i<< " | "<< argv[i]<<endl;
		#endif

		string aParameter = argv[i]; // Stockage du parametre en cours dans une string

		// ------------------ Récupère le chemin du fichier log (dernier argument) ------------------
		if (i==argc-1) // Nom du fichier Log
		{
			#ifdef MAP
			cout << "Recherche de .log dans :"<<aParameter<<endl;
			#endif

			size_t found; // Variable indiquant la présence ou non d'un pattern

			// Test de l'existance de l'extension .log dans le nom du fichier, renvoi la position où il l'a trouvé
			found=aParameter.find(".log");

			if (found!=string::npos) // Présence de l'extension (npos correspond à la position initiale pour le parcours d'une chaine. Ici -1)
			{
				aLogFile=aParameter;

				#ifdef MAP
				cout << "Nom du fichier log : "<< aLogFile<<endl;
				#endif
			}
			else
			{
				bSyntaxError = true;
				cout << "Syntaxe erreur : problème dans la nom du fichier .log : "<<argv[i]<<endl;
			}

		}

		// ------------------ Récupère les info pour le Graphiz ( -g ) ------------------
		else if (aParameter == "-g")
		{
			#ifdef MAP
			cout << "Demande de creation d'un fichier dot"<<endl;
			#endif

			// Recherche de l'extension du fichier
			string aFileName = argv[i+1];
			size_t found;
			found = aFileName.find(".dot");

			if (found!=string::npos)
			{
				aGraphizFile=aFileName;

				// Ne prend pas en compte le prochain paramêtre car on tombe sur le nom du fichier
				i++;

				#ifdef MAP
				cout << "Nom du fichier .dot : "<< aGraphizFile << endl;
				#endif
			}

			else
			{
				bSyntaxError = true;
				cout << "Syntaxe erreur : le nom du fichier .dot est invalide : "<<argv[i+1]<<endl;
			}

		}

		// ------------------ Récupère les info pour le nombre de Hit ( -l )------------------
		else if (aParameter == "-l")
		{
			#ifdef MAP
			cout << "Demande de considerer que les page avec un certain nb de hits"<<endl;
			#endif

			// Prise en compte du nb de Hits et conversion en integer
			int aNbHit = atoi(argv[i+1]);


			if (aNbHit>=0)
			{
				iNbHit = aNbHit;
				#ifdef MAP
				cout << "Nombre de Hit minimum a prendre en comtpe : "<< iNbHit << endl;
				#endif

				// On ne considère pas le prochain parametre
				i++;
			}

			else
			{
				bSyntaxError = true;
				cout << "Syntaxe erreur : le nombre de Hit est invalide : "<<endl;
			}
		}
		else if (aParameter == "-x")
		{
			#ifdef MAP
			cout << "Demande de d'exculsion des fichiers autres que .html"<<endl;
			#endif

			bOptionHtml=true;
		}
		else if (aParameter == "-t")
		{
			int aTimeInt = atoi(argv[i+1]);
			if (aTimeInt >= 0 && aTimeInt<24)
			{
				iOptionHeure=aTimeInt;


				i++;
				cout<<"Creneau horraire considere :"<<iOptionHeure<<"h"<<endl;
			}
			else
			{
				bSyntaxError=true;
				cout<<"Syntaxe Error : Format de l'heure non valide";
			}
		}
		else
		{
			cout << "Le paramêtre n°" << i+1 << " : "<< argv[i]<< " est invalide !"<<endl;
		}
		i++;
	}

	// Verifier que si l'on appel l'option -l, on appelle aussi l'option -g
	if ((aGraphizFile.size()==0) && (iNbHit!=0))
	{
		bSyntaxError=true;
		cout<<"Syntax Error : il l'option -l n'est accessible qu'avec l'option -g"<<endl;
	}


	// Gestion des cas de retour
	if (bSyntaxError == false && aLogFile.size()!=0)
	{
		//appel de la création du cJournal
		cout << "Execution de la commande, sur le fichier : " << aLogFile <<endl;

		cChargement chargement = cChargement(bOptionHtml, iOptionHeure);

		chargement.AddReq(aLogFile);
	}
	else
	{
		//arret de l'execution du programme
		cout<<"Execution de la commande annulée, probleme de syntaxe dans l'appel.";
	}

	//cin>>i;
	return 0;
}

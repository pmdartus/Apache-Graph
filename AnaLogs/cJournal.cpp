#include "cJournal.h"



// Ajout des requetes dans le journal
void cJournal::addReq(string sCible, string sReferer, int aHeure)
{
	//Obtention de l'index pour les Url
	int aCible = Index.addUrl(sCible);
	int aReferer = Index.addUrl(sReferer);

	//Recherche de l'existence de la cible
	itCible=mCible.find(aCible);

	if (itCible!=mCible.end()) //La cible est d�j� stock�e
	{
		itReferer= (*itCible->second).find(aReferer);

		if (itReferer!=(*itCible->second).end()) //Le Referer est d�j� stock� 
		{
			//On incr�ment la case correspondant � l'heure et au compteur total
			itReferer->second[aHeure]++;
			itReferer->second [24]++;
		}
		
		else //le referer de la cible n'existe pas
		{
			//Cr�ation et initialisation du tableau des heures
			int* aTableauHorraire = new (tableauHorraire);
			for( int i=0; i<=24; i++)
			{
				aTableauHorraire[i] =0;
			}
			aTableauHorraire[aHeure]=1;
			aTableauHorraire[24]=1;

			//insertion du tableau dans la map referer associ�e
			(*itCible->second).insert ( pair<int,int*>(aReferer,aTableauHorraire) );
		}
	}

	else //La cible n'existe pas 
	{
		//Cr�ation de la map referer et association avec la cible.
		mapReferer * aMapReferer = new mapReferer;

		int* aTableauHorraire = new (tableauHorraire);
		for( int i=0; i<=24; i++)
		{
			aTableauHorraire [i] =0;
		}
		aTableauHorraire[aHeure]=1;
		aTableauHorraire[24]=1;

		(*aMapReferer).insert ( pair<int,int*>(aReferer,aTableauHorraire) );

		mCible.insert(pair<int,mapReferer*>(aCible,aMapReferer));
	}
}


// Affichage des diff�rentes sources et cibles avec le nombre de Hits associ�s � charque acc�s
int cJournal::dispLogs(int maxHits)
{
	//Cr�ation et initialisation de la nouvelle structure de donn�e
	vReqOrdered aReqOrdered = orderLogs();
	vector<sReq>::reverse_iterator it;

	//Affichage des requetes
	it=aReqOrdered.rbegin();
	int i=0;
	while(it!=aReqOrdered.rend()&&(i<maxHits||maxHits==0))
	{
		cout<<Index.findUrl(it->key)<< " ("<<it->nbHit<<" vue(s))"<<endl;
		it++;
		i++;
	}

	return 0;
}

void cJournal::OptionNbVisite(int iNbVisite)
{
	itCible=mCible.begin();

	while (itCible != mCible.end())
	{
		//Initialisation des variables de parcourt
		int aNbVisite=0;
		itReferer = (*itCible->second).begin();

		//R�cup�ration du nombre de visite
		while (itReferer != (*itCible->second).end() )
		{
			aNbVisite=itReferer->second[24]+aNbVisite;
			++itReferer;
		}

		//Supression de la m�moire allou�e dans le cas ou le nombre de visite est inf�rieur au nombre requis
		if (aNbVisite<iNbVisite)
		{
			itReferer=(*itCible->second).begin();
			while (itReferer != (*itCible->second).end() )
			{
				int* tableau = itReferer->second;
				(*itCible->second).erase(itReferer++);
				delete tableau;
			}

			mCible.erase(itCible++);
		}

		//Sinon passer � la cible suivante
		else
		{
			++itCible;
		}
	}
}

vReqOrdered cJournal::orderLogs()
{
	vReqOrdered aReqOrdered;
	itCible=mCible.begin();

	while (itCible != mCible.end())
	{
		//Initialisation des variables de parcours
		int aNbVisite=0;
		itReferer = (*itCible->second).begin();

		//R�cup�ration du nombre de visite
		while (itReferer != (*itCible->second).end() )
		{
			aNbVisite=itReferer->second[24]+aNbVisite;
			++itReferer;
		}

		//ajout d'une requete dans la structure
		aReqOrdered.push_back(sReq(itCible->first, aNbVisite));

		++itCible;
	}
	
	//tri des requetes
	sort(aReqOrdered.begin(),aReqOrdered.end());

	return aReqOrdered;
}


//Affichage de l'index du Journal
int cJournal::dispIndex() {
	Index.disp();

	return 0;
}

cJournal::cJournal(void)
{
}


cJournal::~cJournal(void)
{
}

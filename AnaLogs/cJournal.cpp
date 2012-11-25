#include "cJournal.h"

void cJournal::addReq(string sCible, string sReferer, int aHeure)
{
	int aCible = Index.addUrl(sCible);
	int aReferer = Index.addUrl(sReferer);

	itCible=mCible.find(aCible);

	if (itCible!=mCible.end()) //Si on a déjà une map de referer
	{
		itReferer= (*itCible->second).find(aReferer);

		if (itReferer!=(*itCible->second).end()) //Si on a aussi le referer
		{
			//On incrément la case correspondant à l'heure et au compteur total
			itReferer->second[aHeure]++;
			itReferer->second [24]++;
		}
		
		else
		{
			//Création et initialisation du tableau des heures
			int* aTableauHorraire = new (tableauHorraire);
			for( int i=0; i<=24; i++)
			{
				aTableauHorraire[i] =0;
			}
			aTableauHorraire[aHeure]=1;
			aTableauHorraire[24]=1;

			(*itCible->second).insert ( pair<int,int*>(aReferer,aTableauHorraire) );
		}
	}

	else //Si on à pas encore une map de referer
	{
		//Création de la map referer et association avec la cible.
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

int cJournal::dispLogs(void)
{
	itCible = mCible.begin();

	while (itCible != mCible.end())
	{
		itReferer = (*itCible->second).begin();

		cout<<endl;
		while (itReferer != (*itCible->second).end() )
		{
			cout<<Index.findUrl(itCible->first) << " vers : "<< Index.findUrl(itReferer->first) << " (" << itReferer->second[24] << " fois)"<<endl;

			++itReferer;
		}

		++itCible;
	}


	return 0;
}

void cJournal::OptionNbVisite(int iNbVisite)
{
	itCible=mCible.begin();

	while (itCible != mCible.end())
	{
		itReferer = (*itCible->second).begin();

		while (itReferer != (*itCible->second).end() )
		{

			if (itReferer->second[24]<iNbVisite)
			{
				int* tableau = itReferer->second;
				(*itCible->second).erase(itReferer++);
				delete tableau;
			}
			else
			{
			++itReferer;
			}
		}

		if ((*itCible->second).begin()== (*itCible->second).end())
		{
			mCible.erase(itCible++);
		}
		else
		{
			++itCible;
		}
	}


}

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

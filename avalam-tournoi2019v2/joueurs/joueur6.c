/********* Moteur de tournoi : joueur ***************/

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


int testCoup(int pot,int max,int i)
{
	if(pot>max)
	{
		max=pot;
		 
		ecrireIndexCoup(i);
	}
	return max;
}

int calculMin(int pot,int min)
{
	if(pot<min)
	{
		min=pot;
	}
	return min;
}

int test(octet dBis,octet oBis,T_Position P)
{
	T_Voisins voisins;
	T_ListeCoups l;
	voisins = getVoisins(dBis);
	int k = 0;
	int pot;
	int min = 0;
	int cpt = 0;
	octet o,d;
	l.nb = 0;
	listerVoisins(dBis);
	int Color = P.cols[dBis].couleur;
	P = jouerCoup(P,oBis,dBis);

	printf("--------------------voisins : %d-----------------\n",voisins.nb);
	printf("--------------------voisins pos: %d-----------------\n",voisins.cases[0]);

	for (int j = 0; j < voisins.nb; ++j)
	{
		printf("nb = %d\n",P.cols[voisins.cases[j]].nb);
		if(((P.cols[voisins.cases[j]].nb)!=0) && ((P.cols[voisins.cases[j]].nb + P.cols[dBis].nb )<= 5))
		{
			l.coups[k].origine = voisins.cases[j];
			l.coups[k].destination = dBis;
			k++;
			l.nb++;
			l.coups[k].origine = dBis;
			l.coups[k].destination = voisins.cases[j];
			k++;
			l.nb++;
		}
	}
	printf("%d",k);
	afficherListeCoups(l);

	if(l.nb == 0)
	{
		min = -10;
	}
	/*else
	{
		for (int j = 0; j < l.nb; ++j)
		{
			printf("test3");
			o = l.coups[j].origine; 
			d = l.coups[j].destination;
			if(P.cols[o].couleur == P.trait)
			{
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					case 5:pot = 4;
					break;
				}
				min = calculMin(pot,min);
			}
			else
			{
				cpt++;
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					case 5:pot = -10;
					break;
				}
				min = calculMin(pot,min);
			}
		}
	}*/
	return min;

}

int coupVoisins(octet dBis,octet oBis,T_Position P)
{
	T_Voisins voisins;
	T_Voisins voisins2;
	T_ListeCoups l;
	voisins = getVoisins(dBis);
	voisins2 = getVoisins(oBis);
	int k = 0;
	int pot;
	int min = 0;
	int cptEn = 0;
	int cptAm = 0;
	int voisEn =0;
	octet o,d;
	l.nb = 0;
	listerVoisins(dBis);
	int Color = P.cols[dBis].couleur;

	for (int j = 0; j < voisins2.nb; ++j)
	{
		printf("voiEn -> Couleur : %d\n",P.cols[voisins2.cases[j]].couleur);
		if(((P.cols[voisins2.cases[j]].nb)!=0) && (P.cols[voisins2.cases[j]].couleur != P.trait))
		{
			voisEn++;
		}
	}
	P = jouerCoup(P,oBis,dBis);

	printf("--------------------voisins : %d-----------------\n",voisins.nb);
	printf("--------------------voisins pos: %d-----------------\n",voisins.cases[0]);

	for (int j = 0; j < voisins.nb; ++j)
	{
		printf("nb = %d\n",P.cols[voisins.cases[j]].nb);
		if(((P.cols[voisins.cases[j]].nb)!=0) && ((P.cols[voisins.cases[j]].nb + P.cols[dBis].nb )<= 5))
		{
			l.coups[k].origine = voisins.cases[j];
			l.coups[k].destination = dBis;
			k++;
			l.nb++;
			l.coups[k].origine = dBis;
			l.coups[k].destination = voisins.cases[j];
			k++;
			l.nb++;
			if(P.cols[voisins.cases[j]].couleur != P.trait)
			{
				cptAm++;
				printf("Couleur : %d",P.cols[voisins.cases[j]].couleur);

			}
			else
			{
				cptEn++;
			}
		}

	}
	printf("%d",k);
	afficherListeCoups(l);


	if(l.nb == 0 && Color != P.trait)
	{
		min = 3;
	}
	else
	{
		for (int j = 0; j < l.nb; ++j)
		{

			o = l.coups[j].origine; 
			d = l.coups[j].destination;
			if(P.cols[o].couleur != P.trait)
			{
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					case 3: pot = 3;
					break;

					case 4: pot = 4;
							//coupVoisins(d);
					break;

					case 5:pot = 5;
					break;
				}
				min = calculMin(pot,min);
			}
			else
			{
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					case 3: printf("test1");
					pot = 3 + test(d,o,P);
					break;

					case 4: printf("test2");
					pot = 3 + test(d,o,P);
					break;

					case 5:pot = -10;
					break;
				}
				min = calculMin(pot,min);
			}
		}
		printf("\ncptAm : %d && cptEn : %d\n",cptAm,cptEn);
		if(cptAm < 1 && cptEn > 1)
		{
			min = -15;
		}
		else if(cptEn == 0)
		{
			min = 7;
		}
	}
	printf("voisEn : %d",voisEn);
	if(voisEn ==0)
	{
		min=-7;
	}
		printf("\n\nmini = %d\n\n",min);
		return min;
}

void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	// Cette fonction peut appeler la fonction ecrireIndexCoup(coupChoisi);
	// Pour sélectionner l'index d'un coup à jouer dans la liste l 


	int i,pot,max=-5;
	octet o, d; 
	octet myColor = currentPosition.trait; 

	//afficherListeCoups(listeCoups);

	printf("Ma couleur : %s\n", COLNAME(currentPosition.trait));
	for(i=0;i<listeCoups.nb; i++)
	{
		o = listeCoups.coups[i].origine; 
		d = listeCoups.coups[i].destination;  
		printf("Coup %d : ", i); 
		printf("%d (%d - %s) ->", o, currentPosition.cols[o].nb, COLNAME(currentPosition.cols[o].couleur));
		printf("%d (%d - %s) \n", d, currentPosition.cols[d].nb, COLNAME(currentPosition.cols[d].couleur)); 

	// Si je peux gagner une colonne, je la prends 
		/*if ((currentPosition.cols[o].couleur == myColor)
			&& (currentPosition.cols[o].nb + currentPosition.cols[d].nb == 5) ) {

				printf("On choisit ce coup ! \n"); 
				ecrireIndexCoup(i);
				return; // on quitte la fonction 
			}*/
		//Jaune sur jaune
		if(currentPosition.cols[o].couleur == myColor && currentPosition.cols[d].couleur == myColor)
		{
			printf("\n\nla somme = %d\n\n",currentPosition.cols[d].nb + currentPosition.cols[d].nb);
			switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
			{
				case 2: pot = 3 + coupVoisins(d,o,currentPosition);
						printf("pot = %d",pot);
				break;

				case 3: pot = 3 + coupVoisins(d,o,currentPosition);
				break;

				case 4:
						pot = 4 + coupVoisins(d,o,currentPosition);
				break;

				case 5:pot = 5;
				break;
			}
			max = testCoup(pot,max,i);
			
		}
		// jaune sur rouge
		else if(currentPosition.cols[o].couleur == myColor && currentPosition.cols[d].couleur != myColor)
		{
			switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
			{
				case 2: pot = 6 + coupVoisins(d,o,currentPosition);
						printf("pot = %d",pot);
				break;

				case 3: pot = 6 + coupVoisins(d,o,currentPosition);
				break;

				case 4:
						pot = 5 + coupVoisins(d,o,currentPosition);
				break;

				case 5:pot = 10;
				break;
			}
			max = testCoup(pot,max,i);
		}
		// Rouge sur rouge
		else if(currentPosition.cols[o].couleur != myColor && currentPosition.cols[d].couleur != myColor)//TODO
		{
			switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
			{
				case 2: pot = -2;

				break;

				case 3: pot = -3;
				break;

				case 4: pot = -4;
				break;

				case 5:pot = -5;
				break;
			}
			max = testCoup(pot,max,i);
		}
		//rouge sur jaune (à ne pas faire)
		else//TODO
		{
			
		}

	}
 


}
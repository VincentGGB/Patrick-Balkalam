/********* Moteur de tournoi : joueur ***************/

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"


void testCoup(int pot,int *max,int i)
{
	if(pot>*(max))
	{
		*(max)=pot;
		ecrireIndexCoup(i);
	}

}

void coupVoisins(int d,T_Position *P)
{
	T_Voisins voisins;
	T_ListeCoups l;
	voisins = getVoisins(d);
	int k = 0;


	for (int j = 0; j < voisins.nb; ++j)
	{
		if(P->cols[voisins.case[j]].nb + P->cols[voisins.case[d]].nb <= 5)
		{
			l.coups[k].origine = voisins.case[j];
			l.coups[k].destination = d;
			k++;
			l.nb++;
			l.coups[k].origine = d;
			l.coups[k].destination = voisins.case[j];
			k++;
			l.nb++;
		}
		else
		{
			j--;
		}
	}

	if(currentPosition.cols[o].couleur == myColor)
		{
			switch(currentPosition.cols[d].nb + currentPosition.cols[d].nb)
			{
				case 2: pot = 2;
				break;

				case 3: pot = 3;
				break;

				case 4: pot = 4;
						coupVoisins(d);
				break;

				case 5:pot = 5;
				break;
			}
		}
		else
		{
			switch(currentPosition.cols[d].nb + currentPosition.cols[d].nb)
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
		}
}

void choisirCoup(T_Position currentPosition, T_ListeCoups listeCoups) {
	// Cette fonction peut appeler la fonction ecrireIndexCoup(coupChoisi);
	// Pour sélectionner l'index d'un coup à jouer dans la liste l 


	int i,pot,max=-5;
	octet o, d; 
	octet myColor = currentPosition.trait; 

	// afficherListeCoups(listeCoups);

	printf("Ma couleur : %s\n", COLNAME(currentPosition.trait));
	for(i=0;i<listeCoups.nb; i++) {
		o = listeCoups.coups[i].origine; 
		d = listeCoups.coups[i].destination;  
		printf("Coup %d : ", i); 
		printf("%d (%d - %s) ->", o, currentPosition.cols[o].nb, COLNAME(currentPosition.cols[o].couleur));
		printf("%d (%d - %s) \n", d, currentPosition.cols[d].nb, COLNAME(currentPosition.cols[d].couleur)); 

	// Si je peux gagner une colonne, je la prends 
		if ((currentPosition.cols[o].couleur == myColor)
			&& (currentPosition.cols[d].nb + currentPosition.cols[d].nb == 5) ) {

				printf("On choisit ce coup ! \n"); 
				ecrireIndexCoup(i);
				return; // on quitte la fonction 
			}

		if(currentPosition.cols[o].couleur == myColor)
		{
			switch(currentPosition.cols[d].nb + currentPosition.cols[d].nb)
			{
				case 2: pot = 2;
				break;

				case 3: pot = 3;
				break;

				case 4: pot = 4;
						coupVoisins(d,&currentPosition);
				break;

				case 5:pot = 5;
				break;
			}
			testCoup(pot,&max,i);
		}
		else
		{
			switch(currentPosition.cols[d].nb + currentPosition.cols[d].nb)
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
		}


	} 
 


}
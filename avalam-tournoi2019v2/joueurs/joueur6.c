/********* Moteur de tournoi : joueur ***************/

#include <stdio.h>
#include <stdlib.h>
#include "avalam.h"
#include "moteur.h"

int coupVoisins(octet dBis,octet oBis,T_Position P);

int testCoup(int pot,int max,int i,T_Position P)
{
	if(P.trait==2)
	{
		if(pot>=max)
		{
			max=pot;
		 
			ecrireIndexCoup(i);
		}
	}
	else
	{
		if(pot>max)
		{
			max=pot;
		 
			ecrireIndexCoup(i);
		}
	}
	
	return max;
}

int calculMax(int pot,int max)
{
	if(pot>max)
	{
		max=pot;
	}
}

int calculMin(int pot,int min)
{
	if(pot<min)
	{
		min=pot;
	}
	return min;
}

int test(octet dBis,octet oBis,T_Position P) //TODO: Ameliorer en verifiant si on peut prendre le point juste derriere le coup ennemi
{
	T_Voisins voisins;
	T_ListeCoups l;
	voisins = getVoisins(dBis);
	int k = 0;
	int pot;
	int max = -5;
	int cpt = 0;
	int cptAm =0;
	int cptEn =0;
	octet o,d;
	l.nb = 0;
	listerVoisins(dBis);
	int Color = P.cols[dBis].couleur;
	P = jouerCoup(P,oBis,dBis);

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
			if(P.cols[voisins.cases[j]].couleur == P.trait)
			{
				cptAm++; //Nombre de tour amis de la tour joué
			}
			else
			{
				cptEn++; // Nombre de tour ennemis de la tour joué
			}
		}
	}
	afficherListeCoups(l);

	if((l.nb == 0) || (cptAm==0 && cptEn > 0))
	{
		max = -10;
	}
	else
	{
		for(int i=0;i<l.nb; i++)
		{
			o = l.coups[i].origine;    // position origine du coup
			d = l.coups[i].destination;// position destination du coup  

			//Ami sur ami
			if(P.cols[o].couleur == P.trait && P.cols[d].couleur == P.trait)
			{
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					//tour de 2
					case 2: pot = 3 + coupVoisins(d,o,P);
					break;
					//tour de 3
					case 3: pot = 3 + coupVoisins(d,o,P);
					break;
					//tour de 4
					case 4:
							pot = 2 + coupVoisins(d,o,P);
					break;
					//tour de 5
					case 5:pot = 10;  // TODO : tester si on peut pas la faire plus tard
					break;
				}
				max = calculMax(pot,max); // reCalcul du meilleur coup
				
			}
			// Ami sur ennemi
			else if(P.cols[o].couleur == P.trait && P.cols[d].couleur != P.trait)
			{
				if(P.cols[o].nb < P.cols[d].nb)// Il vaut mieux jouer un ami sur 2 ennemi
				{
					switch(P.cols[o].nb + P.cols[d].nb)
					{
						//tour de 2
						case 2: pot = 6 + coupVoisins(d,o,P);
						break;

						//tour de 3
						case 3: pot = 6 + coupVoisins(d,o,P);
						break;

						//tour de 4
						case 4:
								pot = 5 + coupVoisins(d,o,P);
						break;

						//tour de 6
						case 5:pot = 15; //Pas de test à faire ici normalement
						break;
					}
				}
				else // Plutôt que 2 ami sur un ennemi
				{
					switch(P.cols[o].nb + P.cols[d].nb)
					{
						//tour de 2
						case 2: pot = 4 + coupVoisins(d,o,P);
						break;

						//tour de 3
						case 3: pot = 4 + coupVoisins(d,o,P);
						break;

						//tour de 4
						case 4:
								pot = 3 + coupVoisins(d,o,P);
						break;

						//tour de 5
						case 5:pot = 13; // Pas de test à faire ici normalement
						break;
					}
				}
				max = calculMax(pot,max);// reCalcul du meilleur coup
			}
			// Ennemi sur ennemi
			else if(P.cols[o].couleur != P.trait && P.cols[d].couleur != P.trait)//TODO
			{
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					//tour de 2
					case 2: pot = 4+coupVoisins(d,o,P);
					break;

					//tour de 3
					case 3: pot = 4+coupVoisins(d,o,P);
					break;

					//tour de 4
					case 4: pot = -4;
					break;

					//tour de 5
					case 5:pot = 0;
					break;
				}
				max = calculMax(pot,max);// reCalcul du meilleur coup
			}
			//Ennemi sur ami (à ne pas faire)
			else
			{
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					//tour de 2
		            case 2: pot = -20;
		            break;

		            //tour de 3
		            case 3: pot = -30;
		            break;

		            //tour de 4
		            case 4: pot = -40;
		            break;

		            //tour de 5
		            case 5:pot = -50;
		            break;
		        }
			}

		}
	}
	
	return max;
}

int coupVoisins(octet dBis,octet oBis,T_Position P)
{
	T_Voisins voisins;  //Voisins une fois le coup joué
	T_Voisins voisinsoBis; //Voisins de l'origine avant de jouer le coup
	T_Voisins voisVois;

	T_ListeCoups l; // Liste de coup possible sur le coup que l'on va simuler

	int pot;
	int min = 0;
	int cptEn = 0;
	int cptAm = 0;
	int voisEnoBis =0;
	int voisAmoBis =0;
	int coloroBis = P.cols[oBis].couleur;
	int colordBis = P.cols[dBis].couleur;
	int voisVoisAm=0,voisVoisEn=0;
	int danger=0;

	octet o,d; // Origine et destination des coup possibles ennemi

	voisins = getVoisins(dBis);    // On récupère les voisins
	voisinsoBis = getVoisins(oBis); // On récupère les voisins de l'origine avant de jouer le coup

	l.nb = 0;  // On initialise le nombre de coup possible à 0

	listerVoisins(dBis); // Printf de debug


	for (int j = 0; j < voisinsoBis.nb; ++j)
	{
		if(((P.cols[voisinsoBis.cases[j]].nb)!=0) && (P.cols[voisinsoBis.cases[j]].couleur != P.trait) && ((P.cols[voisins.cases[j]].nb + P.cols[oBis].nb )<= 5))
		{
			voisEnoBis++;  // Calcul du nombre de tour ennemi qui mette potentiellement en danger notre origine
		}
		else if(((P.cols[voisinsoBis.cases[j]].nb)!=0) && (P.cols[voisinsoBis.cases[j]].couleur == P.trait)&& ((P.cols[voisins.cases[j]].nb + P.cols[oBis].nb )<= 5))
		{
			voisAmoBis++;
			voisVois = getVoisins(voisinsoBis.cases[j]);

			for (int k = 0; k < voisVois.nb; ++k)
			{
				if(((P.cols[voisinsoBis.cases[j]].nb)!=0) && (P.cols[voisinsoBis.cases[j]].couleur != P.trait) && ((P.cols[voisins.cases[j]].nb + P.cols[oBis].nb )<= 5))
				{
					voisVoisEn++;  // Calcul du nombre de tour ennemi qui mette potentiellement en danger notre origine
				}
				else if(((P.cols[voisinsoBis.cases[j]].nb)!=0) && (P.cols[voisinsoBis.cases[j]].couleur == P.trait)&& ((P.cols[voisins.cases[j]].nb + P.cols[oBis].nb )<= 5))
				{
					voisVoisAm++;
				}
			}
			if(voisVoisAm == 1 && voisVoisEn != 0)
			{
				danger=1;
				min = -10;
			}
		}
	}

	P = jouerCoup(P,oBis,dBis);  // Ou joue le coup pour simuler la position du plateau si le coup était joué.


	/*Cette boucle for calcul la liste des coup possible entre la position de la tour joué	*/
	/*et les voisins qu'elle possède.														*/

	for (int j = 0; j < voisins.nb; ++j)
	{
		if(((P.cols[voisins.cases[j]].nb)!=0) && ((P.cols[voisins.cases[j]].nb + P.cols[dBis].nb )<= 5))//On test si le coup est possible
		{
			/*Coup tour voisins sur tour joué*/
			l.coups[l.nb].origine = voisins.cases[j];
			l.coups[l.nb].destination = dBis;	
			l.nb++;

			/*Coup tour joué sur tour voisins*/
			l.coups[l.nb].origine = dBis;
			l.coups[l.nb].destination = voisins.cases[j];
			l.nb++;

			if(P.cols[voisins.cases[j]].couleur != P.trait)
			{
				cptAm++; //Nombre de tour amis de la tour joué
			}
			else
			{
				cptEn++; // Nombre de tour ennemis de la tour joué
			}
		}

	}
	afficherListeCoups(l);


	if(l.nb == 0 && coloroBis !=P.trait && colordBis == P.trait && danger ==0) //S'il ne reste plus de coup et que le sommet=ami sur destination ennemi alors on attribue le minimum pot +3 > Coup Interresant pour nous
	{
		if(voisAmoBis != 0 && voisEnoBis==0)
		{
			min = 12; //TODO: A augmenter peut etre
		}
		else
		{
			min = 10; //TODO: A augmenter peut etre
		}
 		
	}
	else if(l.nb==0 && colordBis !=P.trait)//Si il n'y a plus de coup possible et que la couleur de la tour dBis est la notre
	{
		min=-7; // Ce coup n'est pas à joué, c'est un coup inutile, mais pas dangereux
	}
	else // On calcul le pire coup que l'adversaire peut nous faire après avoir joué
	{
		for (int j = 0; j < l.nb; ++j)
		{

			o = l.coups[j].origine;    // Nouvelle origine du coup adverse
			d = l.coups[j].destination; // Nouvelle origine du coup adverse

			if(P.cols[o].couleur != P.trait) //Si la colonne final est du trait ami > Coup Interresant pour nous
			{
				switch(P.cols[o].nb + P.cols[d].nb)
				{
					//tour de 3
					case 3: pot = 3;
					break;

					//tour de 4
					case 4: pot = 4;
					break;

					//tour de 5
					case 5:pot = 5;
					break;
				}
				min = calculMin(pot,min); //reCalcul du pire coup
			}
			else
			{
				switch(P.cols[o].nb + P.cols[d].nb) //Tour ennemi > Coup dangereux
				{
					//tour de 3
					case 3: pot = 3 + test(d,o,P);
					break;

					//tour de 4
					case 4: pot = 3 + test(d,o,P);
					break;

					//tour de 5
					case 5:pot = -10;
					break;
				}
				min = calculMin(pot,min);
			}
		}

		if(cptAm == 0 && cptEn >= 1) //Pas d'ami et au moins un ennemi autour
		{
			min = -15;
		}
		else if(cptEn == 0 && colordBis == P.trait && danger==0) //Pas d'ennemi autour et couleur de dBis ennemi
		{
			if(coloroBis != P.trait) // Si la couleur d'origine est la notre
			{
				if(voisAmoBis != 0 && voisEnoBis==1)
				{
					min = 9;
				}
				else
				{
					min = 7;
				}
				
			}
			else if(cptAm>=2 && min!=-10 && danger==0)// Si au moins 2 amis et que l'ennemi ne peut pas faire de tour de 5
			{
				min = 7;
			}
			else
			{
				min = -7;
			}
		}
	}

	if(voisEnoBis == 0) //Si la tour oBis n'est pas en danger
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
		o = listeCoups.coups[i].origine;    // position origine du coup
		d = listeCoups.coups[i].destination;// position destination du coup  
		printf("Coup %d : ", i); 
		printf("%d (%d - %s) ->", o, currentPosition.cols[o].nb, COLNAME(currentPosition.cols[o].couleur));
		printf("%d (%d - %s) \n", d, currentPosition.cols[d].nb, COLNAME(currentPosition.cols[d].couleur)); 

		//Ami sur ami
		if(currentPosition.cols[o].couleur == myColor && currentPosition.cols[d].couleur == myColor)
		{
			switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
			{
				//tour de 2
				case 2: pot = 3 + coupVoisins(d,o,currentPosition);
						printf("pot = %d",pot);
				break;
				//tour de 3
				case 3: pot = 3 + coupVoisins(d,o,currentPosition);
				break;
				//tour de 4
				case 4:
						pot = 2 + coupVoisins(d,o,currentPosition);
				break;
				//tour de 5
				case 5:pot = 5;  // TODO : tester si on peut pas la faire plus tard
				break;
			}
			max = testCoup(pot,max,i,currentPosition); // reCalcul du meilleur coup
			
		}
		// Ami sur ennemi
		else if(currentPosition.cols[o].couleur == myColor && currentPosition.cols[d].couleur != myColor)
		{
			if(currentPosition.cols[o].nb < currentPosition.cols[d].nb)// Il vaut mieux jouer un ami sur 2 ennemi
			{
				switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
				{
					//tour de 2
					case 2: pot = 6 + coupVoisins(d,o,currentPosition);
							printf("pot = %d",pot);
					break;

					//tour de 3
					case 3: pot = 6 + coupVoisins(d,o,currentPosition);
					break;

					//tour de 4
					case 4:
							pot = 5 + coupVoisins(d,o,currentPosition);
					break;

					//tour de 6
					case 5:pot = 15; //Pas de test à faire ici normalement
					break;
				}
			}
			else // Plutôt que 2 ami sur un ennemi
			{
				switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
				{
					//tour de 2
					case 2: pot = 4 + coupVoisins(d,o,currentPosition);
							printf("pot = %d",pot);
					break;

					//tour de 3
					case 3: pot = 4 + coupVoisins(d,o,currentPosition);
					break;

					//tour de 4
					case 4:
							pot = 3 + coupVoisins(d,o,currentPosition);
					break;

					//tour de 5
					case 5:pot = 13; // Pas de test à faire ici normalement
					break;
				}
			}
			max = testCoup(pot,max,i,currentPosition);// reCalcul du meilleur coup
		}
		// Ennemi sur ennemi
		else if(currentPosition.cols[o].couleur != myColor && currentPosition.cols[d].couleur != myColor)//TODO
		{
			switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
			{
				//tour de 2
				case 2: pot = 4+coupVoisins(d,o,currentPosition);
				break;

				//tour de 3
				case 3: pot = 4+coupVoisins(d,o,currentPosition);
				break;

				//tour de 4
				case 4: pot = -4;
				break;

				//tour de 5
				case 5:pot = 12;
				break;
			}
			max = testCoup(pot,max,i,currentPosition);// reCalcul du meilleur coup
		}
		//Ennemi sur ami (à ne pas faire)
		else
		{
			switch(currentPosition.cols[o].nb + currentPosition.cols[d].nb)
			{
				//tour de 2
	            case 2: pot = -20;
	            break;

	            //tour de 3
	            case 3: pot = -30;
	            break;

	            //tour de 4
	            case 4: pot = -40;
	            break;

	            //tour de 5
	            case 5:pot = -50;
	            break;
	        }
		}

	}
}
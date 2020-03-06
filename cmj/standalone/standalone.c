#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avalam.h>
#include <topologie.h>

//prototype
void sauvegarder(T_Position pos, char* chaine,T_Score scor);

int main ()
{
	//Declaration des variables
	T_Score s; //score
	T_Position p; //position des pions
	T_ListeCoups l; 
	T_ListeCoups h;
	octet origine; //pions que l'on veut déplacer
	octet destination; //endroit ou l'on veut placer le pion
	char fic[16];
	char rep;

	strcpy (fic, "refresh-data.js");
	p = getPositionInitiale(); //initalise le plateau de jeu
	s=evaluerScore(p); //on initialise le score
	sauvegarder(p,fic,s);
        afficherScore(s);
 	l = getCoupsLegaux(p); //on stock les coups autorisé sur le plateau
	
 	printf("\n");

 	while(l.nb!=0)
 	{   
 		printf0("trait\n");
 		if(p.trait == 1) { //AFFICHAGE A CHAQUE TOUR DU TRAIT A JOUER 
			printf("Le trait est aux : JAUNES \n");
		}				
 		else printf("Le trait est aux : ROUGES \n");

		printf("Il y a %d Coups Legaux \n" , l.nb);
 		printf("Voulez-vous afficher les Coups Possibles [0/N]?");  
		scanf("%c",&rep);
		if (rep=='o' || rep=='O'){ afficherListeCoups(l);} //si l'utilisateur repond oui, on affiche la liste des coups

		printf("Quel pion voulez vous jouer ? \n");
		printf("O : ");
		scanf("%hhu", &origine); //l'utilisateur entre l'emplacement du pion qu'il veut déplacer
		printf("Sur quelle position voulez vous jouer ce pion ? \n");
		printf("D : ");
		scanf("%hhu", &destination); //l'utilisateur entre la destination du pion

		printf0("joue le coup\n");
		p = jouerCoup(p, origine, destination);//JOUER LE COUP (AVEC VERIFICATION (FONCTION estValide)
		printf0("ajoute le coup à l'historique\n");
		addCoup(&h,origine, destination); //HISTORIQUE DES COUPS
		printf("actualise la liste des coups legaux\n");
		l = getCoupsLegaux(p); //on actualise la liste de coups légaux
		s=evaluerScore(p);  // RECUPERE LE SCORE A CHAQUE TOUR
		afficherScore(s); // AFFICHE LE SCORE A CHAQUE TOUR 
		getchar(); //vide le buffer pour eviter les bugs
		printf("\n");
		sauvegarder(p,fic,s); 
	}

	printf("\n");

	//s.nbJ, s.nbJ5, s.nbR, s.nbR5
	if(s.nbJ==s.nbR)//si le nombre de pile jaune et de pile rouge est egal on regarde le nombre de pile de 5 pions
	{
		if(s.nbJ5>s.nbR5)
			printf("Le vainqueur est Jaune"); 
		else
			printf("Le vainqueur est rouge");
	}
	//sinon on regarde qui à le plus de pile de pion de sa couleur
	else if(s.nbJ>s.nbR)
	{
		printf("Le vainqueur est Jaune");
	}
	else{
		printf("Le vainqueur est rouge");
	}

	printf("\n");

return 0;
}

void sauvegarder(T_Position pos, char* chaine,	T_Score scor)
{
	printf0("entrée dans la fonction sauvegarder\n");
	FILE* fichier=NULL; //pointer de fichier
	char chemin[50]="../web/data/"; //LE FICHIER DONT LES DONNEES DE LA PARTIE SOUS FORMAT JSON SERONT STOCKEES
	int i;

	strcat(chemin, chaine); // CONCATENE CHEMIN ET CHAINE POUR FORMER LE BON CHEMIN VERS LE FICHIER 

	fichier=fopen(chemin,"w+");  // OUVRE LE FICHIER EN MODE ECRITURE

	if(fichier!=NULL)
	{
		// On commence ici à créer/modifier le fichier refresh-data.js
		printf0("creation/modification du fichier refresh-data.js\n");

		fprintf(fichier, "traiterJson({\n"); //ECRITURE SOUS FORMAT JSON
		fprintf(fichier, "\"trait\":%d,\n", pos.trait);
		fprintf(fichier, "\"scoreJ\":%d,\n", scor.nbJ);
		fprintf(fichier, "\"scoreJ5\":%d,\n", scor.nbJ5);
		fprintf(fichier, "\"scoreR\":%d,\n", scor.nbR);
		fprintf(fichier, "\"scoreR5\":%d,\n", scor.nbR5);
		fprintf(fichier, "\"cols\":[\n");

		for(i=0; i<=47; i++)//remplis chaque emplacement du plateau un par un
		{
			fprintf(fichier, "{\"nb\":%d, \"couleur\":%d},\n", pos.cols[i].nb,pos.cols[i].couleur);
		}

		fprintf(fichier, "]\n");
		fprintf(fichier, "});");

		fclose(fichier); // Referme le fichier
	}
	else printf("Le fichier n'existe pas\n");

	printf0("sortie de la fonction sauvegarder\n");
}

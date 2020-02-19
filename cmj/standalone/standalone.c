#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avalam.h>
#include <topologie.h>

void sauvegarder(T_Position pos, char* chaine,T_Score scor);

int main ()
{
	T_Score s; 
	T_Position p; 
	T_ListeCoups l;
	octet origine;
	octet destination;
	char fic[16];
	strcpy (fic, "refresh-data.js");
	p = getPositionInitiale();
	s=evaluerScore(p);
	sauvegarder(p,fic,s);
 	l = getCoupsLegaux(p);
 	printf("l.nb = %d",l.nb);
 	printf("\n");

 	while(l.nb!=0)
 	{
		printf("Quel pion voulez vous jouer ? \n");
		scanf("%hhu", &origine);
		printf("Sur quelle position voulez vous jouer ce pion ? \n");
		scanf("%hhu", &destination);
		p = jouerCoup(p, origine, destination);//Appel en plus la fonction estValide
		addCoup(&l,origine, destination);
		l = getCoupsLegaux(p);
		s=evaluerScore(p);  // Récupère le score actuel
		afficherScore(s); // afiiche le score actuel
		printf("\n");
		sauvegarder(p,fic,s);
	}

	printf("\n");
	//s.nbJ, s.nbJ5, s.nbR, s.nbR5
	if(s.nbJ==s.nbR)
	{
		if(s.nbJ5>s.nbR5)
			printf("Le vainqueur est Jaune");
		else
			printf("Le vainqueur est rouge");
	}
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
	FILE* fichier=NULL; //pointer de fichier

	char chemin[50]="../web/data/"; //il s'agit du chemin du fichier dans lequel vont être stockés les données de la partie
	int i;



	strcat(chemin, chaine); // concatère chemin et cat

	fichier=fopen(chemin,"w+");  // Ouvre le fichier en mode écriture

	if(fichier!=NULL)
	{
		// On commence ici à créer/modifier le fichier refresh-data.js

		fprintf(fichier, "traiterJson({\n");
		fprintf(fichier, "\"trait\":%d,\n", pos.trait);
		fprintf(fichier, "\"scoreJ\":%d,\n", scor.nbJ);
		fprintf(fichier, "\"scoreJ5\":%d,\n", scor.nbJ5);
		fprintf(fichier, "\"scoreR\":%d,\n", scor.nbR);
		fprintf(fichier, "\"scoreR5\":%d,\n", scor.nbR5);
		fprintf(fichier, "\"cols\":[\n");

		for(i=0; i<=47; i++)
		{
			fprintf(fichier, "{\"nb\":%d, \"couleur\":%d},\n", pos.cols[i].nb,pos.cols[i].couleur);
		}

		fprintf(fichier, "]\n");
		fprintf(fichier, "});");

		fclose(fichier); // Referme le fichier
	}
	else printf("Le fichier n'existe pas\n");
}

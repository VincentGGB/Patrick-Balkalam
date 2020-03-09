#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avalam.h>
#include <topologie.h>

void sauvegarder(T_Position pos, char* chaine,T_Score scor);

int main (int argc, char * argv[])
{
	T_Score s; 
	T_Position p; 
	T_ListeCoups l;
	T_ListeCoups h;
	octet origine;
	octet destination;
	char fic[16]="";
	
	p = getPositionInitiale();
	s=evaluerScore(p);
	
    afficherScore(s);
 	l = getCoupsLegaux(p);
 	int type=0;
	char rep;
 	printf("\n");


 	if(argc == 2)
 	{
 		strcpy (fic,argv[1]);
 		for (int i = 0; i < strlen(fic); ++i)
 		{
 			if(fic[i]=='.' && fic[i+1]=='j' && fic[i+2]=='s' && fic[i+3]=='\0')
 			{
 				printf0("Le type du fichier a été renseigné");
 				type++;
 			}
 		}

 		if(type!=1)
 		{
 			printf0("Le type du fichier n'est pas renseingné ou mal renseingné");
 			type = strlen(fic);
 			fic[type] = '.';
 			fic[type+1] = 'j';
 			fic[type+2] = 's';
 			fic[type+3] = '\0';
 		}

 	}
 	else
 	{
 		strcpy (fic, "refresh-data.js");
 	}
 	sauvegarder(p,fic,s);

 	printf1("Nom de fichier correct : %s",fic);

 	while(l.nb!=0)
 	{       if(p.trait == 1) { 
		printf("Le trait est aux : JAUNES \n");
				 }				//AFFICHAGE A CHAQUE TOUR DU TRAIT A JOUER 
 		else printf("Le trait est aux : ROUGES \n");
		printf("Il y a %d Coups Legaux \n" , l.nb);
 		printf("Voulez-vous afficher les Coups Possibles [0/N]?");  
		scanf("%c",&rep);
		if (rep=='o' || rep=='O'){ afficherListeCoups(l);}
		printf("Quel pion voulez vous jouer ? \n");
		printf("O : ");
		scanf("%hhu", &origine);
		printf("Sur quelle position voulez vous jouer ce pion ? \n");
		printf("D : ");
		scanf("%hhu", &destination);
		p = jouerCoup(p, origine, destination);//JOUER LE COUP (AVEC VERIFICATION (FONCTION estValide)
		addCoup(&h,origine, destination); //HISTORIQUE DE COUPS 
		l = getCoupsLegaux(p); 
		s=evaluerScore(p);  // RECUPERE LE SCORE A CHAQUE TOUR
		afficherScore(s); // AFFICHE LE SCORE A CHAQUE TOUR 
		getchar();
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

void sauvegarder(T_Position pos, char* chaine,	T_Score scor)  // Fonction qui permet de modifier le Json avec la T_Position
{
	FILE* fichier=NULL; //pointer de fichier

	printf1("chaine = %s",chaine);

	char chemin[50]="../web/data/"; //LE FICHIER DONT LES DONNEES DE LA PARTIES SOUS FORMATS JSON SERONT STOCKES
	int i;



	strcat(chemin, chaine); // CONCATENE CHEMIN ET CHAINE POUR FORMER LE BON CHEMIN VERS LE FICHIER 

	fichier=fopen(chemin,"w+");  // OUVRE LE FICHIER EN MODE ECRITURE

	if(fichier!=NULL)
	{
		// On commence ici à créer/modifier le fichier refresh-data.js

		fprintf(fichier, "traiterJson({\n"); //ECRITURE SOUS FORMAT JSON
		fprintf(fichier, "\"trait\":%d,\n", pos.trait);
		fprintf(fichier, "\"scoreJ\":%d,\n", scor.nbJ);
		fprintf(fichier, "\"scoreJ5\":%d,\n", scor.nbJ5);
		fprintf(fichier, "\"scoreR\":%d,\n", scor.nbR);
		fprintf(fichier, "\"scoreR5\":%d,\n", scor.nbR5);
		fprintf(fichier, "\"cols\":[\n");

		for(i=0; i<=NBCASES-1; i++)
		{
			fprintf(fichier, "{\"nb\":%d, \"couleur\":%d},\n", pos.cols[i].nb,pos.cols[i].couleur);
		}

		fprintf(fichier, "]\n");
		fprintf(fichier, "});");

		fclose(fichier); // Referme le fichier
	}
	else printf("Le fichier n'existe pas\n");
}

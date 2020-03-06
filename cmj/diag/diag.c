#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avalam.h>
#include <topologie.h>


/*IMPORTANT !!!!!!! EXPLICATION DE DIAG.C!!!!!!!!!!*/
/*auteurMessage : Paul Monier*/
/*Le but de ce fichier est de créer une situation particulière de jeu comme dans ./web/avalam-diag.html ouvert avec ../exemples/diag_another.js */
/*Pour celà nous devons créer un fichier json à partir de la position type FEN rentrée par l'utilisateur (nous), voir type FEN dans le cours*/
/*L'utilisateur rentrera dans l'invite de commande "./diag.static <numDiag> <codeFen>" afin de recupérer numDiag et codeFen avec argc et argv*/
/*J'ai mis ci dessous un morceau de code qui vous aidera à comprendre les difficultés qu'on va rencontrer.*/
/*Je vous conseille donc de bien lire les commentaires et de me poser des questions ensuite.*/
/*Bon courage !*/

int charToInt(char *numCharDiag);
T_Position translate(T_Position * P, char * fen);
void ecriture(T_Position pos, char * ficName,char * diagDesc,int numDiag);

int main (int argc, char * argv[])  // Le prototype du main est vide ou comme ceci. Impossible de faire autrement
{
	printf0("TTTTEESSSSSSTTTT!!!!!!!");
	T_Position P;

	int i=0;
	char nom[30];  // On stocke ici le nom du fichier Json à creer
	char desc[256];  // On stocke ici la description du diagramme
	int Diag; // On récupère la valeur int du numéro de diagramme
	printf("Veuillez entrez le nom du fichier à créer : ");  // On demande à l'utilisateur de saisir le nom du fichier comme demandé
	fgets(nom,sizeof(nom),stdin);  // On utilise la fonction fgets car il ne doit y avoir aucun warning
	nom[strlen(nom)-1]='\0';
	printf("\nVeuillez rentrez la description du diagramme : ");  // On demande à l'utilisateur la description du diagramme comme demandé
															   // Elle sera affiché dans le bas de la page web comme dans l'exemple, le site web la récupèrera du fichier Json
															   // ELle est donc à écrire dans le fichier Json
	fgets(desc,sizeof(desc),stdin);
	
	desc[strlen(desc)-1]='\0';  // On utilise fgets car il ne faut aucun warning

	printf1("\nNombre d'arg : %d = argc\n\n",argc);  // argc n'est pas le numdiag, mais le nombre d'arg
	printf1("Numéro de diag (char) : %s = argv[1]\n\n",argv[1]); // argv[1] est le numéro de diag en char
	printf1("Code Fen : %s = argv[2]\n\n",argv[2]);  // On constate que le code fen se trouve dans argv[2]
	printf1("Nom Fichier : >>%s<<\n",nom);  // Les fgets fonctionnent correctement
	printf1("Description : %s\n",desc);  // Les fgets fontionnent correctement 
	
	if(argc == 3) // On vérifira avant de se lancer dans l'interpretation de la commande entrée par l'utilisateur qu'il y a bien trois argument (./diag.static (1) <numDiag> (2) <codeFen> (3))
	{
		Diag = atoi(argv[1]);  // Appel de la fonction charToInt (voir fonction pour comprendre)

		if(Diag!=0)
			printf("Numéro de diag (int) : %d\n\n",Diag);  // On affiche le num de diag en int pour vérifier que ça marche bien
		else
			printf("Erreur : Numéro de diag invalide\n");  // On retourne une erreur si le chiffre rentré est improbable

		P = translate(&P,argv[2]);  // Appel de la fonction translate
	}

	ecriture(P,nom,desc,Diag);

return 0;
}


T_Position translate(T_Position * P, char * fen)  // Voici un début de fontion translate, elle est à terminer, il manque encore plein de truc à vérifier
{
	int i;  // On défini i ici pour le recupérer en sortie de boucle
	int j = 0;
	int place =0;
	
	for (i = 0; /*fen[i]!=' ' && */fen[i]!='\0'; ++i)  // On boucle jusqu'à la fin du code fen soit juste avant le trait (Définit juste après l'espace)
	{
		if(fen[i]>='0' && fen[i]<='9')  // Si c'est un int
        {
                int fenInt;
                int k;
                fenInt = atoi(&fen[i]);  // atoi vérifie le caractère suivant aussi

                if(fenInt <= 47)
                {
	                if(fen[i+1]>='0' && fen[i+1]<='9')  // Si c'est un chiffre
	                {
	                	if(fen[i+2]!='\0')
	                	{
	                    	i=i+2;
	                    }
	                    else
	                    {
	                    	i=i+1;
	                    	fen[i]='\0';
	                    	place =1;
	                    }
	                }
	                else
	                {
	                	i=i+1;
	                }

	                for (k = j; k < fenInt+j; ++k)
	                {
	                    P->cols[k].nb = 0;
	                    P->cols[k].couleur = VIDE;
	                }
	                j=k;
           		}
           		else
           		{
           			fen[i]='\0';           		
           		}
                /*P->cols[j].nb = 0;
                P->cols[j].couleur = VIDE;*/
        }


		switch(fen[i])  // On utilise un switch case pour traduire
		{
			case 'u': P->cols[j].nb = 1;  // On utilise ici la notation fléché pour remplir la taille de la tour
				  P->cols[j].couleur = JAU ;  // Idem pour définir la couleur
			break;
			
			/*La suite est à finir, c'est récurrent et facile*/
			case 'd': P->cols[j].nb = 2;
					  P->cols[j].couleur = JAU ;
			break;

			case 't':P->cols[j].nb = 3;
					 P->cols[j].couleur = JAU ;
			break;

			case 'q':P->cols[j].nb = 4;
					 P->cols[j].couleur = JAU ;
			break;

			case 'c':P->cols[j].nb = 5;
					 P->cols[j].couleur = JAU ;
			break;

			case 'U':P->cols[j].nb = 1;
					 P->cols[j].couleur = ROU ;
			break;

			case 'D':P->cols[j].nb = 2;
					 P->cols[j].couleur = ROU ;
			break;

			case 'T':P->cols[j].nb = 3;
					 P->cols[j].couleur = ROU ;
			break;

			case 'Q':P->cols[j].nb = 4;
					 P->cols[j].couleur = ROU ;
			break;

			case 'C':P->cols[j].nb = 5;
					 P->cols[j].couleur = ROU ;
			break;

			case ' ':
			break;

			case 'r': P->trait = ROU; // Idem que tout à l'heure mais pour le trait
			break;

			case 'R': P->trait = ROU;
			break;

			case 'j': P->trait = JAU;
			break;

			case 'J': P->trait = JAU;
			break;

			case '\0' : if(place == 0)
							printf("Le chiffre saisie dans n'est pas correct\n");
						i=i-1;
			break;

			default: printf("La chaine fen saisie n'est pas correcte");
				 	 printf("La valeur %c n'est pas reconnue",fen[i]);
			break;
		}	
		j++;
	}

	for (int k = j; k <= 47; ++k)
	{
		P->cols[k].nb =0;
		P->cols[k].couleur =VIDE;
	}

// TODO : Si vous pensez à autre chose rajoutez le !
return *P;
}

void ecriture(T_Position pos, char * ficName,char * diagDesc,int numDiag)  // Même fonctionnement que pour le standalone
{
	FILE* fichier=NULL; //pointer de fichier

	char chemin[50]="../web/data/"; //il s'agit du chemin du fichier dans lequel vont être stockés les données de la partie
	int i;



	strcat(chemin, ficName); // concatère chemin et cat

	fichier=fopen(chemin,"w+");  // Ouvre le fichier en mode écriture

	if(fichier!=NULL)
	{
		// On commence ici à créer le fichier Json
		fprintf(fichier, "traiterJson({\n");
		fprintf(fichier, "\"trait\":%d,\n", pos.trait);
		fprintf(fichier, "\"numDiag\":%d,\n", numDiag);
		fprintf(fichier, "\"notes\":\"%s\",\n", diagDesc);
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

// TODO : Fonction qui traduit le code Fen en chiffre et couleur a rentré dans le Json

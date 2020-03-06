#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avalam.h>
#include <topologie.h>

//prototypes
int charToInt(char *numCharDiag);
T_Position translate(T_Position * P, char * fen);
void ecriture(T_Position pos, char * ficName,char * diagDesc,int numDiag);

int main (int argc, char * argv[])  // Le prototype du main est vide ou comme ceci.
{
	//Declaration des variables 
	T_Position P; //position des pions
	char nom[30];  // On stocke ici le nom du fichier Json à creer
	char desc[256];  // On stocke ici la description du diagramme
	int Diag; // On récupère la valeur int du numéro de diagramme

	printf("Veuillez entrez le nom du fichier à créer : ");  // On demande à l'utilisateur de saisir le nom du fichier comme demandé
	fgets(nom,sizeof(nom),stdin);  // On utilise la fonction fgets car il ne doit y avoir aucun warning
	nom[strlen(nom)-1]='\0';
	printf("\nVeuillez rentrez la description du diagramme : ");  // On demande à l'utilisateur la description du diagramme 
															   // Elle sera affiché dans le bas de la page web, le site web la récupèrera du fichier Json
															   // Elle est donc à écrire dans le fichier Json
	fgets(desc,sizeof(desc),stdin); // On utilise fgets car il ne faut aucun warning
	 	
	desc[strlen(desc)-1]='\0'; // On retire \n en fin de chaine 

	printf1("\nNombre d'arg : %d = argc\n\n",argc);  // argc n'est pas le numdiag, mais le nombre d'arguments
	printf1("Numéro de diag (char) : %s = argv[1]\n\n",argv[1]); // argv[1] est le numéro de diag en char
	printf1("Code Fen : %s = argv[2]\n\n",argv[2]);  // On constate que le code fen se trouve dans argv[2]
	printf1("Nom Fichier : >>%s<<\n",nom);  // Les fgets fonctionnent correctement
	printf1("Description : %s\n",desc);  // Les fgets fontionnent correctement 
	
	printf0("verification du nombre d'arg");
	if(argc == 3) // On vérifira avant de se lancer dans l'interpretation de la commande entrée par l'utilisateur qu'il y a bien trois argument (./diag.static (1) <numDiag> (2) <codeFen> (3))
	{
		printf0("arc=3");
		Diag = atoi(argv[1]);  // Appel de la fonction charToInt (voir fonction pour comprendre)

		if(Diag!=0)
			printf("Numéro de diag (int) : %d\n\n",Diag);  // On affiche le num de diag en int pour vérifier que ça marche bien
		else
			printf("Erreur : Numéro de diag invalide\n");  // On retourne une erreur si le chiffre rentré est improbable

		printf0("translate fen")
		P = translate(&P,argv[2]);  // Appel de la fonction translate pour pouvoir utiliser le code fen

		printf0("ecriture");
		ecriture(P,nom,desc,Diag);  // Appel de la fonction écriture pour écrire dans le fichier Json
	}
	else
	{
		printf("./diag.static <numéro de diagramme> <code fen>\n");
	}

	
printf0("fin main");
return 0;
}


T_Position translate(T_Position * P, char * fen) 
{
	//Declaration des variables
	int i;  // Variable d'indice de la chaine fen
	int j = 0; //Variable d'indice de la T_Position P.cols[j];
	int place =0;  // Variable de vérification
	
	printf0("debut de la fonction translate et de la boucle for\n");

	for (i = 0; /*fen[i]!=' ' && */fen[i]!='\0'; ++i)  // On boucle jusqu'à la fin du code fen soit juste avant le trait (Définit juste après l'espace)
	{
		if(fen[i]>='0' && fen[i]<='9')  //On test si le caractère est un int
        {
                int fenInt; // Stockage des int
                int k;
                fenInt = atoi(&fen[i]);  // On récupère le chiffre présent dans la chaine

                if(fenInt <= 47)  // On vérifie que le chiffre soit inférieur à 47
                {
	                if(fen[i+1]>='0' && fen[i+1]<='9')  // Si il y a deux chiffre donc >10
	                {
	                	if(fen[i+2]!='\0')
	                	{
	                    	i=i+2;  // On déplace jusqu'au caractère suivant si il n'est pas \0
	                    }
	                    else
	                    {
	                    	i=i+1
	                    	fen[i]='\0';  // On met \0 dans fen[i] pour éviter les erreur
	                    	place =1;  // On stock 1 dans place pour changer le type d'erreur
	                    }
	                }
	                else
	                {
	                	i=i+1; // On déplace jusqu'au caractère suivant
	                }

	                for (k = j; k < fenInt+j; ++k)
	                {
	                    P->cols[k].nb = 0;        // On remplit les case à nb = 0
	                    P->cols[k].couleur = VIDE;// On remplit la couleur à vide
	                }
	                j=k;  // On récupère la nouvelle valeur de j
           		}
           		else
           		{
           			fen[i]='\0'; // Si la valeur saisie n'est pas correcte          		
           		}
        }


		switch(fen[i])  // On utilise un switch case pour traduire
		{
			case 'u': P->cols[j].nb = 1;  // On utilise ici la notation fléché pour remplir la taille de la tour
				  P->cols[j].couleur = JAU ;  // Idem pour définir la couleur
			break;
			
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

			case 'r': P->trait = ROU; // Idem mais pour le trait
			break;

			case 'R': P->trait = ROU;
			break;

			case 'j': P->trait = JAU;
			break;

			case 'J': P->trait = JAU;
			break;

			case '\0' : if(place == 0)  // On récupère le type de l'erreur
							printf("Le chiffre saisie dans n'est pas correct\n");
						i=i-1;  // On se place juste avant \0 pour sortir de la boucle
			break;

			default: printf("La chaine fen saisie n'est pas correcte \n");
				 	 printf("La valeur %c n'est pas reconnue",fen[i]);
			break;
		}	
		j++;  // On incrémente j
	}

	printf0("sortie de la boucle for\n entrée dans seconde boucle for\n");

	for (int k = j; k <= 47; ++k)  // On vide le reste des cases à la sortie du code fen
	{
		P->cols[k].nb =0;
		P->cols[k].couleur =VIDE;
	}
	printf0("Sortie de la deuxième boucle for\n")

printf0("fin de la fonction translate");
return *P;  // On retourne la T_Position
}



void ecriture(T_Position pos, char * ficName,char * diagDesc,int numDiag)  // Même fonctionnement que pour le standalone
{
	FILE* fichier=NULL; //pointeur de fichier

	char chemin[50]="../web/data/"; //il s'agit du chemin du fichier dans lequel vont être stockées les données de la partie
	int i;

	printf0("debut de la fonction ecriture\n");

	strcat(chemin, ficName); // concatène le chemin et le nom du fichier

	printf0("ouverture du fichier en mode ecriture\n");
	fichier=fopen(chemin,"w+");  // Ouvre le fichier en mode écriture


	if(fichier!=NULL)
	{
		printf0("fichier!=NULL\n");
		// On commence ici à créer le fichier Json
		fprintf(fichier, "traiterJson({\n");
		fprintf(fichier, "\"trait\":%d,\n", pos.trait);
		fprintf(fichier, "\"numDiag\":%d,\n", numDiag);
		fprintf(fichier, "\"notes\":\"%s\",\n", diagDesc);
		fprintf(fichier, "\"cols\":[\n");

		printf0("boucle for, écriture de cols\n");
		for(i=0; i<=47; i++)
		{
			fprintf(fichier, "{\"nb\":%d, \"couleur\":%d},\n", pos.cols[i].nb,pos.cols[i].couleur);
		}

		printf0("sortie de la boucle for \n");

		fprintf(fichier, "]\n");
		fprintf(fichier, "});");

		printf0("fermeture du fichier \n");
		fclose(fichier); // Referme le fichier
	}
	else printf("Le fichier n'existe pas\n");

	printf0("fin de la fonction ecriture\n");
}

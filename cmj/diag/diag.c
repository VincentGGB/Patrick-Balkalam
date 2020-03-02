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
	T_Position P;
	char nom[30];  // On stocke ici le nom du fichier Json à creer
	char desc[256];  // On stocke ici la description du diagramme
	int Diag; // On récupère la valeur int du numéro de diagramme
	printf("Veuillez entrez le nom du fichier à créer : ");  // On demande à l'utilisateur de saisir le nom du fichier comme demandé
	fgets(nom,sizeof(nom),stdin);  // On utilise la fonction fgets car il ne doit y avoir aucun warning
	printf("\nVeuillez rentrez la description du diagramme : ");  // On demande à l'utilisateur la description du diagramme comme demandé
															   // Elle sera affiché dans le bas de la page web comme dans l'exemple, le site web la récupèrera du fichier Json
															   // ELle est donc à écrire dans le fichier Json
	fgets(desc,sizeof(desc),stdin);  // On utilise fgets car il ne faut aucun warning

	printf("\nNombre d'arg : %d = argc\n\n",argc);  // argc n'est pas le numdiag, mais le nombre d'arg
	printf("Numéro de diag (char) : %s = argv[1]\n\n",argv[1]); // argv[1] est le numéro de diag en char
	printf("Code Fen : %s = argv[2]\n\n",argv[2]);  // On constate que le code fen se trouve dans argv[2]
	printf("Nom Fichier : %s\n",nom);  // Les fgets fonctionnent correctement
	printf("Description : %s\n",desc);  // Les fgets fontionnent correctement 

	/*On peut transformer notre argv[1] soit le numéro de diag en int        */
	/*Attention, cette méthode fontionne uniquement pour les chiffre ([0-9])*/

	Diag = *argv[1] - 48; // 48 étant le code ascii de 0
	//  Ou  = argv[1] - '0'; // Qui fonctionne aussi
	printf("Numéro de diag (int) : %d <<< Je fonctionne mal !\n\n",Diag);
	
	if(argc == 3) // On vérifira avant de se lancer dans l'interpretation de la commande entrée par l'utilisateur qu'il y a bien trois argument (./diag.static (1) <numDiag> (2) <codeFen> (3))
	{
		Diag = charToInt(argv[1]);  // Appel de la fonction charToInt (voir fonction pour comprendre)

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
	
	for (i = 0; fen[i]!=' ' && fen[i]!='\0'; ++i)  // On boucle jusqu'à la fin du code fen soit juste avant le trait (Définit juste après l'espace)
	{

		switch(fen[i])  // On utilise un switch case pour traduire
		{
			case 'u': P->cols[i].nb = 1;  // On utilise ici la notation fléché pour remplir la taille de la tour
				  P->cols[i].couleur = JAU ;  // Idem pour définir la couleur
			break;
			
			/*La suite est à finir, c'est récurrent et facile*/
			case 'd':
			break;

			case 't':
			break;

			case 'q':
			break;

			case 'c':
			break;

			case 'U':
			break;

			case 'D':
			break;

			case 'T':
			break;

			case 'Q':
			break;

			case 'C':
			break;

			default: printf("La chaine fen saisie n'est pas correcte");
				 printf("La valeur %c n'est pas reconnue",fen[i]);
			break;
		}	
	}

	if(fen[i]==' '  && fen[i+2]=='\0')  // Une fois sorti de la boucle il faut récupérer le trait en vérifiant que l'utilisateur n'a pas rentré une valeure interdite
	{
		switch(fen[i+1])
		{
			case 'r': P->trait = ROU; // Idem que tout à l'heure mais pour le trait
			break;
			/*Idem à finir et récurant*/
			case 'R':
			break;

			case 'j':
			break;

			case 'J':
			break;
		}
	}
//TODO : Il faut gérer le fait qu'il peut y avoir des chiffre dans le code fen pour désigne le nombre de case vide
// TODO : Il afut gérer le fait que le code fen n'est pas toujours remplit jusqu'à l'indice 48, il faut donc à la fin du code fen définir le reste des cases comme des cases VIDE
// TODO : Si vous pensez à autre chose rajoutez le !
return *P;
}

/*Cette fonction permet de lire un chiffre dans une chaine de caractère et de le retourner en int*/
int charToInt(char *numCharDiag)  // Cette fonction fonctione pour un nombre allant de 0 à 999
{
	int numDiag;  // Variable dans laquelle on va stocker la valeur en int du numDiag

	if(numCharDiag[1]=='\0') // On vérifie que c'est un chiffre [1-9]
	{
		numDiag = numCharDiag[0] - 48;
	}
	else if(numCharDiag[2]=='\0') // On vérifie que le nombre ne dépasse pas 99
	{
		numDiag = (numCharDiag[0] - 48)*10 + (numCharDiag[1]-48);
	}
	else if(numCharDiag[3]=='\0')  // On vérifie que le nombre ne dépasse pas 999
	{
		numDiag = (numCharDiag[0] - 48)*100 + (numCharDiag[1]-48)*10 + (numCharDiag[2]-48);
	}
	else return 0;  // On retourne 0 si plus grand que 999 ou si invalide

return numDiag;
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

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

int main (int argc, char * argv[])  // Le prototype du main est vide ou comme ceci. Impossible de faire autrement
{
	char nom[30];  // On stocke ici le nom du fichier Json à creer
	char desc[256];  // On stocke ici la description du diagramme
	int numDiag; // On récupère la valeur int du numéro de diagramme
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

	/*On peu transformer notre argv[1] soit le numéro de diag en int        */
	/*Attention, cette méthode fontionne uniquement pour les chiffre ([0-9])*/

	numDiag = *argv[1] - 48; // 48 étant le code ascii de 0
	//  Ou  = argv[1] - '0'; // Qui fonctionne aussi

	printf("Numéro de diag (int) : %d\n\n",numDiag);

return 0;
}

// TODO : Fonction qui traduit le code Fen en chiffre et couleur a rentré dans le Json
// TODO : Fonction qui écrit le fichier Json grace à la traduction du code fen
// TODO : Fonction qui récupère le numDiag en int pour numDiag > 9
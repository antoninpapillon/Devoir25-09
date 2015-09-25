#ifndef _LIBJOURNAL_JOURNAL_H_
#define _LIBJOURNAL_JOURNAL_H_

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

/** Énumération des différents niveaux de criticité de journalisation.
 *
 * Chaque énumération peut être convertie en chaîne de caractère grâce à la
 * structure de données niveau_vers_chaine[].
 *
 * @see niveau_vers_chaine[]
 **/
typedef enum {
    NONE = 0,
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    DEBUG = 4,
} niveau_t;

/** Tableau de chaînes assurant la conversion : niveau de criticité => texte
 *
 **/
static char *niveau_vers_chaine[] = {
    NULL,
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
};

/** Initialise la journalisation.
 *
 * __Exemple :__
 * @code{.c}
 * int resultat;
 * resultat = ouvrir_journal(ERROR, "mon_journal.log", NULL, 0);
 * @endcode
 *
 * ou bien
 *
 * @code{.c}
 * int resultat;
 * FILE* fichier_journal_perso;
 * fichier_journal_perso = fopen("mon_journal.log", "w");
 * resultat = ouvrir_journal(ERROR, NULL, fichier_journal_perso, 0);
 * @endcode
 * Ouvrira, par écrasement, le fichier nommé @c mon_journal.log pour y écrire tout
 * événement de criticité inférieur ou égale à @c ERROR .
 *
 * @param niveau Tout futur appel à ecrire_entree_journal() ne journalisera
 * qu'à un niveau inférieur ou égal à ce niveau de criticité.
 * @param nom_fichier La chaîne de caractères définissant le chemin du fichier de
 * journalisation (si NULL, alors fichier doit être valorisé).
 * @param fichier Pointeur sur FILE d'un fichier déjà déclaré (si NULL, alors nom_fichier
 * doit être valorisé).
 * @param ajouter Mode ajout au fichier si différent de 0, mode écrasé si égal à 0.
 *
 * @return 0 si tout va bien, -1 sinon
 *
 * @see ecrire_entree_journal
 **/
int ouvrir_journal(niveau_t niveau, char* nom_fichier, FILE* fichier, int ajouter);


/** Termine l'utilisation possible de la journalisation.
 *
 * Clos le fichier de journalisation et empêche tout ajout d'une nouvelle entrée
 * au journal.
 *
 * __Exemple :__
 * @code{.c}
 * if(ouvrir_journal(ERROR, "mon_journal.log", NULL, 0) != 0)
 * {
 *    return 1;
 * }
 * else{
 *    // Faire quelque chose
 *    // ...
 *    fermer_journal();
 * }
 * @endcode
 *
 * @see ouvrir_journal()
 **/
void fermer_journal(void);


/** Écrit une entrée dans le fichier de journalisation.
 *
 * Ne peut être appellé SI ET SEULEMENT SI ouvrir_journal a été appelé et n'a pas
 * retourné d'erreur.
 *
 * __Exemple :__
 * @code{.c}
 *    char* message = "Bonjour le monde !";
 *    ecrire_entree_journal(DEBUG, __FILE__, __LINE__, "Le message de DEBUG est : %s", message);
 * @endcode
 *
 * @param niveau Le niveau de criticité de l'entrée à journaliser
 * @param fichier Une chaîne décrivant le fichier réalisant l'entrée. @c \__FILE__ est
 * sans nul doute ce que vous préféreriez saisir.
 * @param ligne Un nombre décrivant le numéro de la ligne réalisant l'entrée. @c \__LINE__
 * est sans nul doute ce que vous préféreriez saisir.
 * @param format La chaîne de caractères spécifiant le message à journaliser formatée
 * comme une 'printf format string'.
 *
 * @see JOURNAL
 **/
void ecrire_entree_journal(niveau_t niveau, char* fichier, int ligne, char* format, ...);

/** MACRO permettant de faciliter l'ajout d'une entrée au journal.
 *
 * Cette MACRO fournie une interface simplifiée à ecrire_entree_journal()
 * en passant les définitions @c \__FILE__ et @c \__LINE__ correspondant toutes deux
 * au __nom du fichier__ appelant la MACRO et le __numéro de ligne__ d'appel à la MACRO,
 * respectivement.
 *
 * __Exemple :__
 * @code{.c}
 * if(ouvrir_journal(ERROR, "mon_journal.log", NULL, 0) != 0)
 * {
 *    return 1;
 * }
 * else{
 *    char* message = "Bonjour le monde !";
 *    JOURNAL(DEBUG, "Le message de DEBUG est : %s", message);
 * }
 * @endcode
 *
 * @param niveau Le niveau de criticité de l'entrée.
 * @param args La chaîne de caractères spécifiant le message à journaliser
 * (accompagnée des variables si nécessaire).
 * 
 * @see ecrire_entree_journal()
 **/
#define JOURNAL(niveau, args...) \
    ecrire_entree_journal(niveau, __FILE__, __LINE__, args)

#endif

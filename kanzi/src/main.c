#include "kanzi.h"

void create_kanzi_loop(char kanzi[8]) {
    while (1) {
        create_kanzi(kanzi);

        char response;
        printf("Voulez-vous continuer à créer un autre Kanzi ? (y/n) : ");
        scanf(" %c", &response);
        getchar(); 

        if (response == 'n' || response == 'N') {
            return; 
        } else if (response != 'y' && response != 'Y') {
            printf("Réponse invalide. Veuillez répondre avec 'y' pour oui ou 'n' pour non.\n");
        }
    }
}

int menu_kanzi(void) {
    int choice;
    printf("Menu Kanzi :\n");
    printf("1. Créer un Kanzi\n");
    printf("2. Afficher tous les Kanzi\n");
    printf("3. Jouer à un jeu\n");
    printf("4. Créer des règles\n");
    printf("5. Afficher les règles de Kanzi\n");
    printf("6. Exporter les cartes sur Anki\n");
   	printf("7. Sortir \n");
   	printf("Votre choix : ");
    scanf("%d", &choice);
    getchar();
    return choice;
}

void execute_choice(int choice, char kanzi[8]){
    switch (choice) {
        case 1:
            int result = is_rules_create();
            if (result == 0) 
            {
                create_kanzi_loop(kanzi);
            } else 
            {
                printf("Vous devez avoir crée des règles avant de pouvoir utiliser le kanzi\n");
            }
            break;
        case 2:
            afficher_tous_kanzi();
            break;
        case 3:
            int n;
            printf("Combien de fois voulez-vous jouer ? (maximum %d) : ", MAX_GAMES);
            scanf("%d", &n);
            getchar(); 
            play_game(n);
            break;
        case 4:
            create_rules();
            break;
        case 5: 
            afficher_regle_kanzi();
            break;
        case 6:
            export_anki();
            break;
		case 7:
            printf("Au revoir\n");
            break;


        default:
            printf("Choix invalide. Veuillez réessayer.\n");
    }
}

int main(void) {
    char kanzi[8] = ""; 
    int choice;

    do {
        choice = menu_kanzi();
        execute_choice(choice, kanzi); 
    } while (choice != 7);

    return 0;
}

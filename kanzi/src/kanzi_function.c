#include "kanzi.h"

int is_rules_create() {
    FILE *file = fopen("csv/kanzi_pinyin_final.csv", "r");
    if (file == NULL) {
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    if (size == 0) {
        // File exists but is empty
        return -1;
    }

    // File exists and is not empty
    return 0;
}

char* get_pinyin_line(int last_letter_index) {
    FILE *file = fopen("csv/kanzi_pinyin_final.csv", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (count == last_letter_index) {
            fclose(file);
            return strdup(line);  
        }
        count++;
    }
    fclose(file);
    return NULL;
}

const char *list_first_letters_male[] = {"null", "b", "p", "m", "f", "d", "t", "n", "l", "z", "c", "s", "zh", "ch", "sh", "r", "j", "q", "x", "g", "k", "h"};
const char *list_first_letters_female[] = {"y", "bi", "pi", "mi", "di", "ti", "ni", "li", "ji", "qi", "xi"};
const char *list_first_letters_fictional[] = {"w", "bu", "pu", "mu", "fu", "du", "tu", "nu", "lu", "gu", "ku","hu", "zhu", "chu", "shu", "ru", "zu","cu", "su"};
const char *list_first_letters_god[] = {"yu", "nü", "lü", "ju", "qu", "xu"};

void print_large(const char *caractere) {
    printf("   %s   %s   %s   \n", caractere, caractere, caractere);
    printf("   %s   %s   %s   \n", caractere, caractere, caractere);
    printf("   %s   %s   %s   \n", caractere, caractere, caractere);
    printf("\n");
}


void play_game(int n) {
    char kanzi_list[MAX_GAMES][MAX_LINE_LENGTH];
    FILE *file = fopen("csv/kanzi_list.csv", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    int count = 0;
    while (fgets(kanzi_list[count], sizeof(kanzi_list[0]), file) != NULL && count < MAX_GAMES) {
        size_t len = strlen(kanzi_list[count]);
        if (len > 0 && kanzi_list[count][len - 1] == '\n') {
            kanzi_list[count][len - 1] = '\0';
        }
        count++;
    }
    fclose(file);

    if (n > count) {
        printf("Nombre de jeux demandés est plus grand que le nombre de lignes dans le fichier.\n");
        n = count;
    }

    srand((unsigned int) time(NULL));
    int score = 0;

    printf("Bienvenue dans le jeu Kanzi !\n");
    printf("Vous allez devoir deviner la traduction du Kanzi suivant :\n");

    for (int i = 0; i < n; i++) {
        int random_index = rand() % count;
        char line[MAX_LINE_LENGTH];
        strcpy(line, kanzi_list[random_index]);

        char *kanzi = strtok(line, ",");
        char *traduction = strtok(NULL, ",");
        char *caractere = strtok(NULL, ",");
		char *personnage = strtok(NULL, ",");
		char *lieu = strtok(NULL, ",");
        char *ton_str = strtok(NULL, ",");

        if (!kanzi || !traduction || !caractere || !personnage || !lieu || !ton_str) {
            printf("Erreur de format dans le fichier pour la ligne : %s\n", kanzi_list[random_index]);
            continue;
        }

        int ton = atoi(ton_str);
        print_large(caractere);
        printf("Kanzi : %s  | Ton : %d\n", kanzi, ton);
		printf("Personnage %s | lieu : %s \n", personnage, lieu); 
        printf("Composant(s) : ");
        for (int j = 0; j < 6; j++) {
            char *component = strtok(NULL, ",");
            if (component) {
                printf("%s ", component);
            }
        }
        printf("\n");

        char guess[100];
        printf("Devinez la traduction : ");
        if (fgets(guess, sizeof(guess), stdin) == NULL) {
            printf("Erreur de saisie.\n");
            continue;
        }
        guess[strcspn(guess, "\n")] = '\0';

        if (strcmp(guess, traduction) == 0) {
            printf("Correct ! La traduction est bien '%s'.\n", traduction);
            score++;
        } else {
            printf("Incorrect. La traduction correcte était '%s'.\n", traduction);
        }
    }

    printf("\nPartie terminée. Votre score est de %d sur %d.\n", score, n);
}


void create_rules(void)
{
    const char *list_first_letters_male[] = {"null", "b", "p", "m", "f", "d", "t", "n", "l", "z", "c", "s", "zh", "ch", "sh", "r", "j", "q", "x", "g", "k", "h"};
    const char *list_first_letters_female[] = {"y", "bi", "pi", "mi", "di", "ti", "ni", "li", "ji", "qi", "xi"};
    const char *list_first_letters_fictional[] = {"w", "bu", "pu", "mu", "fu", "du", "tu", "nu", "lu", "gu", "ku","hu", "zhu", "chu", "shu", "ru", "zu","cu", "su"};
    const char *list_first_letters_god[] = {"yu", "nü", "lü", "ju", "qu", "xu"};
    const char *list_pinyin_final[] = {"null", "a", "o", "e", "ai", "ei", "ao", "ou", "an", "ang", "en", "eng", "ong"};
    
    int num_first_letters_male = sizeof(list_first_letters_male) / sizeof(list_first_letters_male[0]);
    int num_first_letters_female = sizeof(list_first_letters_female) / sizeof(list_first_letters_female[0]);
    int num_first_letters_fictional = sizeof(list_first_letters_fictional) / sizeof(list_first_letters_fictional[0]);
    int num_first_letters_god = sizeof(list_first_letters_god) / sizeof(list_first_letters_god[0]);
    int num_pinyin_final = sizeof(list_pinyin_final) / sizeof(list_pinyin_final[0]);
    
    char kanzi_first_letters_male[num_first_letters_male][150];
    char kanzi_first_letters_female[num_first_letters_female][150];
    char kanzi_first_letters_fictional[num_first_letters_fictional][150];
    char kanzi_first_letters_god[num_first_letters_god][150];
    char kanzi_pinyin_final[num_pinyin_final][150];
    
    int i = 0;
    
    printf("Personnage Male :\n ");
    while (i < num_first_letters_male)
    {
        printf("Saisir un nom de personnage masculin commençant par la lettre %s: ", list_first_letters_male[i]);
        scanf("%149s", kanzi_first_letters_male[i]);
        i++;
    }
    
    i = 0;
    
    printf("Personnage féminin : \n");
    while (i < num_first_letters_female)
    {
        printf("Saisir un nom de personnage commençant par la lettre %s: ", list_first_letters_female[i]);
        scanf("%149s", kanzi_first_letters_female[i]);
        i++;
    }
    
    i = 0;
    
    printf("Personnage fictif \n");
    while (i < num_first_letters_fictional)
    {
        printf("Saisir un nom de personnage commençant par la lettre %s: ", list_first_letters_fictional[i]);
        scanf("%149s", kanzi_first_letters_fictional[i]);
        i++;
    }
    
    i = 0;
    
    printf("Personnage Dieu / Empereur :\n");
    while (i < num_first_letters_god)
    {
        printf("Saisir un nom de personnage commençant par la lettre %s: ", list_first_letters_god[i]);
        scanf("%149s", kanzi_first_letters_god[i]);
        i++;
    }
    
    i = 0;
    
    printf("Pinyin final : \n");
    while (i < num_pinyin_final)
    {
        printf("Saisir un lieu commençant par %s: ", list_pinyin_final[i]);
        scanf("%149s", kanzi_pinyin_final[i]);
        i++;
    }
    
    save_to_csv("csv/kanzi_first_letters_male.csv", kanzi_first_letters_male, list_first_letters_male, num_first_letters_male);
    save_to_csv("csv/kanzi_first_letters_female.csv", kanzi_first_letters_female, list_first_letters_female, num_first_letters_female);
    save_to_csv("csv/kanzi_first_letters_fictional.csv", kanzi_first_letters_fictional, list_first_letters_fictional, num_first_letters_fictional);
    save_to_csv("csv/kanzi_first_letters_god.csv", kanzi_first_letters_god, list_first_letters_god, num_first_letters_god);
    save_to_csv("csv/kanzi_pinyin_final.csv", kanzi_pinyin_final, list_pinyin_final, num_pinyin_final);
}

void save_to_csv(const char *filename, char data[][150], const char *list[], size_t size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    // Iterate through each element in the array
    for (size_t i = 0; i < size; i++) {
        // Write data[i] (which is the user-provided value) in Column A
        // Write list[i] (which is the corresponding element from list[]) in Column B
        fprintf(file, "%s,%s\n", list[i], data[i]);
    }

    fclose(file);
}

void load_from_csv(const char *filename, char data[][150], size_t size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (fgets(data[i], 50, file) != NULL) {
            size_t len = strlen(data[i]);
            if (len > 0 && data[i][len - 1] == '\n') {
                data[i][len - 1] = '\0';
            }
        }
    }

    fclose(file);
}

void display_data(const char *title, char data[][150], size_t size) 
{
    printf("%s:\n", title);
    for (size_t i = 0; i < size; i++) {
        printf("%s\n", data[i]);
    }
}

void afficher_regle_kanzi(void)
{
    char kanzi_first_letters_male[22][150];
    char kanzi_first_letters_female[21][150];
	char kanzi_first_letters_fictional[21][150];
	char kanzi_first_letters_god[21][150];
	char kanzi_pinyin_final[13][150];

    load_from_csv("csv/kanzi_first_letters_male.csv", kanzi_first_letters_male, 22);
    load_from_csv("csv/kanzi_first_letters_female.csv", kanzi_first_letters_female, 21);
	load_from_csv("csv/kanzi_first_letters_fictional.csv", kanzi_first_letters_fictional, 21);
	load_from_csv("csv/kanzi_first_letters_god.csv", kanzi_first_letters_god, 19);
	load_from_csv("csv/kanzi_pinyin_final.csv", kanzi_pinyin_final, 13);

    printf("Personnages Masculin: \n");
    display_data("Kanzi Masculine caracter", kanzi_first_letters_male, 22);
	
	printf("\n Personnage Féminin \n");
	display_data("Kanzi Féminine caracter", kanzi_first_letters_female, 11);

	printf("\n Personnage fictionelle \n");
	display_data("Kanzi fictional caracter", kanzi_first_letters_fictional, 19);

    printf("\n Personnage Dieu \n");
	display_data("Kanzi god caracter", kanzi_first_letters_god, 6);

    printf("\n Locations : \n");
	display_data("Kanzi Pinyin Finals", kanzi_pinyin_final, 13);
}


void afficher_tous_kanzi(void) {   
    char kanzi_list[100][250];
    FILE *file = fopen("csv/kanzi_list.csv", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }
    
    size_t count = 0;
    while (fgets(kanzi_list[count], sizeof(kanzi_list[0]), file) != NULL && count < 100) {
        size_t len = strlen(kanzi_list[count]);
        if (len > 0 && kanzi_list[count][len - 1] == '\n') {
            kanzi_list[count][len - 1] = '\0';
        }
        count++;
    }

    fclose(file);

    printf("Tous les Kanjis:\n");
    
    printf("%-20s %-20s %-20s %-20s %-20s %-10s", "Kanzi", "Traduction", "Caractère", "Personnages", "Lieu", "Ton");
    for (int i = 0; i < 6; i++) {
        printf(" %-20s", "Composants");
    }
    printf("\n");
    
    for (size_t i = 0; i < count; i++) {
        char *kanzi = strtok(kanzi_list[i], ",");
        char *traduction = strtok(NULL, ",");
        char *caractere = strtok(NULL, ",");
        char *personnage = strtok(NULL, ",");
        char *lieu = strtok(NULL, ",");
        char *ton_str = strtok(NULL,",");
        char *components[6] = {NULL};

        for (int j = 0; j < 6; j++) {
            components[j] = strtok(NULL, ",");
        }

        if (kanzi && traduction && caractere && personnage && lieu && ton_str) {

            printf("%-20s %-20s %-20s %-20s %-20s %-10s", kanzi, traduction, caractere, personnage, lieu, ton_str);
            for (int j = 0; j < 6; j++) {
                printf(" %-20s", components[j] ? components[j] : "");
            }
            printf("\n");
        }
    }
}

int verification_kanzi(const char *first_letter, const char *second_letter) {
    const char *valid_first_letters[] = {
        "null", "b", "p", "m", "f", "d", "t", "n", "l", "z", "c", "s", "zh", "ch", "sh", "r", 
        "j", "q", "x", "g", "k", "h", "y", "bi", "pi", "mi", "di", "ti", "ni", "li", "ji", 
        "qi", "xi", "w", "bu", "pu", "mu", "fu", "du", "tu", "nu", "lu", "gu", "ku", "hu", 
        "zhu", "chu", "shu", "ru", "zu", "cu", "su", "yu", "nü", "lü", "ju", "qu", "xu"
    };
    const int num_valid_first_letters = sizeof(valid_first_letters) / sizeof(valid_first_letters[0]);
    
    int valid_first = 0;
    for (int i = 0; i < num_valid_first_letters; i++) {
        if (strcmp(first_letter, valid_first_letters[i]) == 0) {
            valid_first = 1;
            break;
        }
    }

    if (!valid_first) {
        return 0;
    } 

    const char *valid_second_letters[] = {
        "null", "a", "ai", "ao", "an", "ang", "e", "ei", "o", "ong", "ou", "yi", "i", "ya", 
        "ia", "yao", "iao", "ye", "ie", "you", "iu", "an", "ian", "ang", "iang", "yin", 
        "in", "you", "yan", "yang", "ying", "ing", "yong", "wu", "u", "wa", "ua", "wo", 
        "uo", "wei", "ui", "wai", "uai", "wan", "uan", "wen", "un", "wang", "uang", 
        "weng", "yu", "u", "yue", "ue", "yuan", "uan", "yun", "un"
    };
    const int num_valid_second_letters = sizeof(valid_second_letters) / sizeof(valid_second_letters[0]);

    int valid_second = 0;
    for (int i = 0; i < num_valid_second_letters; i++) {
        if (strcmp(second_letter, valid_second_letters[i]) == 0) {
            valid_second = 1;
            break;
        }
    }

    return valid_first && valid_second;
}

char *find_first_letter(const char *kanzi) {
    const char *filenames[] = {
        "csv/kanzi_first_letters_god.csv",
        "csv/kanzi_first_letters_fictional.csv",
        "csv/kanzi_first_letters_female.csv",
        "csv/kanzi_first_letters_male.csv"
    };

    for (size_t i = 0; i < sizeof(filenames) / sizeof(filenames[0]); i++) {
        char *result = get_element_from_file(filenames[i], kanzi);
        if (result != NULL) {
            return result;
        }
    }

    return NULL; // No match found in any file
}
char *find_last_letter(const char *kanzi) {
    return get_element_from_file("csv/kanzi_pinyin_final.csv", kanzi);
}

char *get_element_from_file(const char *filename, const char *kanzi) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character

        char *token = strtok(line, ",");
        if (strcmp(token, kanzi) == 0) {
            token = strtok(NULL, ",");
            fclose(file);
            if (token != NULL) {
                return strdup(token);
            }
            return NULL;
        }
    }

    fclose(file);
    return NULL;
}

void create_kanzi(char *kanzi) {
    char first_letter[100];
    char second_letter[100];
    char traduction[100];
    char caracter[100];
    int tone;
    int num_components;
    char components[6][50];

    while (true) {
        printf("Saisir première lettre du Kanzi: (si null écrire null) ");
        if (fgets(first_letter, sizeof(first_letter), stdin) == NULL) {
            printf("Erreur de saisie.\n");
            continue;
        }
        first_letter[strcspn(first_letter, "\n")] = '\0';

        printf("Saisir seconde lettre du Kanzi: (si null écrire null) ");
        if (fgets(second_letter, sizeof(second_letter), stdin) == NULL) {
            printf("Erreur de saisie.\n");
            continue;
        }
        second_letter[strcspn(second_letter, "\n")] = '\0';

        if (strcmp(first_letter, "") == 0 && strcmp(second_letter, "") == 0) {
            printf("Les deux lettres ne peuvent pas être nulles en même temps.\n");
            continue;
        }

        if (!verification_kanzi(first_letter, second_letter)) {
            printf("Les lettres saisies ne sont pas valides.\n");
            continue;
        }

        break;
    }

    if (strcmp(first_letter, "null") == 0) {
        strcpy(kanzi, second_letter);
    } else if (strcmp(second_letter, "null") == 0) {
        strcpy(kanzi, first_letter);
    } else {
        strcpy(kanzi, first_letter);
        strcat(kanzi, second_letter);
    }


    char *first_letter_kanzi = find_first_letter(first_letter);
    char *last_letter_kanzi = find_last_letter(second_letter);

    printf("Saisir traduction: ");
    if (fgets(traduction, sizeof(traduction), stdin) == NULL) {
        printf("Erreur de saisie.\n");
        return;
    }
    traduction[strcspn(traduction, "\n")] = '\0';

    printf("Saisir caractère chinois: ");
    if (fgets(caracter, sizeof(caracter), stdin) == NULL) {
        printf("Erreur de saisie.\n");
        return;
    }
    caracter[strcspn(caracter, "\n")] = '\0';

    printf("Saisir ton du caractère (1 à 4): ");
    if (scanf("%d", &tone) != 1) {
        printf("Erreur de saisie pour le ton.\n");
        return;
    }
    getchar(); 
    if (tone < 1 || tone > 4) {
        printf("Ton invalide. Veuillez saisir un ton entre 1 et 4.\n");
        return;
    }

    printf("Saisir le nombre de composants présents dans le caractère (max 6): ");
    if (scanf("%d", &num_components) != 1) {
        printf("Erreur de saisie pour le nombre de composants.\n");
        return;
    }
    getchar();
    if (num_components < 1 || num_components > 6) {
        printf("Nombre de composants invalide. Veuillez saisir un nombre entre 1 et 6.\n");
        return;
    }

    for (int i = 0; i < num_components; i++) {
        printf("Saisir le composant %d: ", i + 1);
        if (fgets(components[i], sizeof(components[i]), stdin) == NULL) {
            printf("Erreur de saisie pour le composant %d.\n", i + 1);
            return;
        }
        components[i][strcspn(components[i], "\n")] = '\0';
    }

    char entry[500];
    snprintf(entry, sizeof(entry), "%s,%s,%s,%s,%s,%d", kanzi, traduction, caracter, first_letter_kanzi, last_letter_kanzi, tone);

    for (int i = 0; i < num_components; i++) {
        strcat(entry, ",");
        strcat(entry, components[i]);
    }

    free(first_letter_kanzi);
    free(last_letter_kanzi);
    append_to_csv("csv/kanzi_list.csv", entry);
    printf("Le Kanzi créé est: %s\n", kanzi);
}



void append_to_csv(const char *filename, const char *entry) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }
    fprintf(file, "%s\n", entry);
    fclose(file);
}

void export_anki() {
    char kanzi_list[MAX_GAMES][MAX_LINE_LENGTH];
    FILE *file = fopen("csv/kanzi_list.csv", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    size_t count = 0;
    while (fgets(kanzi_list[count], sizeof(kanzi_list[0]), file) != NULL && count < MAX_GAMES) {
        size_t len = strlen(kanzi_list[count]);
        if (len > 0 && kanzi_list[count][len - 1] == '\n') {
            kanzi_list[count][len - 1] = '\0';
        }
        count++;
    }

    fclose(file);

    FILE *output_file = fopen("csv/anki.csv", "w");
    if (output_file == NULL) {
        perror("Unable to open output file");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        char *kanzi = strtok(kanzi_list[i], ",");
        char *traduction = strtok(NULL, ",");
        char *caractere = strtok(NULL, ",");
		char *personnage = strtok(NULL, ",");
		char *lieu = strtok(NULL, ",");
        char *ton_str = strtok(NULL, ",");
        char *components[6] = {NULL};

        for (int j = 0; j < 6; j++) {
            components[j] = strtok(NULL, ",");
        }

        if (kanzi && traduction && caractere && personnage && lieu && ton_str) {
            int ton = atoi(ton_str);
            fprintf(output_file, " <b> Kanzi : %s</b>  <h1> %s </h1>  <br> <b> Ton : %d</b> <br> Composant(s) : ", kanzi, caractere, ton);
            for (int j = 0; j < 6; j++) {
                if (components[j]) {
                    fprintf(output_file,  "		%s	", components[j]);
                }
            }
            fprintf(output_file, ", <h1> %s </h1>  <br>  Personnage : %s  Lieu : %s \n", traduction, personnage, lieu);
        }
    }

    fclose(output_file);
    printf("Exportation réalisée avec succès\n");
}

#ifndef KANZI_H
#define KANZI_H
#define MAX_LINE_LENGTH 250
#define MAX_GAMES 20
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int is_rules_create();
void play_game(int n);
void create_rules(void);
void export_anki();
void save_to_csv(const char *filename, char data[][150], const char *list[], size_t size);
void load_from_csv(const char *filename, char data[][150], size_t size);
void display_data(const char *title, char data[][150], size_t size);
void afficher_tous_kanzi(void);
int verification_kanzi(const char *first_letter, const char *second_letter);
int menu_kanzi(void);
void execute_choice(int choice, char kanzi[8]);
void create_kanzi_loop(char kanzi[8]);
void afficher_kanzi(const char *kanzi);
void afficher_regle_kanzi(void);
int find_position_in_list(const char *kanzi, const char **list, size_t list_size);
char *find_first_letter(const char *kanzi);
char *find_last_letter(const char *kanzi);
char *get_element_from_file(const char *filename, const char *kanzi);
void create_kanzi(char *kanzi);
void append_to_csv(const char *filename, const char *entry);
extern const char *list_first_letters_god[];
extern const char *list_first_letters_fictional[];
extern const char *list_first_letters_female[];
extern const char *list_first_letters_male[];

#endif

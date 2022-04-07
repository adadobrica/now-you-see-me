#ifndef _UTILS_H_
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#define STRING_SIZE 256
#define MAX_SYMBOL_SIZE 8
#define NUM_SYMBOLS 4
#define LINE_MAX 100
#define INVALID_CARD "The provided card is not a valid one.\n"
#define INVALID_COMMAND "Invalid command. Please try again.\n"

ll_t* list_create(int data_size);
void free_list(ll_t **list);
node_t* get_nth_node(ll_t *list, int n);
void free_main_list(ll_t **list);
void add_card(ll_t *deck, const void *card);
int add_deck_to_list(const void *deck, ll_t *list);
int check_valid_card(card_t *card);
int delete_deck(ll_t *list, int index);
void delete_card(ll_t *list, int d_index, int c_index);
void add_cards(ll_t *list, int index, int num);
void get_deck_number(ll_t *list);
node_t* get_nth_node(ll_t *list, int n);
void get_deck_len(ll_t *list, int deck_index);
void shuffle_deck(ll_t *list, int deck_index);
void add_nth_node(ll_t *list, int n, const void *card);
void merge_decks(ll_t *list, int d_index1, int d_index2);
void remove_nth_node(ll_t **list, int n);
void add_nth_deck(ll_t *list, int n, const void *deck);
void split_deck(ll_t *list, int d_index, int split_index);
void reverse_deck(ll_t *list, int deck_index);
void show_deck(ll_t *deck, int deck_index);
void show_all(ll_t *list);
void sort_deck(ll_t *list, int deck_index);
int check_invalid_command(char garb[LINE_MAX]);
void ADD_DECK_COMMAND(ll_t **my_list, int num_cards);
void DELETE_DECK_COMMAND(ll_t **my_list);
void DELETE_CARD_COMMAND(ll_t **my_list);
void ADD_CARDS_COMMAND(ll_t **my_list);
void DECK_NUMBER_COMMAND(ll_t **my_list);
void DECK_LEN_COMMAND(ll_t **my_list);
void SHUFFLE_DECK_COMMAND(ll_t **my_list);
void MERGE_DECKS_COMMAND(ll_t **my_list);
void SPLIT_DECK_COMMAND(ll_t **my_list);
void REVERSE_DECK_COMMAND(ll_t **my_list);
void SHOW_DECK_COMMAND(ll_t **my_list);
void SHOW_ALL_COMMAND(ll_t **my_list);
void SORT_DECK_COMMAND(ll_t **my_list);

#endif  //  _UTILS_H_ //

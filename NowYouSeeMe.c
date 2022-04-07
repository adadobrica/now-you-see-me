// Copyright 2022 Dobrica Nicoleta Adriana
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "struct.h"

#define STRING_SIZE 256
#define MAX_SYMBOL_SIZE 8
#define NUM_SYMBOLS 4
#define LINE_MAX 100
#define INVALID_CARD "The provided card is not a valid one.\n"
#define INVALID_COMMAND "Invalid command. Please try again.\n"

int main(void) {
	ll_t *my_list = list_create(sizeof(ll_t *));
	char command[STRING_SIZE], garb[LINE_MAX];
	int num_cards, deck_index, card_index, i1, i2;
	while (1) {
		scanf("%s", command);
		if (strcmp(command, "ADD_DECK") == 0) {
			scanf("%d", &num_cards);
			if (check_invalid_command(garb) == 1) {
				ADD_DECK_COMMAND(&my_list, num_cards);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "DEL_DECK") == 0) {
			DELETE_DECK_COMMAND(&my_list);
		} else if (strcmp(command, "DEL_CARD") == 0) {
			DELETE_CARD_COMMAND(&my_list);
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			ADD_CARDS_COMMAND(&my_list);
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			DECK_NUMBER_COMMAND(&my_list);
		} else if (strcmp(command, "DECK_LEN") == 0) {
			DECK_LEN_COMMAND(&my_list);
		} else if (strcmp(command,  "SHUFFLE_DECK") == 0) {
			SHUFFLE_DECK_COMMAND(&my_list);
		} else if (strcmp(command, "MERGE_DECKS") == 0) {
			MERGE_DECKS_COMMAND(&my_list);
		} else if (strcmp(command, "SPLIT_DECK") == 0) {
			SPLIT_DECK_COMMAND(&my_list);
		} else if (strcmp(command, "REVERSE_DECK") == 0) {
			REVERSE_DECK_COMMAND(&my_list);
		} else if (strcmp(command, "SHOW_DECK") == 0) {
			SHOW_DECK_COMMAND(&my_list);
		} else if (strcmp(command, "SHOW_ALL") == 0) {
			SHOW_ALL_COMMAND(&my_list);
		} else if (strcmp(command, "EXIT") == 0) {
			free_main_list(&my_list);
			break;
		} else if (strcmp(command, "SORT_DECK") == 0) {
			SORT_DECK_COMMAND(&my_list);
		} else {
			printf(INVALID_COMMAND);
			fgets(garb, LINE_MAX - 1, stdin);
		}
	}
	return 0;
}

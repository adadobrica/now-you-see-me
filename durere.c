#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 256
#define MAX_SYMBOL_SIZE 8
#define DECK_INDEX_OUT_OF_BOUNDS "The provided index is out of bounds \
												for the deck list.\n"
#define CARD_INDEX_OUT_OF_BOUNDS "The provided index is out of bounds \
												for deck %ld.\n"
#define INVALID_CARD "The provided card is not a valid one.\n"
#define INVALID_COMMAND "Invalid command. Please try again.\n"
#define ADDED_DECK "The deck was successfully created with %d cards.\n"


typedef struct node_t
{
	void* data;
	struct node_t *next, *prev;
} node_t;

typedef struct ll_t
{
	node_t *head;
	int data_size;
	int size;
} ll_t;

typedef struct card_t {
	int value;
	char symbol[MAX_SYMBOL_SIZE];
} card_t;

ll_t* list_create(int data_size) {
	ll_t *list = malloc(sizeof(ll_t));
	list->data_size = data_size;
	list->size = 0;
	list->head = NULL;
	return list;
}
void free_list(ll_t **list) {
	node_t *aux = (*list)->head;
	while (aux) {
		node_t *next = aux->next;
		free(aux);
		free(aux->data);
		aux = next;
	}
	free(*list);
	*list = NULL;
}

void add_card(ll_t *deck, const void *card) {
	node_t *new_node = malloc(sizeof(node_t));
	new_node->data = malloc(deck->data_size);
	memcpy(new_node->data, card, deck->data_size);
	new_node->next = NULL;
	new_node->prev = NULL;
	
	if (deck->size == 0) {
		deck->head = new_node;
		deck->size++;
		return;
	}

	node_t *node = deck->head;
	while (node->next != NULL) {
		node = node->next;
	}
	node_t *next_node = node->next;
	node->next = new_node;
	if (next_node != NULL) {
		next_node->prev = new_node;
	}
	new_node->next = next_node;
	new_node->prev = node;
	deck->size++;
}

int add_deck_to_list(const void *deck, ll_t *list) {
	node_t *new_node = malloc(sizeof(node_t));
	new_node->data = malloc(list->data_size);
	memcpy(new_node->data, deck, list->data_size);
	new_node->next = NULL;
	new_node->prev = NULL;

	if (list->size == 0) {
		list->head = new_node;
		list->size++;
		return 1;
	}

	node_t *node = list->head;
	while (node->next != NULL) {
		node = node->next;
	}

	node_t *next_node = node->next;
	node->next = new_node;

	if (next_node != NULL) {
		next_node->prev = new_node;
	}

	new_node->next = next_node;
	new_node->prev = node;
	list->size++;
	return 1;
	
}

int check_valid_card(card_t *card) {
	char sym[4][MAX_SYMBOL_SIZE] = {"HEART", "CLUB", "DIAMOND", "SPADE"};
	if (card->value < 1 && card->value > 14) {
		return 0;
	}
	int valid = 0;
	for (int i = 0; i < 4; i++) {
		if (strcmp(card->symbol, sym[i]) == 0) {
			valid = 1;
		}
	}
	if (valid == 0) {
		return 0;
	}
	return 1;
}

int main(void) {
	ll_t *my_list = list_create(sizeof(ll_t *));
	char command[STRING_SIZE];
	int num_cards, num, check = 0;
	while (1) {
		scanf("%s", command);
		if (strcmp(command, "ADD_DECK") == 0) {
			scanf("%d", &num_cards);
			ll_t *deck = list_create(sizeof(card_t));
			num = 0;
			card_t deck_card;
			while (num != num_cards) {
				scanf("%d %s", &deck_card.value, deck_card.symbol);
				if (check_valid_card(&deck_card) == 0) {
					printf(INVALID_CARD);
					continue;
				}
				add_card(deck, &deck_card);
				num++; 
			}
			check = add_deck_to_list(&deck, my_list);
			if (check == 1) {
				printf(ADDED_DECK, num_cards);
			}

		} else if (strcmp(command, "DEL_DECK") == 0) {
			//TO DO
		} else if (strcmp(command, "DEL_CARD") == 0) {
			//TO DO
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			//TO DO
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			//TO DO
		} else if (strcmp(command, "DECK_LEN") == 0) {
			//TO DO
		} else if (strcmp(command,  "SHUFFLE_DECK") == 0) {
			//TO DO
		} else if (strcmp(command, "MERGE_DECKS") == 0) {
			//TO DO
		} else if (strcmp(command, "SPLIT_DECKS") == 0) {
			//TO DO
		} else if (strcmp(command, "REVERSE_DECK") == 0) {
			//TO DO
		} else if (strcmp(command, "SHOW_DECK") == 0) {
			//TO DO
		} else if (strcmp(command, "SHOW_ALL") == 0) {
			//TO DO
		} else if (strcmp(command, "EXIT") == 0) {
			free_list(&my_list);
			//sa nu uiti sa dai free si la pachete 
			break;
		} else {
			printf(INVALID_COMMAND);
		}
	}
	return 0;
}
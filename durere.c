#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 256
#define MAX_SYMBOL_SIZE 8
#define NUM_SYMBOLS 4
#define DECK_INDEX_OUT_OF_BOUNDS "The provided index is out of bounds \
												for the deck list.\n"
#define CARD_INDEX_OUT_OF_BOUNDS "The provided index is out of bounds \
												for deck %ld.\n"
#define INVALID_CARD "The provided card is not a valid one.\n"
#define INVALID_COMMAND "Invalid command. Please try again.\n"
#define ADDED_DECK "The deck was successfully created with %d cards.\n"
#define DELETED_DECK "The deck %d was successfully deleted.\n"
#define DELETED_CARD "The card was successfully deleted from deck %d.\n"
#define ADD_CARDS "The cards were successfully added to deck %d.\n"
#define DECK_NUMBER "The number of decks is %d.\n"													
#define DECK_LEN "The length of deck %d is %d.\n"
#define SHUFFLE_DECK "The deck %d was successfully shuffled.\n"													
#define MERGE_DECKS "The deck %d and the deck %d were successfully merged.\n"
#define SPLIT_DECK "The deck %d was successfully split by index %d.\n"
#define REVERSE_DECK "The deck %d was successfully reversed.\n"
#define SORT_DECK "The deck %d was successfully sorted.\n"

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
	char sym[NUM_SYMBOLS][MAX_SYMBOL_SIZE] = {"HEART", "CLUB", "DIAMOND", "SPADE"};
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

void delete_deck(ll_t *list, int index) {
	node_t *node = list->head;
	if (index < 0) {
		printf(DECK_INDEX_OUT_OF_BOUNDS);
		return;
	}
	while (node->next != NULL && --index > 0) {
		node = node->next;
	}
	node_t *prev = node->prev;
	node_t *next = node->next;
	prev->next = next;
	next->prev = prev;
	if (node == list->head) {
		list->head = next;
	}
	list->size--;
	printf(DELETED_DECK, index);
}

void delete_card(ll_t *list, ll_t *deck, int d_index, int c_index) {
	node_t *node = deck->head;
	if (c_index < 0) {
		printf(CARD_INDEX_OUT_OF_BOUNDS);
		return;
	}
	while (node->next != NULL && --c_index > 0) {
		node = node->next;
	}
	node_t *prev = node->prev;
	node_t *next = node->next;
	prev->next = next;
	next->prev = prev;
	if (node == deck->head) {
		deck->head = next;
	}
	deck->size--;
	printf(DELETED_CARD, d_index);
	if (deck->size == 0) {
		delete_deck(list, d_index);
	}
}

void add_cards(ll_t *list, int index, int num) {
	node_t *current_deck = list->head;

	while (current_deck->next != NULL && --index > 0) {
		current_deck = current_deck->next;
	}

	int nr = 0;
	card_t new_card;
	while (nr != num) {
		scanf("%d %s", new_card.value, new_card.symbol);
		int ok = check_valid_card(&new_card);
		if (ok == 0) {
			printf(INVALID_CARD);
			return;
		}
		add_card(current_deck, new_card);
		nr++;
	}
	printf(ADD_CARDS, index);

}

void get_deck_number(ll_t *list) {
	int num = list->size;
	printf(DECK_NUMBER, num);
}

void get_deck_len(ll_t *list, int deck_index) {
	node_t *current_deck = list->head;

	while (current_deck->next != NULL && --deck_index > 0) {
		current_deck = current_deck->next;
	}

	ll_t *deck;
	deck = (ll_t*)current_deck->data;
	int length = deck->size;
	printf(DECK_LEN, deck_index);

}

void shuffle_deck(ll_t *list, int deck_index) {
	/*
	-inverseaza prima si a doua jumatate a pachetului <index_pachet>
	-prima jumatate contine primele n/2 carti, iar a doua jumatate
	contine n/2 carti (n par) sau n/2 + 1 carti(n impar), unde n este
	nr de carti din pachet
	-dupa finalizarea comenzii se va afisa msj ...
	ex:
	pachet 0: 1, 2, 3, 4, 5
	rezultat: 3, 4, 5, 1, 2
	*/
}

void merge_decks(ll_t *list, int d_index1, int d_index2) {
	/*
	-combina pachetele index1 si index2 luand cate o carte din fiecare
	pachet rand pe rand
	-cele doua pachete combinate vor fi sterse, iar pachetul rezultat
	va fi adaugat la finalul listei de pachete
	- + msj de la final
	ex:
	pachet 0: 1, 2, 3, 4
	pachet 1: 4, 5, 6, 7, 11, 12, 13
	rezultat: 1, 4, 2, 5, 3, 6, 4, 7, 11, 12, 13
	*/
}

void split_deck(ll_t *list, int d_index, int split_index) {
	/* 
	- imparte pachetul d_index dupa indexul split_index
	- primul pachet rezultat va ramane la d_index, iar al
	doilea pachet rezultat se va insera la pozitia d_index + 1
	- daca in urma comenzii rezulta un pachet gol si un pachet
	ce contine toate cartile (split_index == 0), se va pastra doar
	pachetul ce contine carti

	ex: 
	pachet 0: 1, 2, 3, 4
	pachet 1: 7, 8, 9
	pachet 2: 12, 13, 14
	SPLIT_DECK 0 2
	Rezultate:
		Pachet 1a: 1, 2
		Pachet 1b: 3, 4
		Pachet 2: 7, 8, 9
		Pachet 3: 12, 13, 14
	*/
}

void reverse_deck(ll_t *list, int deck_index) {
	/*
	- inverseaza ordinea cartilor din pachetul index

	*/
}

void show_deck(ll_t *list, int deck_index) {
	/*
	-afiseaza cartile din pachetul deck_index
	- structura: <index_pachet> - {valoare1, simbol1}, {val2, sim2}, ..
	-mesajul afisat pe ecran va fi de forma:
	Deck <index_pachet> :\n
	\t<valoare_carte1> <simbol_carte1>\n
	\t<valoare_carte2> <simbol_carte2>\n
	.....
	*/
}

void show_all(ll_t *list) {
	/*
	mesajul va fi de forma:
	Deck <index_pachet1>:\n
	\t<valoare_carte1> <simbol_carte1>\n
	.....
	Deck <index_pachet2>:\n
	\t<val_carte1> <sim_carte1>\n
	....
	*/
}

int main(void) {
	ll_t *my_list = list_create(sizeof(ll_t *));
	ll_t *deck;
	char command[STRING_SIZE];
	int num_cards, num, check = 0, deck_index, card_index;
	while (1) {
		scanf("%s", command);
		if (strcmp(command, "ADD_DECK") == 0) {
			scanf("%d", &num_cards);
			deck = list_create(sizeof(card_t));
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
			scanf("%d", &deck_index);
			delete_deck(my_list, deck_index);
		} else if (strcmp(command, "DEL_CARD") == 0) {
			scanf("%d %d", &deck_index, &card_index);
			delete_card(my_list, &deck, deck_index, card_index);
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			scanf("%d %d", &deck_index, &num_cards);
			add_cards(my_list, deck_index, num_cards);
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			get_deck_number(my_list);
		} else if (strcmp(command, "DECK_LEN") == 0) {
			scanf("%d", &deck_index);
			get_deck_len(my_list, deck_index);
		} else if (strcmp(command,  "SHUFFLE_DECK") == 0) {
			scanf("")
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
			//free_list(&deck); 
			break;
		} else {
			printf(INVALID_COMMAND);
		}
	}
	return 0;
}
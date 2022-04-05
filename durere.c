// Copyright 2022 Dobrica Nicoleta Adriana
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 256
#define MAX_SYMBOL_SIZE 8
#define NUM_SYMBOLS 4
#define INVALID_CARD "The provided card is not a valid one.\n"
#define INVALID_COMMAND "Invalid command. Please try again.\n"

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
		free(aux->data);
		free(aux);
		aux = next;
	}
	free(*list);
	*list = NULL;
}
node_t* get_nth_node(ll_t *list, int n);

void free_main_list(ll_t **list) {
	node_t *current = (*list)->head;
	ll_t *current_list;
	while (current) {
		current_list = *(ll_t **)current->data;
		free_list(&current_list);
		current = current->next;
	}
	free_list(list);
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
	node->next = new_node;
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

	node->next = new_node;
	new_node->prev = node;
	list->size++;
	return 1;
}

int check_valid_card(card_t *card) {
	char sym[NUM_SYMBOLS][MAX_SYMBOL_SIZE] = {"HEART", "CLUB", "DIAMOND",
												"SPADE"};
	if (card->value < 1 || card->value > 14) {
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

int delete_deck(ll_t *list, int index) {
	node_t *node = list->head;
	if (index < 0 || index >= list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return -1;
	}
	/*
	if (node == list->head) {
		list->head = list->head->next;
		list->size--;
		printf(DELETED_DECK, index);
		return;
	} */
	int ind = index;
	while (node->next != NULL && ind-- > 0) {
		node = node->next;
	}
	node_t *deleted_node = get_nth_node(list, index);
	ll_t *deleted_deck = *(ll_t **)deleted_node->data;
	if (node == list->head) {
			list->head = list->head->next;
			list->size--;
			free_list(&deleted_deck);
			free(node->data);
			free(node);
			return 1;
	}
	node_t *prev = node->prev;
	node_t *next = node->next;
	prev->next = next;
	if (next != NULL) {
			next->prev = prev;
	}
	list->size--;
	free_list(&deleted_deck);
	free(node->data);
	free(node);
	return 1;
}

void delete_card(ll_t *list, int d_index, int c_index) {
	if (d_index >= list->size || d_index < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	node_t *d = get_nth_node(list, d_index);
	ll_t *deck = *(ll_t **)d->data;
	node_t *node = deck->head;
	if (deck->size == 1 && c_index == deck->size) {
		printf("The provided index is out of bounds for deck %d.\n", d_index);
		return;
	}
	if (c_index < 0 || c_index >= deck->size) {
		printf("The provided index is out of bounds for deck %d.\n", d_index);
		return;
	}
	while (node->next != NULL && c_index-- > 0) {
		node = node->next;
	}
	if (node == deck->head) {
			deck->head = node->next;
			deck->size--;
			free(node->data);
			free(node);
			printf("The card was successfully deleted from deck %d.\n",
															d_index);
			if (deck->size == 0) {
				delete_deck(list, d_index);
			}
			return;
	}

	node_t *prev = node->prev;
	node_t *next = node->next;
	prev->next = next;
	if (next != NULL) {
			next->prev = prev;
	}
	deck->size--;
	free(node->data);
	free(node);
	printf("The card was successfully deleted from deck %d.\n", d_index);

	if (deck->size == 0) {
		delete_deck(list, d_index);
	}
}

void add_cards(ll_t *list, int index, int num) {
	node_t *current_deck = list->head;
	int ind = index;
	if (index < 0 || index >= list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	while (current_deck->next != NULL && ind-- > 0) {
		current_deck = current_deck->next;
	}

	int nr = 0;
	char card[100], *v, *sym;
	card_t new_card;
	while (nr != num) {
		/*
		scanf("%d %s", &new_card.value, new_card.symbol);
		int ok = check_valid_card(&new_card);
		if (ok == 0) {
			printf(INVALID_CARD);
			fgets(garbage, 99, stdin);
			continue;
		}
		add_card(*(ll_t **)current_deck->data, &new_card);
		nr++;
		*/
		fgets(card, STRING_SIZE, stdin);
		v = strtok(card, " ");
		sym = strtok(NULL, "\n");
		int len = strlen(v);
		if (len <= 3) {
			int card_val = atoi(v);
			new_card.value = card_val;
			strcpy(new_card.symbol, sym);
			int ok = check_valid_card(&new_card);
			if (ok == 0) {
				printf(INVALID_CARD);
				continue;
			}
			add_card(*(ll_t **)current_deck->data, &new_card);
			nr++;
		}
	}
	printf("The cards were successfully added to deck %d.\n", index);
}

void get_deck_number(ll_t *list) {
	int num = list->size;
	printf("The number of decks is %d.\n", num);
}

node_t* get_nth_node(ll_t *list, int n) {
	node_t *curr = list->head;
	while (curr != NULL && n-- > 0) {
		curr = curr->next;
	}
	return curr;
}

void get_deck_len(ll_t *list, int deck_index) {
	if (deck_index < 0 || deck_index >= list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	node_t *current_deck = get_nth_node(list, deck_index);
	int index = deck_index;
	/*while (current_deck->next != NULL && index > 0) {
		current_deck = current_deck->next;
		--index;
	}
*/
	ll_t *deck;
	deck = *(ll_t **)current_deck->data;
	int length = deck->size;
	printf("The length of deck %d is %d.\n", deck_index, length);
}


void shuffle_deck(ll_t *list, int deck_index) {
	if (deck_index >= list->size || deck_index < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	node_t *d = get_nth_node(list, deck_index);
	ll_t *deck = *(ll_t **)d->data;
	int	d_size = deck->size / 2;
	if (deck->size == 1) {
			printf("The deck %d was successfully shuffled.\n", deck_index);
			return;
	}
	node_t *head = deck->head;
	node_t *tmp = get_nth_node(deck, d_size);
	node_t *tail = deck->head;
	while (tail->next != NULL) {
			tail = tail->next;
	}
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	head->prev = tail;
	tail->next = head;
	deck->head = tmp;
	printf("The deck %d was successfully shuffled.\n", deck_index);
}

void add_nth_node(ll_t *list, int n, const void *card) {
	node_t *prev, *curr, *new_node;
	curr = list->head;
	prev = NULL;
	while (n > 0) {
		prev = curr;
		curr = curr->next;
		--n;
	}
	new_node = malloc(sizeof(node_t));
	new_node->data = malloc(sizeof(card_t));
	memcpy(new_node->data, card, sizeof(card_t));

	new_node->next = curr;
	if (prev == NULL) {
        new_node->next = list->head;
        new_node->prev = NULL;
        list->head = new_node;
	} else {
        new_node->next = curr;
        new_node->prev = prev;
        if (curr != NULL)
            curr->prev = new_node;
		prev->next = new_node;
	}
	list->size++;
}

void merge_decks(ll_t *list, int d_index1, int d_index2) {
	if (d_index1 < 0 || d_index1 >= list->size || d_index2 < 0 ||
										d_index2 >= list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	node_t *d1 = get_nth_node(list, d_index1);
	node_t *d2 = get_nth_node(list, d_index2);
	ll_t *deck1 = *(ll_t **)d1->data;
	ll_t *deck2 = *(ll_t **)d2->data;

	ll_t *merged_deck = list_create(sizeof(card_t));

	node_t *curr1 = deck1->head, *curr2 = deck2->head;
	int current_index1 = 0, current_index2 = 0, m_index = 0;
	node_t *c1, *c2;
	card_t *card1, *card2;
	while (curr1 != NULL && curr2 != NULL) {
		if (curr1 != NULL) {
				c1 = get_nth_node(deck1, current_index1++);
				card1 = (card_t *)c1->data;
				add_card(merged_deck, card1);
				curr1 = curr1->next;
		}
		if (curr2 != NULL) {
				c2 = get_nth_node(deck2, current_index2++);
				card2 = (card_t *)c2->data;
				add_card(merged_deck, card2);
				curr2 = curr2->next;
		}
	}

	while (curr1 != NULL) {
			c1 = get_nth_node(deck1, current_index1++);
			card1 = (card_t *)c1->data;
			add_card(merged_deck, card1);
			curr1 = curr1->next;
	}

	while (curr2 != NULL) {
			c2 = get_nth_node(deck2, current_index2++);
			card2 = (card_t *)c2->data;
			add_card(merged_deck, card2);
			curr2 = curr2->next;
	}

	if (d_index1 > d_index2) {
		delete_deck(list, d_index1);
		delete_deck(list, d_index2);
	} else {
		delete_deck(list, d_index2);
		delete_deck(list, d_index1);
	}
	add_deck_to_list(&merged_deck, list);
	printf("The deck %d and the deck %d were successfully merged.\n",
												d_index1, d_index2);
}


void remove_nth_node(ll_t **list, int n) {
	node_t *node = (*list)->head;
	while (node->next && n-- > 0) {
		node = node->next;
	}

	node_t *prev = node->prev;
	node_t *next = node->next;

	if (prev != NULL) {
		prev->next = next;
	}
	if (next != NULL) {
		next->prev = prev;
	}

	if (node == (*list)->head) {
		(*list)->head = next;
	}
	(*list)->size--;
	free(node->data);
	free(node);
}

void add_nth_deck(ll_t *list, int n, const void *deck) {
	node_t *prev, *curr, *new_node;
	curr = list->head;
	prev = NULL;
	while (n > 0) {
		prev = curr;
		curr = curr->next;
		--n;
	}
	new_node = malloc(sizeof(node_t));
	new_node->data = malloc(sizeof(ll_t));
	memcpy(new_node->data, deck, sizeof(ll_t));

	new_node->next = curr;
	if (prev == NULL) {
			list->head = new_node;
	} else {
			prev->next = new_node;
	}
	list->size++;
}
void split_deck(ll_t *list, int d_index, int split_index) {
	if (d_index >= list->size || d_index < 0) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}

	if (split_index == 0) {
		printf("The deck %d was successfully split by index %d.\n",
											d_index, split_index);
		return;
	}

	node_t *d = get_nth_node(list, d_index);
	ll_t *deck = *(ll_t **)d->data;

	if (split_index < 0 || split_index >= deck->size) {
		printf("The provided index is out of bounds for deck %d.\n", d_index);
		return;
	}

	ll_t *new_list = list_create(sizeof(card_t));
	node_t *curr = deck->head;
	int ind = split_index;
	while (curr && ind-- > 0) {
		curr = curr->next;
    }
	ind = split_index;
	while (ind != deck->size) {
		node_t *split_node = get_nth_node(deck, ind);
		card_t *split_card = (card_t *)split_node->data;
		add_card(new_list, split_card);
		ind++;
	}
	int pos = split_index;
	while (split_index != deck->size) {
			remove_nth_node(&deck, deck->size);
	}
	add_nth_node(list, d_index + 1, &new_list);
	printf("The deck %d was successfully split by index %d.\n",
										d_index, split_index);
}

void reverse_deck(ll_t *list, int deck_index) {
	if (deck_index < 0 || deck_index >= list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	node_t *d = get_nth_node(list, deck_index);
	ll_t *deck = *(ll_t **)d->data;

	node_t *tmp = NULL;
	node_t *curr = deck->head;

    while (curr != NULL) {
        curr->prev = curr->next;
        curr->next = tmp;
        tmp = curr;
        curr = curr->prev;
    }

    deck->head = tmp;

	printf("The deck %d was successfully reversed.\n", deck_index);
}

void show_deck(ll_t *deck, int deck_index) {
	printf("Deck %d:\n", deck_index);

	node_t *curr = deck->head;
	while (curr) {
		card_t card = *(card_t *)curr->data;
		printf("\t%d %s\n", card.value, card.symbol);
		curr = curr->next;
	}
}

void show_all(ll_t *list) {
	node_t *curr = list->head;
	ll_t *deck;
	int index = 0;
	while (curr) {
		deck = *(ll_t **)curr->data;
		show_deck(deck, index);
		curr = curr->next;
		index++;
	}
}

void sort_deck(ll_t *list, int deck_index) {
	if (deck_index < 0 || deck_index >= list->size) {
		printf("The provided index is out of bounds for the deck list.\n");
		return;
	}
	node_t *d = get_nth_node(list, deck_index);
	ll_t *deck = *(ll_t **)d->data;
	node_t *curr = NULL, *next_c = NULL;
	void *temp;
	for (curr = deck->head; curr->next != NULL; curr = curr->next) {
		for (next_c = curr->next; next_c != NULL; next_c = next_c->next) {
			card_t *card1, *card2;
			card1 = (card_t *)curr->data;
			card2 = (card_t *)next_c->data;
			if (card1->value > card2->value) {
				temp = curr->data;
				curr->data = next_c->data;
				next_c->data = temp;
			} else if (card1->value == card2->value) {
				if (strcmp(card1->symbol, "HEART") != 0 &&
					strcmp(card2->symbol, "HEART") == 0) {
						temp = curr->data;
						curr->data = next_c->data;
						next_c->data = temp;
				} else if (strcmp(card1->symbol, "HEART") != 0 &&
							strcmp(card2->symbol, "SPADE") == 0) {
						temp = curr->data;
						curr->data = next_c->data;
						next_c->data = temp;
				} else if (strcmp(card1->symbol, "HEART") != 0 &&
							strcmp(card2->symbol, "DIAMOND") == 0 &&
							strcmp(card1->symbol, "SPADE") != 0) {
						temp = curr->data;
						curr->data = next_c->data;
						next_c->data = temp;
				} else if (strcmp(card1->symbol, "HEART") != 0 &&
							strcmp(card2->symbol, "CLUB") == 0 &&
							strcmp(card1->symbol, "SPADE") != 0 &&
							strcmp(card1->symbol, "DIAMOND") != 0) {
						temp = curr->data;
						curr->data = next_c->data;
						next_c->data = temp;
				}
			}
		}
	}
	printf("The deck %d was successfully sorted.\n", deck_index);
}

int main(void) {
	ll_t *my_list = list_create(sizeof(ll_t *));
	ll_t *deck;
	char command[STRING_SIZE], garbage[100];
	int num_cards, num, check = 0, deck_index, card_index, i1, i2, len;
	while (1) {
		scanf("%s", command);
		if (strcmp(command, "ADD_DECK") == 0) {
			scanf("%d", &num_cards);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
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
					printf("The deck was successfully created with %d cards.\n",
																num_cards);
				}
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "DEL_DECK") == 0) {
			scanf("%d", &deck_index);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				check = delete_deck(my_list, deck_index);
				if (check == 1) {
					printf("The deck %d was successfully deleted.\n", deck_index);
				}
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "DEL_CARD") == 0) {
			scanf("%d %d", &deck_index, &card_index);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				delete_card(my_list, deck_index, card_index);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "ADD_CARDS") == 0) {
			scanf("%d %d", &deck_index, &num_cards);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				add_cards(my_list, deck_index, num_cards);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "DECK_NUMBER") == 0) {
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				get_deck_number(my_list);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "DECK_LEN") == 0) {
			scanf("%d", &deck_index);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				get_deck_len(my_list, deck_index);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command,  "SHUFFLE_DECK") == 0) {
			scanf("%d", &deck_index);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				shuffle_deck(my_list, deck_index);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "MERGE_DECKS") == 0) {
			scanf("%d %d", &i1, &i2);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				merge_decks(my_list, i1, i2);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "SPLIT_DECK") == 0) {
			scanf("%d %d", &i1, &i2);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				split_deck(my_list, i1, i2);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "REVERSE_DECK") == 0) {
			scanf("%d", &deck_index);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				reverse_deck(my_list, deck_index);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "SHOW_DECK") == 0) {
			scanf("%d", &deck_index);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				if (deck_index < 0 || deck_index >= my_list->size) {
					printf("The provided index is out of bounds for the deck list.\n");
				} else {
	        		node_t *d = get_nth_node(my_list, deck_index);
					ll_t *s_deck = *(ll_t **)d->data;
					show_deck(s_deck, deck_index);
				}
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "SHOW_ALL") == 0) {
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				show_all(my_list);
			} else {
				printf(INVALID_COMMAND);
			}
		} else if (strcmp(command, "EXIT") == 0) {
			free_main_list(&my_list);
			break;
		} else if (strcmp(command, "SORT_DECK") == 0) {
			scanf("%d", &deck_index);
			fgets(garbage, 99, stdin);
			len = strlen(garbage);
			if (len == 1) {
				sort_deck(my_list, deck_index);
			} else {
				printf(INVALID_COMMAND);
			}
		} else {
			printf(INVALID_COMMAND);
			fgets(garbage, 99, stdin);
		}
	}
	return 0;
}

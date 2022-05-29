**Dobrica Nicoleta Adriana:**
**311CA**

## Now You See Me 

### Description:

* This homework is about a list of decks that can be modified using different functions, this being done with generic doubly linked lists. The user can add new decks, delete them, or alter them (shuffle, reverse, sort etc).
* For the actual implementation, I used three structures: one for the linked list's nodes, one for the actual linked list and one for the cards that are about to be added to a deck (a card has a value and a symbol).
* If the input is incorrect, an error message will pop up according to the error type: if an index is invalid, if a given card doesn't respect the format (value ranges from 1 to 14 and the symbol can either be "HEART", "SPADE", "DIAMOND" or "CLUB") or if a given command is not valid.

### ADD_DECK
* When the user calls this command, a new deck of cards is added to the main list of decks, with the specified maximum size of cards that are about to be added. Each time this function is called, a new deck is created and added last in the list of decks. 
* After the command is given, the user also adds the desired cards. Before these cards are added to the deck, they have to be checked whether they are valid or not.

### DEL_DECK
* When the user writes this command, the function deletes the deck with the given index from the list of decks. After the deck is deleted, all the memory will be freed.

### DEL_CARD
* This command deletes a certain card from a deck. The user chooses which card to delete and from which deck. After the card is deleted, it will be freed from memory.

### ADD_CARDS
* This commands adds new cards to a certain deck. After specifying the amount of cards to be added and which deck will have these cards, the user will also be prompted to write the actual cards. These will be added if they are valid.

### DECK_NUMBER
* This command prints the number of decks from the list of decks.

### DECK_LEN
* This command prints the number of cards from a desired deck. This is being done by traversing the list of decks, stopping when the given deck is found, then printing the size of the deck.

### SHUFFLE_DECK
* This commands shuffles a certain deck. This function reverses the first and second half of the deck. This is being done by finding the middle of the list, and so the middle node will become the new head, and the previous node will become the last node in the list. Instead of reversing the nodes, manipulating the pointers of the list was easier and faster.

### MERGE_DECKS
* This command merges two given decks. Firstly, a new deck will be created that will contain the cards from the two decks that are about to be merged. The new merged deck will have a card from one deck, a card from the other, and so on.
* After the new merged deck is created and has all the cards from the other two decks, the two decks will be removed and freed from memory, and the new deck is added to the list of decks.

### SPLIT_DECK
* This command splits a certain deck by a given index. Firstly, a new deck is created. After traversing through the soon-to-be-split deck, we find the first node that has to be added to the new deck. After adding the cards to the new list, they are removed from the main deck.
* The new deck is added in the list of decks, on the position after the main deck.

### REVERSE_DECK
* This command reverses a given deck. This is done by swapping the pointers for all nodes and changing the head of the deck in the end. 

### SHOW_DECK
* If the user writes this commmand, along with the desired deck index, it prints the contents of the deck.

### SHOW_ALL
* If the user writes this command, it prints all of the decks in the list, alongside their contents. 

### EXIT
* This command stops the program. If this is the given command, all of the lists will be freed from memory. 

### (BONUS) SORT_DECK
* If this is the given command, with a certain deck index, this function sorts the desired deck, in increasing order. But since a card has a symbol and a value, the sorting is first being done by its value, but if two cards have the same corresponding value, then their symbol (HEART, SPADE, DIAMOND, CLUB) will be the main factor for the sorting.
* The symbols have an order of priority: first is "HEART", then "SPADE", "DIAMOND", and lastly, "CLUB".
* The actual implementation for the sorting of the deck is a simple bubble sort, but adapted to a generic doubly linked list.

### Extra info:

* I think I could have done a better implementation of this homework; Mainly, I think I could have written lesser code and written better (and generic) functions for certain linked list manipulations (adding a node, removing one etc).
* This homework helped me have a better understanding of linked lists, and how useful a generic list can be. 

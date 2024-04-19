#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK_SIZE 52
#define SUITS 4
#define CARDS_SUIT 13

enum Cardsuit {
    Hearts,
    Diamonds,
    Clubs,
    Spades
};
struct Card {
    enum Cardsuit suit;
    char rank;
};
struct Deck {
    struct Card cards[DECK_SIZE];
    int id;
};
struct DDeck {
    int size;
    int id;
    struct Card *cards; 
};

int getval (char card) {
    int value;
    switch (card) {
        case 'T': value = 10;
                 break;
         case 'J': value = 11;
                 break;
        case 'Q': value = 12;
                 break;
        case 'K': value = 13;
                 break;
        case 'A': value = 14;
                 break;
        default: value = card - '0';
    }

    return value;
	
}
struct DDeck *modify_ddeck (struct DDeck *deck, int size, int remove) {
	
    struct DDeck *modifieddeck = malloc(sizeof (struct DDeck));;
    size = size - remove;
    modifieddeck->cards = (struct Card*)malloc(size * sizeof(struct Card));
    modifieddeck->size = size;
    for (int i = 0; i < size; i++) {
        modifieddeck->cards[i].rank = deck->cards[i].rank;
        modifieddeck->cards[i].suit = deck->cards[i].suit;
    }
	
    return modifieddeck;
	
}
struct DDeck *initialize_ddeck (int size) {
	
    struct DDeck *deck = malloc(sizeof (struct DDeck));
    deck->cards = (struct Card*)malloc(size * sizeof(struct Card));
    int count = 0;
    deck->id = 2;
    deck->size = size;
    for (int i = 0; i < SUITS; i++) {
        for (int j = 1; j <= CARDS_SUIT; j++) {
            struct Card card;
            if (j <= 9 && j != 1) {
                card.rank = j + '0';
            } else {
                switch (j) {
                    case 1: card.rank = 'A';
                            break;
                    case 10: card.rank = 'T';
                            break;
                    case 11: card.rank = 'J';
                            break;
                    case 12: card.rank = 'Q'; 
                            break;
                    case 13: card.rank = 'K';
                            break;
                     default: break;
                }
            }
            switch (i) {
                case 0: card.suit = Hearts;
                        break;
                case 1: card.suit = Diamonds;
                        break;
                case 2: card.suit = Clubs; 
                        break;
                case 3: card.suit = Spades;
                        break;
                default: break;
            }
            deck->cards[count].rank = card.rank;
            deck->cards[count].suit = card.suit;
            count++;
        }  
    }
	
    return deck;
	
}

struct Deck *generateDeck () {
	
    struct Deck *deck = malloc(sizeof (struct Deck));
 
    int count = 0;
    deck->id = 1;
    for (int i = 0; i < SUITS; i++) {
        for (int j = 1; j <= CARDS_SUIT; j++) {
            struct Card card;
            if (j <= 9) {
                card.rank = j + '0';
            } else {
                switch (j) {
                    case 10: card.rank = 'T';
                        break;
                    case 11: card.rank = 'J';
                        break;
                    case 12: card.rank = 'Q'; 
                        break;
                    case 13: card.rank = 'K';
                        break;
                     default: break;
                }
            }
            
            switch (i) {
                case 0: card.suit = Hearts;
                        break;
                case 1: card.suit = Diamonds;
                        break;
                case 2: card.suit = Clubs; 
                        break;
                case 3: card.suit = Spades;
                        break;
                default: break;
            }
            deck->cards[count].rank = card.rank;
            deck->cards[count].suit = card.suit;
            count++;
        }
        
    }
	
    return deck;
	
}

int randrange(int min_n, int max_n) {
    return rand() % (max_n - min_n + 1) + min_n;
}

void shuffle (struct Deck *deck){
	
    int random;

    for (int i = 0; i < DECK_SIZE; i++) {
        random = randrange(0,51);
        struct Card tmp = deck->cards[i];
        deck->cards[i] = deck->cards[random];
        deck->cards[random] = tmp;
    }
	
}
void printd (struct Deck *deck){
	
    printf("ID (deck): %d \n", deck->id);
    printf("----------\n");
    for (int i = 0; i < DECK_SIZE; i++){
        printf("[%d]: %c %d \n", i,deck->cards[i].rank, deck->cards[i].suit);
    }
}
void shuffled (struct DDeck *deck){
	
    int random;
    int size = deck->size;

    for (int i = 0; i < size; i++) {
        random = randrange(0,size-1);
        struct Card tmp = deck->cards[i];
        deck->cards[i] = deck->cards[random];
        deck->cards[random] = tmp;
    }
	
}
void printdd (struct DDeck *deck, int size){
	
    printf("ID (deck): %d \n", deck->id);
    printf("----------\n");
	
    for (int i = 0; i < size; i++){
        printf("[%d]: %c %d \n", i,deck->cards[i].rank, deck->cards[i].suit);
    }
	
}


int main () {

    struct Card testcard;
    testcard.rank = '9';
    testcard.suit = Hearts;
    printf("Test Card: %c - %d\n", testcard.rank, testcard.suit);

    
	/*struct Deck *testdeck = generateDeck();

    printf("Address: %p\n", testdeck);
    printf("ID: %d \n", testdeck->id);

    for (int i = 0; i < DECK_SIZE; i++) {
        printf("i: %d, c: %c %i\n", i, testdeck->cards[i].rank, testdeck->cards[i].suit);
    }
    printd(testdeck);
    shuffle(testdeck);
    printd(testdeck);
    free(testdeck); */

    struct DDeck *testddeck = initialize_ddeck(52);
    printf("Test Dynamic:\n");
    printf("----------\n");
    printdd(testddeck, 52);
    printf("Shuffled:\n");
    printf("----------\n");
    shuffled(testddeck);
    printdd(testddeck,testddeck->size);
    printf("Modified:\n");
    printf("----------\n");
    testddeck = modify_ddeck(testddeck,testddeck->size,7);
    printdd(testddeck,testddeck->size);
    printf("Shuffled:\n");
    printf("----------\n");
    shuffled(testddeck);
    printdd(testddeck,testddeck->size);
    printf("Modified:\n");
    printf("----------\n");
    testddeck = modify_ddeck(testddeck,testddeck->size,12);
    printdd(testddeck,testddeck->size);
    free(testddeck);
	
    return 0;
}
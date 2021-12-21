/*
    Samnang San
    Final Project: Seven card stud
    The game is a version of poker. The game begins by asking your name and cash the player has. Once those options are entered, the new hand starts which will display the name of player one and player two with cash amounts.
    Shuffle is started. option will ask players to ante, 1 for yes and 0 for no. if 0 is selected, game will end. Assume no one type in 0, the hand will display. Now it will ask player one if they want to bet and the value.
    Player 2, will be asked if they want to call or fold. This can continue until either player runs out of money.

*/



#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define Clubs 1
#define Diamonds 2
#define Hearts 3
#define Spades 4

#define Ace 14
#define Jack 11
#define Queen 12
#define King 13

#define CardOfDeck 52
#define PlayCard 7




//represent card info
//type: 1 is Clubs, 2 is Diamonds, 3 is Hearts, 4 is Spades
// value: 1 is Ace, 11 is Jack, 12 is Queen, 13 is king
struct card{
    int type;
    int value;
};

typedef struct card card;

//represent deck info
struct deck{
    //save card info of a deck
    card cards[CardOfDeck];
    //save index of cards in a deck
    int index[52];
    //save current top card in deck
    int top;
};

typedef struct deck deck;

//represent player info
struct user{
    char name[100];
    long cash;
    int cardIndex[PlayCard];
};

typedef struct user user;

//represent game info
struct game{
    int hand;
    long pots;
};

typedef struct game game;


void initDeck(deck *aDeck);
void creatPlayer(user *player1, user *player2);
void shuffle(deck *aDeck);
void deals(user *player1, user *player2, deck *aDeck);
void checkWinner(user *player1, user *player2, game *aGame, deck *aDeck);
void sortCards(user *player, deck *aDeck);
int detectRoyalFlush(user *player, deck *aDeck);
int detectStraightFlush(user *player, deck *aDeck);
int detectFourOfAkind(user *player, deck *aDeck);
int detectFullHouse(user *player, deck *aDeck);
int detectFlush(user *player, deck *aDeck);
int detectStraight(user *player, deck *aDeck);
int detectThreeOfKind(user *player, deck *aDeck);
int detectTwoPair(user *player, deck *aDeck);
int detectPair(user *player, deck *aDeck);
int compareHighCard(user *player1, user *player2, deck *aDeck);
int isRoyalFlush(int bestSet[], deck *aDeck);
int isFlush(int bestSet[], deck *aDeck);
int isStraight(int bestSet[], deck *aDeck);
void sort(int bestSet[], deck *aDeck);
int isStraightFlush(int bestSet[], deck *aDeck);
int isFourOfAkind(int bestSet[], deck *aDeck);
int isFullHouse(int bestSet[], deck *aDeck);
int isThreeOfKind(int bestSet[], deck *aDeck);
int isTwoPair(int bestSet[], deck *aDeck);
int isPair(int bestSet[], deck *aDeck);
void printGameState(user *player1, user *player2, game *aGame, deck *aDeck);
void printDeck(deck *aDeck);
void printPlayerInfo(user *player1, user *player2);




int main(){
    user player1, player2;
    game aGame = {.hand = 0, .pots = 0};
    deck aDeck;
    initDeck(&aDeck);
    creatPlayer(&player1, &player2);


    int continuePlay = 1;
    int ante;
    do{

        printf("\n==\n");
        printf("start new hand:...\n");
        printPlayerInfo(&player1, &player2);

        //check cash of user
        if(player1.cash < 5){
            printf("End game ");
            break;
        }

        if(player2.cash < 5){
            printf("End game ");
            break;
        }

        //new hand
        aGame.hand++;
        aGame.pots = 0;
        shuffle(&aDeck);

        do{
            printf("Player1 turn: do you want to ante $5 into the pot to play?(typing 1/0)");
            scanf("%d", &ante);
        }
        while(ante != 1 && ante != 0);

        if(ante == 0){
            printf("end game!");
            break;
        }

        do{
            printf("Player2 turn: do you want to ante $5 into the pot to play?(typing 1/0)");
            scanf("%d", &ante);
        }
        while(ante != 1 && ante != 0);

        if(ante == 0){
            printf("end game!");
            break;
        }



        //ante
        player1.cash = player1.cash - 5;
        player2.cash = player2.cash - 5;
        aGame.pots = 10;

        //deals each player 7 cards
        deals(&player1, &player2, &aDeck);

        printGameState(&player1, &player2, &aGame, &aDeck);
        int isBet;
        long betValue;
        int isCall;

        //if hand is odd then asking player1 before player2
        if(aGame.hand % 2 == 1){
            do{
                printf("Player1 turn: do you want to bet?(typing 1/0)");
                scanf("%d", &isBet);
            }
            while(isBet != 1 && isBet != 0);

            if(isBet == 0){
                printGameState(&player1, &player2, &aGame, &aDeck);
                checkWinner(&player1, &player2, &aGame, &aDeck);
                continue;
            }

            while(1){
                printf("Player1 turn: bet value? ");
                scanf("%ld", &betValue);

                if(betValue < 0 || betValue > player1.cash || betValue > player2.cash){
                    printf("\ninvalid value\n");
                }else{
                    break;
                }
            }

            //update pot
            player1.cash -= betValue;
            aGame.pots += betValue;

            do{
                printf("Player2 turn: call or fold?(typing 1/0)");
                scanf("%d", &isCall);
            }
            while(isCall != 1 && isCall != 0);

            if(isCall == 1){
                //update pot
                player2.cash -= betValue;
                aGame.pots += betValue;
                printGameState(&player1, &player2, &aGame, &aDeck);
                checkWinner(&player1, &player2, &aGame, &aDeck);
            }else{
                player1.cash += aGame.pots;
                aGame.pots = 0;
                printf("player1 win");
            }


        }else {
            //asking player2 before player1

            do{
                printf("Player2 turn: do you want to bet?(typing 1/0)");
                scanf("%d", &isBet);
            }
            while(isBet != 1 && isBet != 0);

            if(isBet == 0){
                printGameState(&player1, &player2, &aGame, &aDeck);
                 checkWinner(&player1, &player2, &aGame, &aDeck);
                 continue;
            }

            while(1){
                printf("Player2 turn: bet value? ");
                scanf("%ld", &betValue);

                if(betValue < 0 || betValue > player1.cash || betValue > player2.cash){
                    printf("\ninvalid value\n");
                }else{
                    break;
                }
            }

            //update pot
            player2.cash -= betValue;
            aGame.pots += betValue;


            do{
                fflush(stdin);
                printf("Player1 turn: call or fold?(typing 1/0)");
                scanf("%d", &isCall);
            }
            while(isCall != 1 && isCall != 0);

            if(isCall == 1){
                player1.cash -= betValue;
                aGame.pots += betValue;
                printGameState(&player1, &player2, &aGame, &aDeck);
                checkWinner(&player1, &player2, &aGame, &aDeck);
            }else{
                player2.cash += aGame.pots;
                aGame.pots = 0;
                printf("player2 win");
            }

        }


    }while(continuePlay);
    return 0;
}


void initDeck(deck *aDeck){
    int i = 0;
    //init Clubs
    for(i = 0; i < (CardOfDeck/4) ; i++){
        aDeck->cards[i].value = i + 2;
        aDeck->cards[i].type = Clubs;
    }
    //init Diamonds
    for(i = CardOfDeck/4; i < (CardOfDeck/2) ; i++){
        aDeck->cards[i].value = i - CardOfDeck/4 + 2;
        aDeck->cards[i].type = Diamonds;
    }

    //init Hearts
    for(i = CardOfDeck/2; i < (3*CardOfDeck/4) ; i++){
        aDeck->cards[i].value = i + 2 -  CardOfDeck/2;
        aDeck->cards[i].type = Hearts;
    }

    //init Spades
    for(i = 3*CardOfDeck/4; i < CardOfDeck ; i++){
        aDeck->cards[i].value = i + 2 -  3*CardOfDeck/4;
        aDeck->cards[i].type = Spades;
    }
}

void creatPlayer(user *player1, user *player2){
    printf("Enter player1 info: \n");
    printf("Enter name: ");
    char trash;
    fgets( player1->name, sizeof(player1->name), stdin);
    do
    {
        printf("Enter cash: ");
        scanf("%ld", &(player1->cash));
        //fflush(stdin);
    } while (player1->cash < 0);

    printf("Enter player2 info: \n");
    printf("Enter name: ");
    scanf("%c", &trash);
    fgets( player2->name, sizeof(player2->name), stdin);

    do
    {
        printf("Enter cash: ");
        scanf("%ld", &(player2->cash));
        fflush(stdin);
    } while (player2->cash < 0);
}


void shuffle(deck *aDeck){
    printf("start shuffle.\n");
    // Use current time as seed for random generator
    srand(time(0));
    //because each player have 7 cards so we just should random 14 first cards in the deck

    int i = 0;
    int j = 0;
    int randValue = 0;
    int ok = 0;
    for(i = 0; i < 14; i++){
        do{
            ok = 1;
            randValue = rand() % CardOfDeck;
            //check exist of randValue in index
            for(j = 0; j < i; j++){
                if(aDeck->index[j] == randValue){
                    ok = 0;
                    break;
                }
            }

        }while(ok == 0);

        aDeck->index[i] = randValue;
    }

    printf("shuffle success.\n");
}
void deals(user *player1, user *player2, deck *aDeck){
    printf("start deals............\n");
    int i = 0;
    int currentCardIndexPlayer1 = 0;
    int currentCardIndexPlayer2 = 0;
    for(i = 0; i < 14; i++){
        if(i % 2 == 0){
            player1->cardIndex[currentCardIndexPlayer1] = aDeck->index[i];
            currentCardIndexPlayer1++;
        }else{
            player2->cardIndex[currentCardIndexPlayer2] = aDeck->index[i];
            currentCardIndexPlayer2++;
        }

    }
    printf("deals success.\n");
}

void sortCards(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int temp;
    for(i = 0; i < 7; i++){
        for(j = i; j < 7; j++){
            if(aDeck->cards[player->cardIndex[i]].value > aDeck->cards[player->cardIndex[j]].value){
                temp = player->cardIndex[i];
                 player->cardIndex[i] =  player->cardIndex[j];
                 player->cardIndex[j] = temp;
            }
        }
    }
}

void checkWinner(user *player1, user *player2, game *aGame, deck *aDeck){
    printf("start check winner.........\n");
    //royalFlush
    if(detectRoyalFlush(player1, aDeck) == 1 && detectRoyalFlush(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by royalFlush");
        return;
    }

    if(detectRoyalFlush(player1, aDeck) == 0 && detectRoyalFlush(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win by royalFlush");
        return;
    }

    if(detectRoyalFlush(player1, aDeck) == 1 && detectRoyalFlush(player2, aDeck) == 1){
        //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win by royalFlush");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win by royalFlush");
            return;
        }
    }


    //straightFlush
    if(detectStraightFlush(player1, aDeck) == 1 && detectStraightFlush(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by straight Flush ");
        return;
    }

    if(detectStraightFlush(player1, aDeck) == 0 && detectStraightFlush(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win  by straight Flush");
        return;
    }

    if(detectStraightFlush(player1, aDeck) == 1 && detectStraightFlush(player2, aDeck) == 1){
        //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win  by straight Flush");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win  by straight Flush");
            return;
        }
    }

    //Four of a kind
    if(detectFourOfAkind(player1, aDeck) == 1 && detectFourOfAkind(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by Four of a kind ");
        return;
    }

    if(detectFourOfAkind(player1, aDeck) == 0 && detectFourOfAkind(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win by Four of a kind ");
        return;
    }

    if(detectFourOfAkind(player1, aDeck) == 1 && detectFourOfAkind(player2, aDeck) == 1){
        //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win by Four of a kind ");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win by Four of a kind ");
            return;
        }
    }

    //Full house
    if(detectFullHouse(player1, aDeck) == 1 && detectFullHouse(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by Full house ");
        return;
    }

    if(detectFullHouse(player1, aDeck) == 0 && detectFullHouse(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win by Full house ");
        return;
    }

    if(detectFullHouse(player1, aDeck) == 1 && detectFullHouse(player2, aDeck) == 1){
        //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win by Full house ");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win by Full house ");
            return;
        }
    }

    //flush
    if(detectFlush(player1, aDeck) == 1 && detectFlush(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by flush");
        return;
    }

    if(detectFlush(player1, aDeck) == 0 && detectFlush(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win by flush");
        return;
    }

    if(detectFlush(player1, aDeck) == 1 && detectFlush(player2, aDeck) == 1){
        //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win by flush");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win by flush");
        }

    }


    //straight
    if(detectStraight(player1, aDeck) == 1 && detectStraight(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by straight");
        return;
    }

    if(detectStraight(player1, aDeck) == 0 && detectStraight(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win by straight");
        return;
    }


    if(detectStraight(player1, aDeck) == 1 && detectStraight(player2, aDeck) == 1){
        //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win by straight");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win by straight");
        }
    }

    //Three of a kind
    if(detectThreeOfKind(player1, aDeck) == 1 && detectThreeOfKind(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by Three of a kind ");
        return;
    }

    if(detectThreeOfKind(player1, aDeck) == 0 && detectThreeOfKind(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win Three of a kind by Three of a kind ");
        return;
    }

    if(detectThreeOfKind(player1, aDeck) == 1 && detectThreeOfKind(player2, aDeck) == 1){
        //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win by Three of a kind ");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win by Three of a kind ");
        }
    }

    //Two pair
    if(detectTwoPair(player1, aDeck) == 1 && detectTwoPair(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win by two pair");
        return;
    }

    if(detectTwoPair(player1, aDeck) == 0 && detectTwoPair(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win  by two pair");
        return;
    }


    if(detectTwoPair(player1, aDeck) == 1 && detectTwoPair(player2, aDeck) == 1){
                //compareHighCard
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win by  by two pair");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win  by two pair");
        }
    }

    //pair
    if(detectPair(player1, aDeck) == 1 && detectPair(player2, aDeck) == 0){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win  by pair");
        return;
    }

    if(detectPair(player1, aDeck) == 0 && detectPair(player2, aDeck) == 1){
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win  by pair");
        return;
    }

    if(detectPair(player1, aDeck) == 1 && detectPair(player2, aDeck) == 1){
        if(compareHighCard(player1, player2, aDeck) == 1){
            player1->cash = (player1->cash + aGame->pots);
            aGame->pots = 0;
            printf("player1 win  by  pair");
            return;
        }else{
            player2->cash = (player2->cash + aGame->pots);
            aGame->pots = 0;
            printf("player2 win  by  pair");
        }
    }

    //compareHighCard
    if(compareHighCard(player1, player2, aDeck) == 1){
        player1->cash = (player1->cash + aGame->pots);
        aGame->pots = 0;
         printf("player1 win  by high card");
        return;
    }else{
        player2->cash = (player2->cash + aGame->pots);
        aGame->pots = 0;
         printf("player2 win by high card");
        return;
    }

}

//check royal flush
int detectRoyalFlush(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isRoyalFlush(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

//check royal flush
int isRoyalFlush(int bestSet[], deck *aDeck){
    if(isStraightFlush(bestSet, aDeck) && bestSet[4] == Ace){
        return 1;
    }

    return 0;
}

//check straight flush
int detectStraightFlush(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isStraightFlush(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

//dectect straight flush = detect flush + detect straight
int isStraightFlush(int bestSet[], deck *aDeck){
    if(isFlush(bestSet, aDeck) && isStraight(bestSet, aDeck)){
        return 1;
    }
    return 0;
}

//check four of a kind
int detectFourOfAkind(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isFourOfAkind(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

//check is four of a kind
int isFourOfAkind(int bestSet[], deck *aDeck){
    //sort by rank
    sort(bestSet, aDeck);

    if(aDeck->cards[bestSet[0]].value == aDeck->cards[bestSet[1]].value &&
        aDeck->cards[bestSet[1]].value == aDeck->cards[bestSet[2]].value &&
        aDeck->cards[bestSet[2]].value == aDeck->cards[bestSet[2]].value){
            return 1;
    }

    if(aDeck->cards[bestSet[1]].value == aDeck->cards[bestSet[2]].value &&
        aDeck->cards[bestSet[2]].value == aDeck->cards[bestSet[3]].value &&
        aDeck->cards[bestSet[3]].value == aDeck->cards[bestSet[4]].value){
            return 1;
    }

    return 0;
}


//check full house
int detectFullHouse(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isFullHouse(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}


//check full house
int isFullHouse(int bestSet[], deck *aDeck){
    //sort by rank
    sort(bestSet, aDeck);

    if(aDeck->cards[bestSet[0]].value == aDeck->cards[bestSet[1]].value &&
        aDeck->cards[bestSet[1]].value == aDeck->cards[bestSet[2]].value &&
        aDeck->cards[bestSet[3]].value == aDeck->cards[bestSet[4]].value){
            return 1;
    }

    if(aDeck->cards[bestSet[0]].value == aDeck->cards[bestSet[1]].value &&
        aDeck->cards[bestSet[2]].value == aDeck->cards[bestSet[3]].value &&
        aDeck->cards[bestSet[3]].value == aDeck->cards[bestSet[4]].value){
            return 1;
    }

    return 0;
}

//check flush
int detectFlush(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isFlush(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

//check flush
int isFlush(int bestSet[], deck *aDeck){
    //check same suit
    if(aDeck->cards[bestSet[0]].type == aDeck->cards[bestSet[1]].type &&
        aDeck->cards[bestSet[1]].type == aDeck->cards[bestSet[2]].type &&
        aDeck->cards[bestSet[2]].type == aDeck->cards[bestSet[3]].type &&
        aDeck->cards[bestSet[3]].type == aDeck->cards[bestSet[4]].type){
            return 1;
    }else{
        return 0;
    }

}

//check straight
int detectStraight(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isStraight(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

// check straight
int isStraight(int bestSet[], deck *aDeck){
    //sort by rank
    sort(bestSet, aDeck);
    //check in a sequence
    if(aDeck->cards[bestSet[4]].value == (aDeck->cards[bestSet[3]].value + 1) &&
        aDeck->cards[bestSet[3]].value == (aDeck->cards[bestSet[2]].value + 1) &&
        aDeck->cards[bestSet[2]].value == (aDeck->cards[bestSet[1]].value  + 1)&&
        aDeck->cards[bestSet[1]].value == (aDeck->cards[bestSet[0]].value + 1)){

    }else{
        return 0;
    }

}

//sort five cards by rank
void sort(int bestSet[], deck *aDeck){
    int i = 0;
    int j = 0;
    int temp;
    for(i = 0; i < 5; i++){
        for(j = i; j < 5; j++){
            if(aDeck->cards[bestSet[i]].value > aDeck->cards[bestSet[j]].value){
                temp = bestSet[i];
                 bestSet[i] =  bestSet[j];
                 bestSet[j] = temp;
            }
        }
    }
}

//check three of kind
int detectThreeOfKind(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isThreeOfKind(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

//check three of kind
int isThreeOfKind(int bestSet[], deck *aDeck){
    //sort by rank
    sort(bestSet, aDeck);

    if(aDeck->cards[bestSet[0]].value == aDeck->cards[bestSet[1]].value &&
        aDeck->cards[bestSet[1]].value == aDeck->cards[bestSet[2]].value ){
            return 1;
    }

    if(aDeck->cards[bestSet[1]].value == aDeck->cards[bestSet[2]].value &&
        aDeck->cards[bestSet[2]].value == aDeck->cards[bestSet[3]].value ){
            return 1;
    }

    if(aDeck->cards[bestSet[2]].value == aDeck->cards[bestSet[3]].value &&
        aDeck->cards[bestSet[3]].value == aDeck->cards[bestSet[4]].value ){
            return 1;
    }
    return 0;
}

//check two pair
int detectTwoPair(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isTwoPair(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

// check two pair
int isTwoPair(int bestSet[], deck *aDeck){
    //sort by rank
    sort(bestSet, aDeck);

    if(aDeck->cards[bestSet[0]].value == aDeck->cards[bestSet[1]].value &&
        aDeck->cards[bestSet[2]].value == aDeck->cards[bestSet[3]].value ){
            return 1;
    }

    if(aDeck->cards[bestSet[0]].value == aDeck->cards[bestSet[1]].value &&
        aDeck->cards[bestSet[3]].value == aDeck->cards[bestSet[4]].value ){
            return 1;
    }

    if(aDeck->cards[bestSet[1]].value == aDeck->cards[bestSet[2]].value &&
        aDeck->cards[bestSet[3]].value == aDeck->cards[bestSet[4]].value ){
            return 1;
    }

    return 0;
}

//check pair
int detectPair(user *player, deck *aDeck){
    int i = 0;
    int j = 0;
    int k = 0;
    int bestSet[5];
    int counter = 0;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 7; j++){
            counter = 0;
            if(i == j){
                continue;
            }
            for(k = 0; k < 7; k++){
                if(k != i && k != j){
                    bestSet[counter] = player->cardIndex[k];
                    counter++;
                }
            }
            if(isPair(bestSet, aDeck) == 1){
                return 1;
            }
        }
    }
    return 0;
}

//check pair
int isPair(int bestSet[], deck *aDeck){
    //sort by rank
    sort(bestSet, aDeck);

    if(aDeck->cards[bestSet[0]].value == aDeck->cards[bestSet[1]].value ){
        return 1;
    }

    if(aDeck->cards[bestSet[2]].value == aDeck->cards[bestSet[3]].value ){
        return 1;
    }

    if(aDeck->cards[bestSet[3]].value == aDeck->cards[bestSet[4]].value ){
        return 1;
    }

    return 0;
}

//return 1 if player1 win and return 0 if player2 win
int compareHighCard(user *player1, user *player2, deck *aDeck){
    //sort
    sortCards(player1, aDeck);
    sortCards(player2, aDeck);

    if(aDeck->cards[player1->cardIndex[6]].value > aDeck->cards[player2->cardIndex[6]].value){
        return 1;
    }

    if(aDeck->cards[player1->cardIndex[6]].value < aDeck->cards[player2->cardIndex[6]].value){
        return 0;
    }

    if(aDeck->cards[player1->cardIndex[6]].value == aDeck->cards[player2->cardIndex[6]].value){
        if(aDeck->cards[player1->cardIndex[6]].type > aDeck->cards[player2->cardIndex[6]].type){
            return 1;
        }
        return 0;
    }
}


//print game info
void printGameState(user *player1, user *player2, game *aGame, deck *aDeck){
    printf("\nplayer1: \n");
    printf("player1: \n");
    printf("Name: %s\n", player1->name);
    printf("Cash: %ld usd\n", player1->cash);

    printf("cards:\n");
    int i = 0;
    for(i = 0; i < 7; i++){


        if(aDeck->cards[player1->cardIndex[i]].value  < 11){
            printf("%d ", aDeck->cards[player1->cardIndex[i]].value);
        } else if(aDeck->cards[player1->cardIndex[i]].value == 11){
            printf("J ");
        } else if(aDeck->cards[player1->cardIndex[i]].value == 12){
            printf("Q ");
        } else if(aDeck->cards[player1->cardIndex[i]].value == 13){
            printf("K ");
        } else if(aDeck->cards[player1->cardIndex[i]].value == 14){
            printf("A ");
        }

        if(aDeck->cards[player1->cardIndex[i]].type == Clubs){
            printf("Clubs ");
        } else if(aDeck->cards[player1->cardIndex[i]].type == Diamonds){
            printf("Diamonds ");
        } else if(aDeck->cards[player1->cardIndex[i]].type == Hearts){
            printf("Hearts ");
        } else if(aDeck->cards[player1->cardIndex[i]].type == Spades){
            printf("Spades ");
        }



        printf("\n");

   }

    printf("\n-player2: -\n");
    printf("player2: \n");
    printf("Name: %s\n", player2->name);
    printf("Cash: %ld usd\n", player2->cash);

    printf("cards: \n");
     for(i = 0; i < 7; i++){

        if(aDeck->cards[player2->cardIndex[i]].value  < 11){
            printf("%d ", aDeck->cards[player2->cardIndex[i]].value);
        } else if(aDeck->cards[player2->cardIndex[i]].value == 11){
            printf("J ");
        } else if(aDeck->cards[player2->cardIndex[i]].value == 12){
            printf("Q ");
        } else if(aDeck->cards[player2->cardIndex[i]].value == 13){
            printf("K ");
        } else if(aDeck->cards[player2->cardIndex[i]].value == 14){
            printf("A ");
        }

        if(aDeck->cards[player2->cardIndex[i]].type == Clubs){
            printf("Clubs ");
        } else if(aDeck->cards[player2->cardIndex[i]].type == Diamonds){
            printf("Diamonds ");
        } else if(aDeck->cards[player2->cardIndex[i]].type == Hearts){
            printf("Hearts ");
        } else if(aDeck->cards[player2->cardIndex[i]].type == Spades){
            printf("Spades ");
        }
        printf("\n");

     }


    printf("\nGames info\n");
    printf("Hand-%d-\n", aGame->hand);
    printf("Pot-%ld-usd\n", aGame->pots);

}

//printDeckInfo
void printDeck(deck *aDeck){
    int i = 0;
    for(i = 0; i < 52; i++){
        printf("%d - %d \n ", aDeck->cards[i].value, aDeck->cards[i].type);
    }

    printf("\n");
}

//print player info
void printPlayerInfo(user *player1, user *player2){
    printf("player1: \n");
    printf("Name: %s\n", player1->name);
    printf("Cash: %ld usd\n", player1->cash);

    printf("player2: \n");
    printf("Name: %s\n", player2->name);
    printf("Cash: %ld usd\n", player2->cash);
}
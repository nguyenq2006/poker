//
//  main.c
//  lab7
//
//  Created by CS on 11/6/16.
//  Copyright © 2016 Quoc Nguyen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUITS 4
#define FACES 13
#define CARDS 52

void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies deck
void deal(unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[]); //dealing doesn's modifiy the array
void checkPair(int hand[], const char *face[]); //check for pair
void threeOfAKind(int hand[], const char *face[]);
void fourOfAKind(int hand[], const char *face[]);
void flush(int hand[], const char *suit[]);
void straight(int hands[], const char *face[]);
void BubbleSort(int a[], int array_size);

int handFaces[5]; //array of faces of the hand
int handSuit[5]; //array of suit of the hand

int main(void) {
    //initalize suit array
    const char *suit[SUITS] = { "Hearts", "Diamonds", "Clubs", "Spades"};
    
    //initializw face array
    const char *face[FACES] = { "Ace", "Duece", "Three", "Four", "Five",
        "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    
    //initialize deck array
    unsigned int deck[SUITS][FACES] = {0};
    
    srand(time(NULL));
    
    shuffle(deck);
//    for(int i = 0; i < SUITS; ++i) {
//        for (int j = 0; j < FACES; ++j) {
//            printf("%d ", deck[i][j]);
//        }
//        printf("\n");
//    }
    deal(deck, face, suit);
    for(int i = 0; i < 5; ++i) {
        int f = handFaces[i];
        int s = handSuit[i];
        printf("%8s of %8s\n", face[f] , suit[s]);
        printf("%8d of %8d\n", handFaces[i] , handSuit[i]);
    }
    checkPair(handFaces, face);
    threeOfAKind(handFaces, face);
    fourOfAKind(handFaces, face);
    flush(handSuit, suit);
    BubbleSort(handFaces, 5);
    straight(handFaces, face);
}

//shuffle card in the deck
void shuffle(unsigned int wDeck[][FACES]) {
    size_t row; //number of row
    size_t column; // number of column
    size_t card; // number of card
    
    for(card = 1; card <= CARDS; ++card) {
        //choose a random location until unoccupied slot found
        do {
            row = rand() % SUITS;
            column = rand() % FACES;
        } while(wDeck[row][column] != 0); // cotinue if the slot is not 0
        //place the card in chosen slot of deck
        wDeck[row][column] = card;
    }
}
void deal (unsigned int wDeck[][FACES], const char *wFace[], const char *wSuit[]) {
    size_t row; //number of row
    size_t column; // number of column
    size_t card; // number of card
    //loop through the deck
    for(card = 1 ; card <= 5; ++card) {
        //loop through the row
        for(row = 0; row < SUITS; ++row) {
            //loop through the column
            for (column = 0; column < FACES; ++column) {
                //if slot contains current card, display card
                if(wDeck[row][column] == card) {
                    handSuit[card-1] = row;
                    handFaces[card-1] = column;
                }
            }
        }
    }
}

void checkPair(int hand[], const char *face[]) {
    int counter = 0;
    int pair[2];
    for (int i = 0 ; i < 5; ++i) {
        for(int j = i+1 ; j < 5; j++){
            if(hand[i] == hand[j] && hand[i] != pair[0]){
                pair[counter] = hand[i];
                counter++;
            }
        }
    }
    if(counter == 2){
        printf("There is %d pair of %s and %s\n", counter, face[pair[0]], face[pair[1]]);
    }
    else if(counter == 1)
        printf("There are %d pair of %s\n", counter, face[pair[0]]);
}

void threeOfAKind(int hand[], const char *face[]) {
    int counter = 1;
    for (int i = 0 ; i < 5; ++i) {
        for(int j = i+1 ; j < 5; j++){
            if(hand[i] == hand[j]){
                counter++;
            }
        }
        if(counter == 3){
            int n = hand[i];
             printf("There is three of a kind of %s\n", face[n]);
        }
        counter = 1;
    }
}

void fourOfAKind(int hand[], const char *face[]) {
    int counter = 1;
    for (int i = 0 ; i < 5; ++i) {
        for(int j = i+1 ; j < 5; j++){
            if(hand[i] == hand[j]){
                counter++;
            }
        }
        if(counter == 4){
            int n = hand[i];
            printf("There is four of a kind of %s\n", face[n]);
        }
        counter = 1;
    }
}

void flush(int hand[], const char *suit[]) {
    int flush = 1;
    for(int i = 1; i < 5; ++i) {
        if(hand[0] != hand[i]){
            flush = 0;
        }
    }
    if(flush)
        printf("There is a flush of %s\n", suit[0]);
}

void straight(int hands[], const char *face[]) {
    int flush = 1;
    for(int i = 1; i < 5; ++i) {
        if(hands[i] != (hands[i-1] + 1))
            flush = 0;
    }
    if(flush)
        printf("There is a straight from %s to %s\n", face[hands[0]], face[hands[4]]);
}

void BubbleSort(int a[], int array_size) {
    int i, j, temp;
    for (i = 0; i < (array_size - 1); ++i)
    {
        for (j = 0; j < array_size - 1 - i; ++j )
        {
            if (a[j] > a[j+1])
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
}

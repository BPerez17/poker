#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "card.h"
using namespace std;



Card::Card(string val, string s) : value(val), suit(s), cardImage(nullptr){
    //adding a new image -- testing 1/13/2024
    this->cardImage = new char*[9];
    for (unsigned int i = 0; i < 9; i++) {
        this->cardImage[i] = new char[5];
    }
}

Card:: ~Card(){
    //delete image of card by deallocatig memory
    if (this->cardImage != nullptr) {
        for (unsigned int i = 0; i < 9; i++) {
            delete[] this->cardImage[i];
            this->cardImage[i] = nullptr;
        }
            delete[] this->cardImage;
            this->cardImage = nullptr;
    }
}

Card::Card(const Card& copyCard) : value(copyCard.value), suit(copyCard.suit), cardImage(nullptr) {
    this->generateImage(copyCard.cardImage);
} // copy constructor 

Card& Card:: operator=(const Card& copyCard){
    if (this == &copyCard)
        return *this; // Self-assignment check

    // Clean up old image
    if (this->cardImage != nullptr) {
        for (unsigned int i = 0; i < 9; i++) {
            delete[] this->cardImage[i];
        }
        delete[] this->cardImage;
        this->cardImage = nullptr;
    }

    this->suit = copyCard.suit;
    this->value = copyCard.value;
    this->generateImage(copyCard.cardImage);

    return *this;
}

void Card::generateImage(char newCardImage[9][5]){
    //if image already exists >> delete then make a new image
    if (this->cardImage != nullptr) {
        for (unsigned int i = 0; i < 9; i++) {
            delete[] this->cardImage[i];
            this->cardImage[i] = nullptr;
        }
        delete[] this->cardImage;
        this->cardImage = nullptr;

    }
    //allocates new memory for image

    this->cardImage = new char*[9];

    for (unsigned int i = 0; i < 9; i++) {
        this->cardImage[i] = new char[5];
    }

    //copy chosen card from the wild card if any

    for (unsigned int i = 0; i < 9; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            this->cardImage[i][j] = newCardImage[i][j];
        }
    }
}

void Card::generateImage(char** newCardImage){
    // will be implmented for copy assingment to copy a card
    if(newCardImage == nullptr){
        return;
    }

    if (this->cardImage != nullptr) {
        for (unsigned int i = 0; i < 9; i++) {
            delete[] this->cardImage[i];
            this->cardImage[i] = nullptr;
        }
            delete[] this->cardImage;
            this->cardImage = nullptr;
    }

    //Allocate new memory for new card image

    this->cardImage = new char*[9];

    for (unsigned int i = 0; i < 9; i++) {
        this->cardImage[i] = new char[5];
    }

    // copy chosen image from wild card 

    for (unsigned int i = 0; i < 9; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            this->cardImage[i][j] = newCardImage[i][j];
        }
    }
}

string Card::getValue() const{
    return this->value;
}

string Card::getSuit() const{
    return this->suit;
}


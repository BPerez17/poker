#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
#include <random>
#include "display.h"
using namespace std;

vector<Card> loadData(string filename){
    vector<Card> output;
    ifstream inFS;
    inFS.open(filename);
    while (!inFS.is_open()) {
        cout << "File was not found, try again: ";
        cin >> filename;
        inFS.open(filename);
    }

    while (!inFS.eof()) {

        string new_value;
        string new_suit;
        char new_image[9][5];
        string readinstring;

        for (int y = 0; y < 5; y++) {
            getline(inFS, readinstring);
            for (int x = 0; x < 9; x++) {
                new_image[x][y] = readinstring.at(x);
            }
        }

        inFS >> new_value >> new_suit;

        Card new_card(new_value, new_suit);
        new_card.generateImage(new_image);
       
        output.push_back(new_card);

        if (getline(inFS, readinstring)) {
            /* This deals with the possible 'enter' character. 
            It will do nothing/passes */
        }

    }

    return output;

}

void shuffle(vector<Card>& deck) {
    std::random_device rd;                         
    std::mt19937 g(rd());                          
    std::shuffle(deck.begin(), deck.end(), g);     
}

void generateHand(vector<Card>& deck, Player& user){

    
    if (deck.size() < 3) {
        cerr << "Error: Not enough cards in deck to generate a hand." << endl;
        return;
    }

    shuffle(deck);
    
    Card card1 = deck.at(0);
    Card card2 = deck.at(2);

    deck.erase(deck.begin() + 2);
    deck.erase(deck.begin());

    user.getHand().push_back(card1);
    user.getHand().push_back(card2);

}

void tableDisplay(vector<Card>& deck, vector<Card>& communitycards, Player& user, Player& computer, int pot, int round){
   
    if(round == 4){
        cout << "\n\t\tCards Revealed!" << endl;
    }
    else{
        cout <<  "\t\t~~Round " << round << "~~\t\t" << endl;
    }
    
        cout << "Computer | Cash: $" << computer.getCash() << "\n\n";

        //cards on the table is displayed similar to code layout in the order it is written

        //displaying computer's cards on the last round
        if(round == 4){
            //display computer cards
            for (unsigned int y = 0; y < 5; y++) {
                for (unsigned int x = 0; x < 24; x++) { 
                    
                    if (x >= 2 && x <= 10) {
                        cout << computer.getHand().at(0).cardImage[x - 2][y];
                    }
                    else if (x >= 14 && x <= 22) {
                        cout << computer.getHand().at(1).cardImage[x - 14][y];
                    }
                    else{
                        cout << " ";
                    }

                }
                    cout << "\n";
            }
            cout << endl;
        }


        //deck cards being shown
        for (unsigned int y = 0; y < 5; y++) {
            for (unsigned int x = 0; x < 34 + ((round - 1)*12) + 1; x++) { 
                // the multiplication of the loop is to prevent unesseccary iterations, saves time
                
                if (x >= 2 && x <= 10) {
                    cout << deck.at(0).cardImage[x - 2][y];
                }
                else if (x >= 14 && x <= 22) {
                    cout << deck.at(2).cardImage[x - 14][y];
                    
                }
                else if(x >= 26 && x<= 34) {
                    cout << deck.at(4).cardImage[x - 26][y];
                }

                //addtional cards added after rounds
                //round 2 (added one card)
                else if(x >= 38 && x<= 46) {
                    if(round > 1){
                        cout << deck.at(6).cardImage[x - 38][y];
                    }
                }

                //round 3 (all 5 cards are down on the river)
                else if(x >= 50 && x<= 58) {
                    if(round > 2){
                        cout << deck.at(8).cardImage[x - 50][y];
                    }
                }

                else{
                    cout << " ";
                }

            }
            cout << endl;
        }

        
        cout << "\n" << endl;
        cout << "Pot has $" << pot << "\n\n";

    if(user.getHand().size() > 1){

        
        for (unsigned int y = 0; y < 5; y++) {
            for (unsigned int x = 0; x < 24; x++) { 
                
                if (x >= 2 && x <= 10) {
                    cout << user.getHand().at(0).cardImage[x - 2][y];
                }
                else if (x >= 14 && x <= 22) {
                    cout << user.getHand().at(1).cardImage[x - 14][y];
                }
                else{
                    cout << " ";
                }

            }
            cout << endl;
        }
    }


        cout << user.getName()  << " | Cash: $" << user.getCash() << endl;

        

    


}






void printCredits(){
    cout << " Welcome!" << endl;
    cout << " This is a poker-like Simulator," << endl;
    cout << " created to have fun experimenting with classes," << endl;
    cout << " dynamic memory, pointers, input management, and" << endl;
    cout << " batch processing-like functions                " << endl;
    cout << " Created by Brandon Perez w/ Visual Studio Code, with Resolution " << endl;
    cout << " of 3840 x 2400                                 " << endl << endl;

    cout << "       ~~~~~  Poker Game Project  ~~~~~     " << endl << endl;

}
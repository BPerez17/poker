#include <iostream>
#include <string>
#include <vector>
#include <fstream> //
#include <algorithm>
#include <random>
#include "card.h"
#include "display.h"
#include "player.h"
#include "hand_evaluator.h"

using namespace std;

int main() {

    char decision = 'p';
    // string helperFileName;
    string userinput;


    printCredits();

    // testing file reading
    // ifstream fileStream;
    // while (!fileStream.is_open()) {
    //     cout << "Enter filename: ";
    //     cin >> helperFileName;
    //     cout << endl;
        
    //     fileStream.open(helperFileName);
    //     if (!fileStream.is_open()) {
    //         cerr << "Error: Unable to open file. Please enter a valid filename." << endl;
    //     }
    //     cout << "Reading cards from file..." << endl;
        
    // }

    // fileStream.close(); 


    while (decision == 'p') {
        cout << "Creating Deck..." << endl;
        vector<Card> deck = loadData("gameplay.txt");  // vector<Card> deck = loadData(helperFileName);
        int totalpot = 0;
        int round = 1;
        vector<Card> communitycards; 

        //Players: you and computer
        Player user("You");
        Player computer;

    
        //random number generator for the computer to bet
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 5);
        int randNum = distrib(gen);        
        int computer_bet;
        int userbet;
        initialBets(user, computer, userbet, computer_bet, totalpot, randNum);
        
     
       
        //dealing cards and creating hands to be displayed on the GUI
        generateHand(deck, user);
        generateHand(deck, computer);

        tableDisplay(deck, communitycards, user, computer, totalpot, round);
        
        //second bets and playing rounds
        computer_bet = distrib(gen) * 70;
        if(computer_bet > computer.getCash()){
            computer_bet = computer.getCash();
        }
        totalpot += computer_bet;
        computer.removeCash(computer_bet);


        cout << "\nMaking initial bets... Computer has bet $" << computer_bet;
        
        //this is the loop that helps the user decide their move.
        // The game ends after all 5 cards are dealt and the winner is decided
        while(round < 4){
            cout << "\nWhat is your next move? (Enter a letter and press enter to continue.)" << endl;
            cout << "C. Check" << endl;
            cout << "R. Raise" << endl;
            cout << "F. Fold" << endl;

            cin >> userinput;
            if(userinput.find('c') != string::npos || userinput.find('C') != string::npos ){
                //the user deciced to check
                round += 1;
            }
            else if(userinput.find('r') != string::npos || userinput.find('R') != string::npos){
                // the user deciced to raise
                // user cannot bet if their balance is empty.
                // user is reprompted to choose a different option
                if(user.getCash() == 0) { 
                    cout << "\nBalance is empty. Try another option: "; 
                }
                else{
                    while (true){
                        cout << "What is your raise? $ ";
                        try {
                            cin >> userinput;
                            userbet = stoi(userinput);
                            break;
                        }   catch (const invalid_argument& e) {
                                cerr << "Try again: " ;
                        }   catch (const out_of_range& e) {
                                cerr << "Try again: " ;
                        }
                    }
                    if(userbet > user.getCash()){
                        userbet = user.getCash();
                        cout << "Bet adjusted\n";
                    }
                    totalpot += userbet;
                    user.removeCash(userbet);
                    round += 1;
                    
                }
            }
            
            else if(userinput.find('f') != string::npos || userinput.find('F') != string::npos){
                // the user has folded, making the computer win
                cout << "You folded. Computer wins!\n\n";
                computer.addCash(totalpot);
                totalpot = 0;
                cout << "Totals:" << endl;
                cout << "Computer score: $" << computer.getCash() << endl;
                cout << user.getName() << "'s score: $" << user.getCash() << endl;
                round = 4;
                
                
            }

            if(round != 4){
                tableDisplay(deck, communitycards, user, computer, totalpot, round);
            }
            
            
        }
        round = 4;

        // the community cards are being added every other card since there is no "burning" of the cards.
        // this creates the same effect
        communitycards.push_back(deck.at(0));
        communitycards.push_back(deck.at(2));
        communitycards.push_back(deck.at(4));
        communitycards.push_back(deck.at(6));
        communitycards.push_back(deck.at(8));
        
        //reveal cards after all cards have been dealt
        tableDisplay(deck, communitycards, user, computer, totalpot, round);

        getWinner(user,computer,communitycards);
        

        // after someone/computer wins, the prompt to play again will appear
        cout << endl;
        cout << " Want to play again?" << endl;
        cout << " (Enter 'p', or 'q' to quit): ";
        cin >> decision;
        cout << "\n\n\n";
        
       
    }

    cout << "Thanks for visiting, until next time ...";

}



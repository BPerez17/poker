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
        int round = 1; // 5,22,25 all rounds work
        vector<Card> communitycards; 

        //maybe add more players?
        cout << "What is your name? ";
        cin >> userinput;
        Player user(userinput);
        Player computer;

    
        //buy-in bets to play the round
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<std::mt19937::result_type> distrib(1, 5);
        int computer_bet = distrib(gen) * 4;
        int userbet = computer_bet;
        
        //prevents bet from exceeding balance
        if(computer_bet > computer.getCash()){
            computer_bet = computer.getCash();
        }

        totalpot += computer_bet;


        if(userbet > user.getCash()){
            userbet = user.getCash();
        }
        
        totalpot += userbet;

        cout << "Computer has bet " << computer_bet << ". Mathing buy-in bet. " << user.getName() << " bets " << userbet << "\n\n";

        computer.removeCash(computer_bet);
        user.removeCash(userbet);
        
        
        //dealing cards and creating hands
        generateHand(deck, user);
        generateHand(deck, computer);

        tableDisplay(deck, communitycards, user, computer, totalpot, round);
        
        //second bets and playing rounds
        // def function to calculate betting
        computer_bet = distrib(gen) * 70;
        if(computer_bet > computer.getCash()){
            computer_bet = computer.getCash();
        }
        totalpot += computer_bet;
        computer.removeCash(computer_bet);

        //add probablity of folding depending on computers hand rank
        cout << "\nMaking initial bets... Computer has bet $" << computer_bet;
        
        
        while(round < 4){
            cout << "\nWhat is your next move? (Enter a letter and press enter to continue.)" << endl;
            cout << "C. Check" << endl;
            cout << "R. Raise" << endl;
            cout << "F. Fold" << endl;

            cin >> userinput;
            if(userinput.find('c') != string::npos || userinput.find('C') != string::npos ){
                //continue without betting
                round += 1;
            }
            else if(userinput.find('r') != string::npos || userinput.find('R') != string::npos){
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
                cout << "You folded. Computer wins!\n\n";
                computer.addCash(totalpot);
                totalpot = 0;
                cout << "Totals:" << endl;
                cout << "Computer score: $" << computer.getCash() << endl;
                cout << user.getName() << "'s score: $" << user.getCash() << endl;
                round = 4;
                //add wins to computer ?
                
            }

            if(round != 4){
                tableDisplay(deck, communitycards, user, computer, totalpot, round);
            }
            
            
        }
        round = 4;

        communitycards.push_back(deck.at(0));
        communitycards.push_back(deck.at(2));
        communitycards.push_back(deck.at(4));
        communitycards.push_back(deck.at(6));
        communitycards.push_back(deck.at(8));
        
        //reveal cards
        
        tableDisplay(deck, communitycards, user, computer, totalpot, round);

        cout << "Hand: " << evaluateTexasHoldEm(user.getHand(), communitycards) << "\n";

        int winner = compareHands(user.getHand(), computer.getHand(), communitycards);
        cout << "Result:\n";
        if (winner == 1) {
            cout << "You win with a " << evaluateTexasHoldEm(user.getHand(), communitycards) << endl;
        } else if (winner == 2) {
            cout << "Computer wins with a " << evaluateTexasHoldEm(computer.getHand(), communitycards)  <<endl;
        } else {
            cout << "It's a tie!" << endl;
        }

        
        

        // After someone/computer wins, the prompt to play again will appear
        
        cout << endl;
        cout << " Want to play again?" << endl;
        cout << " (Enter 'p', or 'q' to quit): ";
        cin >> decision;
        cout << "\n\n\n";
        
       
    }

    cout << "Thanks for visiting, until next time ...";

}
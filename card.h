#ifndef CARD_H
#define CARD_H
using namespace std;

class Card{
    private:
        string value;
        string suit;
    public:
        char** cardImage;
        Card(string val, string s = "");
        //rule of three
        ~Card();
        Card(const Card& copyCard);
        Card& operator = (const Card& copyCard);
        
        void generateImage(char newCardImage[9][5]);
        void generateImage(char** newCardImage);

        string getValue() const;
        string getSuit() const;
        //string printCard();


};


#endif
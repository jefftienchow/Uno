
#include <iostream>
#include <map>
#include <math.h>
#include <random>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

enum Color {RED, YELLOW, GREEN, BLUE, NONE};
enum Rank {NUMBER, SKIP, REVERSE, DRAW_TWO, WILD, WILD_D4};
enum Valid {VALID, INVALID};
int INIT_HAND_SIZE = 7;
enum Direction {FORWARDS, BACKWARDS};


class Card
{
private:
    Color color;
    Rank rank;
    int number;
    Valid validity;
    
public:
    
    Card (Valid validity)
    {
        if (validity == INVALID)
        {
            this -> validity = INVALID;
        }
        else
        {
            this -> validity = VALID;
        }
    }
    
    /* constructor for non-number cards */
    Card(Color color, Rank rank)
    {
        this -> color = color;
        this -> rank = rank;
        this -> number = -1;
        this -> validity = VALID;
    }
    
    /* constructor for number cards */
    Card(Color color, int number)
    {
        this -> color = color;
        this -> rank =  NUMBER;
        this -> number = number;
        this -> validity = VALID;
    }
    
    Card (Color color, int number, Rank rank)
    {
        this -> color = color;
        this -> number = number;
        this -> rank = rank;
        this -> validity = VALID;
    }
    
    /* cost that ending the game with this card would force upon the player */
    int forfeitCost()
    {
        if (this -> rank == SKIP || this -> rank == REVERSE || this -> rank == DRAW_TWO)
        {
            return 20;
        }
        else if (this -> rank == WILD || this -> rank == WILD_D4)
        {
            return 50;
        }
        else if (this -> rank == NUMBER)
        {
            return this -> number;
        }
        else
        {
            return 0;
        }
    }
    
    /* checks to see if the card is a valid card to be played */
    bool canPlayOn(Card c)
    {
        if (this -> rank == WILD || this -> rank == WILD_D4 || this -> color == c.color || (this -> rank == c.rank && this -> rank != NUMBER) || (this -> rank == NUMBER &&  c.rank == NUMBER && this -> number == c.number))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool canPlayColor(Color c)
    {
        if (this -> color == c || this -> color == NONE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    
    Valid getValidity()
    {
        return this -> validity;
    }
    
    /* returns color of the card */
    Color getColor()
    {
        return this -> color;
    }
    
    /* returns rank of the card */
    Rank getRank()
    {
        return this -> rank;
    }
    
    /* returns number of the card (-1 for non-nuber cards */
    int getNumber()
    {
        return this -> number;
    }
    
    /* method to print information about the card */
    void printCard()
    {
        string c;
        if (getColor() == RED)
        {
            c = "RED";
        }
        else if (getColor() == BLUE)
        {
            c = "BLUE";
        }
        else if (getColor() == GREEN)
        {
            c = "GREEN";
        }
        else if (getColor() == YELLOW)
        {
            c = "YELLOW";
        }
        else if (getColor() == NONE)
        {
            c = "NONE";
        }
        
        string r;
        if (getRank() == WILD)
        {
            r = "WILD";
        }
        else if (getRank() == DRAW_TWO)
        {
            r = "DRAW_TWO";
        }
        else if (getRank() == WILD_D4)
        {
            r = "WILD_D4";
        }
        else if (getRank() == NUMBER)
        {
            r = "NUMBER";
        }
        else if (getRank() == SKIP)
        {
            r = "SKIP";
        }
        else if (getRank() == REVERSE)
        {
            r = "REVERSE";
        }
        if (r.compare("NUMBER") == 0)
        {
            cout << c << " " << getNumber();
        }
        else if (r.compare("DRAW_TWO") == 0 || r.compare("SKIP") == 0 || r.compare("REVERSE") == 0)
        {
            cout << c << " " << r;
        }
        else
        {
            cout << r;
        }
    }
};


class Deck
{
    
private:
    vector <Card*> cards; /* array of cards */
    vector <Card*> discardedCards;
    int Random = rand();
    
public:
    int NUMBER_OF_DUP_REGULAR_CARDS = 2;
    int NUMBER_OF_DUP_ZERO_CARDS = 1;
    int NUMBER_OF_DUP_SPECIAL_CARDS = 2;
    int NUMBER_OF_WILD_CARDS = 4;
    int NUMBER_OF_WILD_D4_CARDS = 4;
    int SHUFFLE_FACTOR = 1;
    
    /* constructs a new deck */
    Deck()
    {
        Random = rand();
        fillDeck();
        shuffle();
    }
    
    /* fills decks according to above information regarding number of each type of card */
    void fillDeck()
    {
        
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 0; j < NUMBER_OF_DUP_REGULAR_CARDS; j++)
            {
                cards.push_back(new Card(RED, i));
                cards.push_back(new Card(YELLOW, i));
                cards.push_back(new Card(BLUE, i));
                cards.push_back(new Card(GREEN, i));
            }
        }
        
        // There are fewer "0" cards than other numbers.
        for (int j = 0; j < NUMBER_OF_DUP_ZERO_CARDS; j++)
        {
            cards.push_back(new Card(RED, 0));
            cards.push_back(new Card(YELLOW, 0));
            cards.push_back(new Card(BLUE, 0));
            cards.push_back(new Card(GREEN, 0));
        }
        
        for (int j = 0; j < NUMBER_OF_DUP_SPECIAL_CARDS; j++)
        {
            cards.push_back(new Card(RED, SKIP));
            cards.push_back(new Card(YELLOW, SKIP));
            cards.push_back(new Card(GREEN, SKIP));
            cards.push_back(new Card(BLUE, SKIP));
            cards.push_back(new Card(RED, REVERSE));
            cards.push_back(new Card(YELLOW, REVERSE));
            cards.push_back(new Card(GREEN, REVERSE));
            cards.push_back(new Card(BLUE, REVERSE));
            cards.push_back(new Card(RED, DRAW_TWO));
            cards.push_back(new Card(YELLOW, DRAW_TWO));
            cards.push_back(new Card(GREEN, DRAW_TWO));
            cards.push_back(new Card(BLUE, DRAW_TWO));
        }
        
        for (int i = 0; i < NUMBER_OF_WILD_CARDS; i++)
        {
            cards.push_back(new Card(NONE, WILD));
        }
        
        for (int i = 0; i < NUMBER_OF_WILD_D4_CARDS; i++)
        {
            cards.push_back(new Card(NONE, WILD_D4));
        }
    }
    
    int nextInt(int size)
    {
        return (int) rand() % size;
    }
    
    /* shuffles deck as long as it is partially filled */
    void shuffle()
    {
        for (int i = 0; i < SHUFFLE_FACTOR * cards.size(); i++)
        {
            random_shuffle(cards.begin(),cards.end());
        }
    }
    
    bool isEmpty()
    {
        return cards.size() == 0;
    }
    
    long size()
    {
        return cards.size();
    }
    
    Card draw()
    {
        if (cards.size() == 0)
        {
            cout << "Empty Deck!!"; /* HOW TO THROW AN EXCEPTION! */
        }
        Card temp_card = *cards.at(0);
        cards.erase(cards.begin());
        return temp_card;
    }
    
    void discard(Card c)
    {
        discardedCards.push_back(&c);
    }
    
    void remix()
    {
        cards.insert(cards.end(), discardedCards.begin(), discardedCards.end());
        discardedCards.clear();
        shuffle();
    }
    
    vector<Card *> getDiscardedCards() /* how to specify that an array is being returned */
    {
        return discardedCards;
    }
};

class Hand
{
private:
    vector <Card> cards;
public:
    
    Hand ()
    {
    }
    
    void addCard(Card c)
    {
        cards.push_back(c);
    }
    
    long size()
    {
        return cards.size();
    }
    
    /*    Card play(UnoPlayer_Robot robot, Card upCard, Color calledColor)
     {
     Card playedCard = robot.robotPlay(cards, upCard, calledColor);
     Card toPlay = *new Card (playedCard.getColor(), playedCard.getRank());
     cards.erase(remove(cards.begin(), cards.end(), playedCard), cards.end());
     return toPlay;
     
     }
     */
    
    void display_hand()
    {
        cards[0].printCard();
        for (int i = 1; i < size(); i++)
        {
            cout << ", ";
            cards[i].printCard();
        }
    }
    
    bool isIn(Card card)
    {
        for (int i = 0; i < size(); i++)
        {
            if (card.getColor() == cards[i].getColor())
            {
                if (card.getRank() == cards[i].getRank())
                {
                    if (card.getNumber() == cards[i].getNumber())
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    void remove(Card card)
    {
        for (int i = 0; i < size(); i++)
        {
            if (card.getColor() == cards[i].getColor())
            {
                if (card.getRank() == cards[i].getRank())
                {
                    if (card.getNumber() == cards[i].getNumber())
                    {
                        cards.erase(cards.begin() + i);
                        break;
                    }
                }
            }
        }
    }
    
    bool isEmpty()
    {
        return cards.size() == 0;
    }
    
    int countCards()
    {
        int total = 0;
        for (int i = 0; i < cards.size(); i++)
        {
            total += cards.at(i).forfeitCost();
        }
        return total;
    }
    
    vector <Card> getCards(){
        return this -> cards;
    }
    
    
};

class UnoPlayer_Robot
{
private:
    
public:
    UnoPlayer_Robot ()
    {
    }
    
    Card robotPlay(vector <Card> hand, Card upCard, Color calledColor)
    {
        for (int i=0; i < hand.size(); i++)
        {
            if (calledColor == NONE)
            {
                if (hand[i].canPlayOn(upCard))
                {
                    return hand[i];
                }
            }
            else
            {
                if (hand[i].canPlayColor(calledColor))
                {
                    return hand[i];
                }
            }
        }
        return Card(INVALID);
    }
    
    Color callColor(Hand hand)
    {
        vector <Card> cards = hand.getCards();
        int red_count=0;
        int blue_count=0;
        int green_count=0;
        int yellow_count=0;
        vector <int> counts;
        for (int i=0; i<sizeof(cards);i++){
            if (cards[i].getColor()==RED){
                red_count++;
            }
            if (cards[i].getColor()==BLUE){
                blue_count++;
            }
            if (cards[i].getColor()==GREEN){
                green_count++;
            }
            if (cards[i].getColor()==YELLOW){
                yellow_count++;
            }
            
        }
        counts.push_back(red_count);
        counts.push_back(blue_count);
        counts.push_back(yellow_count);
        counts.push_back(green_count);
        int cur_max=0;
        int index=0;
        for (int i=0;i<sizeof(counts);i++){
            if (counts[i]>cur_max){
                cur_max=counts[i];
                index=i;
            }
        }
        if (index==0){
            return RED;
        }
        else if (index==1){
            return BLUE;
        }
        else if (index==2){
            return YELLOW;
        }
        else {
            return GREEN;
        }
        
    }
    
};



int main()
{
    int num, i, j, input_num, player_turn = 0, bot_playing = 0, bot_after = 0, factor = 1;
    string name;
    Color called_color = NONE, c;
    bool color_not_found;
    string input1, input2;
    Card temp_card(NONE, WILD), played_card(NONE, WILD);
    UnoPlayer_Robot bot;
    vector <Hand> bot_hands;
    vector <int> bot_turns;
    cout <<"Enter your name: ";
    cin >> name;
    Hand hand;
    cout << "Enter the number of bots you want to play with: ";
    cin >> num;
    if (num == 1)
    {
        factor = 1;
    }
    else
    {
        factor = 2;
    }
    for (i = 0; i < num; i++)
    {
        Hand temp_hand;
        bot_hands.push_back(temp_hand);
        bot_turns.push_back(i + 1);
    }
    Deck deck;
    for (i = 0; i < num; i++)
    {
        for (j = 0; j < INIT_HAND_SIZE; j++)
        {
            bot_hands[i].addCard(deck.draw());
        }
    }
    for (j = 0; j < INIT_HAND_SIZE; j++)
    {
        hand.addCard(deck.draw());
    }
    bool game_going = true, card_not_found, valid;
    Card upCard = deck.draw();
    while (game_going)
    {
        if (deck.size() < 5)
        {
            deck.remix();
        }
        cout << "------------------------------------";
        if (player_turn == 0)
        {
            cout << endl << "Opponent hand sizes:" << endl;
            for (i =0; i < num; i++)
            {
                cout << "   Opponent " << i + 1 << ": " << bot_hands[i].size() << endl;
            }
            cout << endl << name << "'s hand: ";
            hand.display_hand();
            cout << endl;
            card_not_found = true;
            while (card_not_found)
            {
                valid = true;
                if (called_color == NONE)
                {
                    cout << endl << "Card to play on: ";
                    upCard.printCard();
                }
                else
                {
                    cout << endl << "Color to play on: ";
                    if (called_color == RED)
                    {
                        cout << "RED";
                    }
                    else if (called_color == BLUE)
                    {
                        cout << "BLUE";
                    }
                    else if (called_color == GREEN)
                    {
                        cout << "GREEN";
                    }
                    else if (called_color == YELLOW)
                    {
                        cout << "YELLOW";
                    }
                }
                cout << endl << "Enter a card to play or 'DRAW' if all cards are unplayable: ";
                cin >> input1;
                if (input1.compare("DRAW") == 0)
                {
                    hand.addCard(deck.draw());
                    card_not_found = false;
                    Card played(INVALID);
                    played_card = played;
                }
                else if (input1.compare("WILD") == 0)
                {
                    Card played(NONE, WILD);
                    played_card = played;
                    card_not_found = false;
                }
                else if (input1.compare("WILD_D4") == 0)
                {
                    Card played(NONE, WILD_D4);
                    played_card = played;
                    card_not_found = false;
                }
                else
                {
                    cin >> input2;
                    if (input1.compare("RED") == 0)
                    {
                        c = RED;
                    }
                    else if (input1.compare("YELLOW") == 0)
                    {
                        c = YELLOW;
                    }
                    else if (input1.compare("BLUE") == 0)
                    {
                        c = BLUE;
                    }
                    else if (input1.compare("GREEN") == 0)
                    {
                        c = GREEN;
                    }
                    else
                    {
                        cout << "Invalid card.";
                        valid = false;
                    }
                    if (valid)
                    {
                        if (input2.size() == 1)
                        {
                            input_num = input2[0] - '0';
                            if (input_num < 10)
                            {
                                Card played(c, input_num);
                                played_card = played;
                                card_not_found = false;
                            }
                            else
                            {
                                cout << "Invalid card.";
                            }
                        }
                        else if (input2.compare("SKIP") == 0)
                        {
                            Card played(c, SKIP);
                            played_card = played;
                            card_not_found = false;
                        }
                        else if (input2.compare("REVERSE") == 0)
                        {
                            Card played(c, REVERSE);
                            played_card = played;
                            card_not_found = false;
                        }
                        else if (input2.compare("DRAW_TWO") == 0)
                        {
                            Card played(c, DRAW_TWO);
                            played_card = played;
                            card_not_found = false;
                        }
                        else
                        {
                            cout << "Invalid card.";
                        }
                    }
                }
                if (not card_not_found && played_card.getValidity() == VALID)
                {
                    if (not hand.isIn(played_card))
                    {
                        card_not_found = true;
                        cout << "Invalid card. That card is not in your hand.";
                    }
                    else if (upCard.getColor() != NONE && not played_card.canPlayOn(upCard))
                    {
                        card_not_found = true;
                        cout << "Invalid card. That card cannot be played.";
                    }
                    else if (called_color != NONE && not played_card.canPlayColor(called_color))
                    {
                        card_not_found = true;
                        cout << "Invalid card. Must play on the specified color.";
                    }
                }
            } // valid card entered
            if (played_card.getValidity() == VALID)
            {
                deck.discard(upCard);
                upCard = played_card;
                hand.remove(played_card);
                called_color = NONE;
                if (bot_turns[0] == 1)
                {
                    bot_after = 0;
                }
                else
                {
                    bot_after = num - 1;
                }
                if (hand.isEmpty())
                {
                    cout << name << " won!!!!" << endl;
                    game_going = false;
                }
                else if (played_card.getRank() == WILD || played_card.getRank() == WILD_D4)
                {
                    color_not_found = true;
                    while (color_not_found)
                    {
                        cout << "Enter a valid color: ";
                        cin >> input1;
                        if (input1.compare("RED") == 0)
                        {
                            called_color = RED;
                            color_not_found = false;
                        }
                        else if (input1.compare("YELLOW") == 0)
                        {
                            called_color = YELLOW;
                            color_not_found = false;
                        }
                        else if (input1.compare("BLUE") == 0)
                        {
                            called_color = BLUE;
                            color_not_found = false;
                        }
                        else if (input1.compare("GREEN") == 0)
                        {
                            called_color = GREEN;
                            color_not_found = false;
                        }
                        else
                        {
                            cout << "Invalid color." << endl;
                        }
                    }
                    if (played_card.getRank() == WILD_D4)
                    {
                        for (i = 0; i < 4; i++)
                        {
                            bot_hands[bot_after].addCard(deck.draw());
                        }
                        player_turn += num - 1;
                        bot_turns[bot_after] = num + factor;
                        for (i = 0; i < num; i++)
                        {
                            bot_turns[i] -= factor;
                        }
                    }
                    else
                    {
                        player_turn += num;
                        for (i = 0; i < num; i++)
                        {
                            bot_turns[i] -= 1;
                        }
                    }
                }//wild card played
                else if (played_card.getRank() == DRAW_TWO)
                {
                    for (i = 0; i < 2; i++)
                    {
                        bot_hands[bot_after].addCard(deck.draw());
                    }
                    player_turn += num - 1;
                    bot_turns[bot_after] = num + factor;
                    for (i = 0; i < num; i++)
                    {
                        bot_turns[i] -= factor;
                    }
                }//draw 2 played
                else if (played_card.getRank() == SKIP)
                {
                    player_turn = num - 1;
                    bot_turns[bot_after] = num + factor;
                    for (i = 0; i < num; i++)
                    {
                        bot_turns[i] -= factor;
                    }
                }//skip played
                else if (played_card.getRank() == REVERSE)
                {
                    for (i = 0; i < num; i++)
                    {
                        bot_turns[i] = num - bot_turns[i];
                    }
                    player_turn = num;
                }//reverse played
                else
                {
                    player_turn = num;
                    for (i = 0; i < num; i++)
                    {
                        bot_turns[i] -= 1;
                    }
                }//number card played
            }//card played, not drawn
            else
            {
                player_turn = num;
                for (i = 0; i < num; i++)
                {
                    bot_turns[i] -= 1;
                }
            }
        }//player's turn
        else
        {
            for (i = 0; i < num; i++)
            {
                if (bot_turns[i] == 0)
                {
                    bot_playing = i;
                }
                if (bot_turns[i] == 1)
                {
                    bot_after = i;
                }
            }
            played_card = bot.robotPlay(bot_hands[bot_playing].getCards(), upCard, called_color);
            if (played_card.getValidity() == INVALID)
            {
                bot_hands[bot_playing].addCard(deck.draw());
                cout << endl << "Opponent " << bot_playing + 1 << " drew a card" << endl;
                player_turn -= 1;
                bot_turns[bot_playing] = num + 1;
                for (i = 0; i < num; i++)
                {
                    bot_turns[i] -= 1;
                }
            }
            else
            {
                deck.discard(upCard);
                upCard = played_card;
                bot_hands[bot_playing].remove(played_card);
                called_color = NONE;
                cout << endl << "Opponent " << bot_playing + 1 << " played ";
                played_card.printCard();
                cout << endl;
                if (bot_hands[bot_playing].isEmpty())
                {
                    cout << endl << "Opponent " << bot_playing + 1 << " won :(" << endl;
                    vector <int> scores;
                    for (int numPlayers = 0; numPlayers < bot_hands.size(); numPlayers++ )
                    {
                        scores.push_back(bot_hands[numPlayers].countCards());
                    }
                    int playerRank = 1;
                    for (int numPlayers = 0; numPlayers < bot_hands.size(); numPlayers++ )
                    {
                        if (scores[numPlayers] < hand.countCards())
                        {
                            playerRank++;
                        }
                    }
                    cout << name << ", you came in rank " << playerRank << ".  Better luck next time..." << endl;
                    game_going = false;
                }
                else
                {
                    if (played_card.getRank() == WILD || played_card.getRank() == WILD_D4)
                    {
                        called_color = bot.callColor(bot_hands[bot_playing]);
                        if (played_card.getRank() == WILD_D4)
                        {
                            if ((bot_playing == num - 1 && bot_turns[bot_playing - 1] == num) || (bot_playing == 0 &&  bot_turns[bot_playing + 1] == num))
                            {
                                for (i = 0; i < 4; i++)
                                {
                                    hand.addCard(deck.draw());
                                }
                                player_turn = num + factor;
                            }
                            else
                            {
                                for (i = 0; i < 4; i++)
                                {
                                    bot_hands[bot_after].addCard(deck.draw());
                                }
                                bot_turns[bot_after] = num + factor;
                            }
                            player_turn -= factor;
                            bot_turns[bot_playing] = num + 1;
                            for (i = 0; i < num; i++)
                            {
                                bot_turns[i] -= factor;
                            }
                        }
                        else
                        {
                            player_turn -= 1;
                            bot_turns[bot_playing] = num + 1;
                            for (i = 0; i < num; i++)
                            {
                                bot_turns[i] -= 1;
                            }
                        }
                    }//wild card played
                    else if (played_card.getRank() == DRAW_TWO)
                    {
                        if ((bot_playing == num - 1 && bot_turns[bot_playing - 1] == num) || (bot_playing == 0 &&  bot_turns[bot_playing + 1] == num))
                        {
                            for (i = 0; i < 2; i++)
                            {
                                hand.addCard(deck.draw());
                            }
                            player_turn = num + factor;
                        }
                        else
                        {
                            
                            for (i = 0; i < 2; i++)
                            {
                                bot_hands[bot_after].addCard(deck.draw());
                            }
                            bot_turns[bot_after] = num + factor;
                        }
                        player_turn -= factor;
                        bot_turns[bot_playing] = num + 1;
                        for (i = 0; i < num; i++)
                        {
                            bot_turns[i] -= factor;
                        }
                    }//draw 2 played
                    else if (played_card.getRank() == SKIP)
                    {
                        if ((bot_playing == num - 1 && bot_turns[bot_playing - 1] == num) || (bot_playing == 0 &&  bot_turns[bot_playing + 1] == num))
                        {
                            player_turn = num + factor;
                        }
                        else
                        {
                            bot_turns[bot_after] = num + factor;
                        }
                        player_turn -= factor;
                        bot_turns[bot_playing] = num + 1;
                        for (i = 0; i < num; i++)
                        {
                            bot_turns[i] -= factor;
                        }
                    }//skip played
                    else if (played_card.getRank() == REVERSE)
                    {
                        for (i = 0; i < num; i++)
                        {
                            bot_turns[i] = num - bot_turns[i];
                        }
                        player_turn = num - player_turn;
                    }//reverse played
                    else
                    {
                        player_turn -= 1;
                        bot_turns[bot_playing] = num + 1;
                        for (i = 0; i < num; i++)
                        {
                            bot_turns[i] -= 1;
                        }
                    }//number card played
                }//if bot didnt win yet
            }//if bot played a card
            
        }//bot turn
    }//actual game function
}



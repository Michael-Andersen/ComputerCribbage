
#ifndef _CARD_H_
#define _CARD_H_
#include <string>


enum class Suit
{
	DIAMONDS,
	CLUBS,
	HEARTS,
	SPADES,
	JOKER = 100

};

enum class Number
{
	ACE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	TEN = 10,
	JACK = 11,
	QUEEN = 12,
	KING = 13,
	JOKER = 100

};

class Card
{
	Suit suit;
	Number number;
public:
	Card();
	Card(Suit tsuit, Number tnumber);
	Suit getSuit();
	std::string printSuit();
	std::string printNumber();
	int getValue();
	std::string print();
	Number getNumber();
};
#endif


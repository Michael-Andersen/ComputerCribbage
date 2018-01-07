#include "stdafx.h"
#include "Card.h"


Card::Card() {
	suit = Suit::JOKER;
	number = Number::JOKER;
}

Card::Card(Suit tsuit, Number tnumber)
{
	suit = tsuit;
	number = tnumber;
}



Suit Card::getSuit()
{
	return suit;

}

std::string Card::printSuit()
{
	switch (suit)
	{
	case Suit::DIAMONDS:
		return "Diamonds";
	case Suit::CLUBS:
		return "Clubs";
	case Suit::HEARTS:
		return "Hearts";
	case Suit::SPADES:
		return "Spades";
	default:
		return "Joker";
	}

}

std::string Card::printNumber()
{
	switch (number)
	{
	case Number::ACE:
		return "Ace";
	case Number::TWO:
		return "Two";
	case Number::THREE:
		return "Three";
	case Number::FOUR:
		return "Four";
	case Number::FIVE:
		return "Five";
	case Number::SIX:
		return "Six";
	case Number::SEVEN:
		return "Seven";
	case Number::EIGHT:
		return "Eight";
	case Number::NINE:
		return "Nine";
	case Number::TEN:
		return "Ten";
	case Number::JACK:
		return "Jack";
	case Number::QUEEN:
		return "Queen";
	case Number::KING:
		return "King";
	default:
		return "Joker";

	}

}

int Card::getValue()
{
	switch (number)
	{
	case Number::ACE:
		return 1;
	case Number::TWO:
		return 2;
	case Number::THREE:
		return 3;
	case Number::FOUR:
		return 4;
	case Number::FIVE:
		return 5;
	case Number::SIX:
		return 6;
	case Number::SEVEN:
		return 7;
	case Number::EIGHT:
		return 8;
	case Number::NINE:
		return 9;
	case Number::TEN:
		return 10;
	case Number::JACK:
		return 10;
	case Number::QUEEN:
		return 10;
	case Number::KING:
		return 10;
	default:
		return 100;

	}
}

std::string Card::print()
{
	return printNumber() + " of " + printSuit();
}

Number Card::getNumber()
{
	return number;

}




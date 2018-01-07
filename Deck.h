#ifndef _DECK_H_
#define _DECK_H_
#include "Card.h"
#include <vector>

void sortCards(std::vector<Card> &hand);

class Deck
{
	std::vector<Card> deck;
public:
	Deck();
	void printCards();
	Card dealCard();
	std::vector<Card> dealStream(int n);
};

#endif

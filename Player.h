#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Deck.h"
#include <vector>

class Player
{
	std::vector<Card> hand;
	int score;
	bool isComputer;

public:
	Player();
	void setComputer();
	bool check();
	void clearHand();
	void addCard(Card c);
	int getScore();
	void updateScore(int n);
	std::vector<Card> getHand();
	std::string printHand();
	void sortHand();
	Card donateCard(int i);
	Card playCard(int i);
};
#endif

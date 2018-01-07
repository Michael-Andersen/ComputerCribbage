#ifndef _GAME_H_
#define _GAME_H_
#include "Player.h"

class Game
{
	Player user;
	Player computer;
	int round;
	int userRoundScore;
	int computerRoundScore;
	int field;
	Card cut;
	bool lastPlayerComputer;
	bool userGo;
	std::vector<Card> stream;
	std::vector<Card> crib;
	std::string userHand;
	std::string computerHand;
	void dealAHand();
	void setCut();
	Card getCut();
	int calculateValue(Card x, Card y);
	int calculateFifteens(std::vector<Card> n);
	int calculatePairs(std::vector<Card> n);
	int calculateRuns(std::vector<Card> n);
	int calculateValue(std::vector<Card> n, bool crib);
	int calculateUserHand();
	int calculateCrib();
	int calculateComputerHand();
	void getUserDonation();
	void getComputerDonations();
	std::string printCrib();
	std::string printUserHand();
	void printScores();
	std::string printComputerHand();
	int checkPairs(Card c);
	int checkRuns(Card c);
	int cardInPlay(Card c);
	int testPlayCard(Card c);
	void computerSelect();
	void userSelect();
	void endRound();
	void playRound();

public:
	Game();
	void start();
};
#endif
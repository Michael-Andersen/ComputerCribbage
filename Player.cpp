#include "stdafx.h"
#include "Player.h"
#include <sstream>


Player::Player()
{
	hand = {};
	score = 0;
	isComputer = 0;
}
void Player::setComputer() {
	isComputer = 1;
}
bool Player::check() {
	return isComputer;
}
void Player::clearHand()
{
	hand.clear();
}
void Player::addCard(Card c) {
	hand.push_back(c);

}
int Player::getScore() {
	return score;
}

void Player::updateScore(int n) {
	score += n;
}

std::vector<Card> Player::getHand()
{
	return hand;
}
std::string Player::printHand()
{
	std::stringstream result;
	for (size_t i = 0; i < hand.size(); i++)
	{
		result << i << ": " << hand[i].print() << "\n";
	}
	std::string s = result.str();
	return s;
}
void Player::sortHand()
{
	sortCards(hand);
}

Card Player::donateCard(int i)
{
	Card result = hand.at(i);
	hand.erase(hand.begin() + i);
	return result;

}

Card Player::playCard(int i)
{
	Card result = hand.at(i);
	hand.erase(hand.begin() + i);
	return result;
}


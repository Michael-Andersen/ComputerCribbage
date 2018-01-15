#include "stdafx.h"
#include "Deck.h"
#include <random>
#include <iostream>



void sortCards(std::vector<Card> &hand) {
	int pos_min;
	Card temp;

	for (size_t i = 0; i < hand.size() - 1; i++)
	{
		pos_min = i;

		for (size_t j = i + 1; j < hand.size(); j++)
		{

			if (static_cast<int>(hand[j].getNumber()) > static_cast<int>(hand[pos_min].getNumber()))
				pos_min = j;
			
		}

		if (pos_min != i)
		{
			temp = hand[i];
			hand[i] = hand[pos_min];
			hand[pos_min] = temp;
		}
	}
}

Deck::Deck() {
	for (int i = 0; i < 4; i++)
	{
		for (size_t j = 1; j < 14; j++)
		{
			deck.push_back(Card(static_cast<Suit>(i), static_cast<Number>(j)));
		}
	}
}

void Deck::printCards()
{
	for (auto &c : deck)
	{
		std::cout << c.print() << ", ";

	}
	std::cout << "\n" << deck.size();
}

Card Deck::dealCard()
{
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> distr(0, deck.size() - 1);
	int pos = distr(mersenne);
	Card result = deck.at(pos);
	deck.erase(deck.begin() + pos);
	return result;
}

std::vector<Card> Deck::dealStream(int n)
{
	std::vector<Card> result = {};
	for (int i = 0; i < n; i++)
	{
		result.push_back(this->dealCard());
	}
	return result;
}

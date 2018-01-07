#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <sstream>



Game::Game() {
	field = 0;
	round = 0;
	userRoundScore = 0;
	computerRoundScore = 0;
	user = Player();
	computer = Player();
	computer.setComputer();
	cut = Card();
	userHand = "";
	computerHand = "";
	stream = {};
	lastPlayerComputer = 0;
	userGo = 0;
}
void Game::dealAHand()
{
	field = 0;
	stream.clear();
	crib.clear();
	cut = Card();
	user.clearHand();
	computer.clearHand();
	Deck deck;
	stream = deck.dealStream(13);
	if (round % 2 == 0) {
		for (int i = 0; i < 12; i++){
		 	if (i % 2 == 0) {
				user.addCard(stream.at(i));
			}
			else {
				computer.addCard(stream.at(i));
			}
		}
	}
	else {
		for (int i = 0; i < 12; i++) {
			if (i % 2 == 0) {
				computer.addCard(stream.at(i));

			} else	{
				user.addCard(stream.at(i));
			}
		}
	}
	computer.sortHand();
	user.sortHand();
	round++;
}

void Game::setCut()
{
	cut = stream.at(12);
}

Card Game::getCut()
{
	return cut;
}

int Game::calculateValue(Card x, Card y)
{
	int value = 0;
	if (x.getValue() + y.getValue() == 15)
	{
		value += 2;
	}
	if (static_cast<int>(x.getNumber()) == static_cast<int>(y.getNumber()))
	{
		value += 2;
	}
	return value;
}
int Game::calculateFifteens(std::vector<Card> n) {
	int value = 0;
	int allCards = n[0].getValue() + n[1].getValue() + n[2].getValue() + n[3].getValue() + n[4].getValue();
	if (allCards == 15) {
		value += 2;
	}
	else {
		for (int i = 0; i < n.size(); i++) {
			if (allCards - n[i].getValue() == 15) {
				value += 2;
			}
		}

		for (int i = 0; i < n.size() - 2; i++) {
			for (int j = i + 1; j < n.size() - 1; j++) {
				for (int k = j + 1; k < n.size(); k++) {
					if (n[i].getValue() + n[j].getValue() + n[k].getValue() == 15) {
						value += 2;
					}
				}
			}
		}

		for (int i = 0; i < n.size() - 1; i++) {
			for (int j = i + 1; j < n.size(); j++) {
				if (n[i].getValue() + n[j].getValue() == 15) {
					value += 2;
				}
			}
		}
	}
	return value;
}

int Game::calculatePairs(std::vector<Card> n) {
	int value = 0;
	for (int i = 0; i < n.size() - 1; i++) {
		for (int j = i + 1; j < n.size(); j++) {
			if (n[i].getNumber() == n[j].getNumber()) {
				value += 2;
			}
		}
	}
	return value;
}

int Game::calculateRuns(std::vector<Card> n) {
	int value = 0;
	int count = 1;
	int biggest = 1;
	int pair = 1;
	bool triple = 0;
	for (int i = 0; i < n.size() - 1; i++) {
		if (static_cast<int>(n[i].getNumber()) - static_cast<int>(n[i + 1].getNumber()) == 1) {
			count++;
			triple = 0;
		}
		else if (static_cast<int>(n[i].getNumber()) - static_cast<int>(n[i + 1].getNumber()) != 0) {
			if (count > biggest) {
				biggest = count;
			}
			if (i == 1) {
				pair = 1;
			}
			count = 1;
			triple = 0;
		}
		else {
			pair *= 2;
			if (triple) {
				pair = 3;
			}
			triple = 1;
			if (count == 1 && i == 3) {
				pair = 1;
			}
		}
	}
		if (count > biggest) {
			biggest = count;
		}
	    if (biggest > 2) {
			biggest *= pair;
			value += biggest;
		}
		
	return value;
}

int Game::calculateValue(std::vector<Card> n, bool crib)
{
	int value = 0;
	if (!crib && static_cast<int>(n[0].getSuit()) == static_cast<int>(n[1].getSuit()) &&
		static_cast<int>(n[0].getSuit()) == static_cast<int>(n[2].getSuit()) &&
		static_cast<int>(n[0].getSuit()) == static_cast<int>(n[3].getSuit()))
	{
		value += 4;
		if (static_cast<int>(n[0].getSuit()) == static_cast<int>(cut.getSuit()))
		{
			value += 1;
		}
	}
	n.push_back(cut);
	sortCards(n);
	if (crib && static_cast<int>(n[0].getSuit()) == static_cast<int>(n[1].getSuit()) &&
		static_cast<int>(n[0].getSuit()) == static_cast<int>(n[2].getSuit()) &&
		static_cast<int>(n[0].getSuit()) == static_cast<int>(n[3].getSuit()) &&
		static_cast<int>(n[0].getSuit()) == static_cast<int>(n[4].getSuit()))
	{
		value += 5;
	}
	
	value += calculateFifteens(n);
	value += calculatePairs(n);
	value += calculateRuns(n);

	if (static_cast<int>(cut.getNumber()) != static_cast<int>(Number::JACK)) {
		for (int i = 0; i < n.size(); i++) {
			if (static_cast<int>(n[i].getNumber()) == static_cast<int>(Number::JACK))
			{
				if (static_cast<int>(n[i].getSuit()) == static_cast<int>(cut.getSuit()))
				{
					value += 1;
				}
			}
		}
	}
	return value;
}
int Game::calculateUserHand()
{
	int temp = calculateValue(user.getHand(), false);
	userRoundScore = temp;
	return temp;
}
int Game::calculateCrib()
{
	int temp = calculateValue(crib, true);
	return temp;
}
int Game::calculateComputerHand()
{
	int temp = calculateValue(computer.getHand(), false);
	computerRoundScore = temp;
	return temp;
}
void Game::getUserDonation()
{
	std::cout << "Choose first card to put in crib: ";
	int temp;
	std::cin >> temp;
	std::cout << "\n";
	std::cin.ignore(32767, '\n');
	std::cout << "Choose second card to put in crib: ";
	int temp2;
	std::cin >> temp2;
	if (temp > temp2) {
		crib.push_back(user.donateCard(temp));
		crib.push_back(user.donateCard(temp2));
	}
	else {
		crib.push_back(user.donateCard(temp2));
		crib.push_back(user.donateCard(temp));
	}
}
void Game::getComputerDonations()
{
	std::vector<Card> result;
	int temp = 0;
	int donate1 = 4;
	int donate2 = 5;
	if (round % 2 == 0) {
		for (int i = 5; i > 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				result = computer.getHand();
				result.erase(result.begin() + i);
				result.erase(result.begin() + j);
				if (calculateValue(result, false) + calculateValue(computer.getHand().at(j), computer.getHand().at(i))
					>= temp) {
					temp = calculateValue(result, false)
						+ calculateValue(computer.getHand().at(i - 1), computer.getHand().at(i));
					donate1 = j;
					donate2 = i;
				}
			}
		}
		crib.push_back(computer.donateCard(donate2));
		crib.push_back(computer.donateCard(donate1));
	}
	else {
		for (int i = 5; i > 0; i--) {
			for (int j = i - 1; j >= 0; j--) {
				result = computer.getHand();
				result.erase(result.begin() + i);
				result.erase(result.begin() + j);
				if (calculateValue(result, false) - calculateValue(computer.getHand().at(j), computer.getHand().at(i))
					>= temp) {
					temp = calculateValue(result, false)
						- calculateValue(computer.getHand().at(i - 1), computer.getHand().at(i));
					donate1 = j;
					donate2 = i;
				}
			}
		}
		crib.push_back(computer.donateCard(donate2));
		crib.push_back(computer.donateCard(donate1));
	}
}

std::string Game::printCrib()
{
	std::stringstream result;
	for (int i = 0; i < crib.size(); i++)
	{
		result << i << ": " << crib[i].print() << "\n";
	}
	std::string s = result.str();
	return s;
}
std::string Game::printUserHand()
{
	std::string result = "User's Hand:\n";
	result += user.printHand();
	return result;

}
void Game::printScores() {
	std::cout << "User score: " << user.getScore() << "\n";
	std::cout << "Computer score: " << computer.getScore() << "\n";
}
std::string Game::printComputerHand()
{
	std::string result = "Computer's Hand:\n";
	result += computer.printHand();
	return result;
}

int Game::checkPairs(Card c) {
	int points = 0;
	int pairs = 0;
	for (int i = 1; i <= stream.size() && i < 4; i++) {
		if (static_cast<int>(c.getNumber()) == static_cast<int>(stream.at(stream.size() - i).getNumber())) {
			pairs++;
		}
		else {
			break;
		}
	}
	switch (pairs) {
	case 1:
		points += 2;
		break;
	case 2:
		points += 6;
		break;
	case 3:
		points += 12;
		break;
	}
	return points;
}

int Game::checkRuns(Card c) {
	int points = 0;
	stream.push_back(c);
	if (stream.size() > 2) {
		std::vector<Card> temp = stream;
		sortCards(temp);
		int counter = 0;
		for (int k = 0; k < temp.size() - 1; k++) {
			if (static_cast<int>(temp[k].getNumber()) - static_cast<int>(temp[k + 1].getNumber()) == 1)
			{
				counter++;
			}
		}
		if (counter == temp.size() - 1) {
			points += temp.size();
		}
		else {
			counter = 0;
			temp = stream;
			std::vector<Card> temp2;
			for (int i = 1; i < stream.size() - 2; i++) {
				for (int j = i; j < stream.size(); j++) {
					temp2.push_back(stream[j]);
				}
				sortCards(temp2);
				for (int k = 0; k < temp2.size() - 1; k++) {
					if (static_cast<int>(temp2[k].getNumber()) - static_cast<int>(temp2[k + 1].getNumber()) == 1)
					{
						counter++;
					}
				}
				if (counter == temp2.size() - 1) {
					points += temp2.size();
					break;
				}
				else {
					counter = 0;
				}
				temp2.clear();
			}
		}
	}
	return points;
}

int Game::cardInPlay(Card c) {
	int points = 0;

	field += c.getValue();
	if (field == 15) {
		points += 2;
	}
	points += checkPairs(c);
	points += checkRuns(c);

	if (field == 31) {
		points += 2;
	}
	return points;
}

int Game::testPlayCard(Card c) {
	int result = cardInPlay(c);
	stream.pop_back();
	field -= c.getValue();
	return result;
}

void Game::computerSelect() {
	int earned = 0;
	std::vector<Card> temp;
	for (int i = 0; i < computer.getHand().size(); i++) {
		if (computer.getHand().at(i).getValue() + field <= 31)
		{
			temp.push_back(computer.getHand().at(i));
		}
	}
	int bestCard = 0;
	if (!temp.size()) {
		userGo = 0;
		int count = 0;
		for (int i = 0; i < user.getHand().size(); i++) {
			if (field + user.getHand()[i].getValue() <= 31) {
				count++;
				break;
			}
		}
		if (count) {
			std::cout << "Go." << "\n";
			return;
		}
		else {
			field = 0;
			stream.clear();
			std::cout << "Go." << "\n";
			if (lastPlayerComputer) {
				computer.updateScore(1);
				std::cout << "1 point for Computer" << "\n";
				if (user.getScore() >= 121 || computer.getScore() >= 121) {
					return;
				}
				printScores();
			}
			else {
				user.updateScore(1);
				std::cout << "1 point for User" << "\n";
				if (user.getScore() >= 121 || computer.getScore() >= 121) {
					return;
				}
				printScores();
			}
			std::cout << "Count: " << field << "\n";
		}
	}
	if (field == 0) {
		int play2 = -1;
		for (int y = 0; y < computer.getHand().size(); y++) {
			if (computer.getHand().at(y).getValue() != 5) {
				play2 = y;
				break;
			}
		}
		if (play2 == -1) {
			play2 = 0;
		}
		Card toPlay2 = computer.playCard(play2);
		earned = cardInPlay(toPlay2);
		if (field != 0 && user.getHand().size() == 0 && computer.getHand().size() == 0) {
			earned += 1;
		}
		std::cout << "Computer Played: " << toPlay2.print() << "\n";
		lastPlayerComputer = 1;
		std::cout << "Count: " << field << "\n";
		if (earned > 0) {
			std::cout << earned << " points\n";
			computer.updateScore(earned);
			if (user.getScore() >= 121 || computer.getScore() >= 121) {
				return;
			}
			printScores();
		}
	}
	else {
		for (int j = 0; j < temp.size(); j++) {
			int attempt = testPlayCard(temp.at(j));
			if (attempt > earned) {
				bestCard = j;
			}
		}
		earned = cardInPlay(temp.at(bestCard));
		std::cout << "Computer Played: " << temp.at(bestCard).print() << "\n";
		lastPlayerComputer = 1;
		std::cout << "Count: " << field << "\n";
		int place = 0;
		for (int z = 0; z < computer.getHand().size(); z++) {
			if (static_cast<int>(temp.at(bestCard).getNumber()) == static_cast<int>(computer.getHand().at(z).getNumber())
				&& static_cast<int>(temp.at(bestCard).getSuit()) == static_cast<int>(computer.getHand().at(z).getSuit()))
			{
				computer.playCard(z);
				break;
			}
		}
		if (field != 0 && user.getHand().size() == 0 && computer.getHand().size() == 0) {
			earned += 1;
		}
		if (earned > 0) {
			std::cout << earned << " points\n";
			computer.updateScore(earned);
			if (user.getScore() >= 121 || computer.getScore() >= 121) {
				return;
			}
			printScores();
		}
		if (field == 31) {
			field = 0;
			stream.clear();
			userGo = 0;
			std::cout << "Count: " << field << "\n";
		}
		if (userGo) {

			if (computer.getHand().size() > 0) {
				computerSelect();
			}
			else {
				std::cout << "Go." << "\n";
				computer.updateScore(1);
				std::cout << "1 point for Computer" << "\n";
				if (user.getScore() >= 121 || computer.getScore() >= 121) {
					return;
				}
				printScores();
			}
		}
	}
}

void Game::userSelect() {
	std::cout << printUserHand() << "\n\n";
	std::cout << "Pick a card to play \n";
	int count = 0;
	for (int i = 0; i < user.getHand().size(); i++) {
		if (field + user.getHand()[i].getValue() <= 31) {
			count++;
			break;
		}
	}
	if (!count) {
		std::cout << "You have no playable cards, enter 9 to Go.\n";
		int go;
		std::cin >> go;
		while (go != 9) {
			std::cout << "That card is not playable, enter 9. \n";
			std::cin.ignore(32767, '\n');
			std::cin >> go;
		}
		std::cin.ignore(32767, '\n');
		if (go == 9) {
			for (int i = 0; i < computer.getHand().size(); i++) {
				if (field + computer.getHand()[i].getValue() <= 31) {
					count++;
					break;
				}
			}
			if (count) {
				std::cout << "Go." << "\n";
				userGo = 1;
				return;
			}
			else {
				field = 0;
				stream.clear();
				std::cout << "Go." << "\n";
				if (lastPlayerComputer) {
					computer.updateScore(1);
					std::cout << "1 point for Computer" << "\n";
					if (user.getScore() >= 121 || computer.getScore() >= 121) {
						return;
					}
					printScores();
				}
				else {
					user.updateScore(1);
					std::cout << "1 point for User" << "\n";
					if (user.getScore() >= 121 || computer.getScore() >= 121) {
						return;
					}
					printScores();
				}
				std::cout << "Count: " << field << "\n";
			}
			std::cout << printUserHand() << "\n\n";
			std::cout << "Pick a card to play \n";
		}
	}

	int temp;
	std::cin >> temp;
	while (count && user.getHand().at(temp).getValue() + field > 31) {
		std::cout << "That card is not playable, pick another \n";
		std::cin.ignore(32767, '\n');
		std::cin >> temp;
	}
	Card toPlay = user.playCard(temp);
	int earned = cardInPlay(toPlay);
	if (field != 0 && user.getHand().size() == 0 && computer.getHand().size() == 0) {
		earned += 1;
	}
	std::cout << "User Played: " << toPlay.print() << "\n";
	lastPlayerComputer = 0;
	std::cout << "Count: " << field << "\n";
	if (earned > 0) {
		std::cout << earned << " points\n";
		user.updateScore(earned);
		if (user.getScore() >= 121 || computer.getScore() >= 121) {
			return;
		}
		printScores();
	}
	if (field == 31) {
		field = 0;
		stream.clear();
		std::cout << "Count: " << field << "\n";
	}
}

void Game::endRound() {
	if (round % 2 == 0) {
		std::cout << userHand << "\n";
		std::cout << "with Cut " << cut.print() << "\n";
		std::cout << "Worth " << userRoundScore << " points" << "\n";
		user.updateScore(userRoundScore);
		if (user.getScore() >= 121 || computer.getScore() >= 121) {
			return;
		}
		std::cout << computerHand << "\n";
		std::cout << "with Cut " << cut.print() << "\n";
		std::cout << "Worth " << computerRoundScore << " points" << "\n";
		computer.updateScore(computerRoundScore);
		if (user.getScore() >= 121 || computer.getScore() >= 121) {
			return;
		}
		std::cout << "Computer's crib:\n" << printCrib() << "\n";
		std::cout << "Worth " << calculateCrib() << " points" << "\n";
		computer.updateScore(calculateCrib());
		if (user.getScore() >= 121 || computer.getScore() >= 121) {
			return;
		}
		printScores();
	}
	else {
		std::cout << computerHand << "\n";
		std::cout << "with Cut " << cut.print() << "\n";
		std::cout << "Worth " << computerRoundScore << " points" << "\n";
		computer.updateScore(computerRoundScore);
		if (user.getScore() >= 121 || computer.getScore() >= 121) {
			return;
		}
		std::cout << userHand << "\n";
		std::cout << "with Cut " << cut.print() << "\n";
		std::cout << "Worth " << userRoundScore << " points" << "\n";
		user.updateScore(userRoundScore);
		if (user.getScore() >= 121 || computer.getScore() >= 121) {
			return;
		}
		std::cout << "User's crib:\n" << printCrib() << "\n";
		int cribpoints = calculateCrib();
		std::cout << "Worth " << cribpoints << " points" << "\n";
		user.updateScore(cribpoints);
		if (user.getScore() >= 121 || computer.getScore() >= 121) {
			return;
		}
		printScores();
	}
}

void Game::playRound()
{
	dealAHand();
	std::cout << printUserHand();
	getUserDonation();
	getComputerDonations();
	userHand = printUserHand();
	computerHand = printComputerHand();
	setCut();
	stream.clear();
	userRoundScore = calculateUserHand();
	computerRoundScore = calculateComputerHand();
	std::cout << "Cut is the " << cut.print() << "\n";
	if (static_cast<int>(cut.getNumber()) == 11) {
		if (round % 2 == 0)
		{
			std::cout << "2 points for computer\n";
			computer.updateScore(2);
			if (computer.getScore() >= 121) {
				return;
			}
		}
		else {
			std::cout << "2 points for user\n";
			user.updateScore(2);
			if (user.getScore() >= 121) {
				return;
			}
		}
		printScores();
	}
	userGo = 0;
	if (round % 2 == 0) {
		while (user.getHand().size() > 0 || computer.getHand().size() > 0)
		{
			if (user.getHand().size() > 0) {
				userSelect();
				if (user.getScore() >= 121 || computer.getScore() >= 121) {
					return;
				}
			}
			if (computer.getHand().size() > 0) {
				computerSelect();
				if (user.getScore() >= 121 || computer.getScore() >= 121) {
					return;
				}
			}
		}

	}
	else {
		while (user.getHand().size() > 0 || computer.getHand().size() > 0)
		{
			if (computer.getHand().size() > 0) {
				computerSelect();
				if (user.getScore() >= 121 || computer.getScore() >= 121) {
					return;
				}
			}
			if (user.getHand().size() > 0) {
				userSelect();
				if (user.getScore() >= 121 || computer.getScore() >= 121) {
					return;
				}
			}
		}
	}
	endRound();
}

void Game::start() {
	std::cout << "Welcome to Cribbage!\n\n";
	while (user.getScore() < 121 && computer.getScore() < 121) {
		playRound();
	}
	if (user.getScore() > computer.getScore()) {
		std::cout << "\nUser has won the game!\n";
		if (computer.getScore() < 61) {
			std::cout << "Computer was double skunked!\n";
		}
		else if (computer.getScore() < 91) {
			std::cout << "Computer was skunked!\n";
		}
		printScores();
	}
	else {
		std::cout << "\nComputer has won the game!\n";
		if (user.getScore() < 61) {
			std::cout << "User was double skunked!\n";
		}
		else if (user.getScore() < 91) {
			std::cout << "User was skunked!\n";
		}
		printScores();
	}
}
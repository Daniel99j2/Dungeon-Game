//
// Created by dj on 21/09/2025.
//

#pragma once

#include <functional>
#include <string>

class Card {
public:
	enum CardType {
		COMMON,
		UNCOMMON,
		RARE,
		LEGENDARY,
		PURCHASED,
		BANE
	};

	Card(const std::string &name, const std::string &desc, const CardType &type, const bool &permanent,
	     const bool &ethereal, const int &maxCount, const int &timeActive, const int &cost, const std::function<void()> &onStarted,
	     const std::function<void()> &onTick, const std::function<void()> &onEnd);

	std::string name;
	std::string desc;
	CardType type;
	bool permanent;
	bool ethereal;
	int maxCount;
	int timeActive;
	int cost;
	std::function<void()> onStarted;
	std::function<void()> onTick;
	std::function<void()> onEnd;

	bool operator==(const Card &other) const {
		return this->name == other.name;
	}
};

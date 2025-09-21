//
// Created by dj on 21/09/2025.
//

#include "Card.h"

Card::Card(const std::string &name, const std::string &desc, const CardType &type, const bool &permanent,
           const bool &ethereal, const int &maxCount, const int &timeActive, const int &cost, const std::function<void()> &onStarted,
           const std::function<void()> &onTick, const std::function<void()> &onEnd) :
	name(name),
	desc(desc),
	type(type),
	permanent(permanent),
	ethereal(ethereal),
	maxCount(maxCount),
	timeActive(timeActive),
	cost(cost),
	onStarted(onStarted),
	onTick(onTick),
	onEnd(onEnd) {

}
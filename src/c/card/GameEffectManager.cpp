//
// Created by dj on 21/09/2025.
//

#include "GameEffectManager.h"

#include <algorithm>
#include <chrono>
#include <random>

#include "Cards.h"
#include "../util/GenericUtil.h"

void GameEffectManager::addCard(Card *card) {
	pickupPile.push_back(*card);
	shuffleCards();
}

void GameEffectManager::tick() {

}

void GameEffectManager::reset() {
	pickupPile.clear();
	discardPile.clear();
	hazard = 0;
	noise = 0;
	noiseBlock = 0;
	hazardBlock = 0;
	delve = 0;
	focus = 0;
	treasureToGenerate = 0;
	frostToGenerate = 0;
	obtainedTreasure = 0;
	obtainedFrost = 0;
	CARD_PICKUP_TIME = 30;
	timeUntilCardPickup = CARD_PICKUP_TIME;
}

std::vector<GameEffectManager::ActiveCardInstance> GameEffectManager::activeCards;
std::vector<Card> GameEffectManager::pickupPile;
std::vector<Card> GameEffectManager::discardPile;

int GameEffectManager::hazard;
int GameEffectManager::noise;
int GameEffectManager::noiseBlock;
int GameEffectManager::hazardBlock;
int GameEffectManager::delve;
int GameEffectManager::focus;
int GameEffectManager::treasureToGenerate;
int GameEffectManager::frostToGenerate;

int GameEffectManager::obtainedTreasure;
int GameEffectManager::obtainedFrost;

int GameEffectManager::timeUntilCardPickup;

int GameEffectManager::CARD_PICKUP_TIME = 30;

void GameEffectManager::addNoise(int amount) {
}

void GameEffectManager::addHazard(int amount) {

}

void GameEffectManager::discardCards(int cards) {
	for (int i = 0; i < cards; ++i) {
		Card card = pickupPile[0];
		pickupPile.erase(pickupPile.begin());
		discardPile.insert(discardPile.begin(), card);
	}
}

void GameEffectManager::addBaneCard() {
	int random = GenericUtil::randomInt(0, 8);
	if (random == 0) {
		addCard(Cards::LOOSE_FINGERS.get());
	} else if (random == 1) {
		addCard(Cards::OVERLOAD.get());
	} else {
		addCard(Cards::STUMBLE.get());
	}
}

void GameEffectManager::shuffleCards() {
	std::minstd_rand0 generator (GenericUtil::randomRandom());
	std::ranges::shuffle(activeCards, generator);
}
//
// Created by dj on 21/09/2025.
//

#pragma once

#include <vector>

class Card;

class GameEffectManager {
public:
	struct ActiveCardInstance {
		int timeLeft;
		Card* card;
	};

	static std::vector<ActiveCardInstance> activeCards;
	static std::vector<Card> pickupPile;
	static std::vector<Card> discardPile;

	static int hazard;
	static int noise;
	static int hazardBlock;
	static int noiseBlock;
	static int delve;
	static int focus;
	static int treasureToGenerate;
	static int frostToGenerate;

	static int obtainedTreasure;
	static int obtainedFrost;

	static int CARD_PICKUP_TIME;

	static int timeUntilCardPickup;

	static void tick();

	static void addCard(Card* card);

	static void reset();

	static void addNoise(int amount);

	static void addHazard(int amount);

	static void discardCards(int cards);

	static void addBaneCard();

	static void shuffleCards();
};
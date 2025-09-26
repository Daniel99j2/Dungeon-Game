//
// Created by dj on 21/09/2025.
//

#pragma once

#include <memory>
#include <vector>
#include <glm/vec2.hpp>

class Card;

class Cards {
public:
	static std::vector<std::shared_ptr<Card>> cards;

	// BANE
	static std::shared_ptr<Card> STUMBLE;
	static std::shared_ptr<Card> LOOSE_FINGERS;
	static std::shared_ptr<Card> OVERLOAD;

	// COMMON
	static std::shared_ptr<Card> SNEAK;
	static std::shared_ptr<Card> STABILITY;
	static std::shared_ptr<Card> TREASURE_HUNTER;
	static std::shared_ptr<Card> EMBER_SEEKER;
	static std::shared_ptr<Card> STEADY_ADVANCE;
	static std::shared_ptr<Card> MOMENT_OF_CLARITY;

	// UNCOMMON
	static std::shared_ptr<Card> EVASION;
	static std::shared_ptr<Card> SKILLFUL_RETREAT;
	static std::shared_ptr<Card> TUNNEL_VISION;
	static std::shared_ptr<Card> TREAD_LIGHTLY;
	static std::shared_ptr<Card> LOOT_AND_SCOOT;
	static std::shared_ptr<Card> FROST_FOCUS;
	static std::shared_ptr<Card> CALL_OF_THE_DEEP;
	static std::shared_ptr<Card> STONESKIN;
	static std::shared_ptr<Card> SECOND_WIND;
	static std::shared_ptr<Card> BEAST_SENSE;
	static std::shared_ptr<Card> BOUNDING_STRIDES;
	static std::shared_ptr<Card> RECKLESS_CHARGE;
	static std::shared_ptr<Card> MEDITATION;
	static std::shared_ptr<Card> NIMBLE_LOOTING;
	static std::shared_ptr<Card> SMASH_AND_GRAB;
	static std::shared_ptr<Card> QUICKSTEP;
	static std::shared_ptr<Card> SUIT_UP;
	static std::shared_ptr<Card> ADRENALINE_RUSH;

	// RARE
	static std::shared_ptr<Card> WATCHFUL_EYE;
	static std::shared_ptr<Card> SMARTER_EVERY_STEP;
	static std::shared_ptr<Card> WHATEVER_LIES_BENEATH;
	static std::shared_ptr<Card> EERIE_SILENCE;
	static std::shared_ptr<Card> DUNGEON_REPAIRS;
	static std::shared_ptr<Card> OVERCONFIDENCE;
	static std::shared_ptr<Card> NECESSARY_SACRIFICES;
	static std::shared_ptr<Card> HASTE;
	static std::shared_ptr<Card> EYES_ON_THE_PRIZE;
	static std::shared_ptr<Card> VANISH;
	static std::shared_ptr<Card> SILENT_RUNNER;
	static std::shared_ptr<Card> BRILLIANCE;
	static std::shared_ptr<Card> POWER_OF_OBSERVATION;

	// LEGENDARY
	static std::shared_ptr<Card> THE_DARKEST_DEPTHS;
	static std::shared_ptr<Card> AVALANCHE;
	static std::shared_ptr<Card> BEAST_MASTER;
	static std::shared_ptr<Card> ROLLING_FORTUNE;

	// PURCHASED
	static std::shared_ptr<Card> PAY_TO_WIN;
	static std::shared_ptr<Card> TACTICAL_APPROACH;
	static std::shared_ptr<Card> A_SHOT_IN_THE_DARK;


	static std::shared_ptr<Card> DEV_TEST_CARD;

	static void renderCard(const Card &card, glm::vec2 pos, int pxWide);
};

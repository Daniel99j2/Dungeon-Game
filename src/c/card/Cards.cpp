//
// Created by dj on 21/09/2025.
//

import "Cards.h";

#include "../util/GameConstants.h"

std::shared_ptr<Card> make_card(const Card &card) {
	auto shared = std::make_shared<Card>(card);
	Cards::cards.push_back(shared);
	return shared;
}

	std::shared_ptr<Card> Cards::STUMBLE = make_card(Card("Stumble", "Generate +2 💥", Card::CardType::BANE, false, false, -1,
	                                               5, -1,
	                                               []() {
		                                               GameEffectManager::addNoise(1);
	                                               },
	                                               []() {
	                                               }, []() {
	                                               }));

	std::shared_ptr<Card> Cards::LOOSE_FINGERS = make_card(Card("Loose Fingers", "Skips the next card", Card::CardType::BANE,
	                                                     false, false,
	                                                     -1, 5, -1,
	                                                     []() {
	                                                     	GameEffectManager::discardCards(1);
	                                                     	GameEffectManager::timeUntilCardPickup +=
				                                                     GameEffectManager::CARD_PICKUP_TIME;
	                                                     },
	                                                     []() {
	                                                     }, []() {
	                                                     }));

	std::shared_ptr<Card> Cards::OVERLOAD = make_card(Card("Overload", "Skips the next card's positive effects",
	                                                Card::CardType::BANE, false, false,
	                                                -1, 5, -1,
	                                                []() {
		                                                //TODO skip the effects
	                                                },
	                                                []() {
	                                                }, []() {
	                                                }));

	//COMMON

	std::shared_ptr<Card> Cards::SNEAK = make_card(Card("Sneak", "Block +2 💥", Card::CardType::COMMON, false, false,
	                                             5, 5, 7,
	                                             []() {
		                                             GameEffectManager::noiseBlock += 2;
	                                             },
	                                             []() {
	                                             }, []() {
	                                             }));

	std::shared_ptr<Card> Cards::STABILITY = make_card(Card("Stability", "Block +2 ⚠️", Card::CardType::COMMON, false, false,
	                                                 5, 5, 8,
	                                                 []() {
		                                                 GameEffectManager::hazardBlock += 2;
	                                                 },
	                                                 []() {
	                                                 }, []() {
	                                                 }));

	std::shared_ptr<Card> Cards::TREASURE_HUNTER = make_card(Card("Treasure Hunter", "+4 🪙", Card::CardType::COMMON, false,
	                                                       false, 5, 5, 9,
	                                                       []() {
		                                                       GameEffectManager::treasureToGenerate += 4;
	                                                       }, []() {
	                                                       }, []() {
	                                                       }));

	std::shared_ptr<Card> Cards::EMBER_SEEKER = make_card(Card("Ember Seeker", "+2 🔥", Card::CardType::COMMON, false, false,
	                                                    5, 5, 10,
	                                                    []() {
		                                                    GameEffectManager::frostToGenerate += 2;
	                                                    }, []() {
	                                                    }, []() {
	                                                    }));

	std::shared_ptr<Card> Cards::STEADY_ADVANCE = make_card(Card("Steady Advance", "Generate +1 💥\n+5 🪜",
	                                                      Card::CardType::COMMON, true, false, 1, -1, 11,
	                                                      []() {
		                                                      GameEffectManager::addNoise(1);
		                                                      GameEffectManager::delve += 5;
	                                                      }, []() {
	                                                      }, []() {
	                                                      }));

	std::shared_ptr<Card> Cards::MOMENT_OF_CLARITY = make_card(Card("Moment of Clarity",
	                                                         "Block +2 ⚠️\nBlock +2 💥\n+4 🪙\n+2 🔥",
	                                                         Card::CardType::COMMON, false, true, 5, 5, 7,
	                                                         []() {
		                                                         GameEffectManager::hazardBlock += 2;
		                                                         GameEffectManager::noiseBlock += 2;
		                                                         GameEffectManager::treasureToGenerate += 4;
		                                                         GameEffectManager::frostToGenerate += 2;
	                                                         }, []() {
	                                                         }, []() {
	                                                         }));

	// UNCOMMON
	std::shared_ptr<Card> Cards::EVASION = make_card(Card("Evasion", "Block +4 💥", Card::CardType::UNCOMMON, false, false, 3,
	                                               5, 14,
	                                               []() { GameEffectManager::noiseBlock += 4; }, []() {
	                                               }, []() {
	                                               }));

	std::shared_ptr<Card> Cards::SKILLFUL_RETREAT = make_card(Card("Skillful Retreat",
	                                                        "If trophy acquired:\nBlock +1 ⚠️\nGenerate +2 💥",
	                                                        Card::CardType::UNCOMMON, false, false, 1, 5, 15,
	                                                        []() {
		                                                        //TODO: check trophy
	                                                        }, []() {
	                                                        }, []() {
	                                                        }));

	std::shared_ptr<Card> Cards::TUNNEL_VISION = make_card(Card("Tunnel Vision", "+8 🪙\nSkips the next card",
	                                                     Card::CardType::UNCOMMON, false, false, 3, 5, 16,
	                                                     []() {
	                                                     	GameEffectManager::treasureToGenerate += 8;
	                                                     	GameEffectManager::discardCards(1);
	                                                     	GameEffectManager::timeUntilCardPickup +=
				                                                     GameEffectManager::CARD_PICKUP_TIME;
	                                                     }, []() {
	                                                     }, []() {
	                                                     }));

	std::shared_ptr<Card> Cards::TREAD_LIGHTLY = make_card(Card("Tread Lightly", "Block +4 ⚠️", Card::CardType::UNCOMMON,
	                                                     false, false, 3, 5, 18,
	                                                     []() { GameEffectManager::hazardBlock += 4; }, []() {
	                                                     }, []() {
	                                                     }));

	std::shared_ptr<Card> Cards::GRAB_AND_RUN = make_card(Card("Grab 'n' Run", "+7 🪙\n+10% speed for 15s",
	                                                    Card::CardType::UNCOMMON, false, false, 3, 15, 20,
	                                                    []() {
		                                                    GameEffectManager::treasureToGenerate += 7;
		                                                    //TODO: SPEED BUFF
	                                                    }, []() {
	                                                    }, []() {
	                                                    }));

	std::shared_ptr<Card> Cards::FROST_FOCUS = make_card(Card("Frost Focus", "+4 🔥", Card::CardType::UNCOMMON, false, false,
	                                                   3, 5, 20,
	                                                   []() { GameEffectManager::frostToGenerate += 4; }, []() {
	                                                   }, []() {
	                                                   }));

	std::shared_ptr<Card> Cards::CALL_OF_THE_DEEP = make_card(Card("Call of the Deep", "Generate +2 💥\n+10 🪜",
	                                                        Card::CardType::UNCOMMON, true, false, 1, -1, 22,
	                                                        []() {
		                                                        GameEffectManager::addNoise(2);
		                                                        GameEffectManager::delve += 10;
	                                                        }, []() {
	                                                        }, []() {
	                                                        }));

	std::shared_ptr<Card> Cards::STONESKIN = make_card(Card("Stoneskin", "+10% resistance but cards cannot grant speed",
	                                                 Card::CardType::UNCOMMON, true, false, 1, -1, 22,
	                                                 []() {
		                                                 //TODO: RESISTANCE
		                                                 //TODO: stop speed
	                                                 }, []() {
	                                                 }, []() {
	                                                 }));

	std::shared_ptr<Card> Cards::SECOND_WIND = make_card(Card("Second Wind", "+10% speed 15s\nHeal for 15s",
	                                                   Card::CardType::UNCOMMON, false, false, 3, 15, 24,
	                                                   []() {
	                                                   	//TODO: SPEED
	                                                   	//TODO: HEAL
	                                                   }, []() {
	                                                   }, []() {
	                                                   }));

	std::shared_ptr<Card> Cards::BEAST_SENSE = make_card(Card("Beast Sense", "Generate +1 💥\nFor the next 3 cards drawn, the area is illuminated for 10s",
	                                                   Card::CardType::UNCOMMON, false, false, 3, 5, 26,
	                                                   []() {
		                                                   GameEffectManager::addNoise(1);
		                                                   //TODO: LIGHT
	                                                   }, []() {
	                                                   }, []() {
	                                                   }));

	std::shared_ptr<Card> Cards::BOUNDING_STRIDES = make_card(Card("Bounding Strides",
	                                                        "Block +2 💥\n+10% speed when far from wall for 15s",
	                                                        Card::CardType::UNCOMMON, false, false, 3, 15, 28,
	                                                        []() {
		                                                        GameEffectManager::noiseBlock += 2;
		                                                        //TODO: SPEED
	                                                        }, []() {
	                                                        }, []() {
	                                                        }));

	std::shared_ptr<Card> Cards::RECKLESS_CHARGE = make_card(Card("Reckless Charge",
	                                                       "Generate +2 💥\nEach 💥 triggered in next 15s gives +10 🔥",
	                                                       Card::CardType::UNCOMMON, false, false, 3, 15, 30,
	                                                       []() {
		                                                       GameEffectManager::addNoise(2);
		                                                       //TODO: noise triggered
	                                                       }, []() {
	                                                       }, []() {
	                                                       }));

	std::shared_ptr<Card> Cards::MEDITATION = make_card(Card("Meditation", "+1 🔥\n+1 🧠", Card::CardType::UNCOMMON, false,
	                                                  false, 3, 5, 32,
	                                                  []() {
		                                                  GameEffectManager::frostToGenerate += 1;
		                                                  GameEffectManager::focus += 1;
	                                                  }, []() {
	                                                  }, []() {
	                                                  }));

	std::shared_ptr<Card> Cards::NIMBLE_LOOTING = make_card(Card("Nimble Looting",
	                                                      "Until 💥 triggered, each 💥 blocked gives +2 🪙",
	                                                      Card::CardType::UNCOMMON, false, false, 3, 5, 34,
	                                                      []() {
		                                                      //TODO: noise not trigggerred
	                                                      }, []() {
	                                                      }, []() {
	                                                      }));

	std::shared_ptr<Card> Cards::SMASH_AND_GRAB = make_card(Card("Smash & Grab", "+13 🪙\nGenerate +4 💥",
	                                                      Card::CardType::UNCOMMON, false, false, 3, 5, 36,
	                                                      []() {
		                                                      GameEffectManager::treasureToGenerate += 13;
		                                                      GameEffectManager::addNoise(4);
	                                                      }, []() {
	                                                      }, []() {
	                                                      }));

	std::shared_ptr<Card> Cards::QUICKSTEP = make_card(Card("Quickstep", "Generate +4 💥\nDraws the next 3 cards instantly",
	                                                 Card::CardType::UNCOMMON, false, false, 3, 5, 38,
	                                                 []() {
		                                                 GameEffectManager::addNoise(4);
		                                                 //TODO: draw next 3 cards instantly
	                                                 }, []() {
	                                                 }, []() {
	                                                 }));

	std::shared_ptr<Card> Cards::SUIT_UP = make_card(Card(
		"Suit Up", "+10% resistance\nEach 💥 triggered has 25% chance to double", Card::CardType::UNCOMMON, true, false,
		1, -1, 40,
		[]() {
			//TODO: RESISTANCE
			//TODO: chance
		}, []() {
		}, []() {
		}));

	std::shared_ptr<Card> Cards::ADRENALINE_RUSH = make_card(Card("Adrenaline Rush",
	                                                       "Generate +1 ⚠️\nEach heartbeat in next 15s gives +1 🪙",
	                                                       Card::CardType::UNCOMMON, false, false, 3, 15, 42,
	                                                       []() {
		                                                       GameEffectManager::addHazard(1);
		                                                       //TODO: heartbets
	                                                       }, []() {
	                                                       }, []() {
	                                                       }));


	//RARES
	std::shared_ptr<Card> Cards::WATCHFUL_EYE = make_card(Card("Watchful Eye", "+2 🧠", Card::CardType::RARE, false, false, 3,
	                                                    5, 44,
	                                                    []() { GameEffectManager::focus += 2; }, []() {
	                                                    }, []() {
	                                                    }));

	std::shared_ptr<Card> Cards::SMARTER_EVERY_STEP = make_card(Card("Smarter Every Step",
	                                                          "Each 💥 triggered has 10% chance to add +1 🧠",
	                                                          Card::CardType::RARE, true, false, 1, -1, 46,
	                                                          []() {
		                                                          //TODO: chance
	                                                          }, []() {
	                                                          }, []() {
	                                                          }));

	std::shared_ptr<Card> Cards::WHATEVER_LIES_BENEATH = make_card(Card("Whatever Lies Beneath...",
	                                                             "Generate +6 💥\n+15 🪜", Card::CardType::RARE,
	                                                             true, false, 1, -1, 48,
	                                                             []() {
		                                                             GameEffectManager::addNoise(6);
		                                                             GameEffectManager::delve += 15;
	                                                             }, []() {
	                                                             }, []() {
	                                                             }));

	std::shared_ptr<Card> Cards::EERIE_SILENCE = make_card(Card("Eerie Silence", "Block +8 💥\nBlock +2 ⚠️\nSkips the next card",
	                                                     Card::CardType::RARE, false, false, 3, 5, 50,
	                                                     []() {
		                                                     GameEffectManager::noiseBlock += 8;
		                                                     GameEffectManager::hazardBlock += 2;
	                                                     	GameEffectManager::discardCards(1);
	                                                     	GameEffectManager::timeUntilCardPickup +=
																	 GameEffectManager::CARD_PICKUP_TIME;
	                                                     }, []() {
	                                                     }, []() {
	                                                     }));

	std::shared_ptr<Card> Cards::DUNGEON_REPAIRS = make_card(Card("Dungeon Repairs", "Block +7 💥\nGenerate +1 ⚠️",
	                                                       Card::CardType::RARE, false, false, 3, 5, 52,
	                                                       []() {
		                                                       GameEffectManager::noiseBlock += 7;
		                                                       GameEffectManager::hazardBlock += 1;
	                                                       }, []() {
	                                                       }, []() {
	                                                       }));

	std::shared_ptr<Card> Cards::OVERCONFIDENCE = make_card(Card("Overconfidence", "+10 🪙\n+10 🔥\nAdds 2 bane cards",
	                                                      Card::CardType::RARE, false, false, 3, 5, 54,
	                                                      []() {
		                                                      GameEffectManager::treasureToGenerate += 10;
		                                                      GameEffectManager::frostToGenerate += 10;
		                                                      GameEffectManager::addBaneCard();
	                                                      	GameEffectManager::addBaneCard();
	                                                      }, []() {
	                                                      }, []() {
	                                                      }));

	std::shared_ptr<Card> Cards::NECESSARY_SACRIFICES = make_card(Card("Necessary Sacrifices",
	                                                            "+25 🔥\nDESTROYS next card as if it were Ethereal",
	                                                            Card::CardType::RARE, false, false, 3, 5, 54,
	                                                            []() {
		                                                            GameEffectManager::frostToGenerate += 25;
		                                                            Card card = GameEffectManager::pickupPile[0];
																		GameEffectManager::pickupPile.erase(GameEffectManager::pickupPile.begin());

	                                                            	if (std::ranges::find(GameConstants::ownedDeck, card) != GameConstants::ownedDeck.end())
	                                                            		GameConstants::ownedDeck.erase(std::ranges::find(GameConstants::ownedDeck, card));
	                                                            }, []() {
	                                                            }, []() {
	                                                            }));

	std::shared_ptr<Card> Cards::HASTE = make_card(Card("Haste", "Cards are drawn 10% faster", Card::CardType::RARE, false,
	                                             false, 3, 5, 56,
	                                             []() {
		                                             GameEffectManager::CARD_PICKUP_TIME *= 90/100;
	                                             }, []() {
	                                             }, []() {
	                                             }));

	std::shared_ptr<Card> Cards::EYES_ON_THE_PRIZE = make_card(Card("Eyes On The Prize",
	                                                         "-1 🧠, Adds extra card to ending shop",
	                                                         Card::CardType::RARE, true, false, 1, -1, 56,
	                                                         []() {
		                                                         GameEffectManager::focus -= 1;
		                                                         //TODO: add extra card to ending shop
	                                                         }, []() {
	                                                         }, []() {
	                                                         }));

	std::shared_ptr<Card> Cards::VANISH = make_card(Card("Vanish", "Block +8 💥\nGenerated 💥 is reset", Card::CardType::RARE,
	                                              false, false, 3, 5, 58,
	                                              []() {
		                                              GameEffectManager::noiseBlock += 8;
	                                              	GameEffectManager::noise = 0;
	                                              }, []() {
	                                              }, []() {
	                                              }));

	std::shared_ptr<Card> Cards::SILENT_RUNNER = make_card(Card("Silent Runner",
	                                                     "Each 💥 triggered may be blocked by speed buff multiplier",
	                                                     Card::CardType::RARE, true, false, 1, -1, 60,
	                                                     []() {
		                                                     //TODO: speed based on block
	                                                     }, []() {
	                                                     }, []() {
	                                                     }));

	std::shared_ptr<Card> Cards::BRILLIANCE = make_card(Card("Brilliance", "Last two cards re-added to pickup pile",
	                                                  Card::CardType::RARE, false, false, 3, 5, 62,
	                                                  []() {
		                                                  Card card = GameEffectManager::discardPile[0];
		                                                  GameEffectManager::discardPile.erase(GameEffectManager::discardPile.begin());
		                                                  GameEffectManager::pickupPile.insert(GameEffectManager::pickupPile.begin(), card);

	                                                  	Card card1 = GameEffectManager::discardPile[0];
														GameEffectManager::discardPile.erase(GameEffectManager::discardPile.begin());
														GameEffectManager::pickupPile.insert(GameEffectManager::pickupPile.begin(), card1);
	                                                  }, []() {
	                                                  }, []() {
	                                                  }));

	// LEGENDARY
	std::shared_ptr<Card> Cards::THE_DARKEST_DEPTHS = make_card(Card("The Darkest Depths", "Generate +10 💥 and +20 🪜",
	                                                          Card::CardType::LEGENDARY, true, false, 1, -1, -1,
	                                                          []() {
		                                                          GameEffectManager::addNoise(10);
		                                                          GameEffectManager::delve += 20;
	                                                          }, []() {
	                                                          }, []() {
	                                                          }));

	std::shared_ptr<Card> Cards::AVALANCHE = make_card(Card("Avalanche", "+1 🔥 for each card played so far",
	                                                 Card::CardType::LEGENDARY, true, false, 1, -1, -1,
	                                                 []() {
	                                                 	//not perfect due to skips but oh well
		                                                 GameEffectManager::frostToGenerate += GameEffectManager::discardPile.size()-1;
	                                                 }, []() {
	                                                 }, []() {
	                                                 }));

	std::shared_ptr<Card> Cards::BEAST_MASTER = make_card(Card("Beast Master",
	                                                    "Each ⚠️ triggered has 50% chance to illuminate area for 10s",
	                                                    Card::CardType::LEGENDARY, true, false, 1, -1, -1,
	                                                    []() {
		                                                    //TODO: add the light
	                                                    }, []() {
	                                                    }, []() {
	                                                    }));

	std::shared_ptr<Card> Cards::ROLLING_FORTUNE = make_card(Card("Rolling Fortune", "+1 🪙 for each card played after this",
	                                                       Card::CardType::LEGENDARY, true, false, 1, -1, -1,
	                                                       []() {
		                                                       //TODO: add coins for play card
	                                                       }, []() {
	                                                       }, []() {
	                                                       }));

	// PURCHASED
	std::shared_ptr<Card> Cards::PAY_TO_WIN = make_card(Card("Pay To Win", "+10 🔥", Card::CardType::PURCHASED, false, true, 3,
	                                                  5, 2,
	                                                  []() { GameEffectManager::frostToGenerate += 10; }, []() {
	                                                  }, []() {
	                                                  }));

	std::shared_ptr<Card> Cards::TACTICAL_APPROACH = make_card(Card("Tactical Approach", "+5 🪙\nBlock +5 💥",
	                                                         Card::CardType::PURCHASED, false, true, 3, 5, 2,
	                                                         []() {
		                                                         GameEffectManager::treasureToGenerate += 5;
		                                                         GameEffectManager::noiseBlock += 5;
	                                                         }, []() {
	                                                         }, []() {
	                                                         }));

	std::shared_ptr<Card> Cards::A_SHOT_IN_THE_DARK = make_card(Card("A Shot in the Dark", "+10 🪜", Card::CardType::PURCHASED,
	                                                          false, true, 3, 5, 2,
	                                                          []() { GameEffectManager::delve += 10; }, []() {
	                                                          }, []() {
	                                                          }));
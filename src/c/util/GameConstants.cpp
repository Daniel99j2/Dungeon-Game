//
// Created by dj on 22/06/2025.
//

#include "GameConstants.h"
#include "../objects/type/Player.h"
#include "Keybinds.h"
#include "../card/Card.h"
#include "model/Shader.h"
#include "../world/World.h"

bool GameConstants::wireframe = false;
bool GameConstants::debug = false;
bool GameConstants::debugging = false;
int GameConstants::debugRenderMode = 0;
bool GameConstants::debugCollision = false;
bool GameConstants::postProcessingEnabled = true;
int GameConstants::window_height = 720;
int GameConstants::window_width = 1280;
GLFWwindow* GameConstants::window;
bool GameConstants::fullscreen = false;

Shader GameConstants::foregroundShader;
Shader GameConstants::backgroundShader;
Shader GameConstants::cardShader;
Shader GameConstants::simpleShader;
Shader GameConstants::shadowShader;
Shader GameConstants::uiShader;
Shader GameConstants::textShader;

std::shared_ptr<Player> GameConstants::player;
World GameConstants::world;
std::vector<Card> GameConstants::ownedDeck;

Keybinds GameConstants::keybindsManager = Keybinds();
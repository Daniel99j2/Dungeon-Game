//
// Created by dj on 22/06/2025.
//

#pragma once
#include <memory>

#include <GLFW/glfw3.h>

class Card;
class World;
class Player;
class Shader;
class Keybinds;
class Config;

class GameConstants {
public:
    static bool wireframe;
    static bool debug;
    static bool debugging;
    static int debugRenderMode;
    static bool debugCollision;
    static bool postProcessingEnabled;
    static int window_width;
    static int window_height;
    static bool fullscreen;

    static Shader foregroundShader;
    static Shader backgroundShader;
    static Shader simpleShader;
    static Shader objectShader;
    static Shader uiShader;
    static Shader textShader;
    static Shader postProcessor;

    static std::shared_ptr<Player> player;
    static World world;
    static std::vector<Card> ownedDeck;
    static Keybinds keybindsManager;
    static GLFWwindow* window;
};

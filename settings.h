#pragma once 
#include <SFML/Graphics.hpp>
const float WINDOW_WIDTH{ 800.f };
const float WINDOW_HEIGHT{ 800.f };
const std::string WINDOW_TITLE{ "SFML Lesson3" };
const unsigned int FPS{ 60 };
const sf::Vector2f START_POS{ 360.f,700.f };
const float SPEED_X = 5.f;
const int METEORS_QTY = 20;
const std::string LASER_FILENAME = "laserBlue02.png";
const std::string SHIP_FILENAME = "playerShip3_blue.png";
const std::string MULTY_BONUS_FILENAME = "powerupBlue_star.png";
const std::string HP_BONUS_FILENAME = "pill_blue.png";
const std::string SHIELD_BONUS_FILENAME = "shield_silver.png";
const std::string SHIELD_FILENAME = "shield3.png";
const float LASER_SPEED = -15.f;
const int FIRE_COOLDOWN = 200;
const int SHIELD_OPERATING_TIME = 5000;
const int FIRE_LASERS_BONUS_COOLDOWN = 3000;
const std::string FONT_FILENAME = "DS-DIGIB.ttf";
const unsigned int FONT_SIZE = 32;
const unsigned int FONT_SIZE1 = 64;
const sf::Vector2f TEXT_POS{ 250.f, 350.f };
const sf::Vector2f TEXT_POS1{ 300.f, 350.f };
const int MAX_POINTS = 10000;
const float BONUS_SPEED = 5.f;
size_t HEAL = 25;


#pragma once
#include "settings.h"
#include "laser.h"
#include <list>
#include "textObj.h"
#include "shield.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedX;
	std::list<Laser*> laserSprites;
	sf::Clock timer;
	int hp;
	int point;
	Textobj hpText;
	Textobj pointText;
	bool threeLasersActive;
	int curTimeFire, prevTimeFire;
	int curTimeTreeLasersFire, prevTimeTreeLasersFire;
	int prevTimeShield;
	Shield shield;
	bool shieldActive = false;
public:
	Player();

	void fire();

	void update();

	void draw(sf::RenderWindow& window);

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	sf::FloatRect getShieldHitBox() { return shield.getHitBox(); }
	std::list<Laser*>* getLaserSprites() { return &laserSprites; }
	int getHp() { return hp; }
	int getPoint() { return point; }
	void hpChange(int damage) {	hp = hp - damage;}
	void increaseHp(int heal) {	hp = hp + heal;}
	void startHp() { hp = 100;}
	void pointChange(int damage) {	point = point + damage;}
	bool isAlife() { return hp > 0; }
	void activateThreeLasers();
	void deactivateThreeLasers() { threeLasersActive = false; }
    bool isThreeLasersActive() { return threeLasersActive; }
	void activateShield() { shieldActive = true;
	prevTimeShield = timer.getElapsedTime().asMilliseconds();
	}
	void deactivateShield() { shieldActive = false; }
	bool shieldIsActive() { return shieldActive; }
};

Player::Player() : hpText(std::to_string(hp), sf::Vector2f{ 0.f,0.f }, FONT_SIZE), pointText(std::to_string(point), sf::Vector2f{ 600.f,0.f }, FONT_SIZE),
shield(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT + 140)) {
	texture.loadFromFile(SHIP_FILENAME);
	sprite.setTexture(texture);
	sprite.setPosition(START_POS);
	timer.restart();
	hp = 100;
	point = 0;
	threeLasersActive = false;
	prevTimeFire = timer.getElapsedTime().asMilliseconds();
}

void Player::fire() {
	curTimeFire = timer.getElapsedTime().asMilliseconds();
	if (curTimeFire - prevTimeFire > FIRE_COOLDOWN) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			sf::Vector2f pos = sprite.getPosition();
			sf::FloatRect bounds = sprite.getGlobalBounds();
			sf::Vector2f posCenter = sf::Vector2f{ pos.x + bounds.width / 2,pos.y + bounds.height / 2 };
			auto laser = new Laser(posCenter);
			laserSprites.push_back(laser);
			if (threeLasersActive) {
				auto laserWidth = laser->getHitBox().width;
				sf::Vector2f posLeft = sf::Vector2f{ pos.x , pos.y + bounds.height / 2 };
				sf::Vector2f posRight = sf::Vector2f{ pos.x + bounds.width - laserWidth , pos.y + bounds.height / 2 };
				laser = new Laser(posLeft);
				laserSprites.push_back(laser);
				laser = new Laser(posRight);
				laserSprites.push_back(laser);
			}
			prevTimeFire = curTimeFire;
		}
	}
}
void Player::update() {
	speedX = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		speedX = -SPEED_X;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		speedX = SPEED_X;
	}
	if (sprite.getPosition().x < 0) {
		sprite.setPosition(0.f, sprite.getPosition().y);
	}
	else if (sprite.getPosition().x > WINDOW_WIDTH - sprite.getGlobalBounds().width) {
		sprite.setPosition(WINDOW_WIDTH - sprite.getGlobalBounds().width, sprite.getPosition().y);
	}

	sprite.move(speedX, 0.f);
	fire();
	for (auto laser : laserSprites) {
		laser->update();
	}
	hpText.update("HP:" + std::to_string(hp));
	pointText.update("POINTS:" + std::to_string(point));

	int curTime= timer.getElapsedTime().asMilliseconds();
	if (threeLasersActive) {
		if (curTime - prevTimeTreeLasersFire > FIRE_LASERS_BONUS_COOLDOWN) {
			deactivateThreeLasers();
		}
	}
	sf::Vector2f shieldPos;
	if (shieldActive) {
		if (curTime - prevTimeShield > SHIELD_OPERATING_TIME) {
			deactivateShield();
		}
		auto playerBounds = getHitBox();
		shieldPos = sf::Vector2f{ playerBounds.left + playerBounds.width / 2, playerBounds.top + playerBounds.height / 2 };
	}
	else {
		shieldPos = sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT + 140.f };
	}
	shield.setPosition(shieldPos);
}
void Player::activateThreeLasers() {
	threeLasersActive = true;
	prevTimeTreeLasersFire = timer.getElapsedTime().asMilliseconds();
}

void Player::draw(sf::RenderWindow& window) {
	shield.draw(window);
	for (auto laser : laserSprites) {
		window.draw(laser->getSprite());
	}
	window.draw(sprite);
	hpText.draw(window);
	pointText.draw(window);
}
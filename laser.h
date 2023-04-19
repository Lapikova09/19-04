#pragma once
#include "settings.h"
class Laser {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool hit;
public:
	Laser(sf::Vector2f playerPos) {
		texture.loadFromFile(LASER_FILENAME);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(playerPos);
		hit = false;
	}
	void update() {
		sprite.move(0.f, LASER_SPEED);
	}
	sf::Sprite& getSprite() { return sprite; }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	void setHit() { hit = true; }
	bool isHit() { return hit; }
	float getPosY() { return sprite.getPosition().y; }

};

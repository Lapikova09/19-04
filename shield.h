#pragma once
#include "settings.h"
class Shield {
public:
	Shield(sf::Vector2f position);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getHitBox();
	void setPosition(sf::Vector2f position);
private:
	sf::Texture texture;
	sf::Sprite sprite;

};
Shield::Shield(sf::Vector2f position) {
	texture.loadFromFile(SHIELD_FILENAME);
	sprite.setTexture(texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite.setPosition(position);
}
void Shield::draw(sf::RenderWindow& window) { window.draw(sprite); }
sf::FloatRect Shield::getHitBox() { return sprite.getGlobalBounds(); }
void Shield::setPosition(sf::Vector2f position) { sprite.setPosition(position); }

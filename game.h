#pragma once
#include "settings.h"
#include "meteor.h"
#include <vector>
#include "Player.h"
#include "bonus.h"

class Game {
public:
	enum GameState { PLAY, GAME_OVER, YOU_WIN };
	GameState gameState = PLAY;
	Game() : text("GAME OVER", TEXT_POS, FONT_SIZE1), text1("YOU WIN", TEXT_POS1, FONT_SIZE1) {
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEORS_QTY);
		for (int i = 0; i < METEORS_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}
	}

	void play() {
		while (window.isOpen()) {// && player.isAlife()
			checkEvents();
			update();
			if (player.getHp() <= 0) gameState = GAME_OVER;
			if (player.getPoint() >= MAX_POINTS) gameState = YOU_WIN;
			checkCollisions();
			draw();
		}
	}

private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteorSprites;
	Player player;
	Textobj text;
	Textobj text1;
	std::list<Bonus*> bonusSprites;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		switch (gameState) {
		case PLAY:
			for (auto& meteor : meteorSprites) {
				meteor->update();
			}
			for (auto& bonus : bonusSprites) {
				bonus->update();
			}
			player.update();
			break;
		case GAME_OVER:
			text.update("GAME OVER");
			break;
		case YOU_WIN:
			text1.update("YOU WIN");
			break;
		}
	}

	void checkCollisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		if (player.shieldIsActive()) {
			sf::FloatRect shieldBounds = player.getShieldHitBox();
			for (auto& meteor : meteorSprites) {
				sf::FloatRect meteorBounds = meteor->getHitBox();
				if (meteorBounds.intersects(shieldBounds)) {
					meteor->spawn();
				}
			}
		}
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorBounds = meteor->getHitBox();
			if (meteorBounds.intersects(playerBounds)) {
				meteor->spawn();
				player.hpChange(meteor->GetDamage());
			}
			auto laserSprites = player.getLaserSprites();
			for (auto& laser : *laserSprites) {
				sf::FloatRect laserBounds = laser->getHitBox();
				if (meteorBounds.intersects(laserBounds)) {
					meteor->spawn();
					laser->setHit();
					player.pointChange(meteor->GetDamage());
					size_t chance = rand() % 10001;
					if (chance < 1500) {
						size_t bonusType = rand() % Bonus::BonusType::TYPES_QTY;
						Bonus* bonus = new Bonus((Bonus::BonusType)bonusType, meteor->getPosition());
						bonusSprites.push_back(bonus);
					}
				}
				if (laser->getPosY() < 0.f) {
					laser->setHit();
				}
			}
			(*laserSprites).remove_if([](Laser* laser) {return laser->isHit(); });
		}
	
		for (auto& bonus : bonusSprites) {
			sf::FloatRect bonusBounds = bonus->getHitBox();
			if (bonusBounds.intersects(playerBounds)) {
					bonus->act(player);
					bonus->setDel();
			}
			if (bonus->getPosY() > WINDOW_HEIGHT) {
				bonus->setDel();
			}
			
		}
		bonusSprites.remove_if([](Bonus* bonus) {return bonus->isToDel(); });
	}

	void draw() {
		switch (gameState) {
		case PLAY:
			window.clear();
			for (const auto& meteor : meteorSprites) {
				window.draw(meteor->getSprite());
			}
			for (const auto& bonus : bonusSprites) {
				bonus->draw(window);
			}
			player.draw(window);
			window.display();
			break;
		case GAME_OVER:
			window.clear();
			text.draw(window);
			window.display();
			break;
		case YOU_WIN:
			window.clear();
			text1.draw(window);
			window.display();
			break;
		}
	}
};
#pragma once
#include "TextureManagement.h"

namespace Texture {
	static Draw::SpriteAnimator* getAnimatedSprite(Texture& texture) {
		sf::Sprite sprite(*texture.texture);


		Draw::SpriteAnimator* anim = new Draw::SpriteAnimator(&sprite,
									texture.animation_time, texture.animationSize, 0);

		return anim;
	}

	static sf::Sprite* getSprite(Texture& texture, sf::IntRect rect, sf::Vector2f pos = sf::Vector2f(0.f, 0.f)) {
		sf::Sprite* s = new sf::Sprite(*texture.texture, rect);
		s->setPosition(pos);

		return s;
	}

	static void combineFiles(TextureFile& file1, TextureFile& file2) {
		for (int i = 0; i < file2.getList()->size(); i++) {
			file1.getList()->push_back(file2.getList()->at(i));
		}
	}


}
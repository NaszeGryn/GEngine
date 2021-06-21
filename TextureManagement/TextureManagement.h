#pragma once
#include "GLEngine.h"
#include "Debug.h"

namespace Texture {

	// new texture struct with id
	class Texture {
	public:
		Texture() { // default constructor
			texture = sf::Texture();
			ID = "";
			animationSize = sf::Vector2i();
			animated = 0;
			animation_time = 0.f;
		}

		void loadTexture(const std::string& loc) {
			this->texture.loadFromFile(loc);
			this->texture.setSmooth(true);
		}

		// struct variables
		sf::Texture texture;
		std::string ID;
		sf::Vector2i animationSize; // frame size or tile size
		bool animated;
		float animation_time;
	};


	// easy loading textures from VL file
	class TextureFile {
	public:
		// constructors
		TextureFile();
		TextureFile(VL::VL_file& file);
		TextureFile(const std::string& filename);

		// destructor
		~TextureFile();

		// get texture
		Texture* getTexture(const std::string& ID);
		Texture* getTexture(uint32_t index);

		std::vector<Texture>* getList();

	private:
		std::vector<Texture> textures;

	private:
		void Interpret(VL::VL_file& file);
	};

	// functions
	static Draw::SpriteAnimator* getAnimatedSprite(Texture& texture) {
		sf::Sprite sprite(texture.texture);


		Draw::SpriteAnimator* anim = new Draw::SpriteAnimator(&sprite,
			texture.animation_time, texture.animationSize, 0);

		return anim;
	}

	static sf::Sprite* getSprite(Texture& texture, sf::IntRect rect, sf::Vector2f pos = sf::Vector2f(0.f, 0.f)) {
		sf::Sprite* s = new sf::Sprite(texture.texture, rect);
		s->setPosition(pos);

		return s;
	}

	static void combineFiles(TextureFile& file1, TextureFile& file2) {
		for (int i = 0; i < file2.getList()->size(); i++) {
			file1.getList()->push_back(file2.getList()->at(i));
		}
	}

	static Collisions::Poly getCollider(sf::Sprite& sprite) {
		return Collisions::Poly(sprite.getPosition(), // position
			sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height)); // size
	}

	static sf::IntRect getTile(Texture& t, int tile) {
		if (t.animationSize.x != 0 && t.animationSize.y != 0) {
			int maxtiles_in_a_row = (t.texture.getSize().x / t.animationSize.x);
			if (maxtiles_in_a_row > 0) {
				int skipped_rows = tile / maxtiles_in_a_row;

				sf::Vector2i pos(t.animationSize.x * (tile - (maxtiles_in_a_row * skipped_rows)), t.animationSize.y * skipped_rows);
				return sf::IntRect(pos, t.animationSize);
			}
		}

		return sf::IntRect(gL_V2IZERO, sf::Vector2i(t.texture.getSize()));
	}

}
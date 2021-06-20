#pragma once
#include "GLEngine.h"

namespace Texture {

	// new texture struct with id
	struct Texture {
		Texture() { // default constructor
			texture = NULL;
			ID = "";
			animationSize = sf::Vector2i();
			animated = 0;
			animation_time = 0.f;
		}

		// struct variables
		sf::Texture* texture;
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
	static Draw::SpriteAnimator* getAnimatedSprite(Texture& texture);
	static sf::Sprite* getSprite(Texture& texture, sf::IntRect rect, sf::Vector2f pos = sf::Vector2f(0.f, 0.f));

	static void combineFiles(TextureFile& file1, TextureFile& file2);

}
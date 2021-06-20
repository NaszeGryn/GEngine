#pragma once
#include "TextureManagement.h"

namespace Texture {
	// default
	TextureFile::TextureFile() {
		;
	}

	// with VL_File
	TextureFile::TextureFile(VL::VL_file& file) {
		this->Interpret(file);
	}

	// with file name
	TextureFile::TextureFile(const std::string& filename) {
		VL::VL_file file(filename, "");
		this->Interpret(file);
	}

	// delete
	TextureFile::~TextureFile() {
		for (int i = 0; i < this->textures.size(); i++) {
			delete this->textures[i].texture;
		}
		this->textures.clear();
	}


	// private function to interpret from file
	void TextureFile::Interpret(VL::VL_file& file) {
		for (int i = 0; i < file.getList()->size(); i++) {
			// interpret textures
			Texture t;

			std::string title = file.getList()->at(i).title;
			std::string value = file.getList()->at(i).value;

			if (title.find("_anim") != std::string::npos) {
				std::string id = title.substr(0, title.length() - 5); // id without _anim


				if (this->getTexture(id) != NULL) { // add to existing variable
					this->getTexture(id)->animated = true;
					this->getTexture(id)->animation_time = atof(value.c_str());
				}
			}
			else if (title.find("_aSize") != std::string::npos) {
				std::string id = title.substr(0, title.length() - 6); // id without _animSize

				if (this->getTexture(id) != NULL) { // add to existing variable
					this->getTexture(id)->animationSize = sf::Vector2i(Math::strToVec2f(value));
				}
			}
			else if (title.find("_tSize") != std::string::npos) { // tile size
				std::string id = title.substr(0, title.length() - 6); // id without _animSize

				if (this->getTexture(id) != NULL) { // add to existing variable
					this->getTexture(id)->animationSize = sf::Vector2i(Math::strToVec2f(value));
					this->getTexture(id)->animated = false;
				}
			}
			else { // new texture
				t.ID = title;
				t.texture = new sf::Texture(GraphFunc::loadHQTexture(value));

				// animated and animation_time remain default
			}

		}
	}


	// texture finding
	Texture* TextureFile::getTexture(const std::string& ID) {
		for (size_t i = 0; i < this->textures.size(); i++) {
			if (ID == this->textures[i].ID) {
				return &this->textures[i];
			}
		}
		return NULL;
	}

	Texture* TextureFile::getTexture(uint32_t index) {
		if (index < this->textures.size()) {
			return &this->textures[index];
		}
		return NULL;
	}

	// get list function
	std::vector<Texture>* TextureFile::getList() {
		return &this->textures;
	}


}
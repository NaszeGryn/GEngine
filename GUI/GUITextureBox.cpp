#include "GUI.h"

namespace GUI {
	//constructor
	TextureBox::TextureBox(
		sf::Vector2f pos,
		sf::Texture* texture, const std::string& ID)
	{
		this->sprite = new sf::Sprite(*texture);
		this->sprite->setPosition(pos);
		this->ID = ID;
	}

	// constructor with intrect
	TextureBox::TextureBox(
		sf::Vector2f pos,
		sf::Texture* texture,
		sf::IntRect rect,
		const std::string& ID)
	{
		this->sprite = new sf::Sprite(*texture, rect);
		this->sprite->setPosition(pos);
		this->ID = ID;
	}

	// deconstructor
	TextureBox::~TextureBox() {
		delete this->sprite;
	}


	void TextureBox::Draw(sf::RenderTarget* target) {
		target->draw(*this->sprite);
	}

	void TextureBox::Update(float deltaTime, sf::RenderWindow* window) {
		;
	}

	void TextureBox::EventUpdate(sf::Event event) {
		;
	}

	Event TextureBox::getEvent() {
		return Event::None;
	}

	ElementType TextureBox::getType() {
		return ElementType::TextureBox;
	}


	sf::Vector2f TextureBox::maxRD() {
		return this->sprite->getPosition() +
			sf::Vector2f(this->sprite->getGlobalBounds().width,
						this->sprite->getGlobalBounds().height);
	}
	sf::Vector2f TextureBox::minRD() {
		return this->sprite->getPosition();
	}
}
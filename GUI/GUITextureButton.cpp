#include "GUI.h"

namespace GUI {
	TextureButton::TextureButton(sf::Vector2f pos, sf::Texture& texture, const std::string& ID) {
		this->event = Event::None;
		this->sprite = new sf::Sprite(texture);
		this->sprite->setPosition(pos);
		this->ID = ID;
	}

	TextureButton::TextureButton(sf::Vector2f pos, sf::Texture& texture, sf::IntRect rect, const std::string& ID) {
		this->event = Event::None;
		this->sprite = new sf::Sprite(texture, rect);
		this->sprite->setPosition(pos);
		
	}

	TextureButton::~TextureButton() {
		delete this->sprite;
		this->sprite = NULL;
	}

	void TextureButton::Draw(sf::RenderTarget* target) {
		target->draw(*this->sprite);
	}

	void TextureButton::Update(float deltaTime, sf::RenderWindow* window) {
		if (this->sprite->getGlobalBounds().contains(
			sf::Vector2f(sf::Mouse::getPosition(*window)))) {

			this->hover = true;

		}
		else {
			this->hover = false;
		}
	}

	void TextureButton::EventUpdate(sf::Event ev) {
		if (ev.type == sf::Event::MouseButtonPressed &&
			ev.mouseButton.button == sf::Mouse::Button::Left) {
			if (this->hover) {
				this->event = Event::Clicked;
			}
		}
	}

	Event TextureButton::getEvent() {
		if (this->event != Event::None) {
			Event eve = this->event;
			this->event = Event::None;
			return eve;
		}
		return this->event;
	}

	ElementType TextureButton::getType() {
		return ElementType::Button;
	}

	sf::Vector2f TextureButton::maxRD() {
		sf::FloatRect fR = this->sprite->getGlobalBounds();
		return sf::Vector2f(fR.left + fR.width, fR.top + fR.height);
	}

	sf::Vector2f TextureButton::minRD() {
		return this->sprite->getPosition();
	}
}
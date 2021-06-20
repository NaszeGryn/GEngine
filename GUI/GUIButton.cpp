#include "GUI.h"

namespace GUI {
	// button class
	Button::Button(
		sf::Vector2f pos, sf::Vector2f size, sf::Text* text,
		sf::Color color, const std::string& ID
	)
	{
		this->event = Event::None;
		this->color = color;
		this->alpha = 180.f;
		this->ID = ID;
		// shape
		{
			this->shape = new sf::RectangleShape(size);
			this->shape->setFillColor(color);
			this->shape->setPosition(pos);
		}

		// text
		{
			this->text = new sf::Text(*text);
			float textXpos = pos.x + ( (size.x - this->text->getGlobalBounds().width) / 2.f );
			float textYpos = pos.y + ( (size.y - this->text->getGlobalBounds().height) / 2.f );

			this->text->setPosition(sf::Vector2f(textXpos, textYpos));
		}
	}

	Button::~Button() {
		delete this->shape;
		this->shape = NULL;

		delete this->text;
		this->text = NULL;
	}

	void Button::Draw(sf::RenderTarget* target) {
		target->draw(*shape);
		target->draw(*text);
	}

	void Button::Update(float deltaTime, sf::RenderWindow* window) {
		// alpha 180 - 240
		if (this->shape->getGlobalBounds().contains(
			sf::Vector2f(sf::Mouse::getPosition(*window)))) {
			
			this->hover = true;
			if (this->alpha < 240) {
				this->alpha += deltaTime * 60;
			}

		}
		else {
			this->hover = false;
			if (this->alpha > 180) {
				this->alpha -= deltaTime * 60;
			}

		}

		this->color.a = (uint8_t)alpha;
		this->shape->setFillColor(color);
	}

	void Button::EventUpdate(sf::Event ev) {
		if (ev.type == sf::Event::MouseButtonPressed &&
			ev.mouseButton.button == sf::Mouse::Button::Left) {
			if (this->hover) {
				this->event = Event::Clicked;
			}
		}
	}

	Event Button::getEvent() {
		if (this->event != Event::None) {
			Event eve = this->event;
			this->event = Event::None;
			return eve;
		}
		return this->event;
	}

	ElementType Button::getType() {
		return ElementType::Button;
	}

	sf::Vector2f Button::maxRD() {
		sf::FloatRect fR = this->shape->getGlobalBounds();
		return sf::Vector2f(fR.left + fR.width, fR.top + fR.height);
	}

	sf::Vector2f Button::minRD() {
		sf::FloatRect fR = this->shape->getGlobalBounds();
		return sf::Vector2f(fR.left, fR.top);
	}

}

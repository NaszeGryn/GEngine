#include "GUI.h"

namespace GUI {
	// textbox class
	TextBox::TextBox(
		sf::Vector2f pos, sf::Vector2f size,
		sf::Text* text, sf::Color color, const std::string& ID
	) 
	{
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
			float textXpos = pos.x + ((size.x - this->text->getGlobalBounds().width) / 2.f);
			float textYpos = pos.y + ((size.y - this->text->getGlobalBounds().height) / 2.f);

			this->text->setPosition(sf::Vector2f(textXpos, textYpos));
		}
	}

	TextBox::~TextBox() {
		delete this->shape;
		delete this->text;

		this->shape = NULL;
		this->text = NULL;
	}

	void TextBox::Draw(sf::RenderTarget* target) {
		target->draw(*shape);
		target->draw(*text);
	}

	void TextBox::Update(float deltaTime, sf::RenderWindow* window) {
			;
	}

	void TextBox::EventUpdate(sf::Event event) {
		;
	}

	Event TextBox::getEvent() {
		return Event::None;
	}

	ElementType TextBox::getType() {
		return ElementType::TextBox;
	}

	sf::Vector2f TextBox::maxRD() {
		sf::FloatRect fR = this->shape->getGlobalBounds();
		return sf::Vector2f(fR.left + fR.width, fR.top + fR.height);
	}

	sf::Vector2f TextBox::minRD() {
		sf::FloatRect fR = this->shape->getGlobalBounds();
		return sf::Vector2f(fR.left, fR.top);
	}
}
#include "GUI.h"
#include <GLEngine.h>

namespace GUI {
	BSBox::BSBox(sf::Vector2f pos, sf::Vector2f size, sf::Color color, sf::Color TextColor,
		std::vector<std::string>& strings, sf::Font* font, int charsize, int def_Val, const std::string& ID) {

		this->strings = strings;
		this->font = font;

		this->value = def_Val;
		this->checkVal();


		this->hover = 0;
		this->ID = ID;
		{
			// arrow width = 1/10 size
			// height = 1/4 size
			middleText.setCharacterSize(charsize);
			middleText.setFillColor(TextColor);
			middleText.setPosition(pos + sf::Vector2f(size.x/20.f + 2.f, 0.f));
			middleText.setFont(*this->font);
			middleText.setString(strings[def_Val]);
		}
		{
			pointers.push_back(sf::RectangleShape(sf::Vector2f(size.x / 20.f, size.y)));
			pointers[0].setFillColor(color);
			pointers[0].setPosition(pos);

			pointers.push_back(sf::RectangleShape(sf::Vector2f(size.x / 20.f, size.y)));
			pointers[1].setFillColor(color);
			pointers[1].setPosition(sf::Vector2f(size.x - (size.x / 20.f), 0.f) + pos);
		}
	}


	void BSBox::Draw(sf::RenderTarget* window) {
		if (value != 0)
			window->draw(pointers[0]);
			
		if (value < strings.size() - 1)
			window->draw(pointers[1]);

		window->draw(middleText);
	}

	void BSBox::Update(float deltaTime, sf::RenderWindow* window) {
		if (hoverTriangle1(sf::Vector2f(sf::Mouse::getPosition(*window)) ))
			hover = 1;
		else if (hoverTriangle2(sf::Vector2f(sf::Mouse::getPosition(*window)) ))
			hover = 2;
		else
			hover = 0;
	}

	void BSBox::EventUpdate(sf::Event event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Button::Left) {
				if (hover == 1) {
					this->event = Event::NewVal;
					this->value--;
				}
				else if (hover == 2) {
					this->event = Event::NewVal;
					this->value++;
				}

				checkVal();

				this->middleText.setString(strings[value]);
			}
		}
	}

	bool BSBox::hoverTriangle1(sf::Vector2f mouse) {
		return this->pointers[0].getGlobalBounds().contains(mouse);
	}

	bool BSBox::hoverTriangle2(sf::Vector2f mouse) {
		return this->pointers[1].getGlobalBounds().contains(mouse);
	}
}
#include "GUI.h"

#include <iostream>

namespace GUI {
	InputBox::InputBox(sf::Vector2f pos, sf::Vector2f size, int charSize, sf::Color color,
		sf::Font* font, const std::string& ID, const std::string& def_text) {

		this->ID = ID;
		this->event = Event::None;
		this->txt = def_text;
		{
			this->background = new sf::RectangleShape(size);
			this->background->setPosition(pos);
			this->background->setFillColor(color);
		}
		{
			this->render_text = new sf::Text(this->txt, *font, charSize);
			this->render_text->setPosition(pos + sf::Vector2f(4.f, 4.f));
		}
	}

	InputBox::~InputBox() {
		delete this->background;
		delete this->render_text;

		this->background = NULL;
		this->render_text = NULL;
	}

	void InputBox::Draw(sf::RenderTarget* window) {
		window->draw(*background);
		window->draw(*render_text);
	}
	void InputBox::Update(float deltaTime, sf::RenderWindow* window) {
		this->hover = background->getGlobalBounds().contains(gL_getRelativeMousePos(*window));
	}

	void InputBox::EventUpdate(sf::Event event) {
		if (event.type == sf::Event::KeyPressed && hover) {
			if (gL_isKeyPressed(sf::Keyboard::BackSpace)) {
				if (txt.size() != 0) {
					txt.erase(txt.end() - 1);
				}
			}
			else if (gL_isKeyPressed(sf::Keyboard::Space)) {
				this->render_text->setString(this->txt + " ");


				if (!(render_text->getPosition().x + render_text->getGlobalBounds().width > this->maxRD().x)) {
					this->txt += " ";
				}
			}
			else {
				if (UI::getChar() != NULL) {
					this->render_text->setString(this->txt + UI::getChar());


					if (!(render_text->getPosition().x + render_text->getGlobalBounds().width > this->maxRD().x)) {
						this->txt += UI::getChar();
					}
				}
			}

			this->render_text->setString(this->txt);
		}
	}
}
#include "GUI.h"

namespace GUI {
	//sf::Color((a.r + b.r) / 2, (a.g + b.g) / 2, (a.b + b.b) / 2)

	// colorstate 0-false 1-true 2-hover

	TFBox::TFBox(sf::Vector2f pos, float size, sf::Color TrueColor,
		sf::Color FalseColor, bool def_Val, const std::string& ID) {
		this->event = Event::None;
		this->value = def_Val;
		this->ID = ID;

		this->FalseColor = FalseColor;
		this->TrueColor = TrueColor;

		hover = false;
		{
			this->shape.setPosition(pos);
			this->shape.setSize(sf::Vector2f(size, size));
			this->shape.setFillColor(this->FalseColor);

			this->shape.setOutlineThickness(3.f);
			this->shape.setOutlineColor(TrueColor);
		}
	}
	
	void TFBox::Draw(sf::RenderTarget* window) {
		window->draw(this->shape);
	}

	void TFBox::Update(float deltaTime, sf::RenderWindow* window) {
		this->hover = this->shape.getGlobalBounds().contains(gL_getRelativeMousePos(*window));
		if (this->color_state != 2) {
			
			if (hover) {
				this->color_state = 2;
				this->shape.setFillColor(sf::Color(
					(TrueColor.r + FalseColor.r) / 2,
					(TrueColor.g + FalseColor.g) / 2,
					(TrueColor.b + FalseColor.b) / 2));
			}

			else if (this->color_state == 1 && !value) {
				this->color_state = 0;
				this->shape.setFillColor(FalseColor);
			}
			else if (this->color_state == 0 && value) {
				this->color_state = 1;
				this->shape.setFillColor(TrueColor);
			}
		}
		if (this->color_state == 2 && !hover) {
			if (!value) {
				this->color_state = 0;
				this->shape.setFillColor(FalseColor);
			}
			else if (value) {
				this->color_state = 1;
				this->shape.setFillColor(TrueColor);
			}
		}
	}

	void TFBox::EventUpdate(sf::Event event) {
		if (hover) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					this->value = !this->value;
					this->event = Event::NewVal;
				}
			}
		}
	}


	sf::Vector2f TFBox::maxRD() {
		return this->shape.getPosition() + this->shape.getSize();
	}
	sf::Vector2f TFBox::minRD() {
		return this->shape.getPosition();
	}
}
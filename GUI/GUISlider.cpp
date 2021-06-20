#include "GUI.h"

namespace GUI {
	Slider::Slider(
		sf::Vector2f pos,
		float size,
		float length,
		sf::Color color,
		int starting_Val,
		const std::string& ID
	) 
	{
		// rect 1 - underline
		// rect 2 - start
		// rect 3 - end
		// rect 4 - slider
		this->ID = ID;
		this->value = starting_Val;
		this->pos = pos;
		this->size = size;
		this->length = length;
		this->event = Event::NewVal;


		this->list.resize(4);
		this->background = sf::IntRect(sf::Vector2i(pos), sf::Vector2i((int)length, (int)size));
		sf::RectangleShape box;
		int a = color.a - 30;
		if (a < 20) {
			a = 20;
		}

		box.setFillColor(sf::Color(color.r, color.g, color.b, a));
		{
			box.setPosition(pos + sf::Vector2f(0.f, size / 2.f));
			box.setSize(sf::Vector2f(length, 2.f));
			this->list.push_back(box);
		}
		box.setFillColor(color);
		{
			box.setPosition(pos);
			box.setSize(sf::Vector2f(size/2.f, size));
			this->list.push_back(box);
		}
		{
			box.setPosition(pos + sf::Vector2f(length, 0.f));
			box.setSize(sf::Vector2f(size / 2.f, size));
			this->list.push_back(box);
		}
		box.setFillColor(sf::Color(color.r, color.g, color.b, 245));
		{
			box.setPosition(pos + sf::Vector2f(value / (100.f / length), 0.f));
			box.setSize(sf::Vector2f(size / 2.f, size));
			box.setOutlineThickness(1.f);
			box.setOutlineColor(sf::Color::Black);
			this->list.push_back(box);
		}
	}

	Slider::~Slider() {
		this->list.clear();
	}

	void Slider::Draw(sf::RenderTarget* target) {
		for(size_t i = 0; i < this->list.size(); i++)
			target->draw(this->list[i]);
	}

	void Slider::Update(float deltaTime, sf::RenderWindow* window) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->background.contains(sf::Mouse::getPosition(*window))) {
				float v = (float)sf::Mouse::getPosition(*window).x;
				if (v < pos.x) {
					v = pos.x;
				}
				else if (v > pos.x + length) {
					v = pos.x + length;
				}
				this->list[3].setPosition(sf::Vector2f(v, pos.y));
				this->value = int((v - pos.x) * (100.f / length));

				this->event = Event::NewVal;
			}
		}
	}

	void Slider::EventUpdate(sf::Event event) {
		;
	}

	Event Slider::getEvent() {
		if (this->event != Event::None) {
			Event eve = this->event;
			this->event = Event::None;
			return eve;
		}
		return this->event;
	}

	ElementType Slider::getType() {
		return ElementType::Slider;
	}

	sf::Vector2f Slider::maxRD() {
		return this->pos + sf::Vector2f(length, size);
	}
	sf::Vector2f Slider::minRD() {
		return this->pos;
	}
}
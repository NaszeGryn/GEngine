#include "GUI.h"

namespace GUI {
	GUIHandler::GUIHandler(sf::Vector2f pos, int margin, sf::Color color) {
		this->margin = margin;

		this->miRD = pos;

		this->shape.setPosition(miRD);
		this->shape.setFillColor(color);

		this->mRD = sf::Vector2f((float)margin * 2.f, (float)margin * 2.f);
		this->shape.setSize(mRD);
	}

	GUIHandler::~GUIHandler() {
		this->elements.clear();
	}

	void GUIHandler::add_GUI_ELEMENT(GUIElement* element) {
		this->elements.push_back(element);
		if (element->minRD().x <= this->miRD.x) {
			this->miRD.x = element->minRD().x - margin;
		}
		if (element->minRD().y <= this->miRD.y) {
			this->miRD.y = element->minRD().y - margin;
		}


		if (element->maxRD().x >= this->mRD.x + this->miRD.x) {
			this->mRD.x = element->maxRD().x - this->miRD.x + margin;
		}
		if (element->maxRD().y >= this->mRD.y + this->miRD.y) {
			this->mRD.y = element->maxRD().y - this->miRD.y + margin;
		}

		this->shape.setSize(mRD);
		this->shape.setPosition(miRD);
	}

	std::vector<GUIElement*>* GUIHandler::getArray() {
		return &this->elements;
	}

	void GUIHandler::Draw(sf::RenderTarget* target) {
		target->draw(this->shape);
		for (size_t i = 0; i < this->elements.size(); i++) {
			this->elements[i]->Draw(target);
		}
	}

	void GUIHandler::Update(float deltaTime, sf::RenderWindow* window) {
		for (size_t i = 0; i < this->elements.size(); i++) {
			this->elements[i]->Update(deltaTime, window);
		}
	}

	void GUIHandler::EventUpdate(sf::Event event) {
		for (size_t i = 0; i < this->elements.size(); i++) {
			this->elements[i]->EventUpdate(event);
		}
	}

	void GUIHandler::clear() {
		this->elements.clear();
		this->mRD = this->miRD;
	}

	size_t GUIHandler::getArraySize() {
		return this->elements.size();
	}
	Event GUIHandler::getEvent(int index) {
		if (index < this->elements.size() && index >= 0)
			return this->elements[index]->getEvent();
		return Event::None;
	}
	ElementType GUIHandler::getElementType(int index) {
		if (index < this->elements.size() && index >= 0)
			return this->elements[index]->getType();
		return ElementType::null;
	}

	int GUIHandler::getValue(int index) {
		if (index < this->elements.size() && index >= 0)
			return this->elements[index]->getValue();
		return 0;
	}
	std::string GUIHandler::getIBValue(int index) {
		if (index < this->elements.size() && index >= 0)
			return this->elements[index]->getIBValue();
		return "";
	}


	Event GUIHandler::getEvent(const std::string& ID) {
		for (int i = 0; i < this->elements.size(); i++) {
			if (elements[i]->getID() == ID)
				return elements[i]->getEvent();
			
		}
		return Event::None;
	}
	ElementType GUIHandler::getElementType(const std::string& ID) {
		for (int i = 0; i < this->elements.size(); i++) {
			if (elements[i]->getID() == ID) {
				return elements[i]->getType();
			}
		}
		return ElementType::null;
	}
	int GUIHandler::getValue(const std::string& ID) {
		for (int i = 0; i < this->elements.size(); i++) {
			if (elements[i]->getID() == ID) {
				return elements[i]->getValue();
			}
		}
		return 0;
	}

	std::string GUIHandler::getIBValue(const std::string& ID) {
		for (int i = 0; i < this->elements.size(); i++) {
			if (elements[i]->getID() == ID) {
				return elements[i]->getIBValue();
			}
		}
		return "";
	}

	int GUIHandler::getIndex(const std::string& ID) {
		for (int i = 0; i < this->elements.size(); i++) {
			if (elements[i]->getID() == ID) {
				return i;
			}
		}
		return -1;
	}

	std::string GUIHandler::getID(int index) {
		if (index < this->elements.size() && index >= 0)
			return this->elements[index]->getID();
		return "";
	}
}
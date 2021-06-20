#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"
#include <GLEngine.h>
#define gL_defaultGuiColor sf::Color(40, 40, 40, 180)

namespace GUI {
	// gui elements events
	enum class Event {
		None = 0,
		// button event
		Clicked = 1,

		// other
		NewVal = 2
	};

	// element types
	enum class ElementType {
		null = 0,
		Button = 1,
		TextureButton = 2,
		TextBox = 3,
		TextureBox = 4,
		Slider = 5,
		InputBox = 6,
		TFBox = 7,
		BSBox = 8
	};

	// virtual class for GUI elements
	class GUIElement {
	public:
		virtual void Draw(sf::RenderTarget* window) = 0;
		virtual void Update(float deltaTime, sf::RenderWindow* window) = 0;
		virtual void EventUpdate(sf::Event event) = 0;
		virtual Event getEvent() = 0;
		virtual ElementType getType() = 0;
		virtual int getValue() = 0;
		virtual std::string getIBValue() = 0;

		virtual sf::Vector2f maxRD() = 0;
		virtual sf::Vector2f minRD() = 0;  
		virtual std::string getID() = 0;
	};

	// button class
	class Button : public GUIElement {
	public:
		Button(
			sf::Vector2f pos, sf::Vector2f size,
			sf::Text* text, sf::Color color, const std::string& ID = "");
		~Button();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }
		std::string getIBValue() { return ""; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::RectangleShape* shape;
		sf::Text* text;
		sf::Color color;

		bool hover;
	private:
		Event event;
		float alpha;
		std::string ID;
	};

	// button class
	class TextureButton : public GUIElement {
	public:
		TextureButton(sf::Vector2f pos, sf::Texture& texture, const std::string & ID = "");
		TextureButton(sf::Vector2f pos, sf::Texture& texture, sf::IntRect rect, const std::string & ID = "");
		~TextureButton();
		
		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }
		std::string getIBValue() { return ""; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::Sprite* sprite;

		bool hover;
	private:
		Event event;
		std::string ID;
	};
	

	// textbox class
	class TextBox : public GUIElement {
	public:
		TextBox(
			sf::Vector2f pos, sf::Vector2f size,
			sf::Text* text, sf::Color color, const std::string& ID = "");
		~TextBox();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }
		std::string getIBValue() { return ""; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::RectangleShape* shape;
		sf::Text* text;

		std::string ID;
	};

	// texturebox class
	class TextureBox : public GUIElement {
	public:
		TextureBox(
			sf::Vector2f pos,
			sf::Texture* texture, const std::string& ID = "");

		TextureBox(
			sf::Vector2f pos,
			sf::Texture* texture,
			sf::IntRect rect, const std::string& ID = "");

		~TextureBox();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return 0; }
		std::string getIBValue() { return ""; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }

	private:
		sf::Sprite* sprite;

		std::string ID;

	};

	// Slider
	class Slider : public GUIElement {
	public:
		Slider(
			sf::Vector2f pos,
			float size,
			float length,
			sf::Color color,
			int starting_Val = 50,
			const std::string& ID = ""
			);

		~Slider();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent();
		ElementType getType();

		int getValue() { return this->value; }
		std::string getIBValue() { return ""; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();

		std::string getID() { return this->ID; }
	private:
		std::vector<sf::RectangleShape> list;
		sf::IntRect background;

	private:
		sf::Vector2f pos;
		float size;
		float length;
		int value;

		Event event;
		std::string ID;
	};
	
	//InputBox
	class InputBox : public GUIElement{
	public:
		InputBox(sf::Vector2f pos, sf::Vector2f size, int charSize, sf::Color color, sf::Font* font, const std::string& ID = "", const std::string& def_text = "");
		~InputBox();

		void Draw(sf::RenderTarget* window);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent() { return this->event; }

		ElementType getType() { return ElementType::InputBox; }
		int getValue() { return 0; }
		std::string getIBValue() { return this->txt; };

		sf::Vector2f maxRD() { return this->background->getPosition() + this->background->getSize(); }
		sf::Vector2f minRD() { return this->background->getPosition(); }
		std::string getID() { return this->ID; }

	private:
		std::string txt;
		std::string ID;

		bool hover;
	private:
		sf::RectangleShape* background;
		sf::Text* render_text;

		Event event;
	};

	// true-false box
	class TFBox : public GUIElement {
	public:
		TFBox(sf::Vector2f pos, float size, sf::Color TrueColor,
			sf::Color FalseColor = sf::Color::Black, bool def_Val = false, const std::string& ID = "");
		~TFBox() { ; }

		void Draw(sf::RenderTarget* window);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent() { Event e = this->event; this->event = Event::None; return e; }
		ElementType getType() { return ElementType::TFBox; }
		int getValue() { return this->value; }
		std::string getIBValue() { return ""; }

		sf::Vector2f maxRD();
		sf::Vector2f minRD();
		std::string getID() { return this->ID; }

	private:
		bool value;
		std::string ID;
		int color_state;

		bool hover;

	private:
		sf::Color TrueColor;
		sf::Color FalseColor;

		Event event;

		sf::RectangleShape shape;

	};

	class BSBox : public GUIElement {
	public:
		BSBox(sf::Vector2f pos, sf::Vector2f size, sf::Color color, sf::Color TextColor,
			std::vector<std::string>& strings, sf::Font* font, int charsize = 20, int def_Val = 0, const std::string& ID = "");
		~BSBox() { ; }

		void Draw(sf::RenderTarget* window);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);
		Event getEvent() { Event e = this->event; this->event = Event::None; return e; }
		ElementType getType() { return ElementType::BSBox; }
		int getValue() { return this->value; }
		std::string getIBValue() { return ""; }

		sf::Vector2f maxRD() { return pointers[1].getPosition() + pointers[1].getSize(); }
		sf::Vector2f minRD() { return pointers[0].getPosition(); }
		std::string getID() { return this->ID; }

	private:
		void checkVal() {
			if (value < 0) {
				value = 0;
			}
			else if (value > strings.size() - 1) {
				value = strings.size() - 1;
			}
		}

		bool hoverTriangle1(sf::Vector2f mouse);
		bool hoverTriangle2(sf::Vector2f mouse);

	private:
		sf::Font* font;

	private:
		std::string ID;
		std::vector<std::string> strings;
		Event event;
		int value;

		int hover;
	private:
		std::vector<sf::RectangleShape> pointers;
		sf::Text middleText;

	private:
		std::vector<sf::Vector2f> tr1;
		std::vector<sf::Vector2f> tr2;
	};

	// GUI handler
	class GUIHandler {
	public:
		GUIHandler(sf::Vector2f pos, int margin, sf::Color color);
		~GUIHandler();

		void add_GUI_ELEMENT(GUIElement* element);
		std::vector<GUIElement*>* getArray();

		void Draw(sf::RenderTarget* target);
		void Update(float deltaTime, sf::RenderWindow* window);
		void EventUpdate(sf::Event event);

		void clear();

		size_t getArraySize();

		Event getEvent(int index);
		ElementType getElementType(int index);
		int getValue(int index);
		std::string getIBValue(int index);

		Event getEvent(const std::string& ID);
		ElementType getElementType(const std::string& ID);
		int getValue(const std::string& ID);
		std::string getIBValue(const std::string& ID);

		int getIndex(const std::string& ID);
		std::string getID(int index);

	private:
		sf::RectangleShape shape;
		std::vector<GUIElement*> elements;

	private:
		int margin;
		sf::Vector2f mRD;
		sf::Vector2f miRD;
	};
}
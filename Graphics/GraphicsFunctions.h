#pragma once
#include <SFML/Graphics.hpp>


namespace GraphFunc {
	// Draws text on the screen
	static void DrawText(sf::Vector2f pos, const std::string& textf,
		sf::Font* font, unsigned int fontSize, sf::RenderTarget* window) {

		sf::Text text(textf, *font, fontSize);
		text.setPosition(pos);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(1.f);
		window->draw(text);
	}

	// Returns text
	static sf::Text getText(const std::string& textf, sf::Font* font,
		unsigned int fontSize, sf::Vector2f pos = sf::Vector2f(0.f, 0.f)) {

		sf::Text text(textf, *font, fontSize);
		text.setPosition(pos);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(1.f);

		return text;
	}

	// creates text
	static void getText(sf::Text* ptr, const std::string& textf, sf::Font* font,
		unsigned int fontSize, sf::Vector2f pos = sf::Vector2f(0.f, 0.f)) {

		ptr = new sf::Text(textf, *font, fontSize);
		ptr->setPosition(pos);
		ptr->setFillColor(sf::Color::White);
		ptr->setOutlineColor(sf::Color::Black);
		ptr->setOutlineThickness(1.f);
	}

	// changes VertexArray color
	static void changeVerArrColor(sf::VertexArray* array, sf::Color color) {
		for (size_t i = 0; i < array->getVertexCount(); i++) {
			(*array)[i].color = color;
		}
	}

	// Returns Texture 
	static sf::Texture loadHQTexture(const std::string& location) {
		sf::Texture texture;
		texture.loadFromFile(location);
			
		texture.setSmooth(true);
		return texture;
	}

	// loads Texture 
	static bool loadHQTexture(sf::Texture* ptr, const std::string& location) {
		ptr->setSmooth(true);
		return ptr->loadFromFile(location);
	}

	// Returns Texture
	static sf::Font loadFont(const std::string& location) {
		sf::Font font;
		font.loadFromFile(location);
		return font;
	}

	// loads Texture
	static bool loadFont(sf::Font* ptr, const std::string& location) {
		return ptr->loadFromFile(location);
	}


	// Creates and saves screenshots
	static void do_ScreenShot(sf::RenderWindow* window, const std::string& location) {
		std::string string = location + "screenshot_";
		sf::Texture txt;
		txt.create(window->getSize().x, window->getSize().y);
		sf::Image img;
		txt.update(*window);

		time_t t = time(NULL);

		tm time;
		localtime_s(&time, &t);

		string += std::to_string(1900 + time.tm_year) + "_" + std::to_string(time.tm_mon + 1) +"_" + std::to_string(time.tm_mday) + "_" +
			std::to_string(time.tm_hour) + "_" + std::to_string(time.tm_min) + "_" + std::to_string(time.tm_sec) + ".png";
	

		img = txt.copyToImage();
		img.saveToFile(string);
	}

	//scales texture
	static void scaleTexture(sf::Sprite* texture, sf::Vector2f size) {
		float scaleX = size.x / texture->getTexture()->getSize().x;
		float scaleY = size.y / texture->getTexture()->getSize().y;

		texture->scale(scaleX, scaleY);
	}

	//scales texture
	static sf::Sprite scaleTextureR(sf::Sprite* texture, sf::Vector2f size) {
		float scaleX = size.x / texture->getTexture()->getSize().x;
		float scaleY = size.y / texture->getTexture()->getSize().y;

		texture->scale(scaleX, scaleY);
		return *texture;
	}

}
#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <strstream>

#define gL_isKeyPressed(key) sf::Keyboard::isKeyPressed(key)
#define gL_getRelativeMousePos(window) sf::Vector2f(sf::Mouse::getPosition(window))

namespace UI {
	class File {
	public:
		File(const std::string& filename) {
			std::fstream stream;
			stream.open(filename, std::ios::in);

			if (stream.good()) {
				std::string linia;
				while (std::getline(stream, linia)) {
					this->file.push_back(linia);
				}
			}

			stream.close();
			}

			std::vector<std::string> file;
	};
	
	static char keyToChar(sf::Keyboard::Key key) {
		// letters return lower
		if (int(key) < 26) {
			return key + 0x61;
		}
		// numers
		else if (int(key) < 36) {
			return key + 0x16;
		}
		// numpad
		else if (int(key) > 74 && int(key) < 85) {
			return key - 0x1B;
		}
		// specific keys , - \ ' / .
		else if (key == sf::Keyboard::Key::Comma) {
			return ',';
		}
		else if (key == sf::Keyboard::Key::Hyphen) {
			return '-';
		}
		else if (key == sf::Keyboard::Key::Backslash) {
			return 92;
		}
		else if (key == sf::Keyboard::Key::Quote) {
			return 39;
		}
		else if (key == sf::Keyboard::Key::Divide) {
			return '/';
		}
		else if (key == sf::Keyboard::Key::Period) {
			return '.';
		}
		else if (key == sf::Keyboard::Key::Equal) {
			return '=';
		}

		return NULL;
	}

	static char toUpperCase(char a) {
		// letters
		if (a >= 97 && a <= 122) {
			a -= 0x20;
		}
		// numbers
		else if (a >= 48 && a <= 57) {
			switch (a - 48) {
				// 1 2 3 4 5  7 8 9 0
			case 1:
			case 3:
			case 4:
			case 5:
				a = a - 16;
				break;

			case 9:
				a = a - 17;
				break;

			case 2:
				a = 64;
				break;

			case 7:
				a = 38;
				break;

			case 8:
				a = 42;
				break;

			case 0:
				a = 41;
				break;

			case 6:
				a = 94;
				break;
			}
		}
		// special keys
		else if (a == ']' || a == '[') {
			a += 32;
		}
		else if (a == ';') {
			a = ':';
		}
		// \ //
		else if (a == 92) {
			a = '|';
		}

		// '
		else if (a == 39) {
			a = '"';
		}
		else if (a == ',') {
			a = '<';
		}
		else if (a == '.') {
			a = '>';
		}
		else if (a == '/') {
			a = '?';
		}
		else if (a == '-') {
			a = '_';
		}
		else if (a == '=') {
			a = '+';
		}
		return a;
	}

	static char getChar() {
		for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(i))) {
				char a = keyToChar(sf::Keyboard::Key(i));
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
					a = toUpperCase(a);
				}
				return a;
			}
		}
		return NULL;
	}
}
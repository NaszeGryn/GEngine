#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define gL_MATH_NEWSEED() srand(int(time(NULL) ) )
#define gL_MATH_PI 3.1415926535897932384626433
#define gL_MATH_RADIAN 180/gL_MATH_PI


#define gL_V2FZERO sf::Vector2f(0.f, 0.f)
#define gL_V2IZERO sf::Vector2i(0, 0)
#define gL_V2UZERO sf::Vector2u(0U, 0U)


namespace Math {
	// Returns distance
	static float dist(sf::Vector2f a, sf::Vector2f b) {
		return sqrt( (a - b).x * (a - b).x + (a - b).y * (a - b).y) ;
	}

	// Returns normalized vector
	static sf::Vector2f normVec(sf::Vector2f a, sf::Vector2f b) {
		return (a - b) / dist(a, b);
	}

	// Returns angle
	static float getAngle(sf::Vector2f start, sf::Vector2f nxt) {
		float ab = (start - nxt).y;
		float ac = sqrt(((start - nxt).x * (start - nxt).x) + ((start - nxt).y * (start - nxt).y));

		float angle = float(asin(ab / ac) * gL_MATH_RADIAN) - 90.f;

		angle = abs(angle);
		return angle;
	}

	// returns positive angle
	static float positiveAngle(float angle) {
		if (angle < 0) {
			angle = angle + 360.f;
		}
		return angle;
	}

	static float getTriangleArea(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {
		return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x*(a.y - b.y)) / 2.f;
	}

	// returns absolute value of Vector2fs
	static sf::Vector2f v2fAbs(sf::Vector2f a) {
		return sf::Vector2f(abs(a.x), abs(a.y));
	}

	// returns random int
	static int randomI(int a, int b) {
		if (a - b != 0) {
			return (rand() % (a - b) + a);
		}
		return 0;
	}

	// returns random float
	static float randomF(int a, int b) {
		return float(randomI(a, b-1)) + (float)rand() / (float)RAND_MAX;
	}

	// returns random Vector2i
	static sf::Vector2f randomVecI(int xmin, int xmax, int ymin, int ymax) {
		return sf::Vector2f(float(randomI(xmin, xmax)), float(randomI(ymin, ymax)));
	}

	// returns random Vector2f
	static sf::Vector2f randomVecF(int xmin, int xmax, int ymin, int ymax) {
		return sf::Vector2f(float(randomF(xmin, xmax)), float(randomF(ymin, ymax)));
	}

	static char getRandomChar() {
		int f = randomI(0, 3);
		switch (f) {
		// numbers
		case 0:
			return randomI(0x30, 0x3A);
			break;
		//lower case
		case 1:
			return randomI(0x61, 0x7B);
			break;
		//upper case
		case 2:
			return randomI(0x41, 0x5B);
			break;
		}
		return NULL;
	}

	static std::string getRandomString(uint32_t length) {
		std::string s = "";

		for (int i = 0; i < length; i++)
			s += getRandomChar();

		return s;
	}

	static std::string getV2fStr(sf::Vector2f a) {
		return std::string(std::to_string(a.x) + "," + std::to_string(a.y));
	}

	// returns avg
	static sf::Vector2f avgV2f(sf::Vector2f first, sf::Vector2f second) {
		return sf::Vector2f((first.x + second.x) / 2.f, (first.y + second.y) / 2.f);
	}

	// returns avg
	static sf::Color avgColor(sf::Color a, sf::Color b) {
		return sf::Color((a.r + b.r) / 2, (a.g + b.g) / 2, (a.b + b.b) / 2);
	}

	// rotates point around (0,0)
	static sf::Vector2f rotateArZero(sf::Vector2f point, float angle) {
		angle *= 3.14159f / 180.f;
		return sf::Vector2f(point.x * cos(angle) - point.y * sin(angle),
							point.x * sin(angle) + point.y * cos(angle));
	}

	//returns avg float
	static float averageF(std::vector<float>* list) {
		float sum = 0.f;
		for (unsigned i = 0; i < list->size(); i++) {
			sum += (*list)[i];
		}
		return sum / (float)list->size();
	}

	//returns avg int
	static float averageI(std::vector<int>* list) {
		int sum = 0;
		for (unsigned i = 0; i < list->size(); i++) {
			sum += (*list)[i];
		}
		return (float)sum / (float)list->size();
	}

	//returns avg unsigned int
	static float averageU(std::vector<unsigned int>* list) {
		int sum = 0;
		for (unsigned i = 0; i < list->size(); i++) {
			sum += (*list)[i];
		}
		return (float)sum / (float)list->size();
	}

	// hex color to sf::Color
	static sf::Color strHexToColor(const std::string& hexNum) {
		if (hexNum.length() == 6) {
			return sf::Color(
				(uint8_t)strtol(hexNum.substr(0, 2).c_str(), NULL, 16),
				(uint8_t)strtol(hexNum.substr(2, 2).c_str(), NULL, 16),
				(uint8_t)strtol(hexNum.substr(4, 2).c_str(), NULL, 16)
			);
		}
		else if (hexNum.length() == 8) {
			return sf::Color(
				(uint8_t)strtol(hexNum.substr(0, 2).c_str(), NULL, 16),
				(uint8_t)strtol(hexNum.substr(2, 2).c_str(), NULL, 16),
				(uint8_t)strtol(hexNum.substr(4, 2).c_str(), NULL, 16),
				(uint8_t)strtol(hexNum.substr(6, 2).c_str(), NULL, 16)
			);
		}
		return sf::Color();
	}

	// string to sf::Vector2f
	static sf::Vector2f strToVec2f(const std::string& line) {
		std::string v1 = "";

		std::string v2 = "";
		if (line.length() > 0) {
			// finding ',' in string
			if (line.find(',') < line.length()) {
				int eqPos = strcspn(line.c_str(), ",");
				v1 = line.substr(0, eqPos);
				v2 = line.substr(eqPos + 1, line.size() - (eqPos + 1));
			}
			else {
				v1 = line;
			}
		}

		return sf::Vector2f(atof(v1.c_str()), atof(v2.c_str()));
	}

	// sf::Vector2f to string
	static std::string vec2fToStr(sf::Vector2f vector) {
		return std::to_string(vector.x) + ", " + std::to_string(vector.y);
	}

	// converts int to hex number
	static std::string intToHexStr(unsigned int a, uint16_t min_length = 0) {
		std::string nums = "0123456789ABCDEF";
		std::string result = "";
		float num = a;
		while (floor(num) > 0) {
			int r = (int)num % 16;
			result.insert(result.begin(), nums[r]);

			num /= 16;
		}

		if (min_length != 0) {
			while (result.length() < min_length) {
				result.insert(result.begin(), '0');
			}
		}

		return result;
	}

	// converts hex string to number
	static int hexStrToUInt(const std::string& number) {
		std::string nums = "0123456789ABCDEF";
		int result = 0;

		for (int i = number.size()-1; i >= 0; i--) {
			if (number[i] >= '0' && number[i] <= '9') {
				result += (number[i] - 48) * (int)pow(16, (number.size()-1)-i);
			}
			else if (number[i] >= 'A' && number[i] <= 'F') {
				result += (number[i] - 55) * (int)pow(16, (number.size() - 1) -i);
			}
			else if (number[i] >= 'a' && number[i] <= 'f') {
				result += (number[i] - 87) * (int)pow(16, (number.size() - 1) -i);
			}
			else {
				return -1;
			}
		}

		return result;
	}

	// sf::Color to string
	static std::string colToStr(sf::Color color) {
		std::string str = intToHexStr((int)color.r, 2) 
			+ intToHexStr((int)color.g, 2) 
			+ intToHexStr((int)color.b, 2);
	
		if (color.a != 255) {
			str += intToHexStr((int)color.a, 2);
		}
		
		return str;
	}

	class ColorF {
	public:
		ColorF(float r = 0.f, float g = 0.f, float b = 0.f, float a = 255.f) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
			this->check();
		}

		ColorF(sf::Color color) {
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = color.a;
			this->check();
		}



		void check() {
			check_One(r);
			check_One(g);
			check_One(b);
			check_One(a);
		}

		sf::Color getColor() {
			this->check();

			return sf::Color((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);
		}

		void add(ColorF x) {
			this->r += x.r;
			this->g += x.g;
			this->b += x.b;
			this->a += x.a;
			this->check();
		}

		void subtract(ColorF x) {
			this->r -= x.r;
			this->g -= x.g;
			this->b -= x.b;
			this->a -= x.a;
			this->check();
		}

		void multiply(float x) {
			this->r *= x;
			this->g *= x;
			this->b *= x;
			this->a *= x;
			this->check();
		}

		float r;
		float g;
		float b;
		float a;

	private:
		void check_One(float& x) {
			if (x > 255.f)
				x = 255.f;
			else if (x < 0.f)
				x = 0.f;
		}
	
	};


	class Counter {
	public:
		Counter(int maxValue = 1) {
			this->actual = 0;
			this->max = maxValue;
		}

		bool Update(int value, bool restart = true) {
			this->actual += value;
			return this->isDone(restart);
		}
	private:
		bool isDone(bool restart = true) {
			if (actual >= max) {
				if (restart)
					actual = 0.f;

				return true;
			}
			return false;
		}

	private:
		int actual;
		int max;
	};
}

namespace Time {
	// clock class
	class Clock {
	public:
		Clock() {
			this->clock = new sf::Clock();
			this->deltaTime = 0.f;
		}

		~Clock() {
			delete this->clock;
		}

		void Update() {
			this->deltaTime = clock->restart().asSeconds();
		}

		float deltaTime;

	private:
		sf::Clock* clock;
	};

	// timer class
	class Timer {
	public:
		Timer(float maxTime = 1.f) {
			this->loc_Time = 0.f;
			this->maxTime = maxTime;
		}

		bool Update(float deltaTime, bool restart = true) {
			this->loc_Time += deltaTime;
			return this->isDone(restart);
		}

		bool CUpdate(Time::Clock& clock, bool restart = true) {
			this->loc_Time += clock.deltaTime;
			return this->isDone(restart);
		}

	private:
		bool isDone(bool restart = true) {
			if (loc_Time >= maxTime) {
				if (restart)
					loc_Time = 0.f;

				return true;
			}
			return false;
		}

		float loc_Time;
		float maxTime;
	};
}

namespace Logic {
	static bool XOR(bool a, bool b) {
		return (a || b) && !(a && b);
	}
	static bool XNOR(bool a, bool b) {
		return !((a || b) && !(a && b));
	}
}
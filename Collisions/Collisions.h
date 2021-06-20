#pragma once
#include <SFML/Graphics.hpp>

namespace Collisions {
	//collisions are buggy

	struct CLine {
		sf::Vector2f a;
		sf::Vector2f b;
	};

	enum class ColliderType {
		Poly = 0,
		Circle = 1
	};

	/*class Collider {
	public:
		virtual std::vector<sf::Vector2f>* getPoly() = 0;
		virtual float getRadius() = 0;
		virtual ColliderType getType() = 0;
		virtual sf::Vector2f getPos() = 0;
		virtual void Update(sf::RectangleShape& shape) = 0;
		virtual void Update(sf::CircleShape* shape) = 0;
	};*/

	class Poly {
	public:
		Poly(sf::RectangleShape& shape) {
			this->Update(shape);
		}

		Poly(sf::Vector2f pos, sf::Vector2f size) {
			this->Update(pos, size);
		}

		Poly() { ; }

		void Update(sf::RectangleShape& shape) {
			this->pos = shape.getPosition() - shape.getOrigin();
			this->size = shape.getSize();
		}
		void Update(sf::Vector2f pos, sf::Vector2f size) {
			this->pos = pos;
			this->size = size;
		}

		ColliderType getType() {
			return ColliderType::Poly;
		}

		sf::Vector2f pos;
		sf::Vector2f size;
	};

	/*
	class Circle {
	public:
		// CENTERED CIRCLE
		Circle(float radius, sf::Vector2f pos) {
			this->radius = radius;
			this->pos = pos;

			this->createPoly();
		}

		// CENTERED CIRCLE
		Circle(sf::CircleShape* shape) {
			this->Update(shape);
		}

		Circle() { this->radius = 0.f; this->pos = sf::Vector2f(0.f, 0.f);
			this->createPoly();
		}

		~Circle() {
			poly.clear();
		}

		void Update(sf::CircleShape* shape) {
			this->radius = shape->getRadius();
			this->pos = shape->getPosition();

			this->createPoly();
		}
		void Update(sf::RectangleShape& shape) {
			;
		}

		std::vector<sf::Vector2f>* getPoly() {
			return &poly;
		}

		float getRadius() {
			return radius;
		}
		sf::Vector2f getPos() {
			return pos;
		}

		ColliderType getType() {
			return ColliderType::Circle;
		}

	private:
		void createPoly() {
			poly.clear();
			poly.resize(2);
			poly.push_back(pos);
			poly.push_back(pos + sf::Vector2f(radius, radius));
		}

		std::vector<sf::Vector2f> poly;

		float radius;
		sf::Vector2f pos;
	};
	*/


	static bool collide(Poly* a, Poly* b) {

		if (a->pos.x < b->pos.x + b->size.x &&
			a->pos.x + a->size.x > b->pos.x &&
			a->pos.y < b->pos.y + b->size.y &&
			a->pos.y + a->size.y > b->pos.y) {
				return true;
		}
			
		return false;
	}
}





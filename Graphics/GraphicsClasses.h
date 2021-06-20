#pragma once
#include <SFML/Graphics.hpp>


namespace Draw {
	// Animated sprite handler
	class SpriteAnimator {
	public:
		SpriteAnimator(sf::Sprite* sprite, float AnimInterval, sf::Vector2i frameSize, int anim) {
			this->sprite = sprite;
			this->frameSize = frameSize;

			this->AnimInterval = AnimInterval;

			this->animTime = 0.f;
			this->xanim = 0;
			this->anim = anim;
			this->maxAnim = int(floor(this->sprite->getTexture()->getSize().x / frameSize.x)) - 1; // it bugs out without - 1
		}

		void changeAnim(int anim) {
			this->xanim = 0;
			this->anim = anim;
		}

		void setMaxAnim(int maxAnim) {
			this->maxAnim = maxAnim;
		}

		void Update(float deltaTime) {
			this->animTime += deltaTime;

			if (this->animTime >= this->AnimInterval) {
				xanim++;

				if (xanim > maxAnim) {
					xanim = 0;
				}

				this->sprite->setTextureRect(sf::IntRect(xanim * frameSize.x, anim * frameSize.y,
					frameSize.x, frameSize.y));

				this->animTime = 0.f;
			}
		}

		int getAnim() {
			return this->anim;
		}

		int getFrame() {
			return this->xanim;
		}

		int getFrameLimit() {
			return this->maxAnim;
		}

		sf::Sprite* getSprite() {
			return this->sprite;
		}
	private:
		sf::Sprite* sprite;
		sf::Vector2i frameSize;

		float AnimInterval; // interval between animations
		float animTime; // animation time
		int anim; // animation
		int xanim; // frame now
		int maxAnim; // frame limit
	};

	// Types of gradient
	enum class GradientType {
		LeftToRight = 0,
		TopToBottom = 1,
		TopLeftToBottomRight = 2,
		TopRightToBottomLeft = 3,
		TopLeft = 4,
		TopRight = 5,
		BottomLeft = 6,
		BottomRight = 7
	};

	// Gradient Rectangle
	class GradientRect {
	public:
		GradientRect(sf::FloatRect pas, GradientType type, sf::Color colorA, sf::Color colorB) {
			std::vector<sf::Color>* colors;

			this->rect.setPrimitiveType(sf::Quads);
			switch (type) {
			case GradientType::LeftToRight:
					for (int i = 0; i < 2; i++) {
						colors->push_back(colorA);
						colors->push_back(colorB);
					}
					break;
			case GradientType::TopToBottom: 
					colors->push_back(colorA);
					colors->push_back(colorA);

					colors->push_back(colorB);
					colors->push_back(colorB);
					break;
			case GradientType::TopLeftToBottomRight:
					colors->push_back(colorA);
					colors->push_back(Math::avgColor(colorA, colorB));
					colors->push_back(Math::avgColor(colorA, colorB));
					colors->push_back(colorB);
					break;
			case GradientType::TopRightToBottomLeft:
					colors->push_back(Math::avgColor(colorA, colorB));
					colors->push_back(colorA);
					colors->push_back(colorB);
					colors->push_back(Math::avgColor(colorA, colorB));
					break;
			case GradientType::TopLeft:
					colors->push_back(colorB);
					colors->push_back(colorA);
					colors->push_back(colorA);
					colors->push_back(colorA);
					break;
			case GradientType::TopRight:
					colors->push_back(colorA);
					colors->push_back(colorB);
					colors->push_back(colorA);
					colors->push_back(colorA);
					break;
			case GradientType::BottomLeft:
					colors->push_back(colorA);
					colors->push_back(colorA);
					colors->push_back(colorB);
					colors->push_back(colorA);
					break;
			case GradientType::BottomRight:
					colors->push_back(colorA);
					colors->push_back(colorA);
					colors->push_back(colorA);
					colors->push_back(colorB);
					break;
			}

			this->rect.append(sf::Vertex(sf::Vector2f(pas.left, pas.top), (*colors)[0]));
			this->rect.append(sf::Vertex(sf::Vector2f(pas.left + pas.width, pas.top), (*colors)[1]));
			this->rect.append(sf::Vertex(sf::Vector2f(pas.left + pas.width, pas.top + pas.height), (*colors)[3]));
			this->rect.append(sf::Vertex(sf::Vector2f(pas.left, pas.top + pas.height), (*colors)[2]));
			
			
			colors->clear();
			delete colors;
			colors = NULL;
		}

		void Draw(sf::RenderWindow* window) {
			window->draw(this->rect);
		}
		sf::VertexArray* getArray() {
			return &this->rect;
		}
	private:
		sf::VertexArray rect;
	};

	// Line
	class Line {
	public:
		Line(sf::Vector2f a, sf::Vector2f b, sf::Color color) {
			ar = sf::VertexArray(sf::Lines);

			ar.append(sf::Vertex(a, color));
			ar.append(sf::Vertex(b, color));
		}

		void Draw(sf::RenderWindow* window) {
			window->draw(this->ar);
		}

		sf::VertexArray* getArray() {
			return &this->ar;
		}
	private:
		sf::VertexArray ar;
	};

	// Point (circle)
	class Point {
	public:
		Point(sf::Vector2f position, float size, sf::Color color) {
			this->shape = new sf::CircleShape(size);
			this->shape->setPosition(position);
			this->shape->setFillColor(color);
			this->shape->setOrigin(sf::Vector2f(size, size));
		}
		~Point() {
			delete this->shape;
			this->shape = NULL;
		}

		void Draw(sf::RenderWindow* window) {
			window->draw(*this->shape);
		}

		sf::CircleShape* getShape() { return this->shape; }

	private:
		sf::CircleShape* shape;
	};


}
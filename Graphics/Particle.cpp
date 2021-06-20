#pragma once
#include "Particles.h"


namespace Particles {
	Particle::Particle(const ParticleProperties& properties) {
		this->prop = properties;

		// init part
		part = sf::RectangleShape(sf::Vector2f(prop.StartSize, prop.StartSize));
		part.setPosition(prop.position);
		part.setFillColor(prop.startColor);
		rem_time = prop.lifeTime;
	}

	void Particle::Update(float dtime) {
		if (!finished()) {
			this->rem_time -= dtime;

			this->part.move(prop.move_Dir * dtime);
			this->part.rotate(prop.rotation_speed * dtime);

			// color transition, alpha transition and size transition
			sf::Color newColor = this->part.getFillColor();
			// alpha
			alpha = 255 * (this->rem_time / this->prop.lifeTime);
			newColor.a = (uint8_t)alpha;

			// size
			sf::Vector2f newSize = sf::Vector2f(prop.EndSize, prop.EndSize);
			newSize += (sf::Vector2f(prop.StartSize, prop.StartSize) -
				sf::Vector2f(prop.EndSize, prop.EndSize)) * (this->rem_time / this->prop.lifeTime);

			this->part.setSize(newSize);

			this->part.setFillColor(newColor);

			this->part.setOrigin(part.getSize() / 2.f);
		}
	}
	void Particle::Draw(sf::RenderTarget* target) {
		if (!finished()) {
			target->draw(this->part);
		}
	}

	void Particle::reStart(const ParticleProperties& properties) {
		this->prop = properties;

		// init part
		part = sf::RectangleShape(sf::Vector2f(prop.StartSize, prop.StartSize));
		part.setPosition(prop.position);
		part.setFillColor(prop.startColor);
		rem_time = prop.lifeTime;
	}


}
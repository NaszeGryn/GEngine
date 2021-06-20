#pragma once
#include "Particles.h"

namespace Particles {
	ParticleHandler::ParticleHandler(ParticleHandlerProperties& h_properties, ParticleProperties& properties, bool adding) {
		this->handler_properties = h_properties;
		this->prop = properties;

		this->adding = adding;
		this->particles.resize(this->handler_properties.vectorSize);

		this->time_between_adding = 0.f;
		this->max_add = this->particles.size() * this->handler_properties.max_add_percent;
	}

	void ParticleHandler::Update(float dtime) {
		this->time_between_adding += dtime;
		if (this->time_between_adding > 0.05f) {
			this->RefreshParticles(dtime);
			time_between_adding = 0.f;
		}
		for (int i = this->particles.size() - 1; i >= 0; i--) {
			this->particles[i].Update(dtime);
		}
	}

	void ParticleHandler::Draw(sf::RenderTarget* target) {
		for (int i = this->particles.size()-1; i >= 0; i--) {
			this->particles[i].Draw(target);
		}
	}



	void ParticleHandler::AddParticles() {
		ParticleProperties pprop;
		for (int i = 0; i < int(this->particles.size() / 10); i++) {
			pprop = prop;

			pprop.lifeTime += Math::randomF(0, this->handler_properties.lifetime_Variety);
			if (this->handler_properties.type == ParticleType::Line) {
				pprop.move_Dir = Math::rotateArZero(pprop.move_Dir, Math::randomF(-handler_properties.span / 2.f, handler_properties.span / 2.f));
			}
			else {
				pprop.move_Dir = Math::rotateArZero(pprop.move_Dir, Math::randomF(0, 360.f));
			}
			this->particles[i].reStart(pprop);
		}
	}

	void ParticleHandler::RefreshParticles(float dtime) {
		if (adding) {
			ParticleProperties pprop;
			int added = 0;
			for (int i = 0; i < this->particles.size(); i++) {
				if (max_add == added) {
					break;
				}
				else if (this->particles[i].finished()) {
					pprop = prop;
					added++;
					pprop.lifeTime += Math::randomF(0, this->handler_properties.lifetime_Variety);
					if (this->handler_properties.type == ParticleType::Line) {
						pprop.move_Dir = Math::rotateArZero(pprop.move_Dir, Math::randomF(-handler_properties.span / 2.f, handler_properties.span / 2.f));
					}
					else {
						pprop.move_Dir = Math::rotateArZero(pprop.move_Dir, Math::randomF(0, 360.f));
					}

					this->particles[i].reStart(pprop);
				}
			}
		}
	}
}
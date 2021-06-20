#pragma once
#include <SFML/Graphics.hpp>
#include "Math/Math.h"

namespace Particles {
	enum ParticleType {
		Line = 0,
		Out = 1
	};

	// float s_Size, float e_Size, float rot_Speed, sf::Vector2f pos, sf::Vector2f move, sf::Color s_Color, float l_Time = 1.f
	struct ParticleProperties {
		ParticleProperties() { ; }
		// float s_Size, float e_Size, float rot_Speed, sf::Vector2f pos, sf::Vector2f move, sf::Color s_Color, float l_Time = 1.f
		ParticleProperties(float s_Size, float e_Size, float rot_Speed,
			sf::Vector2f pos, sf::Vector2f move, sf::Color s_Color, float l_Time = 1.f) {
			this->StartSize = s_Size;
			this->EndSize = e_Size;
			this->rotation_speed = rot_Speed;
			this->position = pos;
			this->move_Dir = move;
			this->startColor = s_Color;
			this->lifeTime = l_Time;
		}

		float StartSize, EndSize;
		float rotation_speed;
		sf::Vector2f position;
		sf::Vector2f move_Dir;

		sf::Color startColor;

		float lifeTime = 1.f;
	};

	// ParticleType particle_Type, uint16_t vector_Size, int span = 0, int l_Variety = 1, float max_a_percent = 1.f
	struct ParticleHandlerProperties {
		ParticleHandlerProperties() { ; }
		// ParticleType particle_Type, uint16_t vector_Size, int span = 0, int l_Variety = 1, float max_a_percent = 1.f
		ParticleHandlerProperties(ParticleType p_Type, uint16_t v_Size, int sp, int l_Variety, float max_a_percent) {
			this->type = p_Type;
			this->vectorSize = v_Size;
			this->span = sp;
			this->lifetime_Variety = l_Variety;
			this->max_add_percent = max_a_percent;
		}
		ParticleType type;
		uint16_t vectorSize;

		int span;
		int lifetime_Variety;

		float max_add_percent;
	};

	class Particle {
	public:
		Particle() {
			this->prop = ParticleProperties();
			this->part = sf::RectangleShape();
			this->alpha = 255.f;
			this->rem_time = 0.f;
		}
		Particle(const ParticleProperties& properties);

		void Update(float dtime);
		void Draw(sf::RenderTarget* target);
		
		void reStart(const ParticleProperties& properties);
	public:
		bool finished() {
			return (this->rem_time <= 0.f);
		}

	private:
		ParticleProperties prop;
		float rem_time;
		float alpha;

	private:
		sf::RectangleShape part;

	};

	class ParticleHandler {
	public:
		ParticleHandler(ParticleHandlerProperties& h_properties, ParticleProperties& properties, bool adding);

		void Update(float dtime);

		void Draw(sf::RenderTarget* target);

		void changeAdding(bool adding) {
			this->adding = adding;
		}
	private:
		bool adding;
		ParticleProperties prop;
		ParticleHandlerProperties handler_properties;
		std::vector<Particle> particles;

		float time_between_adding;
		int max_add;

	private:
		void RefreshParticles(float dtime);
		void AddParticles();
	};

}

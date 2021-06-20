#pragma once
#include <SFML/Audio.hpp>

namespace Audio {
	static sf::SoundBuffer getBuffer(const std::string& location) {
		sf::SoundBuffer buffer;
		buffer.loadFromFile(location);
		return buffer;
	}


	class Sound {
	public:
		Sound(const std::string& filename, float volume, bool loop) {
			this->buffer = new sf::SoundBuffer();
			this->buffer->loadFromFile(filename);
			this->sound = new sf::Sound(*this->buffer);
			this->sound->setVolume(volume);
			this->sound->setLoop(loop);
		}
		Sound(sf::SoundBuffer* buffer, float volume, bool loop) {
			this->buffer = new sf::SoundBuffer(*buffer);
			this->sound = new sf::Sound(*this->buffer);
			this->sound->setVolume(volume);
			this->sound->setLoop(loop);
		}
		~Sound() {
			delete this->sound;
			delete this->buffer;
			this->buffer = NULL;
			this->sound = NULL;
		}

		void setVolume(float volume) { this->sound->setVolume(volume); }

		void play() { this->sound->play(); }
		void stop() { this->sound->stop(); }

		sf::Sound* getSound() { return this->sound; }
		sf::SoundBuffer* getBuffer() { return this->buffer; }
	private:
		sf::Sound* sound;
		sf::SoundBuffer* buffer;
	};
}
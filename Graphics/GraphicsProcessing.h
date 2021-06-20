#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Processing {
	// returns negative
	static sf::Texture getNegative(sf::Texture texture) {
		sf::Image img = texture.copyToImage();
	
		for (unsigned int i = 0; i < img.getSize().x; i++) {
			for (unsigned int j = 0; j < img.getSize().y; j++) {
				sf::Color pixel = img.getPixel(i, j);
				pixel.r = 255 - pixel.r;
				pixel.g = 255 - pixel.g;
				pixel.b = 255 - pixel.b;
				img.setPixel(i, j, pixel);
			}
		}
		texture.update(img);

		return texture;
	}

	// multiplies colors
	static sf::Texture multiply(sf::Texture texture, float val) {
		sf::Image img = texture.copyToImage();
		float f;
		for (unsigned int i = 0; i < img.getSize().x; i++) {
			for (unsigned int j = 0; j < img.getSize().y; j++) {
				sf::Color pixel = img.getPixel(i, j);

				f = pixel.r * val;
				if (f > 255) {
					f = 255.f;
				}
				pixel.r = sf::Uint8(f);

				f = pixel.g * val;
				if (f > 255) {
					f = 255.f;
				}

				pixel.g = sf::Uint8(f);

				f = pixel.b * val;
				if (f > 255) {
					f = 255.f;
				}

				pixel.b = sf::Uint8(f);
				img.setPixel(i, j, pixel);
			}
		}
		texture.update(img);

		return texture;
	}
}

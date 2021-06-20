#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define gL_log(x) std::cout << x << std::endl

static void showV2f(sf::Vector2f a) {
	std::cout << "x: " << a.x << ", y: " << a.y << std::endl;
}

static void showV3f(sf::Vector3f a) {
	std::cout << "x: " << a.x << ", y: " << a.y << ", z: " << a.z << std::endl;
}

static void showColor(sf::Color a) {
	std::cout << "r: " << a.r << ", g: " << a.g << ", b: " << a.b << ", a: " << a.a << std::endl;
}
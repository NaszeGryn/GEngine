#pragma once
#include <SFML/Network.hpp>

#define gL_IP(a, b, c, d) sf::IpAddress(a, b, c, d)
#define gL_cIP(str) sf::IpAddress(str);
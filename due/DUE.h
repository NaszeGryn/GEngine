#pragma once
#include <GLEngine.h>

// creates mousePos variable in Update in DUE
#define GLE_UTL_mousePosTh() sf::Vector2f mousePos; if (this->window != NULL)\
	{	mousePos = sf::Vector2f(sf::Mouse::getPosition(*this->window));}\
	else {	mousePos = sf::Vector2f(sf::Mouse::getPosition());}

namespace GS {
	struct GameState;
}

// Draw, Update, EventUpdate
class DUE {
public:
	virtual GS::GameState* getGState() = 0;
	virtual void Draw() = 0;

	virtual void Update(float dTime) = 0;

	virtual void EventUpdate() = 0;
	virtual int getState() = 0;
			
	virtual sf::RenderWindow* getWindow() = 0;

};
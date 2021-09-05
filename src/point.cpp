#include "point.hpp"

Point::Point() : Point::Point(0, 0) {}

Point::Point(int x, int y, bool locked)
{
	this->pos = sf::Vector2f(x, y);
	this->prevPos = sf::Vector2f(x, y);
	this->locked = locked;
	
	shape = sf::CircleShape(5.f);
	shape.setOrigin(5.f, 5.f);
	this->updateShape();
}

// void Point::update(float deltaTime)
// {

// }

void Point::updateShape()
{
	shape.setFillColor(locked ? sf::Color(0xeb4034ff) : sf::Color(0xeeeeeeff));
	shape.setPosition(pos);
}

void Point::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw( shape, states );
}
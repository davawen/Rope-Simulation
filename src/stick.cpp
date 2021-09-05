#include "stick.hpp"

Stick::Stick(Point &pointA, Point &pointB)
{
	this->pointA = &pointA;
	this->pointB = &pointB;
	
	sf::Vector2f diff = pointB.pos - pointA.pos;
	
	this->length = sqrtf( diff.x * diff.x + diff.y * diff.y );
	
	this->shape = sf::VertexArray(sf::PrimitiveType::LineStrip, 2);
	this->shape[0].position = pointA.pos;
	this->shape[1].position = pointB.pos;
}

void Stick::updateShape()
{
	this->shape[0].position = pointA->pos;
	this->shape[1].position = pointB->pos;
}

void Stick::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(shape, states);
}
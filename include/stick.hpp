#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

#include "point.hpp"

class Stick : public sf::Drawable
{
	private:
		sf::VertexArray shape;
		
	public:
		Point *pointA, *pointB;
		float length;
		
		Stick(Point &pointA, Point &pointB);
		void updateShape();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
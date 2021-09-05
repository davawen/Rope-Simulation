#pragma once

#include <SFML/Graphics.hpp>

class Point : public sf::Drawable
{
	private:
		sf::CircleShape shape;
		
	public:
		bool locked;
		sf::Vector2f pos, prevPos;
		
		Point();
		Point(int x, int y, bool locked = false);
		
		void updateShape();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
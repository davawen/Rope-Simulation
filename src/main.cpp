#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "point.hpp"
#include "stick.hpp"

void simulate(std::vector<Point> &points, std::vector<Stick> &sticks, float deltaTime)
{
	for(auto &p : points)
	{
		if(p.locked) continue;
	
		sf::Vector2f velocity = p.pos - p.prevPos;
		p.prevPos = p.pos;
		
		p.pos += velocity;
		p.pos.y += 98.1f * deltaTime * deltaTime;
	}
	
	// std::shuffle(sticks.begin(), sticks.end(), std::default_random_engine(rand() % 10000));
	
	for(int i = 0; i < 3; i++)
	{
		for(auto &stick : sticks)
		{
			sf::Vector2f diff = stick.pointB->pos - stick.pointA->pos;
			
			float dist = sqrtf(diff.x * diff.x + diff.y * diff.y);
			float distDiff = stick.length - dist;
			float distPercent = distDiff / dist / 2.f;
			
			sf::Vector2f offset = diff * distPercent;
			
			if(!stick.pointA->locked) stick.pointA->pos -= offset;
			if(!stick.pointB->locked) stick.pointB->pos += offset;
			
			// sf::Vector2f center = (stick.pointA->pos + stick.pointB->pos) / 2.f;
			// sf::Vector2f dir = stick.pointA->pos - stick.pointB->pos;
			// float dirLength = sqrtf(dir.x * dir.x + dir.y * dir.y);
			// dir /= dirLength;
			
			// if(!stick.pointA->locked) stick.pointA->pos = center + dir * stick.length / 2.f;
			// if(!stick.pointB->locked) stick.pointB->pos = center - dir * stick.length / 2.f;
		}
	}
}

int main(int argc, char **argv)
{
	sf::RenderWindow window{sf::VideoMode(600, 600), "Window", sf::Style::Default};
	
	std::vector<Point> points;
	points.reserve(13);
	
	for(int i = 300; i > 0; i -= 30)
	{
		points.push_back(Point(i, 100));
	}
	points[0].locked = true;
	
	points.push_back(Point(0, 80));
	points.push_back(Point(-20, 100));
	points.push_back(Point(0, 120));
	
	std::vector<Stick> sticks;
	for(unsigned long i = 0; i < points.size()-1; i++)
	{
		sticks.push_back( Stick( points[i], points[i+1] ) );
	}
	
	sticks.push_back(Stick( points[12], points[9] ));
	sticks.push_back(Stick( points[12], points[10] ));
	
	sf::Clock __deltaClock;
	float delta = 0.f;
	float deltaTime = 0.f;
	
	bool paused = true;
	
	Point *movingPoint = NULL;
	
	while(window.isOpen())
	{
		delta = __deltaClock.restart().asSeconds();
		
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch(event.key.code)
					{
						case sf::Keyboard::Key::Space:
							paused = !paused;
							break;
						default:
							break;
					}
					break;
				case sf::Event::MouseButtonPressed:
					switch(event.mouseButton.button)
					{
						case sf::Mouse::Button::Left:
							for(auto &p : points)
							{
								sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
								sf::Vector2f diff = mousePos - p.pos;
								
								if(diff.x * diff.x + diff.y * diff.y <= 25.f)
								{
									p.locked = !p.locked;
									break;
								}
							}
							break;
						case sf::Mouse::Button::Middle:
							for(auto &p : points)
							{
								sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
								sf::Vector2f diff = mousePos - p.pos;
								
								if(diff.x * diff.x + diff.y * diff.y <= 25.f)
								{
									movingPoint = &p;
									break;
								}
							}
							break;
						default:
							break;
					}
					break;
				case sf::Event::MouseButtonReleased:
					switch(event.mouseButton.button)
					{
						case sf::Mouse::Button::Middle:
							movingPoint = NULL;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
		
		if(movingPoint != NULL)
		{
			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
			
			movingPoint->pos = mousePos;
		}
		
		deltaTime += delta;
		
		while(deltaTime > 1.f/60.f)
		{
			window.clear();
			
			if(!paused) simulate(points, sticks, deltaTime);
			
			for(auto &p : points)
			{
				p.updateShape();
				window.draw(p);
			}
			
			for(auto &stick : sticks)
			{
				stick.updateShape();
				window.draw(stick);
			}
			
			deltaTime -= 1.f/60.f;
		}
		
		window.display();
	}
	
	return 0;
}
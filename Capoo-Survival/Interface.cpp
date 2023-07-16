#include "stdafx.h"
#include "Interface.h"

bool interface_uninitialized = true;
sf::Font font_pixel;

sf::Vector2f changeV2itoV2f(sf::Vector2i vec) {
	return sf::Vector2f((int)vec.x, (int)vec.y);
}
sf::Vector2i changeV2ftoV2i(sf::Vector2f vec) {
	return sf::Vector2i((float)vec.x, (float)vec.y);
}
sf::Vector2i getMousePosition(sf::RenderWindow& window) {
	sf::Vector2f windowPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	//	std::printf("MOUSE: %d %d\n", (int)windowPos.x, (int)windowPos.y);
	return sf::Vector2i((int)windowPos.x, (int)(windowPos.y));
}

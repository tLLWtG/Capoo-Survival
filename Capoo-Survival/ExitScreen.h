#pragma once

#ifndef EXITSCREEN_H
#define EXITSCREEN_H

#include "Interface.h"

class ExitScreen : public Interface {
public:
	ExitScreen();
	int show(sf::RenderWindow& window);


private:
	sf::Font _font_exit;
};


#endif

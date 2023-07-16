#pragma once

#ifndef MAINMENU_H
#define MAINMENU_H

#include "Interface.h"
#include "Animator.h"

class Mainmenu : public Interface {
public:

	enum MenuResult {
		Playing, Exiting
	};

	Mainmenu();
	MenuResult show(sf::RenderWindow& window);
	void click(sf::RenderWindow& window);

private:
};

#endif

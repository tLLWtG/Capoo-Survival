#pragma once

sf::Vector2f changeV2itoV2f(sf::Vector2i vec);
sf::Vector2i changeV2ftoV2i(sf::Vector2f vec);
sf::Vector2i getMousePosition(sf::RenderWindow& window);

sf::Vector2f getWindowStart();

class Button {
private:
	enum ButtonType {
		Icon, Text
	};
	ButtonType _type;
	bool _clickState = false;

	// Icon
	sf::Sprite _sprite;
	// Text
	sf::Text _text;
	sf::Font& _font;
	sf::Sprite _icon_unpointed;
	sf::Sprite _icon_pointed;

	sf::Vector2f _position;
	sf::Rect<int> getSpriteBounds(const sf::Sprite& sprite);

	const float stressFactor = 1.2f;

public:
	std::string name;
	Button(const sf::Vector2f position, std::string const& filepath, std::string const& buttonName);
	Button(const sf::Vector2f position, const std::wstring& str, std::string const& buttonName);

	sf::Rect<int> _rect;
	bool isPointed(sf::Vector2i clickPosition);
	const float stress_factor = 1.1;
	void updateStatus(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void darken();
};

class Interface {
public:
	Interface();

	void addIconButton(const sf::Vector2f& position, std::string const& filepath, std::string const& name);
	void addTextButton(const sf::Vector2f& position, const std::wstring& str, std::string const& name);
	void setBackground(std::string const& filepath);
	void drawBackground(sf::RenderWindow& window);
	void drawButton(sf::RenderWindow& window);
	void drawMouse(sf::RenderWindow& window);
	std::string getClickButtonName(sf::Vector2i clickPosition);
	void drawCrosshairs(sf::RenderWindow& window);

	void darkenWindow(sf::RenderWindow& window);
	

protected:
	std::vector<Button> _buttons;
	sf::Sprite _backgroundSprite;
	sf::Sprite _mouse;

protected:
	sf::Font _font;
};


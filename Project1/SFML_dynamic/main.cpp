#include <Windows.h>

#include <SFML\Graphics.hpp>

#ifdef _DEBUG
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#else
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#endif

class Character
{
public:
	Character()
	{
		shape_.setRadius(10.0f);
		shape_.setPosition(sf::Vector2f(10, 10));
		shape_.setFillColor(sf::Color::White);
		speed_ = 50.0f;
		shape_.setOrigin(10, 10);
	}

	sf::Vector2f get_position()
	{
		return position_;
	}

	void set_position(sf::Vector2f position)
	{
		position_ = position;
	}

	sf::CircleShape get_shape()
	{
		return shape_;
	}

	void Move(sf::Vector2f direction, float delta_time)
	{
		if (direction != sf::Vector2f(0, 0))
		{
			shape_.setRotation(0);
			shape_.setScale(1, 1);

			if (direction.x < 0)
				shape_.setScale(-1, 1);
			else if (direction.y < 0)
				shape_.setRotation(-90);
			else if (direction.y > 0)
				shape_.setRotation(90);
		}

		shape_.move(direction * speed_ * delta_time);

	}

	void set_shape_texture(sf::Texture* texture_)
	{
		shape_.setTexture(texture_);
	}

private:
	sf::CircleShape shape_;
	sf::Vector2f position_;
	float speed_;
	sf::Texture texture_;
};


// Globala variabeler
Character* character;

// Funktionsprototyper
void UserInput(float delta_time);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Pac-man");
	character = new Character();
	sf::Clock delta_clock;

	sf::Texture texture;
	if (!texture.loadFromFile("../../Textures/pacman2.png"))
	{
		// error...
		return 0;
	}
	character->set_shape_texture(&texture);

	while (window.isOpen())
	{
		sf::Time dt = delta_clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		UserInput(dt.asSeconds());

		window.clear();
		window.draw(character->get_shape());
		window.display();
	}

	delete character;
	return 0;
}

void UserInput(float delta_time)
{
	sf::Vector2f direction(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction.x = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction.x = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction.y = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction.y = 1;

	character->Move(direction, delta_time);
}
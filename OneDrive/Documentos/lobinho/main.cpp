#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height) {
    sprite.setScale(width / sprite.getLocalBounds().width, height / sprite.getLocalBounds().height);
}

struct Entity {
    int x {0}; 
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture):
        x {x}, y {y}, step {step}, sprite(texture) {
    }

    void draw(sf::RenderWindow& window) { 
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }
};

struct Board {
	int nc {0};
	int nl {0};
	int step {0};
	sf::Sprite sprite;
	sf::RectangleShape rect;
    Board(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);

        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(2);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);
        for (int i = 0; i < nc; i++) {
            for (int j = 0; j < nl; j++) {
                rect.setPosition(i * step, j * step);
                window.draw(rect);
            }
        }
    }
};

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys) {
    if (key == move_keys[0])
        entity.x--;
    else if (key == move_keys[1])
        entity.y--;
    else if (key == move_keys[2])
        entity.x++;
    else if (key == move_keys[3])
        entity.y++;
}

int main() {
	
	sf::Texture monstro_tex;
	if(! monstro_tex.loadFromFile("sul.png")) {
		std::cout << "Error loading texture" << std::endl;
		exit(1);
	}
	
	sf::Texture doo_tex;
	if(! doo_tex.loadFromFile("Scooby.png")) {
		std::cout << "Error loading texture" << std::endl;
		exit(1);
	}
	
	sf::Texture park_tex;
	if(! park_tex.loadFromFile("Parque.jpg")) {
		std::cout << "Error loading texture" << std::endl;
		exit(1);
	}
	
	const int STEP {100};
	
	Entity monstro(1, 1, STEP, monstro_tex);
	Entity doo(3, 3, STEP, doo_tex);
	Board board(7, 5, STEP, park_tex);
	
	sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "Sullivan e Scooby-doo no Parque do Cocó!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
            	if (event.key.code == sf::Keyboard::Left) {
            		monstro.x--;
				} else if (event.key.code == sf::Keyboard::Up) {
					monstro.y--;
				} else if (event.key.code == sf::Keyboard::Right) {
					monstro.x++;
				} else if (event.key.code == sf::Keyboard::Down) {
					monstro.y++; 
				} if (event.key.code == sf::Keyboard::A) {
            		doo.x--;
				} else if (event.key.code == sf::Keyboard::W) {
					doo.y--;
				} else if (event.key.code == sf::Keyboard::D) {
					doo.x++;
				} else if (event.key.code == sf::Keyboard::S) {
					doo.y++; 
				} 
			}
        }
        
        window.clear();
        board.draw(window);
        monstro.draw(window);
        doo.draw(window);
        window.display(); 
        
    }

    return 0;
}

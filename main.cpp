/*
	SFML Falling Sand Simulation
	Leon Rode - leon.rode13@gmail.com
	Completed on April 29, 2021.
	License: GNU GPL v3 - https://www.gnu.org/licenses/gpl-3.0.en.html
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class World {
private:
	
	static const int width = 161, height = 161; // 160 + 1 to eliminate the need for bounds checking
	
	/*
		`privategrid` is the container for the state that the previous frame held.
		`grid` is where the new updates are written to, and therefore drawn from.
		What otherwise happens is, for example, a sand falls down, and then as we iterate
		to the next row, that sand falls down again, and so on, until the sand drops to the ground 
		all in one frame.
	*/
	int privategrid[width][height]; 
	int grid[width][height];
public:
	const int sandSize = 5;

	World() {
		for (int i = 0; i < width - 1; i++) {
			for (int j = 0; j < height - 1; j++) {
				privategrid[i][j] = 0;
				grid[i][j] = 0;
			}
		}
		
	}
	void update() {
		

		for (int i = 0; i < width - 1; i++) {
			for (int j = 0; j < height - 1; j++) {
				if (privategrid[i][j] == 1) {

					
					/*
						If the space below is empty, just fall
					*/
					if (privategrid[i][j + 1] == 0) {
						grid[i][j] = 0;
						grid[i][j + 1] = 1;
					}

					/*
						If the space below and left is empty as well as the space below and right,
						choose randomly between the sides and move there
					*/

					else if (privategrid[i - 1][j + 1] == 0 && privategrid[i + 1][j + 1] == 0) {
						bool direction = rand() % 2;
						if (direction == 0) {
							// left
							grid[i][j] = 0;
							grid[i - 1][j + 1] = 1;
						}
						else if (direction == 1) {
							grid[i][j] = 0;
							grid[i + 1][j + 1] = 1;
						}
					}
					/*
						If only below and left is empty, move there.
					*/
					else if (privategrid[i - 1][j + 1] == 0) {
						grid[i][j] = 0;
						grid[i - 1][j + 1] = 1;
					}
					/*
						If only below and right is empty, move there.
					*/
					else if (privategrid[i + 1][j + 1] == 0) {
						grid[i][j] = 0;
						grid[i + 1][j + 1] = 1;
					}
				}
			}
		}
		
	}


	void draw(sf::RenderWindow &window) {
		
		for (int i = 0; i < width - 1; i++) {
			for (int j = 0; j < height - 1; j++) {
				if (grid[i][j] == 1) {
					
					// creating sand object
					sf::RectangleShape shape = sf::RectangleShape();

					shape.setSize(sf::Vector2f(sandSize, sandSize));
					shape.setFillColor(sf::Color::White);
					shape.setPosition(i * sandSize, j * sandSize);
					
					window.draw(shape);
				}
				/*
					Here, we reconnect the states of the two grids,
					so that `privategrid` now contains the final state of `grid`,
					allowing the next update to operate on the new state
				*/
				privategrid[i][j] = grid[i][j];
			}
		}
		
		
	}

	void placeSand(int x, int y) {
		grid[x][y] = 1;
	}

	void reset() {
		// Clearing the screen
		for (int i = 0; i < width - 1; i++) {
			for (int j = 0; j < height - 1; j++) {
				privategrid[i][j] = 0;
				grid[i][j] = 0;
			}
		}
	}

	
	
};

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 800), "Falling Sand", sf::Style::Close);
	
	window.setFramerateLimit(60);

	const float updateRate = 0.01f; // adjust to change the rate at which the sand falls

	float countdownMS = updateRate; // used to time the update of the world
	float toggleCounterMS = 0.0f;
	float toggleThresholdMS = 0.125f; // used to allow pausing/unpausing

	World world;

	sf::Clock clock;
	
	bool paused = false;

	while (window.isOpen()) {
	
		window.clear();

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// place sand

				sf::Vector2i localPosition = sf::Mouse::getPosition(window);

				// calculating the array coordinates of where the sand should be placed
				int gridX = floor(localPosition.x / world.sandSize);
				int gridY = floor(localPosition.y / world.sandSize);
				
				world.placeSand(gridX, gridY);
			}

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				if (toggleCounterMS > toggleThresholdMS) {

					paused = !paused;
					toggleCounterMS = 0.0f;
				}
			}
			
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				// clears world
				world.reset();
			}
		}
		
		float sec = clock.restart().asSeconds();
		countdownMS -= sec;
		toggleCounterMS += sec;
		
		
		if (countdownMS < 0.0f) {
			// after `updateRate` amount of time, update the world if it's not paused
			if (!paused) {

				world.update();
				countdownMS = updateRate;
			}
		}
		

		world.draw(window); 
		window.display();
		
	}
	
}

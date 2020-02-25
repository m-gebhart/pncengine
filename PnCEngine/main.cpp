#include "ESprite.h"
#include "EPlayer.h"
#include "Editor.h"

using namespace sf;
using namespace std;

Editor manager;

int main() {
	RenderWindow gameWindow(VideoMode(1100, 1100), "Loading...");
	manager.pWindow = &gameWindow;
	manager.LoadFile("game.xml");

	manager.LoadAssets();
	manager.LoadScene(Editor::activeSceneId);
	while (gameWindow.isOpen())
	{
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{

			switch (event.type)
			{
			case sf::Event::Closed:
				gameWindow.close();
				break;
			case sf::Event::MouseButtonPressed:
				manager.pPlayer->SetTargetPosition(gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow)));
				break;
			}
		}
		if (manager.pPlayer->moving)
			manager.pPlayer->MoveToTargetPosition();

		gameWindow.clear();
		manager.DrawOnWindow();
		gameWindow.display();
	}
	getchar();
	return 0;
}
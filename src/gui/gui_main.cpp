#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

int main(int argc, char** argv)
{
  int wWidth = 800;
  int wHeight = 600;

  // create the window
  sf::RenderWindow window(
    sf::VideoMode(wWidth, wHeight), "Blackjack");
  window.setFramerateLimit(60);

  sf::Font myFont;
  myFont.loadFromFile("Lato/Lato-Light.ttf");

  // create objects
  std::vector<std::shared_ptr<sf::Shape>> shapes;
  std::shared_ptr<sf::Shape> circle =
    std::make_shared<sf::CircleShape>(50.f);
  circle->setFillColor(sf::Color(100, 250, 50));
  circle->setOutlineThickness(10.f);
  circle->setOutlineColor(sf::Color(250, 150, 100));
  circle->setPosition(300.0f, 300.0f);
  shapes.push_back(circle);
  float circleMoveSpeed = -0.01f;


  sf::Text text("Blackjack", myFont, 24);
  text.setPosition(0, wHeight -6 - (float)text.getCharacterSize());

  // Main Loop
  while (window.isOpen()){
    if(window.hasFocus()){

      // Update positions
      sf::Vector2f previousPosition = circle->getPosition();
      sf::Vector2f moveVector(circleMoveSpeed, circleMoveSpeed);
      sf::Vector2f newPosition = previousPosition + moveVector;
      circle->setPosition(newPosition);

      // Handle events
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window.close();
        if (event.type == sf::Event::KeyPressed){
          if(event.key.code == sf::Keyboard::X)
            circleMoveSpeed *= -1.0f;
          if(event.key.code == sf::Keyboard::Y)
            circleMoveSpeed *= 2.0f;
          if(event.key.code == sf::Keyboard::P)
            circleMoveSpeed *= 0.5f;
        }
      }

      // Draw screen
      window.clear(sf::Color::Black);
      for(auto shape : shapes){
        window.draw(*shape);
      }
      window.draw(text);
      window.display();
    }
  }

  return 0;
}


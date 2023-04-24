#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "ghost.h"
#include "random.h"
#include "pickup.h"
#include "wall.h"
#include "textDisplay.h"

using namespace std;

void generateGhostXY(int& x, int& y, float distance, int pX, int pY) {
    float dx;
    float dy;
    while (distance < 100) {
        while (x > 1875 || x == 0) {
            x = generateRandom(1920);
        }
        while (y > 1035 || y == 0) {
            y = generateRandom(1080);
        }

        dx = x - pX;
        dy = y - pY;
        distance = sqrt(dx * dx + dy * dy);
    }
}

int main()
{
    //Variables
    int numberOfGhosts = 0;
    int counter = 0;
    int counterY = 0;
    int counterWalls = 0;
    int counter2 = 0;
    int counter3 = 0;
    bool justStarted = true;
    bool canCollideWithWall = true;
    int difficultLevel = 0;
    int ghostScaredTime = 6;
    sf::Clock clock;
    sf::Clock clock1;
    sf::Clock clock2;
    sf::Clock clockGame;
    int timeAfterDead = 0;
    int pause = 0;
    bool win = false;



    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pacman");
    window.setFramerateLimit(60);

    //Font
    sf::Font font;
    if (!font.loadFromFile("czcionka.ttf"))
    {
        return EXIT_FAILURE;
    }

    //Text
    sf::Text text("Coins:", font, 35);
    text.setFillColor(sf::Color::White);
    text.setPosition(1770, 0);

    //Text2
    sf::Text text2("Wybierz poziom trudnosci(klawisz): [1]-easy, [2]-medium, [3]-hard", font, 50);
    text2.setFillColor(sf::Color::Cyan);
    text2.setPosition(360, 400);

    //Text3
    sf::Text text3("GAME OVER!", font, 200);
    text3.setFillColor(sf::Color::Red);
    text3.setPosition(560, 400);

    //Text4
    sf::Text text4("YOU WIN", font, 200);
    text4.setFillColor(sf::Color::Yellow);
    text4.setPosition(660, 400);

    //Text5
    sf::Text text5("your time: ", font, 50);
    text5.setFillColor(sf::Color::Yellow);
    text5.setPosition(660, 650);


    //lives
    sf::Texture lives;
    if (!lives.loadFromFile("lives.png"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite livesSprite(lives);
    

    //Texture player/ghost
    sf::Texture texture;
    if (!texture.loadFromFile("sprites.png"))
    {
        return EXIT_FAILURE;
    }

    //Texture cherry
    sf::Texture textureCherry;
    if (!textureCherry.loadFromFile("cherry.png"))
    {
        return EXIT_FAILURE;
    }

    //Texture coin
    sf::Texture textureCoin;
    if (!textureCoin.loadFromFile("coin.png"))
    {
        return EXIT_FAILURE;
    }

    //Texture wall
    sf::Texture textureWall;
    if (!textureWall.loadFromFile("wallbg.png"))
    {
        return EXIT_FAILURE;
    }


    //Player object
    player player1;
    player1.sprite.setTexture(texture);


    //Ghost vector array
    vector<ghost>::const_iterator iGhostArray;
    vector<ghost> ghostArray;

    //Text vector array
    vector<textDisplay>::const_iterator iTextArray;
    vector<textDisplay> textDisplayArray;

    //Text display object
    textDisplay textDisplay1;
    textDisplay1.text.setFont(font);

    //Pickup vector array
    vector<pickup>::const_iterator iPickupArray;
    vector<pickup> pickupArray;

    //Pickup object
    pickup pickup1;
    pickup1.sprite.setTexture(textureCoin);
    pickup pickup2;
    pickup2.isCherry = true;
    pickup2.setCherryTexture();
    pickup2.sprite.setTexture(textureCherry);


    counter = 0;
    while (counterY <= 21) {
        while (counter <= 38) {
            if ((generateRandom(90) == 1)) {
                pickup2.rect.setPosition(sf::Vector2f(counter * 50, counterY * 50));
                pickupArray.push_back(pickup2);
                counter++;
            }
            else {
                pickup1.rect.setPosition(sf::Vector2f(counter * 50, counterY * 50));
                pickupArray.push_back(pickup1);
                counter++;
            }           
        }
        counter = 0;
        counterY++;
    }
   
    
    //Wall vector array
    vector<wall>::const_iterator iWallArray;
    vector<wall> wallArray;
    
    //Wall object
    wall wall1;   
    wall1.sprite.setTexture(textureWall);
    
    //border top
    counter = 0;
    while (counter <= 38) {
        wall1.rect.setPosition(50 * counter, -50);
        wallArray.push_back(wall1);
        counter++;
    }
    //border bottom
    counter = 0;
    while (counter <= 38) {
        wall1.rect.setPosition(50 * counter, 1080);
        wallArray.push_back(wall1);
        counter++;
    }
    //border left
    counter = 0;
    while (counter <= 21) {
        wall1.rect.setPosition(-50, 50 * counter);
        wallArray.push_back(wall1);
        counter++;
    }
    //border right
    counter = 0;
    while (counter <= 21) {
        wall1.rect.setPosition(1930, 50 * counter);
        wallArray.push_back(wall1);
        counter++;
    }

    //game map

    //left rectangle I
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 6) {
            wall1.rect.setPosition(135 + (counter * wall1.wallSize), 80+(wall1.wallSize*counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //Left rectangle II
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 6) {
            wall1.rect.setPosition(135 + (counter * wall1.wallSize), 330 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //Left rectangle III
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 6) {
            wall1.rect.setPosition(135 + (counter * wall1.wallSize), 580 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //left rectangle IV
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 6) {
            wall1.rect.setPosition(135 + (counter * wall1.wallSize), 780 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 3) {
            wall1.rect.setPosition(270 + (counter * wall1.wallSize), 870 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //left-mid rectangle I
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 6) {
            wall1.rect.setPosition(535 + (counter * wall1.wallSize), 80 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //left-mid rectangle II
    counter = 0;
    counter2 = 0;
    while (counter2 < 7) {
        while (counter < 2) {
            wall1.rect.setPosition(535 + (counter * wall1.wallSize), 330 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 4) {
            wall1.rect.setPosition(625 + (counter * wall1.wallSize), 430 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //middle rectangle I
    counter = 0;
    while (counter < 6) {
        wall1.rect.setPosition(935,wall1.wallSize * counter);
        wallArray.push_back(wall1);
        counter++;
    }
    //middle square
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 3) {
            wall1.rect.setPosition(885 + (counter * wall1.wallSize), 430 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //long middle rectangle
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 17) {
            wall1.rect.setPosition(574 + (counter * wall1.wallSize), 785 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //right-mid rectangle I
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 6) {
            wall1.rect.setPosition(1085 + (counter * wall1.wallSize), 80 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //right-mid rectangle II
    counter = 0;
    counter2 = 0;
    while (counter2 < 7) {
        while (counter < 2) {
            wall1.rect.setPosition(1285 + (counter * wall1.wallSize), 330 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 4) {
            wall1.rect.setPosition(1105 + (counter * wall1.wallSize), 430 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //right rectangle I
    counter = 0;
    counter2 = 0;
    while (counter2 < 3) {
        while (counter < 6) {
            wall1.rect.setPosition(1485 + (counter * wall1.wallSize), 80 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //right rectangle II
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 6) {
            wall1.rect.setPosition(1485 + (counter * wall1.wallSize), 330 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //right rectangle III
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 6) {
            wall1.rect.setPosition(1485 + (counter * wall1.wallSize), 580 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    //right rectangle IV
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 6) {
            wall1.rect.setPosition(1485 + (counter * wall1.wallSize), 780 + (wall1.wallSize * counter2));
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    counter = 0;
    counter2 = 0;
    while (counter2 < 2) {
        while (counter < 3) {
            wall1.rect.setPosition(1485 + (counter * wall1.wallSize), 870 + (wall1.wallSize * counter2));           
            wallArray.push_back(wall1);
            counter++;
        }
        counter = 0;
        counter2++;
    }
    
    //If pickup item collide with wall begin game start
    counter = 0;
    for (iWallArray = wallArray.begin(); iWallArray != wallArray.end(); iWallArray++) {
        counter2 = 0;
        for (iPickupArray = pickupArray.begin(); iPickupArray != pickupArray.end(); iPickupArray++) {
            if (wallArray[counter].rect.getGlobalBounds().intersects(pickupArray[counter2].rect.getGlobalBounds())) {
                pickupArray.erase(iPickupArray);
            }
            counter2++;
        }
        counter++;
    }
    
    //-------------GAME LOOP-----------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear();

        //Clock
        sf::Time elapsedGame = clockGame.getElapsedTime();
        sf::Time elapsed1 = clock.getElapsedTime();
        sf::Time elapsed2 = clock1.getElapsedTime();
        sf::Time elapsed3 = clock2.getElapsedTime();
        
        if (!justStarted && player1.lifes > 0 && !win) {

            //Player collides with wall
            counter = 0;
            for (iWallArray = wallArray.begin(); iWallArray != wallArray.end(); iWallArray++) {
                if (player1.rect.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds())) {
                    //hit the wall
                    if (player1.direction == 1) {
                        player1.canMoveUp = false;
                        player1.rect.move(0, 5);
                    }
                    if (player1.direction == 2) {
                        player1.canMoveDown = false;
                        player1.rect.move(0, -5);
                    }
                    if (player1.direction == 3) {
                        player1.canMoveLeft = false;
                        player1.rect.move(5, 0);
                    }
                    if (player1.direction == 4) {
                        player1.canMoveRight = false;
                        player1.rect.move(-5, 0);
                    }
                }              
                counter++;
            }

            //Ghost collides with wall
            counter = 0;
            for (iGhostArray = ghostArray.begin(); iGhostArray != ghostArray.end(); iGhostArray++) {

                counterWalls = 0;
                for (iWallArray = wallArray.begin(); iWallArray != wallArray.end(); iWallArray++) {                  
                    if (ghostArray[counter].rect.getGlobalBounds().intersects(wallArray[counterWalls].rect.getGlobalBounds())) {
                        //hit the wall
                        if (ghostArray[counter].direction == 1) {
                            ghostArray[counter].canMoveUp = false;
                            ghostArray[counter].rect.move(0, 5);
                        }
                        else if (ghostArray[counter].direction == 2) {
                            ghostArray[counter].canMoveDown = false;
                            ghostArray[counter].rect.move(0, -5);
                        }
                        else if (ghostArray[counter].direction == 3) {
                            ghostArray[counter].canMoveLeft = false;
                            ghostArray[counter].rect.move(5, 0);
                        }
                        else if (ghostArray[counter].direction == 4) {
                            ghostArray[counter].canMoveRight = false;
                            ghostArray[counter].rect.move(-5, 0);
                        }
                        else {
                            //no movement
                        }

                    }
                    counterWalls++;
                }
                counter++;

            }
            
            //Player collides with pickup item
            counter = 0;
            for (iPickupArray = pickupArray.begin(); iPickupArray != pickupArray.end(); iPickupArray++) {
                if (player1.rect.getGlobalBounds().intersects(pickupArray[counter].rect.getGlobalBounds())) {
                    if (pickupArray[counter].isCoin == true) {
                        player1.coins += pickupArray[counter].coinValue;
                    }
                    if (pickupArray[counter].isCherry == true) {                                       
                        player1.canEatGhosts = true;
                        clock2.restart();     
                        textDisplay1.text.setString(to_string(pickup2.cherryValue));
                        textDisplay1.text.setPosition(player1.rect.getPosition().x, player1.rect.getPosition().y - 50);
                        textDisplayArray.push_back(textDisplay1);
                        player1.coins += pickupArray[counter].cherryValue;
                    }
                    pickupArray[counter].destroy = true;
                }
                counter++;
            }

            //Player collides with ghosts
            counter = 0;
            for (iGhostArray = ghostArray.begin(); iGhostArray != ghostArray.end(); iGhostArray++) {
                if (player1.rect.getGlobalBounds().intersects(ghostArray[counter].rect.getGlobalBounds()) && player1.canEatGhosts) {                   
                    ghostArray.erase(iGhostArray);
                    break;
                }else if (player1.rect.getGlobalBounds().intersects(ghostArray[counter].rect.getGlobalBounds()) && player1.canBeEaten) {
                    player1.alive = false;
                    player1.canBeEaten = false;
                    timeAfterDead = elapsedGame.asSeconds();
                }
                counter++;
            }     

            //Delete pickup item
            counter = 0;
            for (iPickupArray = pickupArray.begin(); iPickupArray != pickupArray.end(); iPickupArray++) {
                if (pickupArray[counter].destroy == true) {
                    pickupArray.erase(iPickupArray);
                    break;
                }
                counter++;
            }

            //Delete text
            counter = 0;
            for (iTextArray = textDisplayArray.begin(); iTextArray != textDisplayArray.end(); iTextArray++) {
                if (textDisplayArray[counter].destroy == true) {
                    textDisplayArray.erase(iTextArray);
                    break;
                }
            }


            //update ghosts
            counter = 0;
            for (iGhostArray = ghostArray.begin(); iGhostArray != ghostArray.end(); iGhostArray++) {
                //Can eat ghost
                if (player1.canEatGhosts) {
                    ghostArray[counter].isScared = true;
                }
                else {
                    ghostArray[counter].isScared = false;
                }

                if (difficultLevel == 1) {
                    ghostArray[counter].movementSpeed = 5;
                }
                if (difficultLevel == 2) {
                    ghostArray[counter].movementSpeed = 6;
                }
                if (difficultLevel == 3) {
                    ghostArray[counter].movementSpeed = 6;
                }
                ghostArray[counter].update(elapsed2);

                //Animation blue/white ghost
                if (elapsed2.asSeconds() > 0.6)
                {
                    clock1.restart();
                }
                //Set Player can't eat ghosts
                elapsed3 = clock2.getElapsedTime();
                if ((elapsed3.asSeconds() > (ghostScaredTime - difficultLevel)) && (player1.canEatGhosts == true)) {
                    player1.canEatGhosts = false;
                    ghostArray[counter].isScared = false;                   
                }
                ghostArray[counter].updateMovement();
                counter++;
                
            }

            //update walls
            counter = 0;

            for (iWallArray = wallArray.begin(); iWallArray != wallArray.end(); iWallArray++) {
                wallArray[counter].update();
                counter++;
            }

            //update player           
            player1.update(timeAfterDead, elapsedGame.asSeconds());
            if(player1.alive) player1.updateMovement();

            //Game over
            if (!player1.alive && elapsed1.asSeconds() >= 0.1 && player1.deadAnimation != 12) {
                player1.dead();
                if (player1.deadAnimation == 12 && player1.lifes >= 1) {
                    player1.lifes--;
                    player1.alive = true;
                    player1.deadAnimation = 0;
                    player1.rect.setPosition(920, 350);
                    player1.sprite.setTextureRect(sf::IntRect(850, 0, 40, 46));
                } 
                clock.restart();
            }
            //Game win
            if(pickupArray.empty()){
                win = true;
                player1.gameTime = elapsedGame.asSeconds();
            } 
            
            

            //Draw coins 
            counter = 0;
            for (iPickupArray = pickupArray.begin(); iPickupArray != pickupArray.end(); iPickupArray++) {             
                pickupArray[counter].update();
                window.draw(pickupArray[counter].sprite);
                counter++;
            }


            //Draw ghosts
            counter = 0;
            for (iGhostArray = ghostArray.begin(); iGhostArray != ghostArray.end(); iGhostArray++) {                            
                window.draw(ghostArray[counter].sprite);             
                counter++;
            }


            //Draw walls
            counter = 0;
            for (iWallArray = wallArray.begin(); iWallArray != wallArray.end(); iWallArray++) {
                window.draw(wallArray[counter].rect);
                window.draw(wallArray[counter].sprite);
                counter++;
            }
            //Draw text
            counter = 0;
            for (iTextArray = textDisplayArray.begin(); iTextArray != textDisplayArray.end(); iTextArray++) {
                textDisplayArray[counter].update();
                window.draw(textDisplayArray[counter].text);
                counter++;
            }

            //Text player coins
            text.setString("Coins: " + to_string(player1.coins));
            window.draw(text);

            //Draw player
            if (player1.deadAnimation != 12) {
                window.draw(player1.sprite);
            }
            
            //Draw lives
            counter = 0;
            while (counter != player1.lifes) {
                livesSprite.setPosition(10 + (counter * 22), 10);
                window.draw(livesSprite);
                counter++;
            }
            
            
            
        }
        else if (player1.lifes == 0) {
            window.draw(text3);
        }
        else if (win) {
            text5.setString("Your time: " + to_string(player1.gameTime) + "s");
            window.draw(text4);
            window.draw(text5);
            
        }
        //Menu (difficult level) czas aktywacji duchów, predkosc duchow, liczba duchów
        else {
            numberOfGhosts = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                justStarted = false;
                difficultLevel = 1;
                player1.alive = true;
                player1.deadAnimation = 0;
                pause = 0;
                
                
                

                //Ghost object
                ghost ghost1;
                ghost1.sprite.setTexture(texture);
                while (numberOfGhosts < 6) {
                    int x = 0;
                    int y = 0;
                    generateGhostXY(x, y, 0, player1.rect.getPosition().x, player1.rect.getPosition().y);
                    ghost1.setGhostColor();
                    ghost1.rect.setPosition(x, y);
                    ghostArray.push_back(ghost1);
                    numberOfGhosts++;
                }

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
                justStarted = false;
                difficultLevel = 2;
                player1.alive = true;
                player1.deadAnimation = 0;
                pause = 0;

                //Ghost object
                ghost ghost1;
                ghost1.sprite.setTexture(texture);
                while (numberOfGhosts < 10) {                  
                    int x = 0;
                    int y = 0;
                    generateGhostXY(x, y, 0, player1.rect.getPosition().x, player1.rect.getPosition().y);
                    ghost1.setGhostColor();
                    ghost1.rect.setPosition(x, y);
                    ghostArray.push_back(ghost1);
                    numberOfGhosts++;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) {
                justStarted = false;
                difficultLevel = 3;
                player1.alive = true;
                player1.deadAnimation = 0;
                pause = 0;

                //Ghost object
                ghost ghost1;
                ghost1.sprite.setTexture(texture);
                while (numberOfGhosts < 16) {
                    int x = 0;
                    int y = 0;
                    generateGhostXY(x, y, 0, player1.rect.getPosition().x, player1.rect.getPosition().y);
                    ghost1.setGhostColor();
                    ghost1.rect.setPosition(x, y);
                    ghostArray.push_back(ghost1);
                    numberOfGhosts++;
                }
            }
            //Text difficult level
            window.draw(text2);
        }
        

            
        window.display();
    }
    return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Snake.h"
#include "Hamiltonian.h"

#define WINDOW_HEIGHT 1200
#define WINDOW_WIDTH 1200
#define GRID_HEIGHT 30
#define GRID_WIDTH 30
#define FRAMERATE 90.0f

sf::Color SNAKE_COLOR(250, 250, 250);
sf::Color FOOD_COLOR(250, 50, 50);
sf::Color BACKGROUND_COLOR(50, 50, 50);

sf::RectangleShape cell(sf::Vector2f(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT) * 0.6f);
sf::RectangleShape food(sf::Vector2f(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT) * 0.6f);
sf::RectangleShape fillerBetweenCells(sf::Vector2f(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT) * 0.6f);

int main()
{
    bool followingH = false;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game");
    sf::Event event;
    sf::Clock frameTime;

    cell.setOrigin(sf::Vector2f(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT) * -0.2f);
    cell.setFillColor(SNAKE_COLOR);
    food.setOrigin(sf::Vector2f(WINDOW_WIDTH / GRID_WIDTH, WINDOW_HEIGHT / GRID_HEIGHT) * -0.2f);
    food.setFillColor(FOOD_COLOR);

    Snake snake(GRID_WIDTH, GRID_HEIGHT);
    Hamiltonian moves(GRID_WIDTH, GRID_HEIGHT);

    // snake.move('r');

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (frameTime.getElapsedTime().asSeconds() > (1 / FRAMERATE))
        {
            frameTime.restart();

            /// Ai starts///////////////////////////////////////////////////////////////////////////////
            int *map = (int *)calloc(GRID_HEIGHT * GRID_WIDTH, sizeof(int));
            char directions[] = {'d'};
            std::vector<std::string> allPaths;
            allPaths.push_back("");
            bool pathNotFound = true;
            char move = 'h';
            while (pathNotFound && !allPaths.empty())
            {
                std::string tempPath = allPaths.front();
                allPaths.erase(allPaths.begin());
                int x = snake.getElementx(0);
                int y = snake.getElementy(0);
                for (int i = 0; i < tempPath.length(); i++)
                {
                    switch (tempPath[i])
                    {
                    case 'r':
                        x++;
                        break;
                    case 'l':
                        x--;
                        break;
                    case 'd':
                        y++;
                        break;
                    case 'u':
                        y--;
                        break;
                    }
                }

                for (int i = 0; i < 4; i++)
                {
                    int dx = x;
                    int dy = y;
                    switch (directions[i])
                    {
                    case 'r':
                        dx++;
                        break;
                    case 'l':
                        dx--;
                        break;
                    case 'd':
                        dy++;
                        break;
                    case 'u':
                        dy--;
                        break;
                    }
                    if (dx == snake.getFoodx() && dy == snake.getFoody())
                    {
                        pathNotFound = false;
                        move = (tempPath + directions[i])[0];
                    }
                    bool correctPath = false;
                    if (dx < GRID_WIDTH && dx >= 0 && dy < GRID_HEIGHT && dy >= 0)
                    {
                        correctPath = true;
                        for (int i = 1; i < snake.getLength(); i++)
                        {
                            if (snake.getElementx(i) == dx && snake.getElementy(i) == dy)
                            {
                                correctPath = false;
                            }
                        }
                        if (map[dx + dy * GRID_WIDTH] == 1)
                        {
                            correctPath = false;
                        }
                    }
                    if (correctPath)
                    {
                        map[dx + dy * GRID_WIDTH] = 1;
                        allPaths.push_back(tempPath + directions[i]);
                    }
                }
            }
            ////// here the move is generated///////////////////////////////////////////////////////////////////////////

            int distance = 0;
            int nextLocx = snake.getElementx(0);
            int nextLocy = snake.getElementy(0);
            switch (move)
            {
            case 'r':
                distance = moves.getDistance(snake.getElementx(0) + 1, snake.getElementy(0), snake.getFoodx(), snake.getFoody());
                nextLocx++;
                break;
            case 'l':
                distance = moves.getDistance(snake.getElementx(0) - 1, snake.getElementy(0), snake.getFoodx(), snake.getFoody());
                nextLocx--;
                break;
            case 'd':
                distance = moves.getDistance(snake.getElementx(0), snake.getElementy(0) + 1, snake.getFoodx(), snake.getFoody());
                nextLocy++;
                break;
            case 'u':
                distance = moves.getDistance(snake.getElementx(0), snake.getElementy(0) - 1, snake.getFoodx(), snake.getFoody());
                nextLocy--;
                break;
            }
            // snake.move(moves.getMove(snake.getElementx(0), snake.getElementy(0)));

            ////// moving
            if (distance < snake.getLength())
            {
                if (nextLocx != snake.getFoodx() || nextLocy != snake.getFoody())
                {
                    snake.move(moves.getMove(snake.getElementx(0), snake.getElementy(0)));
                    followingH = true;
                }
                else
                {

                    if (followingH)
                    {
                        snake.move(moves.getMove(snake.getElementx(0), snake.getElementy(0)));
                        followingH = true;
                    }
                    else
                    {
                        followingH = false;
                        snake.move(move);
                    }
                }
            }
            else
            {
                followingH = false;
                snake.move(move);
            }

            //     if (distance < snake.getLength() + 2)
            //     {

            //         snake.move(moves.getMove(snake.getElementx(0), snake.getElementy(0)));
            //         followingH = true;
            //     }
            //     else
            //     {
            //         if (followingH)
            //         {
            //             char nextM = moves.getMove(snake.getElementx(0), snake.getElementy(0));
            //             int nextLocx = snake.getElementx(0);
            //             int nextLocy = snake.getElementy(0);
            //             switch (move)
            //             {
            //             case 'r':
            //                 distance = moves.getDistance(snake.getElementx(0) + 1, snake.getElementy(0), snake.getFoodx(), snake.getFoody());
            //                 nextLocx++;
            //                 break;
            //             case 'l':
            //                 distance = moves.getDistance(snake.getElementx(0) - 1, snake.getElementy(0), snake.getFoodx(), snake.getFoody());
            //                 nextLocx--;
            //                 break;
            //             case 'd':
            //                 distance = moves.getDistance(snake.getElementx(0), snake.getElementy(0) + 1, snake.getFoodx(), snake.getFoody());
            //                 nextLocy++;
            //                 break;
            //             case 'u':
            //                 distance = moves.getDistance(snake.getElementx(0), snake.getElementy(0) - 1, snake.getFoodx(), snake.getFoody());
            //                 nextLocy--;
            //                 break;
            //             }
            //             if (nextLocx == snake.getFoodx() && nextLocy == snake.getFoody())
            //                 followingH = true;
            //             {
            //                 followingH = false;
            //             }
            //             snake.move(nextM);
            //         }
            //         else
            //         {
            //             followingH = false;
            //             snake.move(move);
            //         }
            //     }
            //
        }
        // Renderning
        // Snake Rendering
        window.clear(BACKGROUND_COLOR);
        for (int i = 0; i < snake.getLength(); i++)
        {
            int x = snake.getElementx(i);
            int y = snake.getElementy(i);
            cell.setPosition(x * (WINDOW_WIDTH / GRID_WIDTH), y * (WINDOW_HEIGHT / GRID_HEIGHT));
            window.draw(cell);
            if (i > 0)
            {
                int posX = x * (WINDOW_WIDTH / GRID_WIDTH) + (WINDOW_WIDTH / GRID_WIDTH) * (0.21f + (snake.getElementx(i - 1) - x) * 0.6f);
                int posY = y * (WINDOW_HEIGHT / GRID_HEIGHT) + (WINDOW_HEIGHT / GRID_HEIGHT) * (0.21f + (snake.getElementy(i - 1) - y) * 0.6f);
                fillerBetweenCells.setPosition(sf::Vector2f(posX, posY));

                window.draw(fillerBetweenCells);
            }
        }
        food.setPosition(snake.getFoodx() * (WINDOW_WIDTH / GRID_WIDTH), snake.getFoody() * (WINDOW_HEIGHT / GRID_HEIGHT));
        window.draw(food);
        window.display();
    }
    return 0;
}
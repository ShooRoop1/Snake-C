#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

bool isGame;

const int width = 30;
const int height = 30;
const int squareSize = 30;

unsigned int snake[width * height][2];

float currentFrame = 0;
Clock clocks;
RenderWindow window(VideoMode(width*squareSize, height*squareSize), "Snake");


int snakeX, snakeY, fruitX, fruitY, gameScore;

enum snakeDirections { LEFT, RIGHT, UP, DOWN };
snakeDirections curDirection;

void newFruit() {
    fruitX = rand() % width;
    fruitY = rand() % height;
    for (int i = 1; i <= gameScore; i++)
    {
        if (fruitX == snake[i][0] && fruitY == snake[i][1]) newFruit();
    }
}

void keyboardTaps (){
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        if (curDirection != DOWN) curDirection = UP;
    }
    else if (Keyboard::isKeyPressed(Keyboard::A))
    {
        if (curDirection != RIGHT) curDirection = LEFT; 
    }
    else if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if (curDirection != UP) curDirection = DOWN;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D))
    {
        if (curDirection != LEFT)  curDirection = RIGHT;
    }
}

void logic() {
    snake[0][0] = snakeX;
    snake[0][1] = snakeY;
    switch (curDirection)
    {
    case LEFT:
        snakeX--;
        break;
    case RIGHT:
        snakeX++;
        break;
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    }
    for (int i = 1; i <= gameScore; i++) 
    {
        if (snakeX == snake[i][0] && snakeY == snake[i][1]) isGame = false;
    }
    if (snakeX < 0 || snakeY < 0 || snakeX > width || snakeY > height) {
        isGame = false;
    }
    if (snakeX == fruitX && snakeY == fruitY) {
        newFruit();
        gameScore++;
    }
}

void draw() {
    RectangleShape fruit, snakeHead;
    fruit.setSize(Vector2f(squareSize, squareSize));
    fruit.setFillColor(Color::Color(230, 126, 34));
    snakeHead.setSize(Vector2f(squareSize, squareSize));
    snakeHead.setFillColor(Color::Color(39, 174, 96));
    while (window.isOpen() && isGame)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        
        float time = clocks.getElapsedTime().asMicroseconds();
        time = time / 400;
        clocks.restart();
        currentFrame += 0.005 * time;
        keyboardTaps();
        for (int i = 1; i <= gameScore; i++)
        {
            RectangleShape segment;
            segment.setSize(Vector2f(squareSize, squareSize));
            segment.setFillColor(Color::Color(46, 204, 113));
            segment.setPosition(snake[i][0] * squareSize, snake[i][1] * squareSize);
            window.draw(segment);
        }
        fruit.setPosition(fruitX * squareSize, fruitY * squareSize);
        snakeHead.setPosition(snakeX * squareSize, snakeY * squareSize);
        window.draw(snakeHead);
        window.draw(fruit);
        window.display();
        window.clear(Color::Color(44, 62, 80));
        if (currentFrame > 1) {
            currentFrame -= 1;
            logic();
            for (int i = gameScore; i >= 1; i--)
            {
                snake[i][0] = snake[i - 1][0];
                snake[i][1] = snake[i - 1][1];
            }
        }
    }
}

void setup() {
    isGame = true;
    curDirection = RIGHT;
    snakeX = width / 2;
    snakeY = height / 2;
    snake[0][0] = snakeX;
    snake[0][1] = snakeY;
    fruitX = rand() % width;
    fruitY = rand() % height;
    gameScore = 0;
    draw();
}

int main() {
	setup();
}
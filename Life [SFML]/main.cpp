#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "LIFE.h"


void gotoxy(int xpos, int ypos); //transfering cursor in a console
void Event(sf::RenderWindow & window, LIFE & Obj); //event handler

int main()
{
	setlocale(LC_ALL, "Russian");

	int Cellsizex=10,
		Cellsizey=10,
		CellOutlineThickness=1;

	sf::RenderWindow window(sf::VideoMode(), "Life", sf::Style::Fullscreen);

	LIFE A(window.getSize().x, window.getSize().y, Cellsizex, Cellsizey, CellOutlineThickness);

	//initialization of rectangles (cells)
	sf::RectangleShape rectangle(sf::Vector2f(Cellsizex, Cellsizey));
	rectangle.setFillColor(sf::Color::Black);
	sf::Color coffee(68, 45, 37);
	rectangle.setOutlineColor(coffee);
	rectangle.setOutlineThickness(CellOutlineThickness);


	A.Set("random");
	A.Output(window, rectangle);
	
	unsigned int generations=0;

	std::cout << "Window size (width õ height) " << window.getSize().x << 'x' << window.getSize().y << std::endl;
	
	int xmouse, ymouse;

	while (window.isOpen())
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			xmouse=sf::Mouse::getPosition(window).x;
			ymouse=sf::Mouse::getPosition(window).y;
			
			std::cout << xmouse << ' ' << ymouse << "    " << std::endl;
			
			if(xmouse<Cellsizex) xmouse=0;
			else xmouse=xmouse/(Cellsizex+CellOutlineThickness);
			
			if(ymouse<Cellsizey) ymouse=0;
			else ymouse=ymouse/(Cellsizey+CellOutlineThickness);

			std::cout << xmouse << ' ' << ymouse << "    " << std::endl;
			A.Set(xmouse, ymouse);			
		}
		window.clear();
		A.GenChange();
		generations++;
		Sleep(100);

		A.Output(window, rectangle);		

		window.display();

		gotoxy(0,2);
		std::cout << "Generations: " << generations << "    " << std::endl;
		
		Event(window, A);

	gotoxy(0,5);
	std::cout << "RowsxCols: " << A.getrows() << 'x' << A.getcols() << "    " << std::endl;
		
	}

	
	_getch();
	return 0;
}


void Event(sf::RenderWindow & window, LIFE & Obj) //event handler
{
	sf::Event event;

		while (window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
					window.close();
					break;

			//To fix
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				Obj.Update(event.size.width, event.size.height);
				std::cout << "New size (width õ height) " << event.size.width << 'x' << event.size.height << "    " << std::endl; 
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}
}

inline void gotoxy(int xpos, int ypos) //transfering cursor in a console
{
  COORD scrn;    
 
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
 
  scrn.X = xpos; scrn.Y = ypos;
 
  SetConsoleCursorPosition(hOuput,scrn);
}
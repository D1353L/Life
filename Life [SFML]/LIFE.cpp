#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include "LIFE.h"

LIFE::LIFE()
{
	rows=0; cols=0;
	CellSizeX=0; CellSizeY=0;
}

LIFE::LIFE(const int windowsizex, const int windowsizey, const int _CellSizeX, const int _CellSizeY,  const int CellOutlineThickness)
{
	CellSizeX=_CellSizeX + CellOutlineThickness;
	CellSizeY=_CellSizeY + CellOutlineThickness;

	rows=windowsizex / CellSizeX;
	cols=windowsizey / CellSizeY;

	Cell temp;
	temp.alive=temp.nextAlive=false;
	
	std::vector<Cell> Temp(cols, temp);
	Field.resize(rows, Temp);
}

LIFE::LIFE(const LIFE &copy_object)
{
	Field=copy_object.Field;

	rows=copy_object.rows;
	cols=copy_object.cols;	

	CellSizeX=copy_object.CellSizeX;
	CellSizeY=copy_object.CellSizeY;
}

LIFE::~LIFE(void)
{
	Field.clear();
}

int LIFE::GetIndex(const int index, const int size) //circuiting of array (determine the index of cells beyond the array)
{
    int result = index % size;
    if (result < 0) result = result + size;
    return result;
}

int LIFE::Sum(const int x, const int y) //sum of alive cells-neighbors
{
	int xDec, xInc, yDec, yInc;

	//definition of cells beyond the array
	if((x-1)>=0) xDec=x-1;
	else xDec=GetIndex(x-1, rows);

	if((x+1)<rows) xInc=x+1;
	else xInc=GetIndex(x+1, rows);

	if((y-1)>=0) yDec=y-1;
	else yDec=GetIndex(y-1, cols);

	if((y+1)<cols) yInc=y+1;
	else yInc=GetIndex(y+1, cols);

	//counting of alive neighbors
	return Field[xDec][yDec].alive + Field[x][yDec].alive + Field[xInc][yDec].alive + Field[xDec][y].alive + Field[xInc][y].alive + Field[xDec][yInc].alive + Field[x][yInc].alive + Field[xInc][yInc].alive;
}

void LIFE::Set(const char *mode) //first initialization
{	
	if(mode=="random")
	{
	srand(time(NULL));

	for(int x=0; x<rows; x++)
			for(int y=0; y<cols; y++)
				Field[rand()%rows][rand()%cols].alive=true;
	}
	else if(mode=="glider")
	{
		Field[1][3].alive=true; Field[2][4].alive=true; Field[3][2].alive=true; 
		Field[3][3].alive=true; Field[3][4].alive=true;
	}
}

void LIFE::Set(const int x, const int y)
{
	if(x<=rows && y<=cols)
		if(Field[x][y].alive) Field[x][y].alive=false;
		else Field[x][y].alive=true;
}

void LIFE::GenChange() //changing of generation
{
	int S;

	//counting of next generation
	for(int x=0; x<rows; x++)
			for(int y=0; y<cols; y++)
			{
				S=Sum(x, y);

				//if near empty (dead) cell exactly three living cells then emerging life
				if( (Field[x][y].alive==false) && (S==3) )
					Field[x][y].nextAlive=true;
				else
				//if a living cell has two or three living neighbors then the cell continues to live; otherwise, the cell dies
					if( (Field[x][y].alive==true) && ( (S==2) || (S==3) ) )
						Field[x][y].nextAlive=true;
					else Field[x][y].nextAlive=false;
			}

	//changing of generation
	for(int x=0; x<rows; x++)
		{
			for(int y=0; y<cols; y++)
			{
				if(Field[x][y].nextAlive==true) Field[x][y].alive=true;
				else Field[x][y].alive=false;
			}
		}
}

void LIFE::Update(const int windowsizex, const int windowsizey) //changing cells count
{
	if(rows!=windowsizex/CellSizeX || cols!=windowsizey/CellSizeY)
	{
		
		rows=windowsizex / CellSizeX;
		cols=windowsizey / CellSizeY;

		Cell temp;
		temp.alive=temp.nextAlive=false;

		std::vector<Cell> Temp(cols, temp);
		Field.resize(rows, Temp);	
	}
}

void LIFE::Output(sf::RenderWindow & window, sf::RectangleShape & rectangle)
{
	int i=0,j=0;

	//filling of a field
	for(float x=2.0; x<rows*CellSizeX; x=x+CellSizeX)
	{
		for(float y=2.0; y<cols*CellSizeY; y=y+CellSizeY)
		{
			if(Field[i][j].alive==true) rectangle.setFillColor(sf::Color::Green);
			else rectangle.setFillColor(sf::Color::Black);

			rectangle.setPosition(x, y);
			window.draw(rectangle);
			 j++;
		}
		i++; j=0;
	}
}

int LIFE::getrows() const
{
	return rows;
}

int LIFE::getcols() const
{
	return cols;
}
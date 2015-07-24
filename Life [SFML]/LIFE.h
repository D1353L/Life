#include <SFML/Graphics.hpp>
#include <vector>


class LIFE
{
private:
	
	struct Cell{bool alive, nextAlive;};

	std::vector< std::vector<Cell>> Field; //two-dimensional array of cells <bool alive, bool nextAlive>

	int rows;

	int cols;

	int CellSizeX;

	int CellSizeY;

	int GetIndex(const int index, const int size); //circuiting of array (determine the index of cells beyond the array)

	int Sum(const int x, const int y); //sum of alive cells-neighbors

public:
	
	LIFE();

	LIFE(const int windowsizex, const int windowsizey, const int _CellSizeX, const int _CellSizeY, const int _CellOutlineThickness);

	LIFE(const LIFE &copy_object);

	~LIFE(void);

	void Set(const char *mode); //first initialization

	void Set(const int x, const int y);

	void GenChange(); //changing of generation

	void Update(const int windowsizex, const int windowsizey); //changing cells count

	void Output(sf::RenderWindow & window, sf::RectangleShape & rectangle); //output on the screen

	int getrows() const;
	
	int getcols() const;
};
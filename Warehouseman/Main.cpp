# include <Siv3D.hpp> // Siv3D v0.6.16

Vec2 convertGrid2Coordinate(int gridX, int gridY, int cellSize)
{
	return Vec2(gridX * cellSize + 50, gridY * cellSize + 50);
}

class Player
{
public:
	// Constructor
	Player()
		: m_circle(50, 50, 20), gridX(0), gridY(0)
	{
	}

	void draw()
	{
		m_circle.x = convertGrid2Coordinate(gridX, gridY, 100).x;
		m_circle.y = convertGrid2Coordinate(gridX, gridY, 100).y;
		m_circle.draw(Palette::Red);
	}

	void update()
	{
		if(KeyUp.down()) gridY = std::max(0, gridY - 1);
		if (KeyDown.down()) gridY = std::min(5, gridY + 1);
		if (KeyLeft.down()) gridX = std::max(0, gridX - 1);
		if (KeyRight.down()) gridX = std::min(7, gridX + 1);
	}

private:
	Circle m_circle;
	int gridX;
	int gridY;
};

class Wall
{
public:
	// Constructor

	void draw()
	{
		m_rect.draw(Palette::Brown);
	}

private:
	Rect m_rect;
	int gridX;
	int gridY;
};

class Baggage
{
public:
	// Constructor
	void draw()
	{
		m_rect.draw(Palette::Blue);
	};
	void update()
	{
	}
private:
	Rect m_rect;
	int gridX;
	int gridY;
};

struct CellState
{
	bool hasPlayer = false;
	bool isWall = false;
	bool isGoal = false;
	bool hasBox = false;
};


void DrawCell(Grid<CellState> grid)
{
	for (int y = 0; y < grid.height(); ++y)
	{
		for (int x = 0; x < grid.width(); ++x)
		{
			RectF rect(Arg::center(convertGrid2Coordinate(x, y, 100)), 100, 100);
			rect.draw(Palette::White).drawFrame(1,Palette::Black);
		}
	}
}

void Main()
{

	Grid<CellState> grid(8, 6);
	Player player;
	Wall wall;
	Baggage baggage;

	while (System::Update())
	{
		// update
		player.update();
		baggage.update();

		// draw
		DrawCell(grid);
		player.draw();
		wall.draw();
		baggage.draw();

	}
}

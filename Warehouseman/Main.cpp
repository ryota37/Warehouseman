# include <Siv3D.hpp> // Siv3D v0.6.16

Vec2 convertGrid2Coordinate(int gridX, int gridY, int cellSize)
{
	return Vec2(gridX * cellSize + 50, gridY * cellSize + 50);
}

struct CellState
{
	bool isWall = false;
	bool hasBox = false;
	bool isGoal = false;
};

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

	void CheckCollision(Grid<CellState>& grid)
	{
	}

	// TODO: Should stop player if the adjacent cell of box is a wall.
	void update(Grid<CellState>& grid)
	{
		if (KeyUp.down())
		{
			if (grid[gridY - 1][gridX].isWall)
			{
				return;
			}
			if (grid[gridY - 1][gridX].hasBox)
			{
				grid[gridY - 1][gridX].hasBox = false;
				grid[gridY - 2][gridX].hasBox = true;
			}
			gridY = std::max(0, gridY - 1);
		}
		if (KeyDown.down())
		{
			if (grid[gridY + 1][gridX].isWall)
			{
				return;
			}
			if (grid[gridY + 1][gridX].hasBox)
			{
				grid[gridY + 1][gridX].hasBox = false;
				grid[gridY + 2][gridX].hasBox = true;
			}
			gridY = std::min(5, gridY + 1);
		}
		if (KeyLeft.down())
		{
			if (grid[gridY][gridX - 1].isWall)
			{
				return;
			}
			if (grid[gridY][gridX - 1].hasBox)
			{
				grid[gridY][gridX - 1].hasBox = false;
				grid[gridY][gridX - 2].hasBox = true;
			}
			gridX = std::max(0, gridX - 1);
		}
		if (KeyRight.down())
		{
			if (grid[gridY][gridX + 1].isWall)
			{
				return;
			}
			if (grid[gridY][gridX + 1].hasBox)
			{
				grid[gridY][gridX + 1].hasBox = false;
				grid[gridY][gridX + 2].hasBox = true;
			}
			gridX = std::min(7, gridX + 1);
		}
	}

private:
	Circle m_circle;
	int gridX;
	int gridY;
};


void InitializeWall(Grid<CellState>& grid)
{
	//for (int x = 0; x < grid.width(); ++x)
	//{
	//	grid[0][x].isWall = true; // Top wall
	//	grid[grid.height() - 1][x].isWall = true; // Bottom wall
	//}
	//for (int y = 0; y < grid.height(); ++y)
	//{
	//	grid[y][0].isWall = true; // Left wall
	//	grid[y][grid.width() - 1].isWall = true; // Right wall
	//}
}

void InitializeBox(Grid<CellState>& grid)
{
	// Example: Place a box at (1, 1)
	grid[1][1].hasBox = true;
}

void InitializeGoal(Grid<CellState>& grid)
{
	// Example: Place a goal at (2, 2)
	grid[2][2].isGoal = true;
}

void DrawCell(Grid<CellState>& grid)
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

void DrawBox(Grid<CellState>& grid)
{
	for (int y = 0; y < grid.height(); ++y)
	{
		for (int x = 0; x < grid.width(); ++x)
		{
			if (grid[y][x].hasBox)
			{
				RectF rect(Arg::center(convertGrid2Coordinate(x, y, 100)), 100, 100);
				rect.draw(Palette::Blue);
			}
		}
	}
}

void DrawGoal(Grid<CellState>& grid)
{
	for (int y = 0; y < grid.height(); ++y)
	{
		for (int x = 0; x < grid.width(); ++x)
		{
			if (grid[y][x].isGoal)
			{
				RectF rect(Arg::center(convertGrid2Coordinate(x, y, 100)), 100, 100);
				rect.draw(Palette::Green);
			}
		}
	}
}

void DrawWall(Grid<CellState>& grid)
{
	for (int y = 0; y < grid.height(); ++y)
	{
		for (int x = 0; x < grid.width(); ++x)
		{
			if (grid[y][x].isWall)
			{
				RectF rect(Arg::center(convertGrid2Coordinate(x, y, 100)), 100, 100);
				rect.draw(Palette::Brown);
			}
		}
	}
}

void CheckGoal(Grid<CellState>& grid)
{
	for (int y = 0; y < grid.height(); ++y)
	{
		for (int x = 0; x < grid.width(); ++x)
		{
			if (grid[y][x].hasBox && grid[y][x].isGoal) Print << U"Goal Reached!";
		}
	}
}

void Main()
{
	Grid<CellState> grid(8, 6);
	Player player;

	// Initialize grid with walls, boxes, and goals
	InitializeBox(grid);
	InitializeGoal(grid);
	InitializeWall(grid);

	while (System::Update())
	{
		// update
		player.update(grid);

		// draw
		DrawCell(grid);
		DrawBox(grid);
		DrawGoal(grid);
		DrawWall(grid);
		player.draw();

		// Check
		player.CheckCollision(grid);
		CheckGoal(grid);
		CheckGoal(grid);
	}
}

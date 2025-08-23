# include <Siv3D.hpp> // Siv3D v0.6.16

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

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
		: m_circle(50, 50, 20), gridX(1), gridY(1)
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

	Point ConvertDirecton2Vector(Direction direction)
	{
		if (direction == Direction::Up)
		{
			return Point(0, -1);
		}
		else if (direction == Direction::Down)
		{
			return Point(0, 1);
		}
		else if (direction == Direction::Left)
		{
			return Point(-1, 0);
		}
		else if (direction == Direction::Right)
		{
			return Point(1, 0);
		}
	}

	void UpdatePlayerAndBox(Grid<CellState>& grid, Direction direction)
	{
		Point moveVector = ConvertDirecton2Vector(direction);
		if (grid[gridY + moveVector.y][gridX + moveVector.x].isWall) return;
		if (grid[gridY + moveVector.y][gridX + moveVector.x].hasBox)
		{
			if (grid[gridY + moveVector.y * 2][gridX + moveVector.x * 2].isWall) return;
			grid[gridY + moveVector.y][gridX + moveVector.x].hasBox = false;
			grid[gridY + moveVector.y * 2][gridX + moveVector.x * 2].hasBox = true;
		}
		gridX = std::clamp(gridX + moveVector.x, 0, 7);
		gridY = std::clamp(gridY + moveVector.y, 0, 5);
	}

	void update(Grid<CellState>& grid)
	{
		if (KeyUp.down()) UpdatePlayerAndBox(grid, Direction::Up);
		if (KeyDown.down()) UpdatePlayerAndBox(grid, Direction::Down);
		if (KeyLeft.down()) UpdatePlayerAndBox(grid, Direction::Left);
		if (KeyRight.down()) UpdatePlayerAndBox(grid, Direction::Right);
	}

private:
	Circle m_circle;
	int gridX;
	int gridY;
};

void InitializeWall(Grid<CellState>& grid)
{
	// Example: Place walls around the grid
	for (int x = 0; x < grid.width(); ++x)
	{
		grid[0][x].isWall = true;
		grid[grid.height() - 1][x].isWall = true;
	}
	for (int y = 0; y < grid.height(); ++y)
	{
		grid[y][0].isWall = true;
		grid[y][grid.width() - 1].isWall = true;
	}
}

void InitializeBox(Grid<CellState>& grid)
{
	// Example: Place a box at (1, 1)
	grid[2][2].hasBox = true;
}

void InitializeGoal(Grid<CellState>& grid)
{
	// Example: Place a goal at (2, 2)
	grid[3][3].isGoal = true;
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
				rect.draw(Palette::Sienna);
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

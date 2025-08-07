# include <Siv3D.hpp> // Siv3D v0.6.15

class Player
{
public:
	// Constructor

	void draw()
	{
		m_circle.draw(Palette::Red);
	}

	void update()
	{

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

void Main()
{
	struct CellState
	{
		bool hasPlayer = false;
		bool isWall = false;
		bool isGoal = false;
		bool hasBox = false;
	};

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
		player.draw();
		wall.draw();
		baggage.draw();

	}
}

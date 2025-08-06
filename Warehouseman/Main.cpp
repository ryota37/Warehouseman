# include <Siv3D.hpp> // Siv3D v0.6.15

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

	while (System::Update())
	{
	}
}

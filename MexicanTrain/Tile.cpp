#include "Tile.h"

void Tile::Filpside()
{
	int temp = side1;
	side1 = side2;
	side2 = temp;
}

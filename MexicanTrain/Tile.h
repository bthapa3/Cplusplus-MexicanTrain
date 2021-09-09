#pragma once
class Tile
{	
	public:
		
		Tile() {
			side1 = -1;
			side2 = -1;
		
		};
		Tile(int firstside, int secondside) {
			side1 = firstside;
			side2 = secondside;
		}
		~Tile() {};

		inline int GetSide1() {
			return side1;
		}
		inline int GetSide2() {
			return side2;
		}
		void Filpside();
	private:

		int side1;
		int side2;
};


#include "soloModel.hpp"
#include "homeModel.hpp"


const array<Vector2D, 5> Tetrmino::JLSTZ_0_OFFSET = { Vector2D(0, 0), Vector2D(0, 0), Vector2D(0, 0), Vector2D(0, 0), Vector2D(0, 0) };
const array<Vector2D, 5> Tetrmino::JLSTZ_R_OFFSET = { Vector2D(0, 0), Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, -2), Vector2D(1, -2) };
const array<Vector2D, 5> Tetrmino::JLSTZ_2_OFFSET = { Vector2D(0, 0), Vector2D(0, 0), Vector2D(0, 0), Vector2D(0, 0), Vector2D(0, 0) };
const array<Vector2D, 5> Tetrmino::JLSTZ_L_OFFSET = { Vector2D(0, 0), Vector2D(-1, 0), Vector2D(-1, +1), Vector2D(0, -2), Vector2D(-1, -2) };

const array<Vector2D, 5> Tetrmino::I_0_OFFSET = { Vector2D(0, 0), Vector2D(-1, 0), Vector2D(2, 0), Vector2D(-1, 0), Vector2D(2, 0) };
const array<Vector2D, 5> Tetrmino::I_R_OFFSET = { Vector2D(-1, 0), Vector2D(0, 0), Vector2D(0, 0), Vector2D(0, -1), Vector2D(0, 2) };
const array<Vector2D, 5> Tetrmino::I_2_OFFSET = { Vector2D(-1, -1), Vector2D(+1, -1), Vector2D(-2, -1), Vector2D(1, 0), Vector2D(-2, 0) };
const array<Vector2D, 5> Tetrmino::I_L_OFFSET = { Vector2D(0, -1), Vector2D(0, -1), Vector2D(0, -1), Vector2D(0, 1), Vector2D(0, -2) };

const Vector2D Tetrmino::O_0_OFFSET = Vector2D(0, 0);
const Vector2D Tetrmino::O_R_OFFSET = Vector2D(0, 1);
const Vector2D Tetrmino::O_2_OFFSET = Vector2D(-1, 1);
const Vector2D Tetrmino::O_L_OFFSET = Vector2D(-1, 0);


const int Tetrmino::MINO_COORD_POOL[7][8] = {
		{-1, 0, 0, 0, 1, 0, 2, 0},
		{-1, -1, -1, 0, 0, 0, 1, 0},
		{-1, 0, 0, 0, 1, 0, 1, -1},
		{0, -1, 0, 0, 1, -1, 1, 0},
		{-1, 0, 0, 0, 0, -1, 1, -1},
		{-1, 0, 0, -1, 0, 0, 1, 0},
		{-1, -1, 0, -1, 0, 0, 1, 0}
};

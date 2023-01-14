#pragma once
#include "iModel.hpp"
#include "../color/color.hpp"
#include <list>
#include <vector>
#include <array>
#include <functional>

using std::array;
using std::function;
using std::list;
using std::vector;

enum TetrminoType
{
	I,
	O,
	T,
	L,
	J,
	S,
	Z
};

enum TetrminoState
{
	_0,
	_R,
	_2,
	_L
};

enum RotateType
{
	TO_L,
	TO_R
};

inline const TetrminoState operator>>(const TetrminoState &state, int i)
{
	auto c = (int)state + i;
	return c >= 0 ? (TetrminoState)(c % 4) : (TetrminoState)(4 + (c % 4));
}

inline const TetrminoState operator<<(const TetrminoState &state, int i)
{
	auto c = (int)state - i;
	return c >= 0 ? (TetrminoState)(c % 4) : (TetrminoState)(4 + (c % 4));
}

struct Piece
{
	enum PieceType
	{
		LOCKED,
		EMPTY,
		UNLOCKED
	};
	Vector2D relative;
	PieceType type;
	TetrminoType minoType;

	Piece() : relative(0, 0), type(EMPTY), minoType(O)
	{
	}
};

struct Tetrmino
{

	static const array<Vector2D, 5> JLSTZ_0_OFFSET;
	static const array<Vector2D, 5> JLSTZ_R_OFFSET;
	static const array<Vector2D, 5> JLSTZ_2_OFFSET;
	static const array<Vector2D, 5> JLSTZ_L_OFFSET;

	static const array<Vector2D, 5> I_0_OFFSET;
	static const array<Vector2D, 5> I_R_OFFSET;
	static const array<Vector2D, 5> I_2_OFFSET;
	static const array<Vector2D, 5> I_L_OFFSET;

	static const Vector2D O_0_OFFSET;
	static const Vector2D O_R_OFFSET;
	static const Vector2D O_2_OFFSET;
	static const Vector2D O_L_OFFSET;

	static const int MINO_COORD_POOL[7][8];

	array<Piece, 4> pieces;

	Vector2D relative;

	TetrminoType type;

	TetrminoState state;

	Tetrmino(TetrminoType t) : type(t), state(_0), relative(4, 1)
	{
		InitPieces(t);
	}

	void ResetRelative()
	{
		relative.x = 4;
		relative.y = 1;
	}

	void InitPieces(TetrminoType type)
	{
		auto set_mino_from_coord_pool = [this, type](int index) -> void
		{
			for (int i = 0; i < 4; i++)
			{
				pieces[i].relative = Vector2D(MINO_COORD_POOL[index][i * 2], MINO_COORD_POOL[index][i * 2 + 1]);
				pieces[i].minoType = type;
				pieces[i].type = Piece::UNLOCKED;
			}
		};

		switch (type)
		{
		case I:
			set_mino_from_coord_pool(0);
			break;
		case O:
			set_mino_from_coord_pool(1);
			break;
		case T:
			set_mino_from_coord_pool(2);
			break;
		case L:
			set_mino_from_coord_pool(3);
			break;
		case J:
			set_mino_from_coord_pool(4);
			break;
		case S:
			set_mino_from_coord_pool(5);
			break;
		case Z:
			set_mino_from_coord_pool(6);
			break;
		default:
			break;
		}
	}

	const array<Vector2D, 5> &GetJLSTZOffset(TetrminoState state) const
	{

		switch (state)
		{
		case _0:
			return JLSTZ_0_OFFSET;
			break;
		case _R:
			return JLSTZ_R_OFFSET;
			break;
		case _2:
			return JLSTZ_2_OFFSET;
			break;
		case _L:
			return JLSTZ_L_OFFSET;
			break;
		}
	}

	const array<Vector2D, 5> &GetIOffset(TetrminoState state) const
	{

		switch (state)
		{
		case _0:
			return I_0_OFFSET;
			break;
		case _R:
			return I_R_OFFSET;
			break;
		case _2:
			return I_2_OFFSET;
			break;
		case _L:
			return I_L_OFFSET;
			break;
		}
	}

	const Vector2D &GetOOffset(TetrminoState state) const
	{
		switch (state)
		{
		case _0:
			return O_0_OFFSET;
			break;
		case _R:
			return O_R_OFFSET;
			break;
		case _2:
			return O_2_OFFSET;
			break;
		case _L:
			return O_L_OFFSET;
			break;
		}
	}

	const array<Vector2D, 5> GetOffsetDiff(RotateType type) const
	{
		auto nextState = type == TO_L ? state << 1 : state >> 1;
		array<Vector2D, 5> of1;
		array<Vector2D, 5> of2;
		if (this->type == I)
		{
			of1 = GetIOffset(state);
			of2 = GetIOffset(nextState);
		}
		else
		{
			of1 = GetJLSTZOffset(state);
			of2 = GetJLSTZOffset(nextState);
		}
		return array<Vector2D, 5>{of1[0] - of2[0], of1[1] - of2[1], of1[2] - of2[2], of1[3] - of2[3], of1[4] - of2[4]};
	}

	const Vector2D GetOOffsetDiff(RotateType type) const
	{
		auto nextState = type == TO_L ? state << 1 : state >> 1;
		return GetOOffset(state) - GetOOffset(nextState);
	}

	void Rotate(int offsetIndex, RotateType rtp)
	{
		auto nextState = rtp == TO_L ? state << 1 : state >> 1;

		Vector2D offset = type == O ? GetOOffsetDiff(rtp) : GetOffsetDiff(rtp).at(offsetIndex);
		Rotate(rtp);
		relative = relative + offset;
		state = nextState;
	}

	void Rotate(RotateType rtp)
	{
		int cos = 0, sin, msin;
		if (rtp == TO_L)
		{
			sin = -1;
			msin = 1;
		}
		else
		{
			sin = 1;
			msin = -1;
		}
		for (auto &p : pieces)
		{
			auto x = p.relative.x;
			p.relative.x = cos * p.relative.x + msin * p.relative.y;
			p.relative.y = sin * x + cos * p.relative.y;
		}
	}
};

class SoloModel : public Model
{
	class RandomMinoTypeBagGenerator
	{
		TetrminoType types[7] = {I, J, L, O, S, T, Z};
		int top = 0;

		bool TouchTop()
		{
			return top == 7;
		}

		void InitTopPoint()
		{
			top = 0;
		}

	public:
		RandomMinoTypeBagGenerator()
		{
			srand(SDL_GetTicks());
			for (int i = 0; i < 6; i++)
			{
				int rand_index = (rand() % (7 - i - 1)) + i + 1;
				auto temp = types[i];
				types[i] = types[rand_index];
				types[rand_index] = temp;
			}
		}

		TetrminoType GetTetrminoType()
		{
			if (TouchTop())
			{
				for (int i = 0; i < 6; i++)
				{
					int rand_index = (rand() % (7 - i - 1)) + i + 1;
					auto temp = types[i];
					types[i] = types[rand_index];
					types[rand_index] = temp;
				}
				InitTopPoint();
			}

			top++;
			return types[top - 1];
		}

		Tetrmino *GetTetrmino()
		{
			return new Tetrmino(GetTetrminoType());
		}
	};

private:
public:
	enum Mode
	{
		PRELOCK,
		CLEARING,
		NORMAL,
		DRAPING
	};

	Tetrmino *currentMino;
	Tetrmino *holdedMino;
	Mode mode;

	Vector2D surfaceOffset;
	RandomMinoTypeBagGenerator minoGenerator;

	Piece pieces[22][10];

	list<Tetrmino *> nextQueque;

	bool holded;

	Uint64 currentTick;

	Uint64 lockDelay;

	Uint64 gravity;

	Uint64 dropDelay;

	Uint64 eraseLineDelay;

	vector<Uint64> tickCounters;

	Uint64 repeateDelay;

	Uint64 preRepeateDelay;

	SoloModel() : mode(NORMAL), tickCounters(5), holded(false), currentTick(0), lockDelay(200), gravity(1), dropDelay(100), eraseLineDelay(300), repeateDelay(20), preRepeateDelay(200)
	{
		EachPieces([](Piece &piece, int x, int y) -> void
				   {
				piece.relative.x = x;
		piece.relative.y = y;
		piece.type = piece.EMPTY; });
		currentMino = minoGenerator.GetTetrmino();
		for (int i = 0; i < 4; i++)
		{
			nextQueque.push_back(minoGenerator.GetTetrmino());
		}
	}

	void EachPieces(function<void(Piece &piece, int x, int y)> fn)
	{
		for (int i = 0; i < 22; i++)
			for (int j = 0; j < 10; j++)
				fn(pieces[i][j], j, i);
	}

	void EachFilteredPieces(function<void(Piece &piece, int x, int y)> fn, function<bool(Piece &piece)> condition)
	{
		for (int i = 0; i < 22; i++)
			for (int j = 0; j < 10; j++)
				if (condition(pieces[i][j]))
					fn(pieces[i][j], j, i);
	}

	bool TouchCheck(const Tetrmino *mino)
	{
		if (mino == nullptr)
			return true;

		bool res = true;
		for (int i = 0; i < 4; i++)
		{
			Vector2D coord(mino->pieces[i].relative + mino->relative);

			res &= coord.y < 22 && coord.x < 10 && coord.y >= 0 && coord.x >= 0 && pieces[coord.y][coord.x].type == Piece::EMPTY;
		}

		return res;
	}

	void UpdateState()
	{
		if (currentTick == 0)
		{
			currentTick = SDL_GetTicks64();
		}
		else
		{
			auto nowTick = SDL_GetTicks64();
			for (Uint64 &tickCounter : tickCounters)
				tickCounter += nowTick - currentTick;
			currentTick = nowTick;
		}

		switch (mode)
		{
		case SoloModel::PRELOCK:
			if (CanDownOneStep(currentMino))
			{
				tickCounters.at(0) = 0;
				mode = NORMAL;
			}

			if (tickCounters.at(0) >= lockDelay)
			{
				Lock();
				if (GetFullLineNum().size() > 0)
				{
					mode = CLEARING;
					tickCounters.at(0) = 0;
				}
				else
				{
					tickCounters.at(0) = 0;
					mode = NORMAL;
				}
			}
			break;
		case SoloModel::CLEARING:
			if (tickCounters.at(0) >= eraseLineDelay)
			{
				mode = NORMAL;
				tickCounters.at(0) = 0;
				ClearLine(GetFullLineNum());
			}
			break;
		case SoloModel::NORMAL:
			if (!CanDownOneStep(currentMino))
			{
				tickCounters.at(0) = 0;
				mode = PRELOCK;
			}
			else if (tickCounters.at(0) >= 1000 / gravity)
			{
				bool res = DownOneStep(currentMino);
				tickCounters.at(0) = 0;
				if (!res)
					mode = PRELOCK;
			}

			break;
		case SoloModel::DRAPING:
			if (tickCounters.at(0) >= dropDelay)
			{
				DownOneStep(currentMino);

				Lock();

				if (GetFullLineNum().size() > 0)
				{
					mode = CLEARING;
					tickCounters.at(0) = 0;
				}
				else
				{
					tickCounters.at(0) = 0;
					mode = NORMAL;
				}
			}
			break;
		default:
			break;
		}
	}

	void HandleMoveFailed(int step)
	{
	}

	void HandleRepeateInput(Controller &controller)
	{
		if (tickCounters.at(2) >= preRepeateDelay)

			if (controller.right_button_down)
			{
				if (tickCounters.at(1) >= repeateDelay)
				{
					tickCounters.at(1) = 0;
					bool res = MoveOneStep(1, currentMino);
					if (!res)
					{
						HandleMoveFailed(1);
					}
					else if (mode == PRELOCK)
					{
						tickCounters.at(0) = 0;
					}
				}
			}

			else if (controller.left_button_down)
			{
				if (tickCounters.at(1) >= repeateDelay)
				{
					tickCounters.at(1) = 0;
					bool res = MoveOneStep(-1, currentMino);
					if (!res)
					{
						HandleMoveFailed(-1);
					}
					else if (mode == PRELOCK)
					{
						tickCounters.at(0) = 0;
					}
				}
			}

			else if (controller.soft_down_button_down)
			{
				if (tickCounters.at(1) >= repeateDelay)
				{
					tickCounters.at(1) = 0;
					bool res = DownOneStep(currentMino);
					if (res)
					{
						if (mode == PRELOCK)
							tickCounters.at(0) = 0;
					}
				}
			}
	}

	virtual void HandleInput(Controller &controller) override
	{
		auto c = controller.PopEvent();
		while (c != Controller::empty)
		{

			bool res = false;

			switch (c)
			{
			case Controller::rightClick:
				tickCounters.at(1) = 0;
				tickCounters.at(2) = 0;
				res = MoveOneStep(1, currentMino);
				if (!res)
				{
					HandleMoveFailed(1);
				}

				else
				{
					if (mode == PRELOCK)
						tickCounters.at(0) = 0;
				}
				break;
			case Controller::leftClick:
				tickCounters.at(1) = 0;
				tickCounters.at(2) = 0;
				res = MoveOneStep(-1, currentMino);
				if (!res)
				{
					HandleMoveFailed(-1);
				}
				else
				{
					if (mode == PRELOCK)
						tickCounters.at(0) = 0;
				}
				break;
			case Controller::downClick:
				while (DownOneStep(currentMino))
					;
				mode = DRAPING;
				break;
			case Controller::softDownClick:
				tickCounters.at(1) = 0;
				tickCounters.at(2) = 0;
				res = DownOneStep(currentMino);
				if (!res)
				{
					mode = PRELOCK;
				}
				else
				{
					if (mode == PRELOCK)
						tickCounters.at(0) = 0;
				}
				break;
			case Controller::swapClick:
				HoldCurrent();
				break;
			case Controller::lrotateClick:
				res = Rotate(currentMino, TO_L);
				if (res)
				{
					if (mode == PRELOCK)
						tickCounters.at(0) = 0;
				}
				break;
			case Controller::rrotateClick:
				res = Rotate(currentMino, TO_R);
				if (res)
				{
					if (mode == PRELOCK)
						tickCounters.at(0) = 0;
				}
				break;
			default:
				break;
			}

			c = controller.PopEvent();
		}

		HandleRepeateInput(controller);
	}

	bool DownOneStep(Tetrmino *mino)
	{
		bool res = true;
		Vector2D backup = mino->relative;
		mino->relative.y++;
		if (!TouchCheck(mino))
		{
			mino->relative = backup;
			res = false;
		}
		return res;
	}

	bool CanDownOneStep(Tetrmino *mino)
	{
		Tetrmino temp(*mino);
		return DownOneStep(&temp);
	}

	bool MoveOneStep(int step, Tetrmino *mino)
	{
		bool res = true;
		Vector2D backup = currentMino->relative;
		mino->relative.x += step;
		if (!TouchCheck(currentMino))
		{
			mino->relative = backup;
			res = false;
		}
		return res;
	}

	bool CanMoveOneStep(int step, Tetrmino *mino)
	{
		Tetrmino temp(*mino);
		return MoveOneStep(step, &temp);
	}

	bool Rotate(Tetrmino *mino, RotateType rtp)
	{

		for (int i = 0; i < 5; i++)
		{
			Tetrmino test(*mino);

			test.Rotate(i, rtp);

			if (TouchCheck(&test))
			{
				mino->Rotate(i, rtp);

				return true;
			}
		}

		return false;
	}
	bool CanRotate(Tetrmino *mino, RotateType rtp)
	{
		Tetrmino temp(*mino);
		return Rotate(&temp, rtp);
	}

	Tetrmino GetCurrentPreLook()
	{
		Tetrmino mino(*currentMino);
		while (DownOneStep(&mino))
			;
		return mino;
	}

	void HoldCurrent()
	{
		if (holdedMino == nullptr)
		{
			holdedMino = currentMino;
			holdedMino->ResetRelative();
			currentMino = nextQueque.front();
			nextQueque.push_back(minoGenerator.GetTetrmino());
		}
		else
		{
			auto temp = holdedMino;
			holdedMino = currentMino;
			holdedMino->ResetRelative();
			currentMino = holdedMino;
		}
		holded = true;
	}

	vector<int> GetFullLineNum()
	{
		auto check = [this](int y) -> bool
		{
			bool res = true;
			for (int x = 0; x < 10; x++)
			{
				res &= pieces[y][x].type == Piece::LOCKED;
			}
			return res;
		};

		vector<int> rows;
		for (int y = 21; y > 2; y--)
		{
			if (check(y))
			{
				rows.push_back(y);
			}
		}

		return rows;
	}

	void ClearLine(vector<int> &rows)
	{

		int i = 0;

		while (i < rows.size())
		{
			int end = -1;
			if (i < rows.size() - 1)
				end = rows[i + 1] + 1;
			for (int col = rows[i] + i; col - 1 - i > end; col--)
			{
				for (int x = 0; x < 10; x++)
				{
					pieces[col][x] = pieces[col - 1 - i][x];
					pieces[col][x].relative = Vector2D(x, col);
				}
			}
			if (end == -1)
			{
				for (int col = end + 1 + i; col >= 0; col--)
				{
					for (int x = 0; x < 10; x++)
					{
						pieces[col][x].type = Piece::EMPTY;
					}
				}
			}
			i++;
		}

		for (int col = 0; col < rows.size(); col++)
		{
			for (int x = 0; x < 10; x++)
			{
				pieces[col][x].type = Piece::EMPTY;
			}
		}
	}

	void Lock()
	{
		for (int i = 0; i < 4; i++)
		{
			currentMino->pieces[i].relative = currentMino->relative + currentMino->pieces[i].relative;
			currentMino->pieces[i].type = Piece::LOCKED;
			pieces[currentMino->pieces[i].relative.y][currentMino->pieces[i].relative.x] = currentMino->pieces[i];
		}

		delete currentMino;
		currentMino = nextQueque.front();
		nextQueque.pop_front();
		nextQueque.push_back(minoGenerator.GetTetrmino());

		holded = false;
	}
};

class SoloInterface : public Interface
{
public:
	SDL_Texture *redTile;
	SDL_Texture *blueTile;
	SDL_Texture *greenTile;
	SDL_Texture *yellowTile;
	SDL_Texture *orangeTile;
	SDL_Texture *purpleTile;
	SDL_Texture *cyanTile;

	SoloModel model;

	string name{"solo"};

	SoloInterface(SDL_Renderer *renderer, TTF_Font *font) : Interface(renderer)
	{
		redTile = IMG_LoadTexture(renderer, "assets/hong.png");
		blueTile = IMG_LoadTexture(renderer, "assets/lan.png");
		greenTile = IMG_LoadTexture(renderer, "assets/lu.png");
		yellowTile = IMG_LoadTexture(renderer, "assets/huang.png");
		orangeTile = IMG_LoadTexture(renderer, "assets/cheng.png");
		purpleTile = IMG_LoadTexture(renderer, "assets/zi.png");
		cyanTile = IMG_LoadTexture(renderer, "assets/qing.png");
		if (redTile == nullptr || blueTile == nullptr || greenTile == nullptr || yellowTile == nullptr || orangeTile == nullptr || purpleTile == nullptr || cyanTile == nullptr)
		{
			throw GameError("load tile filed", IMG_GetError());
		}
	}

	~SoloInterface()
	{
		SDL_DestroyTexture(redTile);
		SDL_DestroyTexture(blueTile);
		SDL_DestroyTexture(greenTile);
		SDL_DestroyTexture(yellowTile);
		SDL_DestroyTexture(orangeTile);
		SDL_DestroyTexture(purpleTile);
		SDL_DestroyTexture(cyanTile);
	}

	SDL_Texture *GetTileForType(TetrminoType type)
	{
		switch (type)
		{
		case I:
			return cyanTile;
			break;
		case O:
			return yellowTile;
			break;
		case T:
			return purpleTile;
			break;
		case L:
			return orangeTile;
			break;
		case J:
			return blueTile;
			break;
		case S:
			return greenTile;
			break;
		case Z:
			return redTile;
			break;
		default:
			return NULL;
			break;
		}
	}

	virtual void UpdateInterface(Controller &controller) override
	{
		model.HandleInput(controller);
		model.UpdateState();
	}

	virtual void RenderDrawBoard(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *target) override
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		int minoSize = 700 / 22;

		SDL_Texture *pregion = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, minoSize * 10, minoSize * 22);
		SDL_Texture *nextQueQue = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, minoSize * 5, minoSize * 5 * model.nextQueque.size());
		SDL_SetRenderTarget(renderer, pregion);
		SDL_RenderClear(renderer);
		model.EachPieces([this, renderer, minoSize](Piece &piece, int x, int y) -> void
						 {
			if (piece.type == Piece::EMPTY)
			{
				//TODO 
			}
			else
			{
				auto tile = GetTileForType(piece.minoType);
				SDL_Rect rect = { x * minoSize, y * minoSize, minoSize, minoSize };
				SDL_RenderCopy(renderer, tile, NULL, &rect);
			} });
		if (model.currentMino != nullptr)
		{
			for (int i = 0; i < 4; i++)
			{
				auto &c = model.currentMino->pieces[i];
				auto tile = GetTileForType(c.minoType);
				SDL_Rect rect = {(c.relative.x + model.currentMino->relative.x) * minoSize, (c.relative.y + model.currentMino->relative.y) * minoSize, minoSize, minoSize};
				SDL_RenderCopy(renderer, tile, NULL, &rect);
			}
		}

		auto mino = model.GetCurrentPreLook();
		for (int i = 0; i < 4; i++)
		{
			auto &c = mino.pieces[i];
			SetDrawColor(renderer, RGBA("#cacaca"));
			SDL_Rect rect = {(c.relative.x + mino.relative.x) * minoSize + minoSize * 0.2, (c.relative.y + mino.relative.y) * minoSize + minoSize * 0.2, minoSize - minoSize * 0.2, minoSize - minoSize * 0.2};
			SDL_RenderDrawRect(renderer, &rect);
		}
		SDL_SetRenderTarget(renderer, nextQueQue);
		SetDrawColor(renderer, RGBA("#000"));
		SDL_RenderClear(renderer);
		int q = 0;

		for (auto &mino : model.nextQueque)
		{
			for (int i = 0; i < 4; i++)
			{
				auto &c = mino->pieces[i];
				auto tile = GetTileForType(c.minoType);
				SDL_Rect rect = {(c.relative.x + 2) * minoSize, (c.relative.y + q + 2) * minoSize, minoSize, minoSize};
				SDL_RenderCopy(renderer, tile, NULL, &rect);
			}
			q += 5;
		}
		SDL_SetRenderTarget(renderer, target);
		SDL_Rect rect{650, 50, 300, 660};
		SDL_RenderCopy(renderer, pregion, NULL, &rect);
		RGBA qingbai("#c0ebd7");
		SetDrawColor(renderer, qingbai);
		SDL_RenderDrawRect(renderer, &rect);
		rect.y += 50;
		rect.x += rect.w + 20;
		rect.w = minoSize * 5 * 0.7;
		rect.h = minoSize * 5 * model.nextQueque.size() * 0.7;
		SDL_RenderCopy(renderer, nextQueQue, NULL, &rect);
		SDL_RenderDrawRect(renderer, &rect);

		SDL_DestroyTexture(nextQueQue);
		SDL_DestroyTexture(pregion);
	};
};

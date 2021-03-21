#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>
#include <iostream>

#define INVERTED true									//if terminal background is black set this to true
														//it switches color in print function for right visualisation

#define ICONS false										//does the terminal support unicode chars?

using namespace std;

class game;
class board;
class piece;
class nullpiece;
class rook;
class knight;
class bishop;
class queen;
class pawn;
class king;

//------------------------------------------------------

class board{
	private:
		board * last;									//stores the board before a move 
		piece * thisboard [8][8];						//the board, with all the pieces

		vector<int> whiteking;							//position of white king
		bool whitechecked;								//is white checked?
		bool whitemated;								//is white mated?

		vector<int> blackking;							//position of black king
		bool blackchecked;								//is black checked?
		bool blackmated;								//is black mated?

		int currentmove;								//can be 0 -> white or 1 -> black
		int move;										// 1-1-2-2-3-3...

	public:
		board();										//constructor for a new board with pieces
		board(board * oldBoard);						//copy constructor
		~board();										//destructor (delete all pieces etc.)

		vector<piece*> whitegrave;						//grave of white pieces
		vector<piece*> blackgrave;						//grave of black pieces

		void Print();									//prints the board
		string Unicode(int type, string color);			//converts type+color in unicode char

		piece * GetPiece(int raw, int col);				//returns piece from raw and column
		piece * FindPiece(string pos);					//returns piece from position (es: c5)

		vector<int> Convert(string pos);				//converts position to 2 int (raw, column)
		string ConvertPos(int raw, int col);			//converts raw,column to string
		int ColCharToInt(char types);					//converts char column (a,b,...,h) to corresponding int index
		bool IsColoumn(char type);						//checks if a char describes a column or not
		int TypeStringToInt(char types);				//converts char type to int corresponding

		bool Occupied(int n_raw, int n_col);			//is a position occupied?

		string GetCurrentMove();						//returns a string with move # & color
		int GetCurrentMoveInt();						//returns 0 || 1 for white & black
		int GetMove();									//returns move # (1,2,3,4...)
		void SetCurrentMoveInt(int a);					//set currentmove

		vector<int> Getwhiteking();						//return white king position
		vector<int> Getblackking();						//return black king position

		bool Getwhitechecked();							//is white checked?
		bool Getblackchecked();							//is black checked?

		void ResetChecks();								//putss both checked bool to false
		void LookForChecks();
		void LookForMate();
		void CheckMate();								//checks for mates
		bool GetMated(string color);					//is color mated?

		void Remember();								//saves current board in last
		void Restore();									//restor board in last

		piece * piecenew(piece * oldPiece);				//returns a copy of a piece
		void Promote(int colstop);						//promotes a pawn

		void Move(string start, string stop);			//moves a piece from start position to stop position, in possible
		void Move(string unic);							//truly just a parser for move in chess format (dxe5), passes all to Move(string,string)
};

class piece{
	protected:
		int raw;										//raw of piece
		int col;										//col of piece
		string color;									//color of piece
		int type;										//type of piece 
															//rook 		-> 1
															//kinght	-> 2
															//bishop 	-> 3
															//queen 	-> 4
															//pawn		-> 5
															//king 		-> 6
		bool alive;										//is this piece alive?
		bool moved;										//has this piece moved yet?
		bool possiblemoves [8][8];						//every piece has a "board" of bool, can it moves in that pos?
	public:
		piece(){};										//default constructor (not used)

		vector<int> GetPos();							//retun pos
		int GetRaw();									//retun raw
		int GetCol();									//retun col
		bool GetAlive();								//retun alive status							
		bool GetMoved();								//retun moved status
		string GetColor();								//retun color
		int GetType();									//retun # for type

		bool SetAlive(bool a);							//set alive status
		bool SetMoved(bool a);							//set moved status
		void ChangePos(int n_raw, int n_col);			//change both raw and col

		void reset();									//resets possiblemove matrix
		virtual void update(board * myBoard){};			//update possiblemove matrix
		void PrintPossible(board * myBoard);			//prints matrix (for debug use)
		bool GetPossibleMove(int n_raw, int n_col);		//prints a single element of matrix without updating 
		bool CanMove(int n_raw, int n_col, board * myBoard);	//can this piece move to pos in this board?

		void Print();									//print some info (for debug use)
};

class nullpiece : public piece{
	public:
		nullpiece(int riga, int colonna);
		void update(board * myBoard);
};

class rook : public piece{
	public:
		rook(string colore, int riga, int colonna);
		void update(board * myBoard);
};

class knight : public piece{
	public:
		knight(string colore, int riga, int colonna);
		void update(board * myBoard);
};

class bishop : public piece{
	public:
		bishop(string colore, int riga, int colonna);
		void update(board * myBoard);
};

class queen : public piece{
	public:
		queen(string colore, int riga, int colonna);
		void update(board * myBoard);
};

class pawn : public piece{
	public:
		pawn(string colore, int riga, int colonna);
		void update(board * myBoard);
};

class king : public piece{
	public:
		king(string colore, int riga, int colonna);
		void update(board * myBoard);
};

//----------------------------------------------------------------
//Game Function. Obv not really of the library, but useful
//----------------------------------------------------------------

inline void StartGame(){
	board * currentgame= new board();

	currentgame -> Print();


	while(true){
		cout << currentgame -> GetCurrentMove();
		string start, end;
		cin >> start;
		currentgame -> Move(start);
		currentgame -> Print();
		if(currentgame -> GetMated("white")){
			cout << "Nero vince" << endl;
			break;
		}
		if(currentgame -> GetMated("black")){
			cout << "Bianco vince" << endl;
			break;
		}
	}
	delete currentgame;
}

#endif
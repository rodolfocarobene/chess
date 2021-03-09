#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <vector>
#include <iostream>

#define INVERTED true	


using namespace std;


class board;
class piece;
class nullpiece;
class rook;
class knight;
class bishop;
class queen;
class pawn;
class king;

class piece{
	protected:
		int raw;
		int col;
		string color;
		bool alive;
		bool moved;
		int type;
		bool possiblemoves [8][8];
	public:
		piece(){};
		piece(piece * oldPiece);
		vector<int> GetPos();
		int GetRaw();
		int GetCol();
		bool GetAlive();
		bool GetMoved();
		bool SetAlive(bool a);
		bool SetMoved(bool a);
		string GetColor();
		int GetType();
		void reset();
		virtual void update(board * myBoard){};
		void PrintPossible(board * myBoard);
		bool CanMove(int n_raw, int n_col, board * myBoard);
		void ChangePos(int n_raw, int n_col);
		void Print();
		bool GetPossibleMove(int n_raw, int n_col);
};

//scacchiera intera, con tutti i pezzi
class board{
	private:
		board * last;
		piece * thisboard [8][8];
		vector<int> whiteking;
		bool whitechecked;
		bool whitemated;
		vector<int> blackking;
		bool blackchecked;
		bool blackmated;
		int currentmove;
	public:
		board();
		board(board * oldBoard);
		~board();
		vector<piece*> whitegrave;
		vector<piece*> blackgrave;
		void Print();
		piece * GetPiece(int raw, int col);
		piece * FindPiece(string pos);
		vector<int> Convert(string pos);
		void Move(string start, string stop);
		void Move(string unic);
		bool Occupied(int n_raw, int n_col);
		string Unicode(int type, string color);
		string ConvertPos(int raw, int col);
		string GetCurrentMove();
		int GetCurrentMoveInt();
		void SetCurrentMoveInt(int a);
		vector<int> Getwhiteking();
		bool Getwhitechecked();
		vector<int> Getblackking();
		bool Getblackchecked();
		void ResetChecks();
		void CheckChecks(string type = "total");
		void Remember();
		void Restore();
		int TypeStringToInt(char types);
		piece * piecenew(piece * oldPiece);
		int ColCharToInt(char types);
		bool IsColoumn(char type);
		bool GetMated(string color);
		void CheckMate();
		void Promote(int colstop);
};


//pezzo nullo, probabilmente 
//si può anche togliere con un po' di lavoro
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

#include "board.h"
#include "piece.h"

//----------------------------------------------------------------

nullpiece::nullpiece(int riga, int colonna){
	raw = riga;
	col = colonna;
	color = "";
	type = 0;
	alive = false;
	moved = false;
}

rook::rook(string colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 1;
	alive = true;
	moved = false;
}

knight::knight(string colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 2;
	alive = true;
	moved = false;
}

bishop::bishop(string colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 3;
	alive = true;
	moved = false;
}

queen::queen(string colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 4;
	alive = true;
	moved = false;
}

pawn::pawn(string colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 5;
	alive = true;
	moved = false;
}

king::king(string colore, int riga, int colonna){
	raw = riga;
	col = colonna;
	color = colore;
	type = 6;
	alive = true;
	moved = false;
}

//---------------------------------------------------------

void rook::update(board * myBoard){
	this -> reset();
	int j = 1;
	while(col+j<8){
		if(myBoard -> Occupied(raw,col+j) == false)
			possiblemoves[raw][col+j] = true;
		else{
			if(myBoard -> GetPiece(raw,col+j) -> GetColor() != color){
				possiblemoves[raw][col+j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(col-j>=0){
		if(myBoard -> Occupied(raw,col-j) == false)
			possiblemoves[raw][col-j] = true;
		else{
			if(myBoard -> GetPiece(raw,col-j) -> GetColor() != color){
				possiblemoves[raw][col-j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw+j<8){
		if(myBoard -> Occupied(raw+j,col) == false)
			possiblemoves[raw+j][col] = true;
		else{
			if(myBoard -> GetPiece(raw+j,col) -> GetColor() != color){
				possiblemoves[raw+j][col] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw-j>=0){
		if(myBoard -> Occupied(raw-j,col) == false)
			possiblemoves[raw-j][col] = true;
		else{
			if(myBoard -> GetPiece(raw-j,col) -> GetColor() != color){
				possiblemoves[raw-j][col] = true;
				break;
			}
			else break;
		}
		j++;
	}
}

void knight::update(board * myBoard){
	this -> reset();
	possiblemoves[raw][col] = true;
	if(raw+1<8 && col+2<8) 
		if(myBoard -> GetPiece(raw+1,col+2) -> GetColor() != color)
			possiblemoves[raw+1][col+2] = true;
	if(raw+1<8 && col-2>=0) 
		if(myBoard -> GetPiece(raw+1,col-2) -> GetColor() != color)
			possiblemoves[raw+1][col-2] = true;
	if(raw-1>=0 && col+2<8) 
		if(myBoard -> GetPiece(raw-1,col+2) -> GetColor() != color)
			possiblemoves[raw-1][col+2] = true;
	if(raw-1>=0 && col-2>=0) 
		if(myBoard -> GetPiece(raw-1,col-2) -> GetColor() != color)
			possiblemoves[raw-1][col-2] = true;

	if(raw+2<8 && col+1<8) 
		if(myBoard -> GetPiece(raw+2,col+1) -> GetColor() != color)
			possiblemoves[raw+2][col+1] = true;
	if(raw+2<8 && col-1>=0) 
		if(myBoard -> GetPiece(raw+2,col-1) -> GetColor() != color)
			possiblemoves[raw+2][col-1] = true;
	if(raw-2>=0 && col+1<8) 
		if(myBoard -> GetPiece(raw-2,col+1) -> GetColor() != color)
			possiblemoves[raw-2][col+1] = true;
	if(raw-2>=0 && col-1>=0) 
		if(myBoard -> GetPiece(raw-2,col-1) -> GetColor() != color)
			possiblemoves[raw-2][col-1] = true;
}

void bishop::update(board * myBoard){
	this -> reset();
	int j = 1;
	while(raw+j<8 && col+j<8){
		if(myBoard -> Occupied(raw+j,col+j) == false)
			possiblemoves[raw+j][col+j] = true;
		else{
			if(myBoard -> GetPiece(raw+j,col+j) -> GetColor() != color){
				possiblemoves[raw+j][col+j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw-j>=0 && col-j>=0){
		if(myBoard -> Occupied(raw-j,col-j) == false)
			possiblemoves[raw-j][col-j] = true;
		else{
			if(myBoard -> GetPiece(raw-j,col-j) -> GetColor() != color){
				possiblemoves[raw-j][col-j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw+j<8 && col-j>=0){
		if(myBoard -> Occupied(raw+j,col-j) == false)
			possiblemoves[raw+j][col-j] = true;
		else{
			if(myBoard -> GetPiece(raw+j,col-j) -> GetColor() != color){
				possiblemoves[raw+j][col-j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw-j>=0 && col+j<8){
		if(myBoard -> Occupied(raw-j,col+j) == false)
			possiblemoves[raw-j][col+j] = true;
		else{
			if(myBoard -> GetPiece(raw-j,col+j) -> GetColor() != color){
				possiblemoves[raw-j][col+j] = true;
				break;
			}
			else break;
		}
		j++;
	}
}

void queen::update(board * myBoard){
	this -> reset();
	int j = 1;
	while(col+j<8){
		if(myBoard -> Occupied(raw,col+j) == false)
			possiblemoves[raw][col+j] = true;
		else{
			if(myBoard -> GetPiece(raw,col+j) -> GetColor() != color){
				possiblemoves[raw][col+j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(col-j>=0){
		if(myBoard -> Occupied(raw,col-j) == false)
			possiblemoves[raw][col-j] = true;
		else{
			if(myBoard -> GetPiece(raw,col-j) -> GetColor() != color){
				possiblemoves[raw][col-j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw+j<8){
		if(myBoard -> Occupied(raw+j,col) == false)
			possiblemoves[raw+j][col] = true;
		else{
			if(myBoard -> GetPiece(raw+j,col) -> GetColor() != color){
				possiblemoves[raw+j][col] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw-j>=0){
		if(myBoard -> Occupied(raw-j,col) == false)
			possiblemoves[raw-j][col] = true;
		else{
			if(myBoard -> GetPiece(raw-j,col) -> GetColor() != color){
				possiblemoves[raw-j][col] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;

	while(raw+j<8 && col+j<8){
		if(myBoard -> Occupied(raw+j,col+j) == false)
			possiblemoves[raw+j][col+j] = true;
		else{
			if(myBoard -> GetPiece(raw+j,col+j) -> GetColor() != color){
				possiblemoves[raw+j][col+j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw-j>=0 && col-j>=0){
		if(myBoard -> Occupied(raw-j,col-j) == false)
			possiblemoves[raw-j][col-j] = true;
		else{
			if(myBoard -> GetPiece(raw-j,col-j) -> GetColor() != color){
				possiblemoves[raw-j][col-j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw+j<8 && col-j>=0){
		if(myBoard -> Occupied(raw+j,col-j) == false)
			possiblemoves[raw+j][col-j] = true;
		else{
			if(myBoard -> GetPiece(raw+j,col-j) -> GetColor() != color){
				possiblemoves[raw+j][col-j] = true;
				break;
			}
			else break;
		}
		j++;
	}
	j = 1;
	while(raw-j>=0 && col+j<8){
		if(myBoard -> Occupied(raw-j,col+j) == false)
			possiblemoves[raw-j][col+j] = true;
		else{
			if(myBoard -> GetPiece(raw-j,col+j) -> GetColor() != color){
				possiblemoves[raw-j][col+j] = true;
				break;
			}
			else break;
		}
		j++;
	}
}

void king::update(board * myBoard){
	this -> reset();
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			bool rawbool = raw+i >= 0 && raw+i < 8;
			bool colbool = col+j >= 0 && col+j < 8;
			if(rawbool && colbool) 
				if(myBoard -> GetPiece(raw+i,col+j) -> GetColor() != color)
					possiblemoves[raw+i][col+j] = true;
		}
	}
}

void pawn::update(board * myBoard){
	this -> reset();
	if(color == "white"){
		if(moved==false){
			if(myBoard -> Occupied(raw+1, col) == false){
				possiblemoves[raw+1][col] = true;
				if(myBoard -> Occupied(raw+2, col) == false){
					possiblemoves[raw+2][col] = true;
				}
			}
		}
		else{
			if(raw+1 < 8){
				if(myBoard -> Occupied(raw+1, col) == false) possiblemoves[raw+1][col] = true;
			} 
		}
		if(raw + 1 < 8 && col + 1 < 8){
			if(myBoard -> GetPiece(raw+1,col+1) -> GetColor() != this -> GetColor() && myBoard -> Occupied(raw+1,col+1))
				possiblemoves[raw+1][col+1] = true;
		}
		if(raw + 1 < 8 && col - 1 >= 0){
			if(myBoard -> GetPiece(raw+1,col-1) -> GetColor() != this -> GetColor() && myBoard -> Occupied(raw+1,col-1))
				possiblemoves[raw+1][col-1] = true;
		}
	}
	if(color == "black"){
		if(moved==false){
			//cout << raw << " " << col << endl;
			if(myBoard -> Occupied(raw-1, col) == false){
				//cout << "occupied" << endl;
				possiblemoves[raw-1][col] = true;
				if(myBoard -> Occupied(raw-2, col) == false){
					possiblemoves[raw-2][col] = true;
				}
			}
		}
		else{
			if(raw-1 >= 0){
				if(myBoard -> Occupied(raw-1, col) == false) possiblemoves[raw-1][col] = true;
			} 
		}
		if(raw - 1 >= 0 && col + 1 < 8){
			if(myBoard -> GetPiece(raw-1,col+1) -> GetColor() != this -> GetColor() && myBoard -> Occupied(raw-1,col+1))
				possiblemoves[raw-1][col+1] = true;
		}
		if(raw - 1 >= 0 && col - 1 >= 0){
			if(myBoard -> GetPiece(raw-1,col-1) -> GetColor() != this -> GetColor() && myBoard -> Occupied(raw-1,col-1))
				possiblemoves[raw-1][col-1] = true;
		}
	}
}

void nullpiece::update(board * myBoard){
	this -> reset();
}

#endif
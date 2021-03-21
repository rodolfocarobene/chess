#include "chess.h"

//---------------------------------------------------------
//all constructors
//---------------------------------------------------------

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
//all update functions
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

//---------------------------------------------------------

vector<int> piece::GetPos(){
	vector<int> a;
	a.push_back(raw);
	a.push_back(col);
	return a;
}

int piece::GetRaw(){
	return raw;
}

int piece::GetCol(){
	return col;
}

bool piece::GetAlive(){
	return alive;
}

bool piece::GetMoved(){
	return moved;
}

string piece::GetColor(){
	return color;
}

int piece::GetType(){
	return type;
}

//---------------------------------------------------------

bool piece::SetAlive(bool a){
	alive = a;
}

bool piece::SetMoved(bool a){
	moved = a;
}

void piece::ChangePos(int n_raw, int n_col){
	moved = true;
	raw = n_raw;
	col = n_col;
}

//---------------------------------------------------------

void piece::reset(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			possiblemoves[i][j] = false;
		}
	}
}

void piece::PrintPossible(board * myBoard){
	this -> update(myBoard);
	for(int i = 7; i >= 0; i--){
		for(int j = 0; j < 8; j++){
			cout << possiblemoves[i][j] << "\t";
		}
		cout << endl;
	}
}

bool piece::GetPossibleMove(int n_raw, int n_col){
	return possiblemoves[n_raw][n_col];
}

bool piece::CanMove(int n_raw, int n_col, board * myBoard){
	this -> update(myBoard);
	//cout << "canmove to " << n_raw << " " << n_col << ": " << possiblemoves[n_raw][n_col] << endl;
	return possiblemoves[n_raw][n_col];
}

//---------------------------------------------------------

void piece::Print(){
	cout << "pezzo= " << raw << " " << col << " - " << type << " - " << color << endl;
}

//---------------------------------------------------------
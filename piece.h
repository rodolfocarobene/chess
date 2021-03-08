//piece.h

piece::piece(piece * oldPiece){
	raw = oldPiece -> GetRaw();
	col = oldPiece -> GetCol();
	color = oldPiece -> GetColor();
	type = oldPiece -> GetType();
	alive = oldPiece -> GetAlive();
	moved = oldPiece -> GetMoved();

	for(int i = 0; i < 8; i++){
		for (int j= 0; j < 8; j++){
			possiblemoves[i][j] = oldPiece -> GetPossibleMove(i,j);
		}
	}

}

bool piece::GetPossibleMove(int n_raw, int n_col){
	return possiblemoves[n_raw][n_col];
}

void piece::Print(){
	cout << "pezzo= " << raw << " " << col << " - " << type << " - " << color << endl;
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


bool piece::SetAlive(bool a){
	alive = a;
}

bool piece::SetMoved(bool a){
	moved = a;
}


vector<int> piece::GetPos(){
	vector<int> a;
	a.push_back(raw);
	a.push_back(col);
	return a;
}

string piece::GetColor(){
	return color;
}

int piece::GetType(){
	return type;
}

bool piece::CanMove(int n_raw, int n_col, board * myBoard){
	this -> update(myBoard);
	//cout << "canmove to " << n_raw << " " << n_col << ": " << possiblemoves[n_raw][n_col] << endl;
	return possiblemoves[n_raw][n_col];
}

void piece::ChangePos(int n_raw, int n_col){
	moved = true;
	raw = n_raw;
	col = n_col;
}

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
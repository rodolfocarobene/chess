board::board(){

	thisboard[0][0] = new rook("white",0,0);
	thisboard[0][1] = new knight("white",0,1);
	thisboard[0][2] = new bishop("white",0,2);
	thisboard[0][3] = new queen("white",0,3);
	thisboard[0][4] = new king("white",0,4);
	thisboard[0][5] = new bishop("white",0,5);
	thisboard[0][6] = new knight("white",0,6);
	thisboard[0][7] = new rook("white",0,7);

	thisboard[7][0] = new rook("black",7,0);
	thisboard[7][1] = new knight("black",7,1);
	thisboard[7][2] = new bishop("black",7,2);
	thisboard[7][3] = new queen("black",7,3);
	thisboard[7][4] = new king("black",7,4);
	thisboard[7][5] = new bishop("black",7,5);
	thisboard[7][6] = new knight("black",7,6);
	thisboard[7][7] = new rook("black",7,7);

	for(int i = 0; i < 8; i++){
		thisboard[1][i] = new pawn("white",1,i);
		thisboard[6][i] = new pawn("black",6,i);		
	}

	for(int i = 0; i < 8; i++){
		for(int j = 2; j < 6; j++){
			thisboard[j][i] = new nullpiece(j,i);
		}
	}

	whiteking.push_back(0);
	whiteking.push_back(4);
	blackking.push_back(7);
	blackking.push_back(4);

	whitechecked = false;
	blackchecked = false;

	currentmove = 0;
}

board::board(board * oldBoard){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			thisboard[i][j] = this -> piecenew(oldBoard -> GetPiece(i,j));
		}
	}

	whiteking = oldBoard -> Getwhiteking();
	blackking = oldBoard -> Getblackking();

	//cout << "re nero: " << oldBlack[0] << " " << oldBlack[1] << endl;
	//cout << "re bianco: " << oldWhite[0] << " " << oldWhite[1] << endl;

	currentmove = oldBoard -> GetCurrentMoveInt();

	whitechecked = oldBoard -> Getwhitechecked();
	blackchecked = oldBoard -> Getblackchecked();

	blackmated = oldBoard -> GetMated("black");
	whitemated = oldBoard -> GetMated("white");
}

board::~board(){
	delete last;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++)
			delete thisboard[i][j];
	}
}

void board::Remember(){
	delete last; //se last non è NULL
	last = new board(this);
}

void board::Restore(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			delete thisboard[i][j];
			thisboard[i][j] = this -> piecenew(last -> GetPiece(i,j));
		}
	}

	whiteking = last -> Getwhiteking();
	blackking = last -> Getblackking();

	currentmove = last -> GetCurrentMoveInt();

	whitechecked = last -> Getwhitechecked();
	blackchecked = last -> Getblackchecked();

	blackmated = last -> GetMated("black");
	whitemated = last -> GetMated("white");
}

vector<int> board::Getwhiteking(){
	return whiteking;
}

bool board::Getwhitechecked(){
	return whitechecked;
}

vector<int> board::Getblackking(){
	return blackking;
}

bool board::Getblackchecked(){
	return blackchecked;
}

void board::Print(){
	for(int i = 7; i >= 0; i--){
		for(int j = 0; j < 8; j++){
			int type = thisboard[i][j] -> GetType();
			string color = thisboard[i][j] -> GetColor();
			if(j == 0) cout << "|__";
			cout << this -> Unicode(type,color);
			if(j != 7) cout << "__|__";
			else cout << "__|\t" << i+1;
		}
		cout << "\n" << endl;
	}
	cout << "   a     b     c     d     e     f     g     h" << endl;
}

string board::Unicode(int type, string color){
	if(type == 0) return " ";
	if(type == 1){	//rook
		if(color == "black") return "\u2656";
		if(color == "white") return "\u265C";
	}
	if(type == 2){	//knight
		if(color == "black") return "\u2658";
		if(color == "white") return "\u265E";
	}
	if(type == 3){	//bishop
		if(color == "black") return "\u2657";
		if(color == "white") return "\u265D";
	}
	if(type == 4){	//queen
		if(color == "black") return "\u2655";
		if(color == "white") return "\u265B";
	}
	if(type == 5){	//pawn
		if(color == "black") return "\u2659";
		if(color == "white") return "\u265F";
	}
	if(type == 6){	//king
		if(color == "black") return "\u2654";
		if(color == "white") return "\u265A";
	}
}

piece * board::GetPiece(int raw, int col){
	return thisboard[raw][col];
}

vector<int> board::Convert(string pos){
	char chcol = pos[0];
	int mycol;
	int myraw = pos[1] - '0';
	myraw = myraw - 1;
	switch(chcol){
		case 'a':
			mycol = 0;
			break;
		case 'b':
			mycol = 1;
			break;
		case 'c':
			mycol = 2;
			break;
		case 'd':
			mycol = 3;
			break;
		case 'e':
			mycol = 4;
			break;
		case 'f':
			mycol = 5;
			break;
		case 'g':
			mycol = 6;
			break;
		case 'h':
			mycol = 7;
			break;
		default:
		//errore
			mycol = 100;;
			break;
	}
	vector<int> a;
	a.push_back(myraw);
	a.push_back(mycol);
	return a;
}

piece * board::FindPiece(string pos){
	vector<int> a = this -> Convert(pos);
	int mycol = a[1];
	int myraw = a[0];
	return this -> GetPiece(myraw, mycol);
}

piece * board::piecenew(piece * oldPiece){
	int n_raw = oldPiece -> GetRaw();
	int n_col = oldPiece -> GetCol();
	string n_color = oldPiece -> GetColor();
	int n_type = oldPiece -> GetType();
	bool n_alive = oldPiece -> GetAlive();
	bool n_moved = oldPiece -> GetMoved();
	piece * ritorno;
	switch(n_type){
		case 0:
			ritorno = new nullpiece(n_raw,n_col);
			break;
		case 1:
			ritorno = new rook(n_color,n_raw,n_col);
			break;
		case 2:
			ritorno = new knight(n_color,n_raw,n_col);
			break;
		case 3:
			ritorno = new bishop(n_color,n_raw,n_col);
			break;
		case 4:
			ritorno = new queen(n_color,n_raw,n_col);
			break;
		case 5:
			ritorno = new pawn(n_color,n_raw,n_col);
			break;
		case 6:
			ritorno = new king(n_color,n_raw,n_col);
			break;
	}
	ritorno -> SetAlive(n_alive);
	ritorno -> SetMoved(n_moved);
	return ritorno;
}

void board::Move(string start, string stop){
	//cout <<  __LINE__ << endl;
	board * myBoard = this;
	if(whitechecked == false && blackchecked == false){
		vector<int> vstart = this -> Convert(start);
		int rawstart = vstart[0];
		int colstart = vstart[1];
		vector<int> vstop = this -> Convert(stop);
		int rawstop = vstop[0];
		int colstop = vstop[1];

		piece * current = myBoard -> GetPiece(rawstart,colstart);
		string curr_color = current -> GetColor();
		piece * final = myBoard -> GetPiece(rawstop,colstop);
		string fin_color = final -> GetColor();

		//cout << "currentmove = " << currentmove << " currcolor: " << curr_color << endl;

		//controllo che sia il turno del giocatore giusto
		if(currentmove == 0 && curr_color == "black") return;
		if(currentmove == 1 && curr_color == "white") return;

		bool moved = false;

		//muovi, se possibile
		if(current -> CanMove(rawstop,colstop, myBoard)){
			if(final -> GetType() != 0){
				if(curr_color != fin_color){
					//cout <<  __LINE__ << endl;
					if(fin_color == "white") whitegrave.push_back(final);
					if(fin_color == "black") blackgrave.push_back(final);
					delete thisboard[rawstop][colstop];
					thisboard[rawstart][colstart] = new nullpiece(rawstart, colstart);
					thisboard[rawstop][colstop] =  this -> piecenew(current);
					thisboard[rawstop][colstop] -> ChangePos(rawstop, colstop);

					
				}
				else{
					//errore
				}
			}
			else{
				//cout <<  __LINE__ << endl;
				piece * temp_a = thisboard[rawstop][colstop];
				thisboard[rawstop][colstop] = this -> piecenew(current);
				thisboard[rawstop][colstop] -> ChangePos(rawstop, colstop);
				thisboard[rawstart][colstart] = this -> piecenew(temp_a);
				thisboard[rawstart][colstart] -> ChangePos(rawstart, colstart);
				delete temp_a;
			}
			if(current -> GetType() == 6){
				if(curr_color == "white"){
					whiteking[0] = rawstop;
					whiteking[1] = colstop;
				}
				else{
					blackking[0] = rawstop;
					blackking[1] = colstop;
				}
			}
			moved = true;
		}
		else{
			//errore
		}

		//cout <<  __LINE__ << endl;
		bool ispawn = thisboard[rawstop][colstop] -> GetType() == 5;
		bool arrived = (rawstop == 7 && currentmove == 0) || (rawstop == 0 && currentmove == 1);

		//cout <<  __LINE__ << endl;
		if(ispawn && arrived){
			this -> Promote(colstop);
		}

		//cambia la mossa corrente
		if(currentmove == 0 && moved == true) currentmove = 1;
		else if(currentmove == 1 && moved == true) currentmove = 0;

	}
	else if(whitechecked == true){
		this -> Remember();

		this -> ResetChecks();
		this -> Move(start,stop);
		this -> CheckChecks("justcheck");
		if(whitechecked == true){
			//restore last
			this -> Restore();
			this -> ResetChecks();
			this -> CheckChecks("justcheck");
			return;
		}
	}
	else if(blackchecked == true){
		this -> Remember();

		this -> ResetChecks();
		this -> Move(start,stop);
		this -> CheckChecks("justcheck");
		if(blackchecked == true){
			//restore last
			this -> Restore();	
			this -> ResetChecks();
			this -> CheckChecks("justcheck");
			return;
		}
	}
	//cout <<  __LINE__ << endl;
	this -> CheckChecks("justcheck");
	//cout <<  __LINE__ << endl;
}

void board::Promote(int colstop){
	string type;
	cout << "Promote in [Q,N,B,R]: ";
	cin >> type;
	piece * newpiece;
	string color;
	int raw;
	if(currentmove == 0){
		color = "white";
		raw = 7;
	}
	else if(currentmove == 1){
		color = "black";
		raw = 0;
	}
	if(type == "Q")
		newpiece = new queen(color,raw,colstop); 
	else if(type == "N")
		newpiece = new knight(color,raw,colstop); 
	else if(type == "B")
		newpiece = new bishop(color,raw,colstop); 
	else if(type == "R")
		newpiece = new rook(color,raw,colstop); 
	else return;

	delete thisboard[raw][colstop];
	thisboard[raw][colstop] = newpiece;
	return;
}

void board::Move(string unic){
	//cout <<  __LINE__ << endl;
	int length = unic.length();
	if(length == 2){ //d4
		vector<int> vstop = this -> Convert(unic);
		int rawstop = vstop[0];
		int colstop = vstop[1];
		//mossa di pedone
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				bool controlmove = thisboard[i][j] -> CanMove(rawstop,colstop, this);
				int controlpiece = thisboard[i][j] -> GetType();
				bool justmove = colstop == j;
				bool iswhite = currentmove == 0 && thisboard[i][j] -> GetColor() == "white";
				bool isblack = currentmove == 1 && thisboard[i][j] -> GetColor() == "black";
				bool rightcolor = iswhite || isblack;
				if(controlmove && controlpiece == 5 && justmove && rightcolor){
					this -> Move(this->ConvertPos(i,j),unic);
					this -> CheckChecks();
					return;
				}
			}
		}
	}
	if(length == 3 && unic[0] != 'O'){ //Nd4
		char types = unic[0];
		int type = this -> TypeStringToInt(types);
		string pos;
		pos.push_back(unic[1]);
		pos.push_back(unic[2]);
		vector<int> vstop = this -> Convert(pos);
		int rawstop = vstop[0];
		int colstop = vstop[1];
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				bool controlmove = thisboard[i][j] -> CanMove(rawstop,colstop, this);
				int controlpiece = thisboard[i][j] -> GetType();
				bool occupied = this -> Occupied(rawstop,colstop);
				bool iswhite = currentmove == 0 && thisboard[i][j] -> GetColor() == "white";
				bool isblack = currentmove == 1 && thisboard[i][j] -> GetColor() == "black";
				bool rightcolor = iswhite || isblack;
				if(controlmove && controlpiece == type && occupied == false && rightcolor){
					this -> Move(this->ConvertPos(i,j),pos);
					this -> CheckChecks();
					return;
				}
			}
		}
	}
	if(length == 4 && this -> IsColoumn(unic[0]) == true && unic[1] == 'x'){ //dxe3
		char colchar = unic[0];
		int col = this -> ColCharToInt(colchar);	//----------
		string pos;
		pos.push_back(unic[2]);
		pos.push_back(unic[3]);
		vector<int> vstop = this -> Convert(pos);
		int rawstop = vstop[0];
		int colstop = vstop[1];
		
		for(int j = 0; j < 8; j++){
			bool controlmove = thisboard[j][col] -> CanMove(rawstop,colstop, this);
			int controlpiece = thisboard[j][col] -> GetType();
			bool occupied = this -> Occupied(rawstop,colstop);
			bool iswhite = currentmove == 0 && thisboard[j][col] -> GetColor() == "white";
			bool isblack = currentmove == 1 && thisboard[j][col] -> GetColor() == "black";
			bool rightcolor = iswhite || isblack;
			if(controlmove && controlpiece == 5 && occupied == true && rightcolor){
				this -> Move(this->ConvertPos(j,col),pos);
				this -> CheckChecks();
				return;
			}
		
		}
	}
	if(length == 4 && this -> IsColoumn(unic[0]) == false && unic[1] == 'x'){ //Nxe3
		char types = unic[0];
		int type = this -> TypeStringToInt(types);
		string pos;
		pos.push_back(unic[2]);
		pos.push_back(unic[3]);
		vector<int> vstop = this -> Convert(pos);
		int rawstop = vstop[0];
		int colstop = vstop[1];
		
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				bool controlmove = thisboard[i][j] -> CanMove(rawstop,colstop, this);
				int controlpiece = thisboard[i][j] -> GetType();
				bool occupied = this -> Occupied(rawstop,colstop);
				bool iswhite = currentmove == 0 && thisboard[i][j] -> GetColor() == "white";
				bool isblack = currentmove == 1 && thisboard[i][j] -> GetColor() == "black";
				bool rightcolor = iswhite || isblack;
				if(controlmove && controlpiece == type && occupied == true && rightcolor){
					this -> Move(this->ConvertPos(i,j),pos);
					this -> CheckChecks();
					return;
				}
			}
		}
	}
	if(unic == "O-O"){
		if(currentmove == 0){ //mossa al bianco
			bool kingmoved = thisboard[0][4] -> GetMoved();
			bool rookmoved = thisboard[0][7] -> GetMoved();
			bool occupied = this -> Occupied(0,5) || this -> Occupied(0,6);
			if(kingmoved == false && rookmoved == false && occupied == false){
				this -> Remember();
				thisboard[0][5] = thisboard[0][7];
				thisboard[0][6] = thisboard[0][4];

				thisboard[0][4] = new nullpiece(0,4);
				thisboard[0][7] = new nullpiece(0,7);

				thisboard[0][5] -> SetMoved(true);
				thisboard[0][6] -> SetMoved(true);

				thisboard[0][5] -> ChangePos(0,5);
				thisboard[0][6] -> ChangePos(0,6);

				whiteking[1] = 6;
				currentmove = 1;

				this -> CheckChecks("justcheck");
				if(whitechecked == true){
					//restore last
					this -> Restore();
					this -> ResetChecks();
					this -> CheckChecks("justcheck");
				}
				this -> CheckChecks();
				return;
			}
		}
		if(currentmove == 1){
			bool kingmoved = thisboard[7][4] -> GetMoved();
			bool rookmoved = thisboard[7][7] -> GetMoved();
			bool occupied = this -> Occupied(7,5) || this -> Occupied(7,6);
			if(kingmoved == false && rookmoved == false && occupied == false){
				this -> Remember();
				thisboard[7][5] = thisboard[7][7];
				thisboard[7][6] = thisboard[7][4];

				thisboard[7][4] = new nullpiece(7,4);
				thisboard[7][7] = new nullpiece(7,7);

				thisboard[7][5] -> SetMoved(true);
				thisboard[7][6] -> SetMoved(true);

				thisboard[7][5] -> ChangePos(7,5);
				thisboard[7][6] -> ChangePos(7,6);

				blackking[1] = 6;
				currentmove = 0;

				this -> CheckChecks();
				if(blackchecked == true){
					//restore last
					this -> Restore();
					this -> ResetChecks();
					this -> CheckChecks();
				}
				return;
			}
		}
	}
	if(unic == "O-O-O"){
		if(currentmove == 0){ //mossa al bianco
			bool kingmoved = thisboard[0][4] -> GetMoved();
			bool rookmoved = thisboard[0][0] -> GetMoved();
			bool occupied = this -> Occupied(0,1) || this -> Occupied(0,2) || this -> Occupied(0,3);
			if(kingmoved == false && rookmoved == false && occupied == false){
				this -> Remember();
				thisboard[0][3] = thisboard[0][0];
				thisboard[0][2] = thisboard[0][4];

				thisboard[0][4] = new nullpiece(0,4);
				thisboard[0][0] = new nullpiece(0,0);

				thisboard[0][3] -> SetMoved(true);
				thisboard[0][2] -> SetMoved(true);

				thisboard[0][3] -> ChangePos(0,3);
				thisboard[0][2] -> ChangePos(0,2);

				whiteking[1] = 2;
				currentmove = 1;

				this -> CheckChecks("justcheck");
				if(whitechecked == true){
					//restore last
					this -> Restore();
					this -> ResetChecks();
					this -> CheckChecks("justcheck");
				}
				this -> CheckChecks();
				return;
			}
		}
		if(currentmove == 1){
			bool kingmoved = thisboard[7][4] -> GetMoved();
			bool rookmoved = thisboard[7][0] -> GetMoved();
			bool occupied = this -> Occupied(7,1) || this -> Occupied(7,2) || this -> Occupied(7,3);
			if(kingmoved == false && rookmoved == false && occupied == false){
				this -> Remember();
				thisboard[7][3] = thisboard[7][0];
				thisboard[7][2] = thisboard[7][4];

				thisboard[7][4] = new nullpiece(7,4);
				thisboard[7][0] = new nullpiece(7,0);

				thisboard[7][3] -> SetMoved(true);
				thisboard[7][2] -> SetMoved(true);

				thisboard[7][3] -> ChangePos(7,3);
				thisboard[7][2] -> ChangePos(7,2);

				blackking[1] = 2;
				currentmove = 0;

				this -> CheckChecks();
				if(blackchecked == true){
					//restore last
					this -> Restore();
					this -> ResetChecks();
					this -> CheckChecks();
				}
				return;
			}
		}
	}	
	if(unic == "resign"){
		if(currentmove == 0) whitemated = true;
		else if (currentmove == 1) blackmated = true;
	}
}

bool board::IsColoumn(char type){
	bool col0 = type == 'a';
	bool col1 = type == 'b';
	bool col2 = type == 'c';
	bool col3 = type == 'd';
	bool col4 = type == 'e';
	bool col5 = type == 'f';
	bool col6 = type == 'g';
	bool col7 = type == 'h';
	return col0 || col1 || col2 || col3 || col4 || col5 || col6 || col7; 
}

int board::ColCharToInt(char types){
	switch(types){
		case 'a':
			return 0;
			break;
		case 'b':
			return 1;
			break;
		case 'c':
			return 2;
			break;
		case 'd':
			return 3;
			break;
		case 'e':
			return 4;
			break;
		case 'f':
			return 5;
			break;
		case 'g':
			return 6;
			break;
		case 'h':
			return 7;
			break;
		default:
			return 22;
			break;
	}
}

int board::TypeStringToInt(char types){
	string type;
	type.push_back(types);
	if(type == "R") return 1;
	if(type == "N") return 2;
	if(type == "B") return 3;
	if(type == "Q") return 4;
	if(type == "K") return 6;
}

string board::ConvertPos(int raw, int col){
	string a;
	string b;
	switch(col){
		case 0:
			a = "a";
			break;
		case 1:
			a = "b";
			break;
		case 2:
			a = "c";
			break;
		case 3:
			a = "d";
			break;
		case 4:
			a = "e";
			break;
		case 5:
			a = "f";
			break;
		case 6:
			a = "g";
			break;
		case 7:
			a = "h";
			break;
	}
	b = to_string(raw+1);
	return a+b;
}

void board::SetCurrentMoveInt(int a){
	currentmove = a;
}

bool board::Occupied(int n_raw, int n_col){
	if(thisboard[n_raw][n_col] -> GetType() != 0) return true;
	else return false;
}

string board::GetCurrentMove(){
	if(currentmove == 0) return "Mossa al bianco: ";
	else return "Mossa al nero: ";
}

int board::GetCurrentMoveInt(){
	return currentmove;
}

void board::ResetChecks(){
	whitechecked = false;
	blackchecked = false;
}

void board::CheckChecks(string type){
	//controlla scacchi
	blackchecked = false;
	whitechecked = false;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			//cout <<  __LINE__ << " " << i << " " << j << endl;

			piece * current = thisboard[i][j];
			if(current -> GetColor() == "white" && current -> CanMove(blackking[0], blackking[1], this)){
				blackchecked = true;
				if(type != "justcheck") this -> CheckMate();
			}
			if(current -> GetColor() == "black" && current -> CanMove(whiteking[0], whiteking[1], this)){
				whitechecked = true;
				if(type != "justcheck") this -> CheckMate();
			}
		}
	}

	//cout << "checked " << whitechecked << " " << blackchecked << endl;
}

void board::CheckMate(){
	if(currentmove == 0){ //white is getting mated
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(thisboard[i][j] -> GetColor() == "white"){
					string start = this -> ConvertPos(i,j);
					for(int h = 0; h < 8; h++){
						for(int k = 0; k < 8; k++){
							if(thisboard[i][j] -> CanMove(h,k, this)){
								//prova a muovere e controlla i check
								this -> Remember();
								this -> ResetChecks();
								this -> Move(start, this -> ConvertPos(h,k));
								this -> CheckChecks("justcheck");
								if(whitechecked == false){
									whitemated = false;
									this -> Restore();
									return;
								}
								this -> Restore();
								this -> CheckChecks("justcheck");
							}
						}
					}
				}
			}
		}
		whitemated = true;
	}
	else if(currentmove == 1){ //black is getting mated
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(thisboard[i][j] -> GetColor() == "black"){
					string start = this -> ConvertPos(i,j);
					for(int h = 0; h < 8; h++){
						for(int k = 0; k < 8; k++){
							if(thisboard[i][j] -> CanMove(h,k, this)){
								//prova a muovere e controlla i check
								this -> Remember();
								this -> ResetChecks();
								this -> Move(start, this -> ConvertPos(h,k));
								this -> CheckChecks("justcheck");
								if(blackchecked == false){
									blackmated = false;
									this -> Restore();
									return;
								}
								this -> Restore();
								this -> CheckChecks("justcheck");
							}
						}
					}
				}
			}
		}
		blackmated = true;
	}
}

bool board::GetMated(string color){
	if(color == "white") return whitemated;
	if(color == "black") return blackmated;
}

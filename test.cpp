#include "chess.h"
#include <iostream>


int main(int argc, char const *argv[]){
		
	board * myBoard = new board();

	myBoard -> Print();


	while(true){
		cout << myBoard -> GetCurrentMove();
		string start, end;
		cin >> start;
		myBoard -> Move(start);
		myBoard -> Print();
		if(myBoard -> GetMated("white")){
			cout << "Nero vince" << endl;
			break;
		}
		if(myBoard -> GetMated("black")){
			cout << "Bianco vince" << endl;
			break;
		}
	}
	



	return 0;
}
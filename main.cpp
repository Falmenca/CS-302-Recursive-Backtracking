#include <iostream>
#include <fstream> 
#include <sstream>
using namespace std;

char sheikahSlate[7][7];
int totalStepsNeeded = 0;
int endX = 0, endY = 0; //End coordinates
char s = '0';

void displayBoard(){ //Display our 2d array onto console
    for(int x = 0; x < 7; x++){
        for(int y = 0; y < 7; y++){ cout << sheikahSlate[x][y] << " "; }
        cout << endl;
    }
}

void backtrackCharInsert(char grid[7][7], char &s, int x, int y) {
    grid[x][y] = s;
    if (s != '9') s++;
    else s = 'A';
}

void backtrackCharUndo(char grid[7][7], char &s, int x, int y){
    if (s == 'A') s = '9';
    else if (s > '0') s--; // Reset character if we backtrack
    grid[x][y] = ' '; // Undo the move
}

bool validMove(char grid[7][7], int x, int y) {
    return x >= 0 && x < 7 && y >= 0 && y < 7 && grid[x][y] == ' ';
}

bool backtrack(char grid[7][7], int x, int y, int stepCounter) {
    backtrackCharInsert(grid, s, x, y);
    if (x == endX && y == endY && stepCounter == totalStepsNeeded) return true; //Found a valid path
    if(validMove(grid, x+1, y)){if(backtrack(grid, x+1, y, stepCounter+1)){return true;}} //Check up
    if(validMove(grid, x-1, y)){if(backtrack(grid, x-1, y, stepCounter+1)){return true;}} //Check down
    if(validMove(grid, x, y+1)){if(backtrack(grid, x, y+1, stepCounter+1)){return true;}} //Check right
    if(validMove(grid, x, y-1)){if(backtrack(grid, x, y-1, stepCounter+1)){return true;}} //Check left
    backtrackCharUndo(grid, s, x, y);
    return false; //No valid moves from this position, backtrack
}

void readBoard(string file){ //Open and read text file into our 2d array
    ifstream boardIn(file);
    string reader;
    int x, y = 0;
    while(!boardIn.eof() && x < 7){
        getline(boardIn, reader);
        for(y = 0; y < 7; y++){ 
            if(reader[y] == ' ') totalStepsNeeded++;
            sheikahSlate[x][y] = reader[y]; 
        }
        x++;
    }
    boardIn.close(); //Don't forget to close files
}

int main(){
    int startX = 0, startY = 0; //Starting coordinates
    int stepCounter = 1; 

    string boardFile = " "; 
    cout << "Enter config file: "; cin >> boardFile; 
    cout << boardFile << endl;
    cout << "Please enter starting coordinates: "; cin >> startX >> startY; //cout << startX << " " << startY << endl; 
    cout << "Please enter end coordinates: "; cin >> endX >> endY; //cout << endX << " " << endY << endl; //Program breaks without this cout statement

    readBoard(boardFile);
    backtrack(sheikahSlate, startX, startY, stepCounter); 
    displayBoard();
    
    return 0;
}
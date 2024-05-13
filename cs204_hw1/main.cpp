#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
//Anıl Sümer Topaloğlu 22589
using namespace std;
// printer function for given matrix
void Printer(const vector<vector<char>> & mat)
{
    for (int j = 0; j < mat.size(); j++)
    {
        for (int k = 0; k < mat[0].size(); k++)
        {
            cout << mat[j][k];
        }
        cout << endl;
    }
}
// function to check to moves returns no possible moves if there is not left any.
bool check_moves(vector<vector<char>> & matrix)
{   int space = 0;
    int blocked = 0;
    int cell_number = matrix.size() * matrix[0].size();
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            if (matrix[i][j] == '-'){
                space++;
            }
            else if (matrix[i][j] == 'r' && j != matrix[0].size() -1 && (matrix[i][j+1] == 'l' || matrix[i][j-1] == 'r')){
                blocked++;
            }
            else if (matrix[i][j] == 'l' && j!= 0 && (matrix[i][j-1] == 'r'  || matrix[i][j-1] == 'l')){
                blocked++;
            }
            else if  (matrix[i][j] == 'u' && i!= 0 && (matrix[i-1][j] == 'd' || matrix[i][j-1] == 'u')){
                blocked++;
            }
            else if  (matrix[i][j] == 'd' &&  i != matrix.size() -1 && (matrix[i+1][j] == 'u' || matrix[i][j-1] == 'd')){
                blocked++;
            }
        }
    }
    if (space + blocked == cell_number){
        return true;
    }
    return false;


}
//check if the matrix all empty
bool is_matrix_empty(vector<vector<char>>& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != '-') {
                return false;
            }
        }
    }
    return true;
}
// reads the file and returns in a vector of vector data type
vector<vector<char>> readMatrixFromFile(const string& filename) {
    vector<vector<char>> matrix;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<char> row;
        stringstream ss(line);
        char num;
        while (ss >> num) {
            row.push_back(num);
        }
        matrix.push_back(row);
    }
    file.close();
    return matrix;
}


bool check_input(vector<vector<char>> & matrix){
    // list to check only 4 lower case chars
    vector<char> valid = {'u', 'd', 'l', 'r', '-'};
    int ct = matrix[0].size();
    for (int i = 0 ; i < matrix.size(); i++){
       if (matrix[i].size() != ct){
           return true;
       }
   }
   for (int i = 0; i < matrix.size(); i++){
       for (int j = 0; j < matrix[i].size(); j++){
           bool flag = false;
           for (int k = 0 ; k < valid.size(); k++) {
               if (matrix[i][j] == valid[k]) {
                   flag = true;
               }
           }
           if (!flag){
           return true;
           }

       }
   }
   return false;
}


// returns the furthest possible move location. change it in the main function's game loop, if the cell able to leave the matrix it swaps the matrix value with '-'
bool move_cell(vector<vector<char>>& matrix, int row, int col){
  if (matrix[row][col] == 'r')
  {
      if (col == matrix[0].size()-1){
          matrix[row][col] = '-';
          return true;
      }
      else if (matrix[row][col+1] != '-'){

          return false;
      }
      else{
          for (int i = col; i <= matrix[0].size()-1; i++){
              if (matrix[row][i] != '-' && col != i){
                  matrix[row][col] = '-';
                  matrix[row][i-1] = 'r';
                  return true;
              }
              else if (matrix[row][i] == '-' && i == matrix[0].size()-1){
                  matrix[row][col] = '-';
                  return true;
              }



          }
      }

  }
  else if (matrix[row][col] == 'l') {
      if (col == 0) {
          matrix[row][col] = '-';
          return true;
      }
      else if (matrix[row][col - 1] != '-') {

          return false;
      } else {
          for (int i = col; i >= 0; i--) {
              if (matrix[row][i] != '-' && i != col) {
                  matrix[row][i + 1] = 'l';
                  matrix[row][col] = '-';
                  return true;
              } else if (matrix[row][i] == '-' & i == 0) {
                  matrix[row][col] = '-';
                  return true;
              }
          }
      }
  }
  else if (matrix[row][col] == 'u')
  {
      if (row == 0){
          matrix[row][col] = '-';
          return true;

      }
      else if (matrix[row-1][col]!= '-'){

          return false;
      }
      else{


      for (int i = row; i >= 0; i--) {
          if ((matrix[i][col] != '-' && row != i)) {
              matrix[row][col] = '-';
              matrix[i + 1][col] = 'u';
              return true;
          } else if (matrix[i][col] == '-' && i == 0) {
              matrix[row][col] = '-';
              return true;
          }

      }
      }
  }
  else if (matrix[row][col] == 'd')
  {
      if (row == matrix.size()-1){
          matrix[row][col] = '-';
          return true;
      }
      else if(matrix[row+1][col] != '-'){

          return false;
      }
      else {

          for (int i = row; i <= matrix.size() - 1; i++) {
              if ((matrix[i][col] != '-' && row != i)) {
                  matrix[row][col] = '-';
                  matrix[i - 1][col] = 'd';
                  return true;
              } else if (matrix[i][col] == '-' && i == matrix.size() - 1) {
                  matrix[row][col] = '-';
                  return true;
              }
          }
      }
  }
  return false;
}
// checks row and the column within the range of the matrix
bool check_range(const vector<vector<char>>& matrix, int row, int col){
    int i,j;
    i = matrix.size();
    j = matrix[0].size();
    if (row >= i || col >= j || row < 0 || col < 0){
        return true;
    }
    return false;
}

int main ()
{
    string file_name;
    ifstream file;
    cout << "Please enter the file name: " << endl;
    cin >> file_name;
    file.open(file_name);

    // to check the input txt file is valid.
    while (!file.is_open())
    {
        cout << "Could not open the file. Please enter a valid file name: " << endl;
        cin.clear();
        cin >> file_name;
        file.open(file_name);
    }
    vector<vector<char>> matrix = readMatrixFromFile(file_name);
    if (check_input(matrix)){
        cout << "Erroneous file content. Program terminates."<< endl;
        return 0;
    }
    cout << "The matrix file contains: "<< endl;
    Printer(matrix);

    if (is_matrix_empty(matrix)){
        cout << "The matrix is empty." << endl;
        return 0;
    }
    if (check_moves(matrix)){
        cout << "No more moves are possible.";
        return 0;
    }
    // loop to play the game.
    int row, col;
    while(true){

        if (is_matrix_empty(matrix)){
            cout << "The matrix is empty." << endl;
            return 0;
        }
        cout << "Please enter the row and column of the tile that you want to move: " << endl;
        cin >> row >> col;
        while (check_range(matrix,row,col)){
            cout << "Invalid row or column index." << endl;
            cin.clear();
            cin.ignore();
            cout << "Please enter the row and column of the tile that you want to move: " << endl;
            cin >> row >> col;
            }



        if (move_cell(matrix,row,col)){
            cout << "Tile at " << "(" << row << "," << col << ")" << " has been moved." << endl;
        }
        else{
            cout << "No tiles have been moved." << endl;
        }
        Printer(matrix);
        if (check_moves(matrix)){
            if (!is_matrix_empty(matrix)) {
                cout << "No more moves are possible." << endl;
                return 0;
            }

        }



    }

    return 0;
}
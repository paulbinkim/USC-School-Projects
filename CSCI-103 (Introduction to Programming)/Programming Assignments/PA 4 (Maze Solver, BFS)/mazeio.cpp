/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
   // *** You complete ****
  int row, col;
  
  ifstream ifile (filename);
  if (ifile.fail()) {
    return NULL;
  }
  
  ifile >> row >> col;
  if (ifile.fail()) {
    return NULL;
  }
  
  *rows = row;
  *cols = col;
  
  char**  mazeboard = new char*[row]; // Declaring 2D array
  for (int i=0; i < row; i++) {
       mazeboard[i] = new char[col];  // Mazeboard [row][column]
  }
  
  for (int i=0; i < row; i++) {
    string line;
    ifile >> line;
    for (int k=0; k < col; k++) {
      mazeboard[i][k] = line[k];
      if (line[k] != '#' && line[k] != 'S' && line[k] != 'F' && line[k] != '.')
        return NULL;
    }
  }
  
  return mazeboard;
  
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{
   // *** You complete ****
  cout << rows << " " << cols << endl;
  
  for (int i = 0; i < rows; i++) {
    for (int z = 0; z < cols; z ++) {
      cout << maze [i][z];
    }
    cout << endl;
  }
	
}


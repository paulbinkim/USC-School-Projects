/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
  
   mymaze = read_maze (argv[1], &rows, &cols);
   if (mymaze == NULL) {
     cout << "Error, input format incorrect." << endl;
     return 1;
   }

	 //================================
   // When working on Checkpoint 3, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
  
   result = maze_search(mymaze, rows, cols);
	
	
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

	 //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated (IMPORTANT)
   
   for (int i = 0; i < rows; i++) {
     delete[] mymaze [i];
   }
   delete[] mymaze;
 
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  // *** You complete ****
  Location start;
  int Scount = 0;
  int Fcount = 0;
  
  for (int i = 0; i < rows; i++) { // Searching for S and F and error checking
    for (int z = 0; z < cols; z++) {
      if (maze[i][z] == 'S') {
        Scount++;
        start.row = i;
        start.col = z;
      }
      else if (maze[i][z] == 'F') {
        Fcount++;
      }
    }
  }
  
  if (Scount != 1 || Fcount !=1) {
    return -1;
  }
  
  bool** visited = new bool*[rows]; // Initializing visited array
  for (int i = 0; i < rows; i++) {
    visited [i] = new bool [cols];
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      visited [i][j] = false;
    }
  }
  
  int maxlength = rows*cols; // Create queue
  Queue queue(maxlength);
  
  queue.add_to_back(start);
  visited[start.row][start.col] = true;
  
  Location** predecessor = new Location*[rows]; // Creating Predecessor array
  for (int i = 0; i < rows; i++) {
    predecessor[i] = new Location [cols];
  }
  
  Location empty; // We do this to make sure predecessor is initialized
  empty.row = -1; 
  empty.col = -1;
  
  for (int i =0; i< rows; i++) {
    for (int j = 0; j < cols; j++) {
      predecessor[i][j] = empty;
    }
  }
  
  bool finish = false;
  
  while (!queue.is_empty()) {
    
    Location start2 = queue.remove_from_front();
    
    Location north;
    north.row = start2.row-1;
    north.col = start2.col;
    
    if (north.row >= 0 && north.row < rows && north.col >= 0 && north.col < cols) {
      if (visited[north.row][north.col] == false && maze [north.row][north.col] == '.'){
        queue.add_to_back(north);
        visited[north.row][north.col] = true;
        predecessor[north.row][north.col] = start2;
      }
      else if (maze[north.row][north.col] == 'F') {
        while (maze[start2.row][start2.col] != 'S') {
          maze [start2.row][start2.col] = '*';
          start2 = predecessor [start2.row][start2.col];
        }
        finish = true;
        break;
      }
    }
      
    Location west;
    west.row = start2.row;
    west.col = start2.col-1;
    
    if (west.row >= 0 && west.row < rows && west.col >= 0 && west.col < cols) {
      if (visited[west.row][west.col] == false && maze [west.row][west.col] == '.'){
        queue.add_to_back(west);
        visited[west.row][west.col] = true;
        predecessor[west.row][west.col] = start2;
      }
      else if (maze[west.row][west.col] == 'F') {
        while (maze[start2.row][start2.col] != 'S') {
          maze [start2.row][start2.col] = '*';
          start2 = predecessor [start2.row][start2.col];
        }
        finish = true;
        break;
      }
    }
      
    Location south;
    south.row = start2.row+1;
    south.col = start2.col;
    
    if (south.row >= 0 && south.row < rows && south.col >= 0 && south.col < cols) {
      if (visited[south.row][south.col] == false && maze [south.row][south.col] == '.'){
        queue.add_to_back(south);
        visited[south.row][south.col] = true;
        predecessor[south.row][south.col] = start2;
      }
      else if (maze[south.row][south.col] == 'F') {
        while (maze[start2.row][start2.col] != 'S') {
          maze [start2.row][start2.col] = '*';
          start2 = predecessor [start2.row][start2.col];
        }
        finish = true;
        break;
      }
    }
      
    Location east;
    east.row = start2.row;
    east.col = start2.col+1;
  
    if (east.row >= 0 && east.row < rows && east.col >= 0 && east.col < cols) {
      if (visited[east.row][east.col] == false && maze [east.row][east.col] == '.'){
        queue.add_to_back(east);
        visited[east.row][east.col] = true;
        predecessor[east.row][east.col] = start2;
      }
      else if (maze[east.row][east.col] == 'F') {
        while (maze[start2.row][start2.col] != 'S') {
          maze [start2.row][start2.col] = '*';
          start2 = predecessor [start2.row][start2.col];
        }
        finish = true;
        break;
      }
    }
  }
  
  for (int i = 0; i < rows; i++) { // Delete dynamic memory.
    delete [] visited [i];
    delete [] predecessor[i];
  }
  delete [] visited;
  delete [] predecessor;
        
  if(finish == true) {
    return 1;
  }
  return 0;      
}
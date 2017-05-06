#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"
#include "list.h"

PathLL * solveMaze(Maze * m) {

	PathLL * successPaths = buildPaths();
	char * retval = malloc(((m->height * m->width) + 1) * sizeof(char));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	depthFirstSolve(m, mp, retval, 0, successPaths);

	free(retval);

  // test to see list
  PathNode * curr = successPaths->head;
  int i = 0;
  while (curr != NULL) {
    printf("Path %2d: %s\n", i, curr->path);
    i++;
    curr = curr->next;
  }

	return successPaths;
}

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths) {

  //Fill in. (Your best bet is to modify a working implementation from PA08)
	// row and col cursor variables

  //base cases:
  //1. if curpos is at the end, append \0 to the path, return true
  if (atEnd(curpos, m)) {
    path[step] = '\0';
		//("path: %s\n",path); // remove
		if (!containsNode(successPaths, path)){
			addNode(successPaths, path);
    	return;
		}
  }
  //2. if curpos is invalid (wall, out of bounds, or already visited)
  //   return
  if (!squareOK(curpos, m)) {
    return ;
  }

  //Set this square to visited
	// change this so it will find all paths
  m->maze[curpos.ypos][curpos.xpos].visited = true;

  //inductive case: check each possible direction from curpos
  char direction[4] = {NORTH, SOUTH, EAST, WEST};
  // 4 directions that cursor can move to
  MazePos steps[4] = {
    {.xpos = curpos.xpos, .ypos = curpos.ypos - 1}, //NORTH
    {.xpos = curpos.xpos, .ypos = curpos.ypos + 1}, //SOUTH
    {.xpos = curpos.xpos + 1, .ypos = curpos.ypos}, //EAST
    {.xpos = curpos.xpos - 1, .ypos = curpos.ypos}  //WEST
  };

  for (int i = 0; i < 4; i++) {
    //Try to make a move and see if it's successful
    path[step] = direction[i];
    depthFirstSolve(m, steps[i], path, step + 1, successPaths);
  }
	m->maze[curpos.ypos][curpos.xpos].visited = false;
  //If no move is successful, return
  return;
}

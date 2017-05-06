#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

// builds the head
PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	//fill in
	PathNode * tmp = NULL;
	while (p->head != NULL) { // check if check is o.k.
		tmp = p->head;
		p->head = p->head->next;
		freeNode(tmp);
	}
  free(p);
}

// needs work
PathNode * buildNode(char * path) {
  PathNode * newPath = malloc(sizeof(PathNode));
  newPath->path = malloc(sizeof(char) * strlen(path) + 1); // +1 accounts for '\0'
  if (newPath == NULL)
  {
    return NULL;
  }
  strcpy(newPath->path, path);
  newPath->next = NULL; // should be NULL? yes
  return newPath;

	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
}


void freeNode(PathNode * p) {
	free(p->path);
	free(p);
}

// needs work
bool addNode(PathLL * paths, char * path) {
  //fill in
	if (containsNode(paths, path))
	{
		return false;
	}
  PathNode * newNode = buildNode(path);
  if (paths->head == NULL)
  {
		newNode->next = paths->head;
		paths->head = newNode;
  }
	if (strlen(paths->head->path) > strlen(path)) {
		newNode->next = paths->head;
		paths->head = newNode;
	}
	else if ((strlen(paths->head->path) == strlen(path) && pathTurn(path) < pathTurn(paths->head->path))) {
		newNode->next = paths->head;
		paths->head = newNode;
	}
	else if (strlen(paths->head->path) == strlen(path) && pathTurn(path) == pathTurn(paths->head->path) && strcmp(path,paths->head->path) < 0) {
		newNode->next = paths->head;
		paths->head = newNode;
	}

  PathNode * prev = paths->head;
  PathNode * cur = paths->head->next;

	// sorting function to insert node
	bool check = 1;

	// problem: skips the check if there is only 1 node in list
  while (cur != NULL && check){
		int len1 = strlen(path);
		int len2 = strlen(cur->path);
		if (len1 < len2) { // insert path, stop loop
			check = 0;
	  }
	  else if (len1 > len2) { // continue to next node
			prev = prev->next;
			cur = cur->next;
	  }
		// *** goto lesser turns ***
	  else {
			int turn1 = pathTurn(path);
			int turn2 = pathTurn(cur->path);
			if (turn1 < turn2) { // insert path, stop loop
				check = 0;
			}
			else if (turn1 > turn2) { // continue to next node
				prev = prev->next;
				cur = cur->next;
			}
			// *** goto alphabetical ***
			else {
				check = 0;
				int alpha = strcmp(path, cur->path);
				if (alpha < 0) { // newNode is alpha higher, insert
					check = 0;
				}
				if (alpha > 0) { // continue to next node
					prev = prev->next;
					cur = cur->next;
				}
			}
	  }
  }

  prev->next = newNode;
  newNode->next = cur;
  //PathLL should be sorted by the following priority
  //  1. In ascending order of length (shortest path first), then
  //  2. By number of turns (see README), then
  //  3. Alphabetical order
	return true;
}

// **** needs more work
bool removeNode(PathLL * paths, char * path) {
  if (paths == NULL || paths->head == NULL) {
    return false;
  }
  // ****** needs special case if remove from beginning ****
  PathNode * prev = paths->head;
  PathNode * cur = paths->head->next; // check
	if (!strcmp(paths->head->path, path))
	{
		free(prev);
		paths->head = cur;
	}
	while (cur != NULL && strcmp(path, cur->path)) { // check if check is o.k.
		prev = prev->next;
		cur = cur->next;
	}
	if (cur != NULL) {
		prev->next = cur->next;
		freeNode(cur);
		return true;
	}
  return false;
}

// **** needs to be checked *****
///* Return true if path exists in the list */
bool containsNode(PathLL * paths, char * path) {
	//fill in
	PathNode * curr = paths->head;
  while ((curr != NULL) && (strcmp(curr->path, path))) {
    curr = (curr->next);
  }
  if (curr != NULL) {
    return true;
  }
  else {
    return false;
  }
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}

// function made to find number of turns
int pathTurn(char * path)
{
  int turns = 0;
  char start = path[0];
  int x;
  for(x = 0; x < strlen(path); x++)
  {
    //printf("start: %c  path[x+1]: %c\n", start, path[x+1]);
    if ((start != path[x+1]) && ((path[x+1] != 0)  || (path[x+1] != '\0')))
    {
      turns++;
    }
    start = path[x+1];
  }
  return turns;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

int main(){


	PathLL * successPaths = buildPaths();
  // test to see list

  char path1[3] = {'e','e', '\0'};
  char path2[4] = {'e','e','e', '\0'};
  char path3[5] = {'n','n','n', 'n', '\0'};
  char path4[4] = {'s','e','e','\0'};
  char path5[4] = {'w','e','w','\0'};
	char path6[4] = {'w','n','s','\0'};
	char path7[9] = {'w','n','s','e','w','n','s','s','\0'};
	char path8[4] = {'w','n','s','e','w','n','s','e','\0'};
	addNode(successPaths, path6);
  addNode(successPaths, path5);
  addNode(successPaths, path4);
  addNode(successPaths, path3);
  addNode(successPaths, path2);
  addNode(successPaths, path1);
	addNode(successPaths, path1);
	addNode(successPaths, path8);
	addNode(successPaths, path7);
	printf("path turn7: %d path turn8: %d", pathTurn(path7), pathTurn(path8));
  PathNode * curr = successPaths->head;
  int i = 1;
  while (curr != NULL) {
    printf("Path%d: %s\n", i, curr->path);
    i++;
    curr = curr->next;
  }
//  removeNode(successPaths, path2);
  //removeNode(successPaths, path1);
  removeNode(successPaths, path5);
  removeNode(successPaths, path3);
	printf("\n");
  curr = successPaths->head;
  i = 0;
  while (curr != NULL) {
    printf("Path%d.5: %s\n", i, curr->path);
    i++;
    curr = curr->next;
  }
  return EXIT_SUCCESS;
}

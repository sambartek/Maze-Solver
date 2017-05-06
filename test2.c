#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

int pathTurn(char * path);


int main()
{
  printf("\n"); //out
  char path1[] = "eenw"; //out
  char path2[] = "eens"; // out

  // ******* test 1 **********  
  printf("Path 1: %s \nPath 2: %s\n", path1, path2); // out
  int len1 = strlen(path1);
  int len2 = strlen(path2);
  printf("1. Shortest Path\n"); // out
  if (len1 < len2) {
    printf("insert path1\n\n"); // out
    return 0; //out
  }
  else if (len1 > len2) {
    printf("continue to next node\n\n"); // out
    return 0; // out
  }
  else {
    printf("goto lesser turns\n\n"); //out
  }


  // ******* test 2 ********
  printf("2. Less Turns\n"); // out
  int turn1 = pathTurn(path1);
 // printf("\n");
  int turn2 = pathTurn(path2);
  printf("Path1 turns: %d  Path2 turns: %d\n", turn1, turn2); // out
  if (turn1 < turn2) {
    printf("insert path 1\n\n");  //out
    return 0; //out
  }
  else if (turn1 > turn2) {
    printf("continue to next node\n\n"); //out
    return 0; // out
  }
  else {
    printf("goto alphabetical\n\n"); //out
  }
    
  // ****** test 3 *******
  printf("3. Alphabetical\n"); // out
  int y;
  for (y=0; y < strlen(path1); y++)
  {
    if (path1[y] < path2[y])
    {
      printf("insert path1\n\n"); // out
      return 0; // out
    }
    if (path1[y] > path2[y])
    {
      printf("continue to next node\n\n"); //out
      return 0; // out
    }
  }
  
  printf("\n");
  return 0;
}

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

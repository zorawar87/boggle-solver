/* puzzle.c
 * 
 *
 *
 * authors James Rodiger, Zorawar 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void main(){
  time_t start, end;

  int nRow,nCol;
  int i;
  char **grid;
  char * word;
  
  scanf("%d",&nRow);
  scanf("%d",&nCol);

  grid = (char **)malloc(nRow*sizeof(char*));
  for(i=0;i<nRow;i++)
    grid[i] = (char *)malloc(nCol*sizeof(char));

  for(i=0;i<nRow;i++)
    scanf("%s",*grid[i]);
  scanf("%s",word);
  

  start = time(NULL);

  //search for word

  end = time(NULL);

  printf("Elapsed time = %ld seconds\n", end - start);
}


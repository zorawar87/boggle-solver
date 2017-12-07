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

void search(char **grid,int nRow,int nCol,char *word);

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

  word = (char *)malloc(nRow*sizeof(char));
  
  for(i=0;i<nRow;i++)
    scanf("%s",grid[i]);
  
  scanf("%s",word);
  

  start = time(NULL);


  search(grid,nRow,nCol,word);
  //search for word

  end = time(NULL);

  printf("Elapsed time = %ld seconds\n", end - start);
}

void search(char **grid,int nRow,int nCol,char *word){
  int i,x,y;
  for(i=0;word[i+1]!='\0';i++);//find final letter
  for(y=0;y<nCol;y++){
    for(x=0;x<nRow;x++){
      if(grid[y][x]==word[0]){
	//check right then downleft then down then downright
      }elseif(grid[y][x]==word[i]){
      }
    }
  }
}

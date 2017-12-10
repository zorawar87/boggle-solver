/* puzzle.c
 * searches for a word
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
  for(i=0;i<=nRow;i++)
    grid[i] = (char *)malloc(nCol*sizeof(char));

  word = (char *)malloc(nRow*sizeof(char));
  
  for(i=0;i<nRow;i++)
    scanf("%s",grid[i]);
  
  scanf("%s",word);
  

  start = time(NULL);

  search(grid,nRow,nCol,word);

  end = time(NULL);
  free(word);
  free(grid);
  printf("Elapsed time = %ld seconds\n", end - start);
}

void search(char **grid,int nRow,int nCol,char *word){
  int i,x,y,l;
  short found = 0;
  for(i=0;word[i+1]!='\0';i++);//find final letter
  for(y=0;y<nRow&&!found;y++){
    for(x=0;x<nCol&&!found;x++){
      if(grid[y][x]==word[0]){
        if(nCol-x>=i&&grid[y][x+1]==word[1]){ //check right
	  for(l=2;l<=i;l++){
	    if(grid[y][x+l]!=word[l]){
	      break;
	    }
	  }
	  if(grid[y][x+l-1]==word[i]){
	    printf("Row: %d Column: %d\n",y+1,x+1);
	    found=1;
	  }
	  
	}else if(x!=0&&y<nCol&&grid[y+1][x-1]==word[1]){//check downleft
	  for(l=2;l<=i;l++){
	      if(y+l<nRow&&x-l>=0){
		if(grid[y+l][x-l]!=word[l]){
		  break;
		}
	      }
	  }
	  if(grid[y+l-1][x-l+1]==word[i]){
	    printf("Row: %d Column: %d\n",y+1,x+1);
	    found=1;
	  }
	}else if(nRow-y>=i&&grid[y+1][x]==word[1]){//check down
	  for(l=2;l<=i;l++){
	    if(grid[y+l][x]!=word[l]){
	      break;
	    }
	  }
	  if(grid[y+l-1][x]==word[i]){
	    printf("Row: %d Column: %d\n",y+1,x+1);
	    found=1;
	  }	  
	}else if(x<nCol&&y<nRow&&grid[y+1][x+1]==word[1]){//check downright
	  for(l=2;l<=i;l++){
	      if(y+l<nRow&&x+l<nCol){
		if(grid[y+l][x+l]!=word[l]){
		  break;
		}
	      }
	  }
	  if(grid[y+l-1][x+l-1]==word[i]){
	    printf("Row: %d Column: %d\n",y+1,x+1);
	    found=1;
	  }
	}
      }else if(grid[y][x]==word[i]){
	if(nCol-x>=i&&grid[y][x+1]==word[i-1]){ //check right
	  for(l=2;l<=i;l++){
	    if(grid[y][x+l]!=word[i-l]){
	      break;
	    }
	  }
	  if(grid[y][x+l-1]==word[0]){
	    printf("Row: %d Column: %d\n",y+1,x+l);
	    found=1;
	  }
	  
	}else if(x!=0&&y<nCol&&grid[y+1][x-1]==word[i-1]){//check downleft
	  for(l=2;l<=i;l++){
	      if(y+l<nRow&&x-l>=0){
		if(grid[y+l][x-l]!=word[i-l]){
		  break;
		}
	      }
	  }
	  if(grid[y+l-1][x-l+1]==word[0]){
	    printf("Row: %d Column: %d\n",y+l,x-l+1);
	    found=1;
	  }
	}else if(nRow-y>=i&&grid[y+1][x]==word[i-1]){//check down
	  for(l=2;l<=i;l++){
	    if(grid[y+l][x]!=word[i-l]){
	      break;
	    }
	  }
	  if(grid[y+l-1][x]==word[0]){
	    printf("Row: %d Column: %d\n",y+l,x+1);
	    found=1;
	  }	  
	}else if(x<nCol&&y<nRow&&grid[y+1][x+1]==word[i-1]){//check downright
	  for(l=2;l<=i;l++){
	      if(y+l<nRow&&x+l<nCol){
		if(grid[y+l][x+l]!=word[i-l]){
		  break;
		}
	      }
	  }
	  if(grid[y+l-1][x+l-1]==word[0]){
	    printf("Row: %d Column: %d\n",y+l,x+l);
	    found=1;
	  }
	}
      }
    }
  }
  if(!found){
    printf("No such word");
  }
}

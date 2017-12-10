/* puzzle_threaded.c
 * 
 *
 *
 * authors James Rodiger, Zorawar 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int nRow,nCol,thread_count;
char **grid;
char * word;

void searchx(char **grid,int nRow,int nCol,int offset);
void searchy(char **grid,int nRow,int nCol,int offset);
void *split(void *rank);



void main(){
  time_t start, end;
  long tid;
  pthread_t *thread;

  //int nRow,nCol;
  int i;
  //char **grid;
  // char * word;
  
  scanf("%d",&nRow);
  scanf("%d",&nCol);

  grid = (char **)malloc(nRow*sizeof(char*));
  for(i=0;i<=nRow;i++)
    grid[i] = (char *)malloc(nCol*sizeof(char));

  word = (char *)malloc(nRow*sizeof(char));
  
  for(i=0;i<nRow;i++)
    scanf("%s",grid[i]);
  
  scanf("%s",word);

  thread_count = 8;
  thread = (pthread_t*)malloc(thread_count*sizeof(pthread_t));

 

  start = time(NULL);
  for(tid=0;tid<thread_count;tid++)
    pthread_create(&thread[tid],NULL,split,(void*)tid);
  
 
  for(tid=0;tid<thread_count;tid++)
    pthread_join(thread[tid],NULL);
  end = time(NULL);

  

  printf("Elapsed time = %ld seconds\n", end - start);
}

void searchx(char **grid,int row,int col,int offset){
  int i,x,y,l;
  short found=0;
  for(i=0;word[i+1]!='\0';i++);//find final letter
  for(y=0;y<row&&!found;y++){
    for(x=offset;x<offset+col&&!found;x++){
      if(grid[y][x]==word[0]){
	//check right then downleft then down then downright
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
      }
    }
  }
}
void searchy(char **grid,int row,int col,int offset){
  int i,x,y,l;
  short found=0;
  for(i=0;word[i+1]!='\0';i++);//find final letter
  for(y=0;y<row&&!found;y++){
    for(x=offset;x<offset+col&&!found;x++){
      if(grid[y][x]==word[i]){
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
}

void *split(void*rank){
  long tid = (long)rank;
  int nQRow=nRow/2;
  int nQCol=nCol/2;
  
  switch(tid)
    {
    case 0:
      printf("got %ld\n",tid);
      searchx(grid,nQRow,nQCol,0);
      break;
    case 1:
      printf("got %ld\n",tid);
      searchx(&grid[nQRow],nQRow,nQCol,0);
      break;
    case 2:
      printf("got %ld\n",tid);
      searchx(grid,nQRow,nQCol,nQCol);
      break;
    case 3:
      printf("got %ld\n",tid);
      searchx(&grid[nQRow],nQRow,nQCol,nQCol);
      break;
    case 4:
      printf("got %ld\n",tid);
      searchy(grid,nQRow,nQCol,0);
      break;
    case 5:
      printf("got %ld\n",tid);
      searchy(&grid[nQRow],nQRow,nQCol,0);
      break;
    case 6:
      printf("got %ld\n",tid);
      searchy(grid,nQRow,nQCol,nQCol);
      break;
    case 7:
      printf("got %ld\n",tid);
      searchy(&grid[nQRow],nQRow,nQCol,nQCol);
      break;
  
    }
  return NULL;
}

#include <stdio.h>
#include <stdbool.h>
#include <time.h>


//#define size 4
int size=4,score = 0;
int scorep=0;


int findempty(int new[16][16],int list[64][2]);
void Random(int new[16][16]);
void restoreold(int new[16][16],int old[16][16]);
void display(int new[16][16]);
void initialize(int new[16][16]);
bool pairexist(int new[16][16]);
bool slidel(int new[size]);
void rotate(int new[16][16]);
bool lefta(int new[16][16]);
bool up(int new[16][16],int old[16][16]);
bool left(int new[16][16],int old[16][16]);
bool down(int new[16][16],int old[16][16]);
bool right(int new[16][16],int old[16][16]);
bool gameover(int new[16][16]);
int main()
{
        printf("          _______  ________  ___   ___  ________ _______ \n ");
	printf(	" /  ___  \\|\\   __  \\|\\  \\ |\\  \\|\\   __  \\   \n ");
	printf(	"/__/|_/  /\\ \\  \\|\\  \\ \\  \\\\_\\  \\ \\  \\|\\  \\  \n ");
	printf(	"|__|//  / /\\ \\  \\\\\\  \\ \\______  \\ \\   __  \\  \n");
	printf(	"    /  /_/__\\ \\  \\\\\\  \\|_____|\\  \\ \\  \\|\\  \\\n ");
	printf(	"   |\\________\\ \\_______\\     \\ \\__\\ \\_______\\\n");
	printf(	"    \\|_______|\\|_______|      \\|__|\\|_______|\n");
	


printf("The goal of the game is to merge numbers together (powers of 2) in order to reach the ultimate '2048' tile and win the game !\n");

printf("enter the dimensions of the grid \n");      
 scanf("%d",&size);
 
 
	int new[16][16],old[16][16];
	bool move = 0;
        char c;//
	initialize(new);
        restoreold(new,old);
	display(new);//c=getchar();
	while(c=getchar())
	{
		
		switch(c) 
		{
			case 97:
			  {
				move= left(new,old);  
        break;
			  }	
			case 68:
			  {
				move= left(new,old);  
        break;
			  }	
			case 100:
			  {
				move = right(new,old); 
        break;
			  }	
			case 67:
			  {
				move = right(new,old);
        break;
			  }	
			case 119:
                          {
			         move = up(new,old);    
               break;
			  }	
			case 65:
			  {
			         move = up(new,old);    
               break;
			  }	
			case 115:
			  {
				move = down(new,old); 
        break;
			  } 	
			case 66:
			  {
				move = down(new,old); 
        break; 
			  } 
                   
		case 'r':
		  {
		  score=0;
		  system("clear");
		  initialize(new);
                  restoreold(new,old);
                  display(new);
                  c=getchar();break;
		  }
		case 'u':
		{
		  score=scorep;
		  restoreold(old,new);
		  display(old);
		  break;
		}
case 'q':
{
return 0;
}
                default: move = 0;
                }
		if(gameover(new)==1)
		{
			system("clear");
			printf("\n\n\n\t\t\tGAME OVER!!! ( :-( )...YOU LOST");
			break;
		}				
		if(move==1)
		{       system("clear");
		        Random(new);
			display(new);			
		}
 //     c=getchar();
	}//system("stty cooked");
        
	return 0;
	}
int findempty(int new[16][16],int list[64][2])
{
  int l=0;
  for (int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(new[i][j] == 0)
			{
				list[l][0] = i;
				list[l++][1] = j;
			}
		}
	}
	return l;
}
void Random(int new[16][16])
{
  int  select, list[64][2],r;
  int l=findempty(new,list);
  srand(time(NULL));
  if(l > 0)
    {
		select = rand() % l;
		r = 2 * ((rand() % 15) / 14 + 1);
		new[list[select][0]][list[select][1]]=r;
    }
}
void restoreold(int new[16][16],int old[16][16])
{
  for(int i=0;i<size;i++)
    {
      for(int j=0;j<size;j++)
	{
	  old[i][j]=new[i][j];
	}
    }
}
void display(int new[16][16])
{
	char empty = '_';
	system("clear");
	printf("\n\n");
	printf("\t\t\t     TWO ZERO FOUR EIGHT (2048 :-) )\n");
        printf("\t\t Use the arrow keys or the w,s,a,d keys to play \n\n");
printf("\t\t\t\t\t\tYOUR SCORE IS: %d\n\n", score);
	printf("\n\n\t\t\t         \n");
	for(int i = 0; i < size; i++)
	{
		printf("\t\t");
		for(int j = 0; j < size; j++)
		{
			if(j != size - 1)
				if(new[i][j] == 0)
					printf(" %5c  |", empty);
				else
					printf(" %5d  |", new[i][j]);
			else
				if(new[i][j] == 0)
					printf(" %5c  ", empty);
				else
					printf(" %5d  ", new[i][j]);
		}
		printf("\n");
			printf("\t\t\t           ");
		printf("\n");
	}
	printf("\n");
	
	
	printf("\n\t\t Press key 'q' to QUIT program;\nPress 'u' to undo and 'r' to restart\n");
}

void initialize(int new[16][16])
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			new[i][j] = 0;
		}
	}
	Random(new);
	Random(new);
}

bool pairexist(int new[16][16])
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size - 1; j++)
		{
			if(new[i][j] == new[i][j + 1])
			{
			  return 1;
			}
		}
	}
	return 0;
}

bool slidel(int new[size])
{
	int i, j, temp, flag[8],k=0;// = {0, 0, 0, 0};
        for(i=0;i<size;i++)
        {
        flag[i]=0;
        }
	bool move = 0;
	for(i = 0; i < size; i++)
	{
		temp = i;
		for(j = 0; j < i; j++)
		{
			if(new[temp] != 0)
			{
				if(new[temp] == new[temp - 1] && flag[temp - 1] == 0 && flag[temp] == 0)
				{
					new[temp - 1] = 2 * new[temp];
					score = score + new[temp - 1];
					new[temp] = 0;
                                        k=temp-1;flag[k]=1;
					/*if(temp - 1 == 0)
						flag[0] = 1;
					else if(temp - 1 == 1)
						flag[1] = 1;
					else if(temp - 1 == 2)
						flag[2] = 1;*/
					move = 1;
				}
				else if(new[temp - 1] == 0 && new[temp] != 0)
				{
					new[temp - 1] = new[temp];
					new[temp] = 0;
					move = 1;
				}
			}
			temp--;
		}	
	}
	return move;
}

void rotate(int new[16][16])
{
	int i, j, temp ;
	for(i = 0; i < size / 2; i++)
	{
		for(j = i; j < size- i - 1; j++)
		{
			temp = new[i][j];
			new[i][j] = new[j][size-i-1];
			new[j][size-i-1] = new[size-i-1][size-j-1];
			new[size-i-1][size-j-1] = new[size-j-1][i];
			new[size-j-1][i] = temp;
		}
	}
}

bool lefta(int new[16][16])
{
	bool move = 0;
	int i;
        scorep=score;
	for(i = 0; i < size; i++)
	{
		move |= slidel(new[i]);
	}
	return move;	      
}
       
bool up(int new[16][16],int old[16][16]) 
{
	bool move=0;
	restoreold(new,old);
	rotate(new);
	move = lefta(new);
	rotate(new);rotate(new);rotate(new);
	return move;
}
bool left(int new[16][16],int old[16][16]) 
{
	bool move = 0;
        move =lefta(new);
	restoreold(new,old);
	return move;
}

bool down(int new[16][16],int old[16][16]) 
{
	bool move=0;
	restoreold(new,old);
	rotate(new);rotate(new);rotate(new);
	move=lefta(new);
	rotate(new);
	return move;
}

bool right(int new[16][16],int old[16][16]) 
{
	bool move=0;
	restoreold(new,old);
	rotate(new);rotate(new);
	move = lefta(new);
	rotate(new);rotate(new);
	return move;
}

bool gameover(int new[16][16])
{
  int i, j,list[64][2];
  if(findempty(new,list)>0)
    {
      return 0;
    }
  if(pairexist(new)==1)
    {
      return 0;
    }
  rotate(new);
  if(pairexist(new)==1)
    {
      return 0;
    }
  rotate(new);
rotate(new);
rotate(new);
  return 1;
}

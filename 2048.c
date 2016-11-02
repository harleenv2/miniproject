
/*
==============================================================================================================================================
 * Name        : 2048.c
 * Author      : harleen virk (S.Y.Btech in Computer Engineering from CoEP)
 * Description : Console version of the 2048 game for GNU/Linux
 * Copyright (C) harleen virk ID : hrlnvirk78@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
==============================================================================================================================================
*/



#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<error.h>
#include<errno.h>


int size=4,score = 0;//define size of the grid,initialize the score and previous score(scorep) as 0
int scorep=0;

int findempty(int new[16][16],int list[256][2]);
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
void rules();

int main(int argc, char *argv[])
{
	
	if(argc>1 &&strcmp(argv[1] , "-h") == 0){
		rules();
		return 0;
	}
	
	else{
		
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
	display(new);c=getchar();
	while(true)//input command
	{
		
		switch(c) 
		{
			case 97://swipe left
			  {
				move= left(new,old);  
				break;
			  }	
			case 68:
			  {
				move= left(new,old); 
				 break;
			  }	
			case 100://swipe right
			  {
				move = right(new,old); 
				break;
			  }	
			case 67:
			  {
				move = right(new,old); 
				break;
			  }	
			case 119://swipe up
                          {
			         move = up(new,old);   
				 break;
			  }	
			case 65:
			  {
			         move = up(new,old);  
				  break;
			  }	
			case 115://swipe down
			  {
				move = down(new,old);
				  break;
			  } 	
			case 66:
			  {
				move = down(new,old);
				 break; 
			  } 
                   
		case 'r'://for input 'r' restart the game
		  {
		  score=0;
		  system("clear");
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
		system("clear");
		  initialize(new);
                  restoreold(new,old);
                  display(new);
                  c=getchar();break;
		  }
		case 'u'://for input 'u' undo the move
		{
		  score=scorep;
		  restoreold(old,new);
		  display(old);
		  break;
		}
case 'q'://for input 'q' quit the game
{
return 0;
}
                default: move = 0;
                }
		if(gameover(new)==1)//check if the game has been lost
		{
			system("clear");
			printf("\n\n\n\t\t\tGAME OVER!!! ( :-( )...YOU LOST\f\f");
			
			break;
		}				
		if(move==1)
		{       system("clear");
		        Random(new);
			display(new);			
		}
        c=getchar();
 
	}
	}
	return 0;
	}
int findempty(int new[16][16],int list[256][2])//find the empty tiles
{
  int l=0 , i , j;
  for ( i = 0; i < size; i++)
	{
		for( j = 0; j < size; j++)
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
void Random(int new[16][16])//randomly select an empty tile and plce a number(either 2 or 4) at it
{
  int  select, list[256][2],r;
  int l=findempty(new,list);
  srand(time(NULL));
  if(l > 0)
    {
		select = rand() % l;
		r = 2 * ((rand() % 15) / 14 + 1);
		new[list[select][0]][list[select][1]]=r;
    }
}
void restoreold(int new[16][16],int old[16][16])//initialize the old[][] grid as a copy of the new[][] grid
{
int i , j ;
  for( i=0;i<size;i++)
    {
      for( j=0;j<size;j++)
	{
	  old[i][j]=new[i][j];
	}
    }
}
void display(int new[16][16])//display
{
	int i , j ;
	char empty = '_';
	system("clear");
	printf("\n\n");

	printf("\t\t\t     TWO ZERO FOUR EIGHT (2048 :-) )\n");

        printf("\t\t Use the arrow keys or the w,s,a,d keys to play \n\n");

printf("\t\t\t\t\t\tYOUR SCORE IS: %d\n\n", score);

	printf("\n\n\t\t\t         \n");

	for( i = 0; i < size; i++)
	{
		printf("\t\t");


		for( j = 0; j < size; j++)
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

void initialize(int new[16][16])//initialize the grid
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

bool pairexist(int new[16][16])//find if a possible pair i.e. a pair of two consecutive tiles having the same number, exists
{
int i , j ;
	for( i = 0; i < size; i++)
	{
		for( j = 0; j < size - 1; j++)
		{
			if(new[i][j] == new[i][j + 1])
			{
			  return 1;
			}
		}
	}
	return 0;
}

bool slidel(int new[size])//slide left along the given row
{
	int i, j, temp, flag[16],k=0;// = {0, 0, 0, 0};
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

void rotate(int new[16][16])//rotate
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

bool lefta(int new[16][16])//swipe left(no save copy(old[][]) created)
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
       
bool up(int new[16][16],int old[16][16]) //swipe up
{
	bool move=0;
	restoreold(new,old);
	rotate(new);
	move = lefta(new);
	rotate(new);rotate(new);rotate(new);
	return move;
}
bool left(int new[16][16],int old[16][16]) //swipe left(save copy(old[][]) created)
{
	bool move = 0;
        move =lefta(new);
	restoreold(new,old);
	return move;
}

bool down(int new[16][16],int old[16][16]) //swipe down
{
	bool move=0;
	restoreold(new,old);
	rotate(new);rotate(new);rotate(new);
	move=lefta(new);
	rotate(new);
	return move;
}

bool right(int new[16][16],int old[16][16]) //swipe right
{
	bool move=0;
	restoreold(new,old);
	rotate(new);rotate(new);
	move = lefta(new);
	rotate(new);rotate(new);
	return move;
}

bool gameover(int new[16][16])//check if the game has been lost
{
  int list[256][2];
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
	
void rules(){
	printf("The objective of the game is to get the number 2048 using additions of the number two and its multiples.");
	printf("game can be played using arrows or letter a,s,d,w  \n");
	printf("we can select the grid size from 2-16\n");
	printf("there is an option to quit restart and undo\n");
}

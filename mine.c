/*
==========================================================================================
====================================================
 * Name        : mine.c
 * Author      : harleen virk (S.Y.Btech in Computer Engineering from CoEP)
 * Description : Console version of the snake game for GNU/Linux
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
==========================================================================================
==============================================
the following is a program for the classic game minesweeper played on a 9*9 grid.Each 
tile is represented by the user defined datatype grid/matrix.Each tile has 2 components.1
-lock-might hold values 0,1,2(representing the status of the tile as unlocked,locked and 
flagged respectively),2.-display-regarding what is actually displayed on the screen.(the 
charachters F,_ and * represent the status of the style as flagged,locked and mine 
respectively).3-real-represents what is actually present in the tile.(note. -1 represents 
the presence of a mine)*/



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

char discalculate(int real, int lock) /*to calculate display*/
{
	if (lock == 2)
	{
		return ('F');
	}
	else if (lock == 1)
	{
		return ('_');
	}
	else if (lock == 0)
	{
		if (real < 0)
		{
			return '*';
		}
		else if (real == 0)
		{
			return '0';
		}
		else
		{
			return 48 + real;
		}
	}
	else
	{
		return 99;
	}
}

typedef struct grid  /*object type representing a tile*/
{
	int real;
	int lock;
	char display;
}matrix;

void randomselect(matrix e[11][11], int list[100][2]);
void un(matrix e[11][11],int i,int j);
void randomi(matrix e[11][11]);
void numbering(matrix e[11][11]);
void slate(matrix e[11][11]);
void empty(matrix e[11][11]);
void initiate(matrix e[11][11]);
void dis(matrix e[11][11],int f);
void unlockall(matrix e[11][11]);
bool gameover(matrix e[11][11]);
bool gamewon(matrix e[11][11]);
//void ifzero(matrix e[11][11], int i, int j);
void check(matrix e[11][11], int a, int b);
void rules();

int main(int argc, char *argv[]){
	
	if(strcmp(argv[1] , "-h") == 0){
		rules();
		return 0;
	}
	
	else{
		
	matrix e[11][11];/*create a two-dimensional array of size 11*11.note- the objectsrepresented by e[x][0],e[0][x],e[10][x] and e[x][10] wont be represented on the screen. */
	initiate(e);
	 slate(e);
	 int f = 17;/*initiate number of flags*/
	dis(e,f);/*display*/
	char c, c1, c2; 
        c=getchar();
	while (true)
	{
		if(c=='r'||c=='R')/*if input r the game restarts*/
		{
			f = 17;
			 initiate(e); 
			slate(e);
			 dis(e, f);
		}
		else if (c== 'f'||c=='F')/*enter fab to place a flag at the co-ordinates a,b*/
		{
			c1=getchar();	
			c2=getchar();
			int i = c1-48 , j = c2-48; f--;
			if (e[i][j].lock == 1)
			{
				e[i][j].lock = 2;
				 e[i][j].display = 'F';
				slate(e);
				 dis(e, f);
			}
		}
		else if (c == 'g'||c=='G')/*enter gab to remove a flag from the coordinates a,b*/
		{
			c1=getchar();	
			c2=getchar();
			int i = c1-48, j = c2-48; 
                        if(e[i][j].lock==2)
                        { 
			f++;
			e[i][j].lock = 1;
			 e[i][j].display = '_';
			slate(e); 	
			e[i][j].display = '_';
			dis(e,f);
                        }
		}
                else if(c=='q'||c=='Q')/*enter q to quit the game*/
               {
                return 0;
                }
         	else if(c=='e'||c=='E')/*enter eab to unlock the tile at a,b*/
		{
			c1=getchar();
			c2=getchar();
			int i = c1-48, j = c2-48;
                        if(e[i][j].lock==1)
                        {
			check(e, i, j);
			slate(e); 
			dis(e,f);
                        }
		}
          	else if (c== 'u'||c=='U')/*enter uab to unlock the tiles surrounding a,b*/
		{
			c1=getchar();
			c2=getchar();
                        int i = c1-48,j = c2-48;
			
                    
                        if(e[i][j].lock==0)
                        {     
			un(e,i,j);
			slate(e);
			 dis(e,f);
                        }
		}
		if (gameover(e) == 1)/*to check if the player has lost the game*/
		{
			slate(e); 
			dis(e,f);
			 printf("\n\n YOU LOST \n\n");
			 return 0;
		}
		if (gamewon(e) == 1)/*to check if the user has won the game*/
		{
			
			slate(e);
			 dis(e,f); 
			printf("\n\n YOU WON \n\n"); 	
			return 0;
		}
                c=getchar();
	}
	return 0;
}}
void un(matrix e[11][11],int i,int j)/*unlock neighbouring tiles(to i,j)*/
{
	int x , y ;
	int a = i - 1, a1 = i + 1, b = j - 1, b1 = j + 1;
	if (i - 1 < 0)a =0;
	if (i + 1 > 10)a1 = 10;
	if (j - 1 < 0)b = 0;
	if (j + 1 > 10)b1 = 10;
	if (i > 0 && i < 10 && j>0 && j < 10)
	{
		for ( x = a; x <= a1; x++)
		{
			for ( y = b; y <= b1; y++)
			{
                           if(e[x][y].lock!=2)  
				check(e,x,y);
			}
		}
	}
}
void randomselect(matrix e[11][11],int list[100][2])/*to select a tile at random so as to place a mine at the selected tile( Note-the tile should not have a mine laced at it)*/
{
	int i ,j ;
	int l = 0;
	for ( i = 1; i <10; i++)
	{
		for ( j = 1; j <10; j++)
		{
			if (e[i][j].real != -1)
			{
				list[l][0] = i;
				list[l][1] = j;
				l++;
			}
		}
	}
	srand(time(NULL));
	int r = rand() % l;
	e[list[r][0]][list[r][1]].real = -1;
}
void randomi(matrix e[11][11])/*randomly allocate mines at 17 different positions on the grid using the randomselect function*/
{
	int list[100][2], i;
	for (i = 0; i < 17; i++)
	{
		randomselect(e, list);
	}
}
void numbering(matrix e[11][11])/*assign numbers to each mine-free tile(note-the number reresents the number of mines surrounding the said tile)*/
{
	int i , j;
	int count = 0;
	int x = 0, y = 0;
	for ( i = 1; i<10; i++) 
	{
		for ( j = 1; j<10; j++)
		{
			if (e[i][j].real != -1)
			{
				count = 0;
				for (x = i - 1; x <= i + 1; x++)
				{
					for (y = j - 1; y <= j + 1; y++)
					{
							if (e[x][y].real == -1)
							{
								count++;
							}
					}
				}
				e[i][j].real = count;
			}
		}
	}
}
void slate(matrix e[11][11])/*to check and calculate display for each tile using the discalculate() function.*/
{
	int i ,j ;
	for ( i = 0; i < 11; i++)
	{
		for ( j = 0; j < 11; j++)
		{
			e[i][j].display=discalculate(e[i][j].real,e[i][j].lock);
		}
	}
}
void empty(matrix e[11][11])/*empty the grid...i.e. lock all the tiles and remove all the mines and numbers.(said mines and numbers are to be replaced with 0)*/
{
	int i ,j ;
	for (i = 0; i < 11; i++)
	{
		for ( j = 0; j < 11; j++)
		{
			e[i][j].real = 0;
			e[i][j].lock = 1;
		}
	}
}
void initiate(matrix e[11][11])/*initiate the grid*/
{
	system("clear");
	empty(e);
	randomi(e);
	numbering(e);
	slate(e);
}
void dis(matrix e[11][11],int f)/*display*/
{
	int i , j ;
	system("clear");
	printf("\f\f\f\f\f");
	printf("\t\t\t\t MINESWEEPER \n\n");
        printf("1.Enter 'e' if you want to unlock a tile.\n");
        printf("2.Enter 'f' if you want to place a flag \n");
        printf("3.'g' to remove a flag\n");
        printf("4.Enter 'u' to unlock the surrounding tiles.\n");
        printf("followed by the co-ordinates.\n");
        printf(" Enter the x co-ordinate and the y co-ordinate respectively\n");
        printf("(note: the coordinates(x,y)the following and then enter your co-ordinates accordingly:");
        printf("\ntop left corner:(1,1)\ntop right corner:(1,09)\nbottom left corner:(09,1)");
        printf("\nbottom right corner:(09,09)\n");
	printf("FLAGSLEFT=%d \n",f);
	
	printf("----");
	for ( i = 1; i<10; i++)
	{
			printf("-0%d",i);
		
	}
	printf("---\n---");
	for ( i = 0; i<9; i++)
	{
		printf("----");
	}
	printf("\n");
	for ( i = 1; i<10; i++)
	{
			printf("-0%d- ",i);
		for ( j = 1; j<10; j++)
		{

			{
				printf( " %c ",e[i][j].display);
			}
		}
		printf("\n\n");
	}printf("--");
	for (i = 0; i<11; i++)
	{
		printf("---");
	}printf("--\n");
	printf("Press 'r' to restart;Press 'q' to quitv\n");
}
void unlockall(matrix e[11][11])/*unlock all the un-flagged tiles*/
{
	int i , j;
	for ( i = 0; i < 11; i++)
	{
		for ( j = 1; j < 11; j++)
		{
			if (e[i][j].lock != 2)
			{
				e[i][j].lock = 0;
				e[i][j].display=discalculate(e[i][j].real,e[i][j].lock);
			}
		}
	}
}
bool gameover(matrix e[11][11])/*to check if the game has been lost*/
{
	int i , j;
	for ( i = 1; i<10; i++)
	{
		for ( j = 1; j<10; j++)
		{
			if (e[i][j].lock == 0 && e[i][j].real == -1)
			{
				unlockall(e);
				return 1;
			}
		}
	}
	return 0;
}
bool gamewon(matrix e[11][11])/*to check if the game has been won*/
{
	int i , j ;
	for ( i = 1; i<10; i++)
	{
		for ( j = 0; j<10; j++)
		{
			if (e[i][j].real != -1 && e[i][j].real != 0)
			{
				return 0;
			}
		}
	}
	unlockall(e);
	return 1;
}
void ifzero(matrix e[11][11], int i, int j)/*to avoid unlocking empty tiles(note-if a tile neighbouring a zero-tile is to be unlocked,the zero tile will be unlocked too)*/
{
	int x , y ;
	e[i][j].lock = 0;
	int a = i - 1, a1 = i + 1, b = j - 1, b1 = j + 1;
	if (i - 1 < 0)a =0;
	if (i + 1 > 10)a1 = 10;
	if (j - 1 < 0)b = 0;
	if (j + 1 > 10)b1 = 10;
	if (i > 0 && i < 10 && j>0 && j < 10)
	{
		for ( x = a; x <= a1; x++)
		{
			for ( y = b; y <= b1; y++)
			{
				if (e[x][y].real == 0 && e[x][y].lock == 1)
				{
					ifzero(e, x, y);
				}
				if (x > 0 && x < 10 && y>0 && y < 10) e[x][y].lock = 0;
			}
		}
	}
}
void check(matrix e[11][11], int i, int j)/*to unlock a tile present at the coordinates (a,b)*/
{
	int x , y ;
	if (e[i][j].lock == 2)
	{
		return;
	}
	if(e[i][j].real==0)
	{
		ifzero(e,i,j);
	}
	for( x=i-1;x<=i+1;x++)
	{
		for( y=j-1;y<=j+1;y++)
		{
			if(e[x][y].real==0)
			{
				ifzero(e,x,y);
			}
		}
	}
	e[i][j].lock = 0;
}
void rules(){
	printf("Uncover a mine, and the game ends.Uncover an empty square, and you keep playing.Uncover a number, and ");
        printf("it tells you how many mines lay hidden in the eight surrounding squaresÃ¢â‚¬â€information ");
        printf("you use to deduce which nearby squares are safe to click.\n");
	printf("to unclock - exy and press enter\n");
	printf("to flag - fxy and press enter\n");
	printf("to remove flag - gxy and press enter\n");
}

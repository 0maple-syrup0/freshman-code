#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define size 4
int pane[4][4]={0};
void DrawFrame();
void random();
void Direction();
void Initial();
void drawboard();
void addrandom();
unsigned int findtarget(int array[size],unsigned int x,unsigned int stop);
void slide(int array[],unsigned int length);
void moveup();
void moveright();
void moveleft();
void movedown();
void rotate();
void Direction();
void result(int mode);
int hasempty();
int findpairdown();
int gameend();
//void init_pane();

int main()
{
	DrawFrame();
	Initial();
	drawboard();
	while(1)
	{
		
		int mode;
		Direction();
		addrandom();
		drawboard();
		if(mode==gameend())
		{
			result(mode);
			break;
		}
	}
	
	return 0;
}

void cleanboard()
{
	int i = 0, j = 0;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			pane[i][j] = 0;
		}
	}
}

void DrawFrame()
{
	char a='|';
	char b='_'; 
	for(int i=1;i<10;i++)
	{
		printf("\t");
		for(int j=1;j<6;j++)
		{
			if(i%2==1)
			{
				if(i==1)
				{
					printf("\n\t");
					for(j=1;j<5;j++)
					{
						printf(" ");
						printf("%c%c%c",b,b,b);
					}
					break;
				}
				printf("%c",a);
				if(j==5)	break;
				printf("%c%c%c",b,b,b);
			}
			else
			{
				printf("%-4c",a);
			}
		}
		printf("\n");	
	}	
}	

void random()//25%Realized
{
	for(int i=1;i<=16;i++)
	{
		if(i%4==1)	printf("\t");
		srand((unsigned)time(NULL)); 
		int x = 2 + rand() % 3;	
		printf("%4d",x);
		if(i%4==0)	printf("\n\n");
	}
}

void Initial()
{
	cleanboard();
	addrandom();
	addrandom();
} 

void drawboard()
{
	int x,y;
	for(x=0;x<size;x++)
	{
		for(y=0;y<size;y++)
		{
			if(pane[x][y]!=0)
			{
				printf("[%8d]",pane[x][y]);
			}
			else
			{
				printf("[%8s]"," ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void addrandom()
{
	int x,y;
	for(x=0;x<size;x++)
	{
		for(y=0;y<size;y++)
		{
			if(pane[x][y]==0)
			{
				pane[x][y]=2;
				break;
			}
		}
		if(y<size)
		{
			break;
		}
	}
}

//初始化二维数组
/*void init_pane()
{
	int pane[4][4];
	int i = 0, j = 0;
	for (i = 0; i<4; i++)
	{
		for (j = 0; j<4; j++)
		{
			pane[i][j] = 0;
		}
	}
	srand(time(NULL));
	i = rand() % 4;
	j = rand() % 4;
	if (i == 0 || i == 2)
	{
		pane[i][j] = 2;
	}
	else
	{
		pane[i][j] = 4;
	}
}*/

unsigned int findtarget(int array[size],unsigned int x,unsigned int stop)
{
	int t;
	for(t=x-1;t>=stop;t--)
	{
		if(array[t]!=array[x]&&array[t]!=0)
		{
			return t+1;
		}
	}
	return t+1;
}

void slide(int array[],unsigned int length)
{
	int x,t,stop=0;
	for(x=0;x<size;x++)
	{
		if(array[x]!=0)
		{
			t=findtarget(array,x,stop);
			if(t!=x)
			{
				if(array[t]==0)
				{
					array[t]=array[x];
				}
				else if(array[t]=array[x])
				{
					array[t]*=2;
					stop=t+1;
				}
				array[x]=0;
			}
		}
	}
}

void moveup()
{
	int x;
	for(x=0;x<size;x++)
	{
		slide(pane[x],size);
	}
}

void moveright()
{
	rotate();
	rotate();
	rotate();
	moveup();
	rotate();
}

void moveleft()
{
	rotate();
	moveup();
	rotate();
	rotate();
	rotate();
}

void movedown()
{
	rotate();
	rotate();
	moveup();
	rotate();
	rotate();
}

void rotate()
{
	int i,j,tmp,n=size;
	for(i=0;i<n/2;i++)
	{
		for(j=0;j<n-1-i;j++)
		{
			tmp=pane[i][j];
			pane[i][j]=pane[j][n-1-i];
			pane[j][n-1-i]=pane[n-1-i][n-1-j];
			pane[n-1-i][n-1-j]=pane[n-1-j][i];
			pane[n-1-j][i]=tmp;
		}
	}
}

void Direction()
{   
    int ch1=0;
    int ch2=0;
    while (1)
    {
      	if (ch1=getch())
      	{ 
        	ch2=getch();
         	switch (ch2)
         	{
	         	case 72: moveup();break;  
	         	case 80: movedown();break; 
	         	case 75: moveleft();break;
	         	case 77: moveright();break;                                   
	         	default: printf("No direction keys detected \n");break;
	        	break;
         	}
      	}  
    }
}

int hasempty()
{
	int x,y;
	for(x=0;x<size;x++)
	{
		for(y=0;y<size;y++)
		{
			if(pane[x][y]==0)
			{
				return 1;
			}
		}
	}
	return 0;
}

int findpairdown()
{
	int x,y;
	for(x=0;x<size;x++)
	{
		for(y=0;y<size-1;y++)
		{
			if(pane[x][y]==pane[x][y+1])
			{
				return 1;
			}
		}
	}
	return 0;
}

int haswon()
{
	int x,y;
	for(x=0;x<size;x++)
	{
		for(y=0;y<size;y++)
		{
			if(pane[x][y]==2048)
			{
				return 1;
			}
		}
	}
	return 0;
}

int gameend()
{
	if(haswon())
	{
		return 2;
	}
	if(!hasempty())
	{
		return 0;
	}
	if(findpairdown())
	{
		return 0;
	}
	rotate();
	int isended=1;
	if(findpairdown())
	{
		isended=1;
	}
	rotate();
	rotate();
	rotate();
	return isended;
}

void result(int mode)
{
	if(mode==1)
	{
		printf("Lose!");
	}
	else if(mode==2)
	{
		printf("Win!");
	}
}

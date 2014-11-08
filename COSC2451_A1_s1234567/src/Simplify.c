#include "stdio.h"
#include "stdlib.h"

#define Row 4
#define Col 4

void printMap(int **x){
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col;j++){
			printf("%i ", x[i][j] );
		}
		printf("\n");
	}
}
void up(int **x, int row, int col){
	// x[row][col] ==> x[j][i]
	for(int i = 0; i < col; i++){
		int stop = 0;
		for (int j = 1; j < row; j++)
		{			
			int k = j;
			while(k != stop){
				if(x[k - 1][i] == x[k][i] && x[k][i] != 0){
					x[k - 1][i] += x[i][i];
					x[k][i] = 0;
					stop = k;
					break;
				}  else if (x[k - 1][i] == 0){
					x[k - 1][i] += x[k][i];
					x[k][i] = 0;
				}
				k--;
			}
		}
	}
}

void down(int **x, int row, int col){
	// x[row][col] ==> x[j][i]
	for(int i = 0; i < col ; i++){
		int stop = row - 1;
		for (int j = row - 2; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[k + 1][i] == x[k][i] && x[k][i] != 0){
					x[k + 1][i] += x[k][i];
			 		x[k][i] = 0;
					stop = k;
					break;
				}  else if (x[k + 1][i] == 0){
					x[k + 1][i] += x[k][i];
					x[k][i] = 0;
				}
				k++;
			}
		}
	}
}

void left(int **x, int row, int col){
	// x[row][col] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = 0;
		for (int j = 1; j < col; j++)
		{
			int k = j;
			while(k != stop){
				if(x[i][k-1] == x[i][k] && x[i][k] != 0){
					x[i][k-1] += x[i][k];
					x[i][k] = 0;
					stop = k;
					break;
				} else if (x[i][k-1] == 0){
					x[i][k-1] += x[i][k];
					x[i][k] = 0;
				}

				k--;
			}
		}
	}
}


void right(int **x, int row, int col){
	// x[row][col] ==> x[i][j]
	for(int i = 0; i < row; i++){
		int stop = col -1;
		for (int j = col -1; j >= 0; j--)
		{
			int k = j;
			while(k != stop){
				if(x[i][k+1] == x[i][k]  && x[i][k] != 0){
					x[i][k+1] += x[i][k];
					x[i][k] = 0;
					stop = k;
					break;
				} else if(x[i][k+1] == 0){
					x[i][k+1] += x[i][k];
					x[i][k] = 0;
				}
				k++;	
			}
		}
	}
}

void simplify(int **x, int dir, int row, int col)
{
	printf("test\n");
	switch(dir){
		case 1:
			printf("up method\n");
			up(x, row, col);
			printf("up\n");
			break;
		case 2:
			printf("down method\n");
			down(x, row, col);
			printf("down\n");
			break;
		case 3:
			left(x, row, col);
			printf("left\n");
			break;
		case 4:
			right(x, row, col);
			printf("right\n");
			break;
	}
}

int main()
{
int **x = malloc(sizeof(int *) * Row);

// There are 2 map: map.txt and map2.txt
FILE *f = fopen("map.txt", "r");
	for(int i = 0; i < Row; i++){
		x[i] = malloc(sizeof(int) *Col);
	}

	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col;j++){
			// printf("x[%i][%i]: ",i,j);
			// scanf("%i",&x[i][j]);
			fscanf (f, "%i", &x[i][j]);   
		}
	}
	fclose (f);     

	printMap(x);

	// simplify(,x,,)
	// x: 1 -> Up; 2 -> Down; 3 -> Left; 4 -> Right;
	for (int i = 0; i < 2; i++)
	{
		simplify(x, 4, Row, Col);

		printMap(x);
	}
	return 0;
	return 0;
}
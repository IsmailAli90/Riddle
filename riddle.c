//The following code is of Number Riddle game.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Show the board on the screen
void printTable(int rows, int cols, int table[rows][cols]);

// Randomly populate the array eFxcept the last element
void fillArray(int rows, int cols, int size, int table[rows][cols]);

// Generate a random number between min and max, inclusive.
int MyRand(int min, int max);

// Check if an element exists in the first couple of elements of an array
int exists( int rows,int cols,int limit, int num,int array[rows][cols]);
// Check if the move entered by a user is possible
int possibleMove(int rows, int cols, int move, int array[rows][cols]);
//swaps the elements of a two dimensional array
int swap(int row, int col, int move, int emptyPos,int array[row][col]);

int main() {

	puts("**************************");
	puts("******* Welcome to *******");
	puts("*** Number Riddle Game ***");
	puts("******** Ver. 1.0 ********");
	puts("******* Student *******");
	puts("****** Ismail Ali *******");
	puts("");

	srand(time(NULL));

	do {

		// Variables for number of rows and columns
		int row, col;

		// Get the number of rows and columns from the user
		do {
			printf("Enter number of rows (3 - 8):\n");
			scanf("%d",&row);
		} while (row <3 || row > 8);

		do {
			printf("Enter number of columns (3 - 8):\n");
			scanf("%d",&col);
		} while (col < 3 || col > 8);

		// Create a two-dimensional array for the game board, and initialize the elements with zero
		int p[row][col];
		for (int i = 0; i < row; i++) {
            for(int j=0;j<col;j++){
                p[i][j]=0;
            }
		}

		// Generate random numbers and put in the board cells
		fillArray(row,col,row*col,p);

		// Randomize the location of the empty cell
		int i = rand() % (row*col-1);

		int emptyPosition = i;//position of the empty cell
		int emptyRow;//row of the empty cell
		int emptyCol;//column of the empty cell
		int count=0;
		for (int i = 0; i < row; i++) {
            for(int j=0;j<col;j++){
                if(emptyPosition==count){//goes through the array until it reaches the empty cell
                    p[row-1][col-1]=p[i][j];//sets the previous empty position to the value the next empty psoition will have
                    p[i][j]=0;//sets the empty position to 0
                    emptyRow=i;//gets the row of empty position
                    emptyCol=j;//gets the column of empty position
                }
                count+=1;//increases once it goes through the array
            }
		}

		puts("");

		// Show the board on the screen
		printTable(row, col,p);

		int won = 0;

		time_t start, end;		// Record the time taken in each round of play
		time(&start);
		int counter = 0;
		int gone;//checks if the player has moved
		// Loop for one game:
		do {

			// get the player's move
			int answer;
			do {

				printf("(#Move %d), Enter the number you want to move ( 0 to exit):\n", counter);
				scanf("%d",&answer);
				if (answer >= 0 && answer < row*col){
                    gone=0;

					break;
				}
				else
					printf("Invalid number.\n");
			} while (1);
			if (answer == 0) {
				break;
			}
            int canMove=possibleMove(row,col,answer,p);//check if can move
            if(canMove==1){//returns 1 if the player can move
			for (int i=0; i<row; i++) {

                for (int j=0; j<col; j++) {
				if (p[i][j] == answer) {
                    if(gone==0){


					// Check the validity of the movement

					int pRow=i;
					int pCol=j;

					for (int i = 0; i < row; i++) {
                        for(int j=0;j<col;j++){
                            if(emptyPosition==count && gone==0){
                                p[row-1][col-1]=p[i][j];
                                p[i][j]=0;
                                emptyRow=i;
                                emptyCol=j;

                            }

                        }
                    }
                    gone=1;//player has moved





					if (abs(pRow-emptyRow) + abs(pCol - emptyCol) == 1) {//if empty position is to the left,right,up or down of where the player is moving
						p[emptyRow][emptyCol] = p[i][j];//sets the empty cell to the number that the player is moving
						p[i][j] = 0;//sets the new empty cell
						emptyCol= j;
                        emptyRow=i;
						// Show the board on the screen
                        printTable(row, col,p);

						// Check if the game is over
						int check=0;

						for(int i=0;i<row;i++){
                            for(int j=0;j<col;j++){
                                if(i!=row-1 && j!=col-1){
                                if(p[i][j]!=check){
                                    break;
                                }
                                }
                                check+=1;
                            }
						}

                        counter++;

						// Game is over and the player wins
						if (i==row && j==col) {
							time(&end);
							double t = difftime(end,start);
							printf("Excellent!!! you solved it with %d guesses, in %3.0f seconds.\n",counter, t);
							won = 1;
							break;
						}
					}

					// Invalid movement
					else {
						printf("This cell can't move!\n");
					}


					break;
                    }
				}
                }
			}
            }

		} while (!won);

		// Ask the user to play again or not
		printf("To play again, enter 1:\n");
		int answer;
		scanf("%d",&answer);
		if (answer != 1) {
			break;
		}
	} while (1);

	printf("GoodBye!\n");

	return 0;

}

void printTable(int rows, int cols, int array[rows][cols]){
    //goes through the table and prints the table with "|" seperating the numbers
	for (int r = 0; r < rows; r++) {
		printf("| ");
		for (int c = 0; c < cols; c++) {
			if (array[r][c]==0) {
				printf("   | ");
			}
			else {
				printf("%2d | ", array[r][c]);
			}
		}
		puts("");
	}
}

void fillArray(int rows, int cols, int size, int array[rows][cols]){


	int a = 0;//used to check if random is already in array
	int count=0;
	int x=0;//used for position of the array
	int y=0;


	while(count<size-1){//ends once the whole array is filled

        int random =  MyRand(1, size-1);

        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(array[i][j]==random){//if the number is in array already
                    a=1;
                }
            }
        }
        if(a==0){//if number is not in array

            array[x][y]=random;
            count+=1;
            if(y==cols-1){//new row
                y=0;
                x+=1;
            }
            else{//not a new row
                y+=1;
            }

    }
        if(a==1){//resets value
            a=0;
        }

    }
}

int MyRand(int min, int max) {
    //gets a random number
	int range = max-min+ 1;

	return rand() % range + min;
}

int exists(int rows,int cols,int limit, int num,int array[rows][cols]) {
    //check if the number is in the array
	if (limit == 0){
		return 0;
	}

	for (int i = 0; i < rows; i++) {
        for(int j=0;j< cols;j++){
            if (num == array[i][j]) {

                return 1;
            }

        }
	}

	return 0;
}
int possibleMove(int rows, int cols, int move, int array[rows][cols]){
        //goes through array and checks if the number is in the array
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(array[i][j]==move){
                    return 1;
                }
            }
        }
        return 0;
}
int swap(int row, int col, int move,int emptyPos,int array[row][col]){
    //explained previously
    int pRow;
    int pCol;
    int count;
    int emptyRow;
    int emptyCol;
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
                if (array[i][j] == move) {
                    int pRow=i;
					int pCol=j;

					for (int i = 0; i < row; i++) {
                        for(int j=0;j<col;j++){
                            if(emptyPos==count ){
                                array[row-1][col-1]=array[i][j];
                                array[i][j]=0;
                                emptyRow=i;
                                emptyCol=j;

                            }
                            count+=1;

                        }
                    }

                    if (abs(pRow-emptyRow) + abs(pCol - emptyCol) == 1) {
						array[emptyRow][emptyCol] = array[i][j];
						array[i][j] = 0;
						emptyCol= j;
                        emptyRow=i;
                    }
        }
        }
}
    return 0;
}

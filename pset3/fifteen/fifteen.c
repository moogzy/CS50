/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 * 
 * Author: Adrian Arumugam(apa@moogzy.net)
 * Date: 2016-12-13
 * 
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// Maintain location of the blank space
int zero_row;
int zero_col;

// prototypes
void clear(void);
void greet(void);
void init(int arr_size, int row_size);
void draw(int row_size, int *zero_row, int *zero_col);
bool move(int tile, int max_tiles, int row_size, int *zero_row, int *zero_col);
bool won(int row_size, int max_tiles);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // Define the num of tiles in the array.
    int max_tiles = (d * d) - 1;
    
    //Define the num of tiles in a row.
    int row_size = d;
    
    // greet user with instructions
    greet();

    // initialize the board
    init(max_tiles, row_size);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(row_size, &zero_row, &zero_col);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won(row_size, max_tiles))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile, max_tiles, row_size, &zero_row, &zero_col))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(int arr_size, int row_size)
{
    bool odd = false;
    int value;
    
    // Determine if the array size is odd
    //
    // If yes then set odd == true for later use.
    // This assists in determining whether 1 & 2 tiles
    // should be switched around in their starting positions.
    if ((arr_size % 2) != 0)
    {
        odd = true;
    }
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < row_size; j++)
        {
            value = arr_size--;
            
            // Manipulate tile 1 & 2 based on even or odd
            // array.
            if (value == 1 && odd == true)
            {
                value++; // 1 becomes 2 if odd numbered array.
            }
            else if (value == 2 && odd == true)
            {
                value--; // 2 becomes 1 if odd numbered array.
            }
            board[i][j] = value;
        }
    }
}

/**
 * Prints the board in its current state.
 * 
 * Iterate through the 2D array printing each value
 * along the way.
 * 
 * Pass in use pointer references for zero_row and zero_col to keep track of the blank space(0) array position.
 */
void draw(int row_size, int *zero_row, int *zero_col)
{
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < row_size; j++)
        {
            // We don't want to print '0' if we come across it
            // store the item as '0' but print out '_' to represent it.
            //
            // Store the row & column location of '_' so we can use it
            // when moving tiles in move().
            if (board[i][j] == 0)
            {
                printf("%3s", "_");
                *zero_row = i;
                *zero_col = j;
            }
            else
            {
                // Print out values as we iterate through the array.
                printf("%3i", board[i][j]);                
            }

        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 * 
 */
bool move(int tile, int max_tiles, int row_size, int *zero_row, int *zero_col)
{
    int tile_row;
    int tile_col;
    
    // Data validation of the tile to be moved to ensure it is within the required range
    if (tile > 0 && tile <= max_tiles)
    {
        // Loop through all elements to find the given tile.
        //
        // Record the array location in tile_row,tile_col.
        for (int i = 0; i < row_size; i++)
        {
            for (int j = 0; j < row_size; j++)
            {
                if (board[i][j] == tile)
                {
                    tile_row = i;
                    tile_col = j;
                }
            }
        }
        // If the tile to be moved is one row away(+1 or -1) and in the same column or one column away(+1 or -1) 
        // and in the same row from the blank space tile then this consitutes a valid move. Swap the tile to be moved 
        // with the blank space tile in the 2D array.
        //
        // Example: tile = 7 the current location of 7 in the array is 0,1.
        //          blank_space tile(0) current location is 1,1.
        //          
        //          7 = board[0][1]
        //          0 = board[1][1]
        //          * This is a valid move as 7 is -1 row away from the blank space and in the same column.
        //
        // All other moves are invalid as they aren't bordering blank space.
        if (((tile_row == (*zero_row - 1) || tile_row == (*zero_row + 1)) && tile_col == *zero_col) || 
           (tile_row == *zero_row && (tile_col == (*zero_col - 1) || tile_col == (*zero_col + 1))))
        {
            int tile_val = board[tile_row][tile_col]; // temporary variable to facilitate a clean swap of the tiles in the array.
            board[tile_row][tile_col] = board[*zero_row][*zero_col];
            board[*zero_row][*zero_col] = tile_val;
            return true;
        }
        else
        {
            // Return false if tile is valid but the move is invalid.
            return false;
        }
        
    }
    else
    {   // Return false if the tile is invalid.
        return false;
    }
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int row_size, int max_tiles)
{
    int counter = 1;
    bool win = false;
    
    // Iterate through 2D array. If the array is sorted that means we've reached a
    // winning configuration.
    //
    // This means each element in the array is equal to the counter variable.
    // EXCEPT the final element which should be 0.
    //
    // If we reach counter == max_tiles + 1 then we have a complete sorted array and
    // the final element should be '0'. If so then set win = true.
    //
    // Otherwise win = false and we break from the loop.
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < row_size; j++)
        {
            if (board[i][j] == counter)
            {
                counter++;
            }
            else if ((counter == max_tiles + 1) && (board[i][j] == 0))
            {
                win = true;
            }
            else
            {
               win = false;
               break;
            }
        }
    }
    
    // If win == true then return true as we reached a winning configuration
    // for the fifteen board.
    //
    // Otherwise return false and we continue on we moving tiles.
    if (win)
    {
        return true;
    }
    else
    {
        return false;
    }
}
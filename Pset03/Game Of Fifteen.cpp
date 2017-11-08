/**
 * fifteen.c
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


// prototypes
void clear(void);
void greet(void);
void init(const int d , int board[][d]);
void draw(const int d , int board[][d]);
bool move(int tile , const int d , int board[][d]);
bool won(const int d , int board[][d]);
void swap(int *a, int *b);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }
    

    // dimensions
    int d;

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // board
    int board[d][d];


    // initialize the board
    init(d,board);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(d , board);

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
        if (won(d , board))
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
        if (!move(tile , d ,board))
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
void init(const int d , int board[][d])
{
    int inject = d*d-1;
    for(int r = 0 ; r < d ; r++)
    {
        for(int c = 0 ; c < d ; c++)
        {
            board[r][c]=inject;
            inject--;
        }
    }

    if(d%2==0) swap(&board[d-1][d-2], &board[d-1][d-3]);

}

void swap(int *a , int *b)
{
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}
/**
 * Prints the board in its current state.
 */
void draw(const int d , int board[][d])
{
    for (int r = 0 ; r < d ; r ++)
    {
        for (int c = 0 ; c < d ; c++)
        {
            if(board[r][c])
            printf("%2d ",board[r][c]);
            else
            printf("   ");
        }
        printf("\n");
    }

}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool IsInBoard(int r , int c , int d)
{
    if(r<d && r >= 0 && c < d && c >=0) return true;
    return false;
}
int tileIndex (int tile , const int d , int board[][d])
{
    int TD =0;
    for(int r = 0 ; r < d ; r++)
    {
        for(int c = 0 ; c < d ; c++)
        {
            TD++;
            if(board[r][c]==tile) return TD;
        }
    }
    return TD;
}
bool move(int tile , const int d , int board[][d])
{
    int indexInFlattened = tileIndex(tile,d,board);
    int r = (indexInFlattened-1)/d;
    int c = (indexInFlattened-1)%d;
    if( IsInBoard(r+1,c,d) && board[r+1][c]==0 ) {swap(&board[r][c],&board[r+1][c]);return 1;}
    else if( IsInBoard(r-1,c,d) && board[r-1][c]==0) {swap(&board[r][c],&board[r-1][c]);return 1;}
    else if( IsInBoard(r,c+1,d) && board[r][c+1]==0) {swap(&board[r][c],&board[r][c+1]);return 1;}
    else if( IsInBoard(r,c-1,d) && board[r][c-1]==0) {swap(&board[r][c],&board[r][c-1]);return 1;}
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(const int d , int board[][d])
{
    int ci = 1;
    for (int r = 0 ; r < d ; r++)
    {
        for (int c = 0 ; c < d ; c++ , ci==d*d ? ci=0 : ci)
        {
            if(board[r][c]!=ci++) return 0;
        }
    }

    return 1;
}

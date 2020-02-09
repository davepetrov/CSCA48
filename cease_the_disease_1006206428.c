#include <stdbool.h>            // Note this is needed to use the bool type
#include <stdio.h>

#define TISSUE_SIZE (10)                    

// We are going to take advantage of the 'typedef' keyword - it can be used to make
// a nickname for any data type, not just compound data types as we have been doing
// in lecture. For this exercise, we're going to be dealing with 2D arrays that contain
// different symbols, we will create a convenient nickname for these 2D arrays.
// The typedef below creates an alias 'Tissue' for a char array of size [TISSUE_SIZE][TISSUE_SIZE].
// Thereafter, we can do this:
//
//   Tissue  one_tissue;
//
// and this is equivalent to:
//
//   char one_tissue[TISSUE_SIZE][TISSUE_SIZE];
//
typedef char Tissue[TISSUE_SIZE][TISSUE_SIZE];  // The syntax is kind of funky, but that's just a
                                                // quirk of C, nothing to worry yourself about :)

/**
 * Return true iff there exists a Leo coli within tissue_sample that can attack position x, y.
 *
 * Legal moves are limited to the pattern (where X is a legal move and L is the bacterium):
 *      X _ X _ X
 *      _ _ _ _ _
 *      X _ L _ X
 *      _ _ _ _ _
 *      X _ X _ X
 *
 * INPUT:
 *  tissue_sample:
 *      - an array of arrays of characters with dimensions TISSUE_SIZE * TISSUE_SIZE
 *      - gives positions of each bacterium and each infected cell
 *      - each cell can only contain one of the following types:
 *          - `I`: Infected Cell
 *          - `L`: A Leo coli bacterium
 *          - `W`: A Willmonella bacterium
 *          - `_`: An uninfected cell (bacteria will ignore these)
 *  x:  the row coordinate (starting at 0) of the cell (within tissue_sample) to be checked.
 *  y:  the column coordinate (starting at 0) of the cell (within tissue_sample) to be checked.
 *
 * RETURN:
 *  true, if there exists some Leo coli that can make a legal move to position x, y
 *  false, if no Leo coli can make a legal move to position x, y
 */
bool canLeoEat(Tissue tissue_sample, int x, int y){
    int x_eat[1024], y_eat[1024], count=0;
    int x_offset[8]={-2,0,2,2,2,0,-2,-2};
    int y_offset[8]={-2,-2,-2,0,2,2,2,0};
    for (int row=0; row<TISSUE_SIZE; row++){
        for (int col=0; col<TISSUE_SIZE; col++){
            if (tissue_sample[row][col] == 'L'){
                //printf("NEW L(%d, %d)\n", col,row);
                for (int k=0; k<8 ;k++){
                    y_eat[count]=row+y_offset[k];
                    x_eat[count]=col+x_offset[k];
                    count++;
                }
            }
        }

    }
    //printf("-L-\n");
    for (int i=0; i<=count; i++){
        //printf("(%d, %d) | [%d,%d]\n",x_eat[i]+1,y_eat[i]+1, x+1,y+1);
        if (x_eat[i]==x && y_eat[i]==y){
            return true;
        }
    }
 
    return false;  
}
bool canWillEat(Tissue tissue_sample, int x, int y){
    int x_eat[1024], y_eat[1024], count = 0;
    int x_offset[20]={-1,0,1,0,0,       1,2,3,3,3,    0,0,0,-1,1,  -1,-2,-3,-3,-3};
    int y_offset[20]={-3,-3,-3,-2,-1,   0,0,-1,0,1,   1,2,3,3,3,   0,0,0,-1,1};
    for (int row=0; row<TISSUE_SIZE; row++){
        for (int col=0; col<TISSUE_SIZE; col++){
            if (tissue_sample[row][col] == 'W'){
                for (int k=0; k<20 ;k++){
                    y_eat[count]=row+y_offset[k];
                    x_eat[count]=col+x_offset[k];
                    count++;
                }
            }
        }

    }
    //printf("-W-\n");
    for (int i=0; i<=count; i++){
        //printf("(%d, %d) | [%d,%d]\n",x_eat[i]+1,y_eat[i]+1, x+1,y+1);
        if (y_eat[i]==y && x_eat[i]==x){
            return true;
        }
    }
    return false;  
}

int percentKilled(Tissue tissue_sample){
    float total = 0, ate=0;
    for (int row=0; row<TISSUE_SIZE; row++){
        for (int col=0; col<TISSUE_SIZE; col++){
            if (tissue_sample[row][col]=='I'){
                total++;
                //printf("\nI: [%d, %d]\n", col+1, row+1);
                if (canLeoEat(tissue_sample,col,row) || (canWillEat(tissue_sample,col,row))){
                    //printf("(%d, %d): Eaten by L\n",col+1,row+1);
                    ate++;
                }
            }
        }
    }
    //return rounded product
    if (((ate/total)*100 - (int)(ate/total*100)>=0.5))  return (int)(ate/total*100) + 1;
    else return (int)(ate/total*100);
}

void printTissueSample(Tissue tissue_sample)
{
    printf("   A B C D E F G H I J\n");
    for (int x = 0; x < TISSUE_SIZE; x++)
    {
        printf("%2d ", x + 1);
        for (int y = 0; y < TISSUE_SIZE; y++) printf("%c ", tissue_sample[x][y]);
        printf("\n");
    }
}

#ifndef __TESTING  // this compiler directive
int main()
{
    printf("====Deep's Sample====\n");
    Tissue deep_sample = {{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', 'L', '_', 'I', '_', '_', '_'},
                          {'_', '_', '_', '_', 'I', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', 'I', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', 'W', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
                          {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'}};
    printTissueSample(deep_sample);
    printf("Calculated: Killed %03d%% of bacteria\n", percentKilled(deep_sample));
    printf("  Expected: Killed 067%% of bacteria\n");

    // Feel free to add your own examples/tests here
    printf("====Donnie's Sample====\n");

    char donnie_sample[TISSUE_SIZE][TISSUE_SIZE] = {
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', 'I', '_'},
        {'_', '_', '_', '_', '_', 'I', '_', '_', 'I', '_'},
        {'_', '_', '_', '_', '_', '_', '_', '_', '_', 'I'},
        {'_', '_', '_', 'I', '_', '_', '_', '_', 'I', 'W'},
        {'_', '_', '_', 'I', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', 'L', '_', '_', '_', '_', 'L', '_'},
        {'_', '_', '_', '_', '_', '_', '_', 'I', 'I', 'I'},
        {'_', '_', '_', '_', '_', '_', '_', '_', 'I', '_'}};
    printTissueSample(donnie_sample);
    printf("Calculated: Killed %03d%% of bacteria\n", percentKilled(donnie_sample));
    printf("  Expected: Killed 064%% of bacteria\n");
}
#endif  // and this compiler directive

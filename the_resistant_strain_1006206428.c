/*  CSC A48 - Winter 2020
*
*   Exercise 6 - The Resistant Strain
*
*   Please read the comments below carefully, they
*  describe your task in detail. Any clarifications
*  and corrections will be posted to Piazza so please
*  keep an eye on the forum!
*
*  Starter code: Joe Armitage & William Song, 2020
*/


#include <stdio.h>
#include <math.h>

#define TISSUE_SIZE (10)

typedef enum tissueType
{
    _ = '_',  // Uninfected cell
    I = 'I',  // Infected cell
    S = 'S',  // Good bacterium: Sakinacoccus
    C = 'C',  // Good bacterium: Charlestridium tetani
} TissueType;

typedef struct cell
{
    TissueType type;  // Indicates if good bacterium, infected cell or uninfected cell
    int health;  // For good bacteria: the multiple the range is extended by, for infected cells,
                 // number of lives
} Cell;

typedef Cell Tissue[TISSUE_SIZE][TISSUE_SIZE];  // A nice name for a 2D Cell array -> Tissue
typedef int Pattern[2];

/**
 * CRUNCHY: Use this helper helper function to implement Charles AND Sakina
 * HINT: I would implement numberOfCharlesInRange like this:
 *      Pattern charles_patterns[4] = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
 *      return numberOfBacteriaInRange(tissue_sample, x, y, charles_patterns, 4, C);
 */

int numberOfBacteriaInRange(Tissue tissue, int x, int y, Pattern pattern[], int num_patterns,
                            TissueType type){
    int counter = 0;
    int range;
    for (int row=0; row<TISSUE_SIZE; row++){
        for (int col=0; col<TISSUE_SIZE; col++){
            if (tissue[row][col].type==type){
                range=tissue[row][col].health;
                for (int i=1; i<=range; i++){
                    for (int offset=0; offset<num_patterns; offset++){
                        if ((row+(pattern[offset][0]*i)==y) && (col+(pattern[offset][1]*i)==x)){
                            counter++;
                        }
                    }
                }
            }
        }
    }
    return counter;
}

int numberOfCharlesInRange(Tissue tissue_sample, int x, int y){
   Pattern charles_patterns[4] = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
   return numberOfBacteriaInRange(tissue_sample, x, y, charles_patterns, 4, C);
}

int numberOfSakinaInRange(Tissue tissue_sample, int x, int y){
    Pattern sakina_patterns[4] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    return numberOfBacteriaInRange(tissue_sample, x, y, sakina_patterns, 4, S);
}

/**
 * Computes the percentage of infected cells in the given tissue sample which can be killed
 * by Sakinacoccus or Charlestridium tetani bacteria in the sample and updates the tissue sample to
 * the state after the attacks.
 *
 * INPUT:
 *  tissue_sample:
 *      - an array of arrays of Cells with dimensions TISSUE_SIZE * TISSUE_SIZE
 *      - gives positions of each bacterium and each infected cell
 *      - each cell can only contain one of the following types:
 *          - `I`: Infected Cell
 *          - `C`: A Charlestridium tetani bacterium
 *          - `S`: A Sakinacoccus bacterium
 *          - `_`: An uninfected cell (bacteria will ignore these)
 *      - REQ: there is at least one infected cell
 *
 * OUTPUT:
 *  tissue_sample: - mutated such that:
 *      - All `I` cells have their health reduced by the number of good bacteria that can attack.
 *      - Any `I` cell whose health drops to <= 0 is replaced by a `_` cell, with 0 health.
 *
 * RETURN:
 *  The percentage of infected cells that are killed by the good bacteria (Sakinacoccus and
 * Charlestridium tetani).
 */
double testBacteria(Tissue tissue_sample)
{
    int kills;
    float deaths = 0, total = 0;
    for (int row=0; row<TISSUE_SIZE; row++){
        for (int col=0; col<TISSUE_SIZE; col++){
            if (tissue_sample[row][col].type==I){ // CURRENTLY LOOKING FOR Infected Cells
                total++;
                kills = numberOfSakinaInRange(tissue_sample,col,row)+numberOfCharlesInRange(tissue_sample, col,row);
                tissue_sample[row][col].health-=kills;
                if (tissue_sample[row][col].health <=0){
                    tissue_sample[row][col].type=_;
                    deaths++;
                }
            }
        }
    }
    return deaths/total*100;
}

/**
 * Prints the tissue sample in a human readable format.
 *
 * INPUT:
 *  tissue_sample:
 *      - an array of arrays of Cells with dimensions TISSUE_SIZE * TISSUE_SIZE
 *      - gives positions of each bacterium and each infected cell
 *      - each cell can only contain one of the following types:
 *          - `I`: Infected Cell
 *          - `C`: A Charlestridium tetani bacterium
 *          - `S`: A Sakinacoccus bacterium
 *          - `_`: An uninfected cell (bacteria will ignore these)
 *
 * NOTE: The displayed indices do not match the implementation.
 * That is, they start at 1 (when we know array indices start at 0).
 * This is more obvious for the column indices, which are A - J.
 */
void printTissueSample(Tissue tissue_sample)
{
    printf("   A B C D E F G H I J\n");
    for (int x = 0; x < TISSUE_SIZE; x++)
    {
        printf("%2d ", x + 1);
        for (int y = 0; y < TISSUE_SIZE; y++) printf("%c ", tissue_sample[x][y].type);
        printf("\n");
    }
}

#ifndef __TESTING  // this compiler directive
int main()
{
    printf("====Jackson's Sample====\n");
    Tissue jackson_sample = {
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {C, 1}, {_, 0}, {I, 1}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 3}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 2}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {S, 2}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}}};
    printTissueSample(jackson_sample);
    printf("Calculated: Killed %06.2f%% of bacteria\n", testBacteria(jackson_sample));
    printf("  Expected: Killed 066.67%% of bacteria\n");
    printTissueSample(jackson_sample);
    
    printf("====Silviu's Sample====\n");
    Tissue silviu_sample = {
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 1}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 1}, {_, 0}, {_, 0}, {I, 1}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 1}},
        {{_, 0}, {_, 0}, {_, 0}, {I, 1}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 1}, {S, 2}},
        {{_, 0}, {_, 0}, {_, 0}, {I, 1}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {C, 3}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {C, 2}, {_, 0}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 1}, {I, 1}, {I, 1}},
        {{_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {_, 0}, {I, 1}, {_, 0}}};
    printTissueSample(silviu_sample);
    printf("Calculated: Killed %06.2f%% of bacteria\n", testBacteria(silviu_sample));
    printf("  Expected: Killed 036.36%% of bacteria\n");
    printTissueSample(silviu_sample);
}
#endif

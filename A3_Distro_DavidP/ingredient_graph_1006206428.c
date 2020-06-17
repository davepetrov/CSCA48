/* 
 * CSC A48 - Assignment 3 - Ingredient networks
 * 
 * In this assignment, you will practice and strengthen your
 * understanding of graph and recursion. The application 
 * you're working on is a simple network for studying
 * how food ingredients interact. 
 * 
 * This kind of network is the basic model that very
 * powerful systems such as IMB's Watson use as the 
 * basis for creating new combinations of ingredients
 * that are likely to go well together, but haven't been
 * used in previously printed recipes.
 * 
 * Your work here has several components:
 * 
 * - Understanding how the graph is represented by an
 *   adjacency matrix.
 * - Using the adjacency matrix to figure out, given
 *   an input ingredient, what other ingredients it is
 *   related to directly
 * - Using the adjacency matrix to determine, given
 *   a specific ingredient, which others are related
 *   to it directly *and* indirectly by a distance 
 *   of k hops along the graph (k>=1).
 * - Get lists of ingredients that are related, but
 *   not including ingredients from a separate
 *   list of ingredients
 * - *crunchy* Using the adjacency matrix that, given
 *   a recipe (which a list of ingredients) and 
 *   a target ingredient (part of the recipe) to
 *   replace, finds the best replacement from the
 *   remaining ingredients in the graph and updates
 *   the recipe.
 * 
 * This file contains the functions that set up
 * the adjacency matrix and the list of ingredients
 * for you. We provide you with 2 graphs, a 
 * small one with 10 ingredients (an adjacency
 * matrix of size 10x10), and a full one with 
 * 400 ingredients (adjacency matrix of size 400x400).
 * 
 * Use the 10x10 while implementing and testing your
 * solution, and only move to the full-size one once
 * you're confident your code works well.
 * 
 * Select which matrix to use by uncommenting the
 * respective #define statement below.
 * 
 * (c) F. Estrada, March 2019
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STR_LEN 1024
#ifndef __testing
//#define MAT_SIZE 10	// Use the small graph
#define MAT_SIZE 400	// Use full-size graph
#endif

// The following are GLOBAL variables you can use
// anywhere in your code. They include the 
// adjacency matrix, as well as an array of strings
// to store the ingredient names.
double AdjMat[MAT_SIZE][MAT_SIZE];
char ingredients[MAT_SIZE][MAX_STR_LEN];

// Bare-bones implementation of a linked-list of
// integers, you can use it to return the ingredient
// lists requested from functions you have to
// implement. DO NOT CHANGE THE IMPLEMENTATION
// OF THE LINKED LISTS.

typedef struct intNode_struct{
    int  x;
    struct intNode_struct *next;
} intNode;

intNode *insertInt(intNode *h, int x){
  // Inserts the int 'x' into the linked list 
  // whose head is at the address in 'h'
  
  intNode *newNode;
  
  newNode=(intNode *)calloc(1,sizeof(intNode));
  newNode->x=x;
  newNode->next=NULL;
  
  if (h!=NULL)
    newNode->next=h;
  
  return newNode;
}

int searchInt(intNode *h, int x){
  // Search the linked list for the value 'x', if
  // found, it returns 1, else it returns 0
  while (h!=NULL)
  {
    if (h->x==x) return 1;
    h=h->next;
  }
  return 0;
}

intNode *deleteList(intNode *h){
  // Delete list and free memory
  intNode *q;
  if (h==NULL) return NULL;
  
  while (h!=NULL)
  {
     q=h->next;
     free(h);
     h=q;
  }
  
  return NULL;
}

// Read the adjacency matrix from file, and read the ingredient
// names
void load_ingredients(void)
{
  // Loads the adjacency matrix and ingredients list from file,
  // N must be either 10 (small graph), or 400 (full-size).
  
  FILE *f;
  int n=MAT_SIZE;
  
  if (n==10) f=fopen("AdjMat_small.dat","rb");
  else f=fopen("AdjMat_full.dat","rb");
  if (f==NULL)
  {
    printf("Can not open file with adjacency matrix. Please make sure it's in this directory\n");
    return;
  }
  fread(&AdjMat[0][0],n*n*sizeof(double),1,f);
  fclose(f);
  printf("   ");
  for (int i=0; i<MAT_SIZE; i++){
    printf("%d     ",i);
} 
printf("\n");
  for (int i=0; i<MAT_SIZE; i++)
  {
    printf("%d: ", i);
    for (int j=0; j<MAT_SIZE; j++)
      printf("%2.2lf, ",AdjMat[i][j]);
    printf("\n");
  }
  
  
  if (n==10) f=fopen("Ingredient_names_small.txt","r");
  else f=fopen("Ingredient_names_full.txt","r");
  if (f==NULL)
  {
    printf("Can not open file with ingredient names. Please make sure it's in this directory\n");
    return;
  }
  printf("Reading ingredient names. Available ingredient are:\n");
  for (int i=0; i<n; i++)
  {
    fgets(&ingredients[i][0],MAX_STR_LEN,f);
    for (int j=0; j<strlen(ingredients[i]); j++)
      if (ingredients[i][j]==10||ingredients[i][j]==13) ingredients[i][j]=0;
    printf("%s\n",ingredients[i]);
  }
  fclose(f);
}

/***************************************************************
 * The part of the assignment you need to implement starts below
 ***************************************************************/

void print_ingredients(intNode *h){
    /*
     * This function prints out all the ingredients corresponding
     * to the ingredient indexes stored in the linked list
     * whose head is 'h'.
     */
  
  if (h==NULL)return;
  printf("%s\n",ingredients[h->x]); //in order
  print_ingredients(h->next);
  
}

int find_index_recursive(char source_ingredient[MAX_STR_LEN], int i){
  if (strcmp(ingredients[i],source_ingredient)==0)
    return i;
  
  if (i==MAT_SIZE)
    return -1;
  
  return find_index_recursive(source_ingredient,i+1);
}
int ingredient_index(char source_ingredient[MAX_STR_LEN]){
    /*
     * This function looks into the array with ingredient
     * names for one that matches the requested 
     * 'source_ingredient'. If a match is found, it
     * returns the index at which the matching ingredient
     * name was found.
     * 
     * If the 'source_ingredient' is *not* in the ingredients
     * array, the function returns -1
     */
    
  return find_index_recursive(source_ingredient, 0);
}



void related_ingredients(char source_ingredient[MAX_STR_LEN]){
    /*
     * This function prints out all the ingredients related
     * to the source ingredient. 
     * 
     * One per line, with no additional characters or symbols.
     *
     * Format of the adjacency matrix:
     * 
     * AdjMat[i][j] = 0 if two ingredients i and j are not directly linked
     *                (no edge in the graph between them, this means
     *                 they never appeared together in one recipe)
     * AdjMat[i][j] > 0 if two ingredients i and j are neighbours (they
     * 			appeared together in at least a recipe). The
     * 			actual value indicates how many times these two
     * 			ingredients appeared together in a recipe
     * 
     * Make sure you understand what this is telling you about the
     * ingredients in your graph. You'll need it later
     */
    
  int source_i = ingredient_index(source_ingredient);
  for (int row=0; row<MAT_SIZE; row++){
    if (AdjMat[row][source_i]>0){
      printf("%s\n", ingredients[row]);
    }
  }
}




intNode *related_k_dist(intNode *h, char source_ingredient[MAX_STR_LEN], int k, int dist)
{
    /*
     * This function determines the ingredients related to the
     * specified source ingredient by a distance of at most k.
     * k >= 1
     * 
     * For instance, if k=1, the list should contain all the
     * ingredients who are neighbours of source_ingredient[]
     * as well as the ingredients that are neighbours of
     * the neighbours (distance=2).
     * 
     * If k=2, then we want source_ingredients' neighbours, its
     * neighbours' neighbours, and its neighbours' neighbours'
     * neighbours. And so on.
     * 
     * Obviously, you'll have to employ recursion carefully.
     * 
     * Ingredients are returned as *indexes*, so, for instance,
     * if we find a related ingredient 'chicken' is stored at
     * index 7 in ingredients[][], then we store 7 in the
     * linked list of related ingredients.
     * 
     * The returned list MUST CONTAIN NO DUPLICATES.
     * 
     * And be smart about it, or you'll end up in an infinite
     * recursion! So think carefully about the base case(s)
     * and about what the recursive case must do.
     *
     * Example call:
     * 
     * Our test code may call your function in this way:
     * 
     * intNode *head=NULL;
     * head=related_k_dist(head,"rice",2,0);
     * 
     * After that call, 'head' must point to a linked list with
     * all the ingredients related to 'rice' up to a distance of
     * 2 away.
     * 
     * It's up to *you* to figure out what the 'dist' parameter
     * is for!
     * 
     */
  if(dist==k+1){
    return h;
  }

  int source_i = ingredient_index(source_ingredient);

  for (int row=0; row<MAT_SIZE; row++){
    if (AdjMat[row][source_i]>0 && row!=source_i){
      h = related_k_dist(h, ingredients[row], k, dist+1);

      if (!searchInt(h,row)){ // not found
        h=insertInt(h,row);
      }
    }
  }
  return h;
}

intNode *findInt(int n, intNode *head){
    intNode *p = head;

    while (p != NULL){
        if (p->x == n){
            return p;
        }
        p = p->next;
    }
    return p;
}
int countNodes(intNode *head){
    intNode *p = head;
    int count = 0;
    while (p!= NULL){    
        p = p->next; 
        count++;
    }
    return count;
}

intNode *related_with_restrictions(char source_ingredient[MAX_STR_LEN], char avoid[MAX_STR_LEN], int k_source, int k_avoid)
{
  /*
    * This function returns a linked list that contains the indexes of
    * all ingredients related to source_ingredient[] with a distance
    * of at most k_source.
    * 
    * BUT, the list *must not contain* any ingredients related to avoid[]
    * (including avoid[] itself) by a distance of up to k_avoid.
    * 
    * Example:
    * 
    * intNode *head=NULL;
    * head=related_with_avoidance("rice", "nuts", 2, 0);
    * 
    * Should return a list of ingredients related to 'rice' by a distance 
    * of up to 2, NOT INCLUDING 'nuts'.
    * 
    * intNode *head=NULL;
    * head=related_with_avoidance("rice", "chicken", 2, 1);
    * 
    * Should return a list of ingredients related to 'rice' by a distance
    * of up to 2, NOT INCLUDING 'chicken' and any ingredients related
    * to 'chicken' with a distance of up to 1.
    * 
    */
  


  intNode *main_h = related_k_dist(NULL, source_ingredient, k_source, 0);
  intNode *avoid_h = related_k_dist(NULL, avoid, k_avoid, 0);
  intNode *p = main_h;
  intNode *return_h = NULL;

  while (p!=NULL){
    // Ensure the return LL includes all the wanted values
    if (!searchInt(avoid_h, p->x) && strcmp(ingredients[p->x], avoid)){
      return_h = insertInt(return_h, p->x);
    }
    p = p->next;
  }
  return return_h;
}



int isIntIn(int array[10], int n, int len){
  for (int i=0 ; i<len; i++){
    if (n == array[i]) return 1;
  }
  return 0;
}

void substitute_ingredient(char recipe[10][MAX_STR_LEN], char to_change[MAX_STR_LEN])
{
  /*
   * *CRUNCHY!*
   * 
   * This function takes a recipe (which is an array of ingredients with up to 10
   * ingredients), and replaces the one in 'to_change' by *the most compatible
   * ingredient from the graph*
   * 
   * By most compatible, we mean the ingredient that appears most often with 
   * the remaining ingredients in the recipe.
   * 
   * The definition above may seem fuzzy, but it's not if you consider that the
   * weights in the adjacency matrix are meaningful.
   * 
   * As you see, nothing is returned - the result of this function is that the
   * ingredient 'to_change' is replaced in the recipe by the most compatible
   * ingredient given the graph that is *not already in the recipe*.
   * 
   * Assume that the input recipe is such that *all ingredients are in the
   * array of ingredients* (i.e. you don't have to worry about ingredients
   * that don't exists).
   * 
   * However, the recipe *may have less than 10 ingredients*, in which case
   * unused ingredients will be set to empty strings ("")
   */

  int recipe_indexes[10];
  char candidates[MAT_SIZE][MAX_STR_LEN]; // Candidates [names]
  double points[MAT_SIZE]; // Candidates points
  int candidates_total=0;
  int recipe_len=0;
  int replace_i=-1;
  int current_recipe_index;
  int to_change_i = ingredient_index(to_change);

  // Get len of recipe and the index of to_change in recipe 
  while (recipe_len<10 && strlen(recipe[recipe_len])>0){
    current_recipe_index=ingredient_index(recipe[recipe_len]);
    recipe_indexes[recipe_len] = current_recipe_index;

    if (current_recipe_index == to_change_i){
      replace_i=recipe_len;
    }
    recipe_len++;
  }

  for (int i=0; i<MAT_SIZE; i++){
    if (!isIntIn(recipe_indexes, i, recipe_len)){
      //Not in the recipe -> possible candidate
      for (int k=0; k<MAT_SIZE; k++){
        if (k != ingredient_index(recipe[replace_i]) && isIntIn(recipe_indexes,k , recipe_len)){
          //Better candidate! add to candidates and increase points based on weight
          points[candidates_total]+=AdjMat[k][i];         
        }
      }
      strcpy(candidates[candidates_total], ingredients[i]);
      candidates_total++;
    }
  }

  //Pick best candidate
  double max=0;
  int max_i;
  for (int i = 0; i<candidates_total; i++){
    if (points[i]>=max){
      max_i = i;
      max=points[i];
    }
  }
  
  if (candidates_total>0 && replace_i!=-1){   //Note: If replace_i == -1 -> The "avoiding" ingredient is not in recipe
    strcpy(recipe[replace_i], candidates[max_i]);
  }

  //DO NOT replace any ingredient in the recuipe if no candidate is found for this particular "avoiding" ingredient




}


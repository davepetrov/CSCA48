#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // You can use the string library!

// The values for the constants below could change, so make sure your
// program is using them where appropriate!
#define MAX_STRING_LENGTH 128
#define MAX_ROW_COUNT 100
#define DELIMITER ','

/**
 * Joins two tables (produces a larger table with combined information from both).
 * Note that the input tables each have fields (chunks of test) separated by 'DELIMITER'. 
 * The first field in each table is a person's name (see the example tables in main())
 * and the second field records appropriate information for the corresponding individual.
 *
 * This function will create a combined (joined) table such that the first field is the
 * person's name, the second is the nationality (from the nationality table), and the
 * third is their favorite food (from the food table).
 *
 * This requires you to *match* the person's name in the two tables, and to do a bit 
 * of string manipulation to build the combined row containing name, nationality, food,
 * and then putting that joined result into the joined table.
 *
 * Your joined table must not contain any rows from either table for which there is no
 * corresponding row in the other table (e.g. in the sample input from main(),
 * 'Nyah Way' appears only on the nationality table, and not in the food table, so there
 * will NOT be any rows in the joined table for this individual.
 *
 * Person's names in the first field must be *unique* within each table (e.g. 'Paco Estrada'
 * can only appear once in the nationality table, and only once in the food table).
 * But 'Paco Estrada' is not the same name as 'paco estradA' (these are considered 
 * different people).
 *
 * INPUT:
 *  nationalities_table:
 *      - an array of strings, each string has 2 DELIMITER-separated columns
 *      - represents Name -> Nationality mappings
 *  foods_table:
 *      - an array of strings, each string has 2 DELIMITER-separated columns
 *      - represents Name -> Favourite Food mappings
 *
 * OUTPUT:
 *  joined_table:
 *      - an array of strings, each with 3 DELIMITER-separated columns
 *      - represents the combined information for a person: name, nationality, food
 *      - The ORDER of the rows in this output table does not matter, so don't worry
 *        about it, as long as the rows are all there that should be there.
 */

int get_row_len(char table[MAX_ROW_COUNT][MAX_STRING_LENGTH]){
    int size=0;
    while (strcmp(table[size],"")!=0){
        size++;
    }
    return size;
}

int index_first_delimeter(char string[MAX_STRING_LENGTH]){
    int index=0;
    while (string[index]!= DELIMITER){
        index++;
    }
    return index;
}

int min(int a, int b){
    if (a<b)return a;
    else if (a>b)return b;
    return a;
}
void innerJoin(char nationalities_table[MAX_ROW_COUNT][MAX_STRING_LENGTH],
               char foods_table[MAX_ROW_COUNT][MAX_STRING_LENGTH],
               char joined_table[MAX_ROW_COUNT][MAX_STRING_LENGTH * 2]){

    //Declarations
    int nationalities_rows=get_row_len(nationalities_table);
    int foods_rows=get_row_len(foods_table);
    char names_nationalities[MAX_ROW_COUNT][MAX_STRING_LENGTH];
    char names_foods[MAX_ROW_COUNT][MAX_STRING_LENGTH];
    char nats[MAX_ROW_COUNT][MAX_STRING_LENGTH];
    char foods[MAX_ROW_COUNT][MAX_STRING_LENGTH];
    int i, f, names_foods_num, names_nationalities_num, string_size;
    char current_row[MAX_STRING_LENGTH];

    int index_delimeter;

    //Seperate name from nationalities
    for (i=0; i<nationalities_rows; i++){
        strcpy(current_row, nationalities_table[i]);
        string_size=strlen(current_row);
        index_delimeter = index_first_delimeter(current_row);
        //Search for the name up to the delimeter
        for (int k=0; k < index_delimeter; k++){
            names_nationalities[i][k]=current_row[k];
            names_nationalities[i][k+1]='\0';
        }
        //Search for the food from the delimeter on
        for (int h=index_delimeter+1; h < string_size; h++){
            nats[i][h-index_delimeter-1]=current_row[h];
            nats[i][h+1-index_delimeter-1]='\0';
        }
    }
    names_nationalities_num=i;

    //Seperate name from foods
    for (f=0; f<foods_rows; f++){
        strcpy(current_row, foods_table[f]);
        index_delimeter = index_first_delimeter(current_row);
        string_size=strlen(current_row);
        //Search for the name up to the delimeter
        for (int k=0; k < index_delimeter; k++){
            names_foods[f][k]=current_row[k];
            names_foods[f][k+1]='\0';
        }
        //Search for the food from the delimeter on
        for (int k=index_first_delimeter(current_row)+1; k < string_size; k++){
            foods[f][k-index_delimeter-1]=current_row[k];
            foods[f][k+1-index_delimeter-1]='\0';
        }

    }
    names_foods_num=f;

    //remove duplicate names
    char names[MAX_ROW_COUNT][MAX_STRING_LENGTH];
    int shortest_size=min(names_nationalities_num, names_foods_num);
    int names_count=0;
    char name[MAX_STRING_LENGTH];
    int name_len;
    if (shortest_size == names_nationalities_num){
        for (int x=0; x<shortest_size; x++){
            strcpy(name,names_nationalities[x]);
            name_len=strlen(name);
            for(int v=0;v<names_foods_num;v++){
                if(strcmp(name,names_foods[v])==0){
                    strcpy(names[names_count], name);
                    names_count++;
                }
            }
        } 
    }
    else{
        for (int x=0; x<shortest_size; x++){
            strcpy(name,names_foods[x]);
            name_len=strlen(name);
            for(int v=0;v<names_nationalities_num;v++){
                if(strcmp(name,names_nationalities[v])==0){
                    strcpy(names[names_count], name);
                    names_count++;
                }
            }
        } 
    }

    char del[2];
    del[0]=DELIMITER;
    char name_comp[MAX_STRING_LENGTH];
    for (int k=0; k<names_count; k++){
        //Search for name in nationalities table
        strcpy(name_comp,names[k]);

        for (int j=0; j<names_nationalities_num; j++){ 
            //Compare names
            if (strcmp(name_comp,names_nationalities[j])==0){
                //concatenate names[k]+','+nats[k] and put it into joined_table[k]
                strcat(joined_table[k], name_comp);
                strcat(joined_table[k], del);
                strcat(joined_table[k], nats[j]);
            }
        }

        for (int j=0; j<names_foods_num; j++){   
            //Compare names         
            if (strcmp(name_comp,names_foods[j])==0){
                //concatenate joined_table[k]+','+foods[k] and put it into joined_table[k]
                strcat(joined_table[k], del);
                strcat(joined_table[k], foods[j]);  
            }
        }
    }

    
}

#ifndef __TESTING  // this compiler directive
int main()
{
    // Please note that these are JUST EXAMPLES!
    // You will be tested on a wide range of data
    //
    // IMPORTANT: The join function above doesn't know how many rows are in
    //            each table, so, we add an *empty string* as the last row
    //            of the tables below. You can assume any input tables we
    //            use to test your program will contain an empty string 
    //            at the last row so you can tell you've reached the end
    //            of the table.
    //
    //  As before - you are expected to make reasonable assumptions
    //  regarding any information not given in these instructions.
    //

    char example_nationalities_table[MAX_ROW_COUNT][MAX_STRING_LENGTH] = {
        "Paco Estrada|Mexico",
        "Joe Armitage|England",
        "Angela Zavaleta|Peru",
        "Nyah Way|Canada",
        "Anya Tafliovich|Ukraine",
        "Brian Harrington|Canada",
        "",                          // <-- Empty string signals end of table
    };
    char example_foods_table[MAX_ROW_COUNT][MAX_STRING_LENGTH] = {
        "Brian Harrington|Avocado Salad",
        "Paco Estrada|Chocolate",
        "Joe Armitage|Chocolate",
        "Angela Zavaleta|Green Eggs",
        "Jack Long|Ham",
        "",                         // <-- Empty string signals end of table
    };

    // Notes on indexing an array of strings:
    // example_nationalities_table[i]   <- gives you a pointer to the string at row i of this table
    // example_nationalities_table[i][j]  <- Is the actual character at row i, position j in the table

    // Note that the size of this output array could have the MAX_ROW_COUNT, but
    // the length of each row may be up to 2*MAX_STRING_LENGTH.
    // We set the first row of this output table to "" (empty string),
    // so we know the table doesn't contain any *valid* rows. Remember though, 
    // this is a large array of chars we haven't actually cleaned-up, so it
    // will contain JUNK - be sure your join function is filling up each row with
    // proper strings, that all have their end-of-string delimiter.
    char joined[MAX_ROW_COUNT][MAX_STRING_LENGTH * 2] = {""};       

    // calling your function...
    // This should create the example joined table from the handout (and put it in `joined`).
    innerJoin(example_nationalities_table, example_foods_table, joined);

    // Printing the table:
    // (leaving THIS print statement is fine, but leave NONE in the `innerJoin` function!)
    for (int idx = 0; 0 != strcmp("", joined[idx]); idx++)
    {
        printf("%s\n", joined[idx]);
    }
}
#endif  // and this compiler directive
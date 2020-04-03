#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME_LENGTH (1024)

// This is a linked list node for either the stack or the queue
typedef struct ticket Ticket;
struct ticket
{
    char name[MAX_NAME_LENGTH];  // The person waiting
    Ticket *next;                // Another Ticket in the data structure
};

// You MAY NOT NEED both first and last for both data structures.
typedef struct data_struct
{
    Ticket *first;  // Use this, however you like, to implement the ADTs
    Ticket *last;   // Use this, however you like, to implement the ADTs
} Data;

// This enum is just for selecting your ADT of choice, below, in CORRECT_ADT.
typedef enum adt
{
    STACK,
    QUEUE,
    PICK_ONE
} ADT;

const ADT CORRECT_ADT = QUEUE; /** PICK: STACK or QUEUE */

/**
 * Adds name to the end of the Queue.
 *
 * INPUT:
 *  - data: the container for the Queue
 *  - name: the name to be added to the Queue
 * RETURN:
 *  - true, if the operation succeeds
 *  - false, if no memory is available or data is NULL
 */
bool enqueue(Data *data, char *name)
{
    if (data == NULL) return false;
    Ticket *new = NULL;
    new = (Ticket *)calloc(1, sizeof(Ticket));
    if (new == NULL)return false;

    //Initalize the new node
    strcpy(new -> name, name);
    new->next = NULL;

    //Refresh the data
    if (data -> first == NULL){
        data -> first = new;
        data ->last = new;
    }
    else{
        data ->last -> next = new;
        data ->last = data ->last -> next;
    }
    return true;
}

/**
 * Gets a name from the start of the Queue.
 *
 * INPUT: - data: the container for the Queue
 * OUTPUT: - returned_name: the name retrieved from the Queue
 * RETURN:
 *  - true, if the operation succeeds
 *  - false, if the queue is empty or data is NULL
 */
bool dequeue(Data *data, char *returned_name)
{
    if (data == NULL || (data -> first ==NULL)) return false;
    strcpy(returned_name, data -> first -> name);

    //Initalize the new node
    Ticket *new = NULL;
    strcpy(returned_name, data ->first ->name);
    new = data ->first ->next;

    //Refresh Data
    free(data->first);
    data->first = new;
    return true;
}

/**
 * Adds name to the top of the Stack.
 *
 * INPUT:
 *  - data: the container for the Stack
 *  - name: the name to be added to the Stack
 * RETURN:
 *  - true, if the operation succeeds
 *  - false, if no memory is available or data is NULL
 */
bool push(Data *data, char *name)
{
    if (data == NULL) return false;

    //Allocate memory
    Ticket *new = NULL;
    new = (Ticket *)calloc(1, sizeof(Ticket));
    if (new == NULL)return false;

    //Initalize the new node
    strcpy(new -> name, name);
    new -> next = data-> first;

    //Refresh the data
    if (data -> first == NULL){
        data -> first = new;
    }
    data -> first = new;
    return true;
}

/**
 * Gets a name from the top of the Stack.
 *
 * INPUT: - data: the container for the Stack
 * OUTPUT: - returned_name: the name retrieved from the Stack
 * RETURN:
 *  - true, if the operation succeeds
 *  - false, if the stack is empty or data is NULL
 */
bool pop(Data *data, char *returned_name)
{
    if (data == NULL || (data -> first ==NULL)) return false;

    //Initalize the new node
    Ticket *new = NULL;
    strcpy(returned_name, data ->first ->name);
    new = data ->first ->next;

    //Refresh Data
    free(data->first);
    data->first = new;
    return true;
}

// This is a wrapper for enqueue and push. It just calls the correct one based on CORRECT_ADT and
// then checks if an error happened during that call.
void takeTicket(Data *data, char *name)
{
    switch (CORRECT_ADT)
    {
    case STACK:
        if (push(data, name)) break;
        printf("Operation failure: push\n");
        exit(2);
    case QUEUE:
        if (enqueue(data, name)) break;
        printf("Operation failure: enqueue\n");
        exit(3);
    default:
        printf("Pick the CORRECT_ADT value before compiling and running!\n");
        exit(1);
    }
}

// This is a wrapper for dequeue and pop. It just calls the correct one based on CORRECT_ADT and
// then checks if an error happened during that call.
void callTicket(Data *data, char *returned_name)
{
    switch (CORRECT_ADT)
    {
    case STACK:
        if (pop(data, returned_name)) break;
        printf("Operation failure: pop\n");
        exit(4);
    case QUEUE:
        if (dequeue(data, returned_name)) break;
        printf("Operation failure: dequeue\n");
        exit(5);
    default:
        printf("Pick the CORRECT_ADT value before compiling and running!\n");
        exit(1);
    }
}

// Pauses program execution for length seconds
void sleep(double length)
{
    // (NOTE: This is an awful way of doing it but it is cross-platform)
    time_t second_start, second_end;
    time(&second_start);
    do
        time(&second_end);
    while (difftime(second_end, second_start) <= length / 2);
}

// We NEED these compiler directives to test your code with our own main(). Don't break them.
#ifndef __TESTING  // THIS compiler directive
#define NUM_NAMES (24)
int main()
{
    // You can play around with this code if you want:
    const char NAMES[NUM_NAMES][MAX_NAME_LENGTH] = {
        "Austen", "Bronte", "Carol", "Dickens", "Eliot", "Fyodor", "Gaskell", "Hardy",
    };                            // It doesn't matter if you change these strings, so have fun.
    const int NUM_CUSTOMERS = 8;  // Change this to integers between 2 and NUM_NAMES to test.
    const double RATE = 0.1;     // Change this to rationals between 0.1 and 0.9 to test.
    const double SEED = 2;  // Change this to rationals between 2 and 5 to test.

    double likelihood_of_new_customer = SEED;
    char name[MAX_NAME_LENGTH];
    time_t start, end;
    Data data = {NULL, NULL};
    int i, n;

    // Truly random numbers don't get made by computers. They're not good at it.
    srand(SEED);  // Changing SEED helps make this "random"ish.

    // Backlog of waiting customers before Brian
    for (n = 0, i = rand() % NUM_NAMES; n < NUM_CUSTOMERS; n++, i = rand() % NUM_NAMES)
        takeTicket(&data, (char *)NAMES[i]);

    takeTicket(&data, "Brian");  // Brian takes a ticket

    // Backlog of waiting customers after Brian
    for (n = 0, i = rand() % NUM_NAMES; n < NUM_CUSTOMERS; n++, i = rand() % NUM_NAMES)
        takeTicket(&data, (char *)NAMES[i]);

    // Brian waits for his ticket to be called...
    start = time(NULL);
    do
    {
        sleep(1);  // wait a second

        // Add another ticket, maybe
        if ((double)rand() / RAND_MAX < likelihood_of_new_customer)
        {
            takeTicket(&data, (char *)NAMES[i]);
            i = rand() % NUM_NAMES;
        }

        // Process the next ticket
        callTicket(&data, name);
        printf("Consulate now serving ticket for customer named: %s\n", name);

        // make it less likely that another name will be added next loop
        likelihood_of_new_customer *= RATE;

    } while (0 != strncmp(name, "Brian", MAX_NAME_LENGTH));

    end = time(NULL);
    printf("Hooray, Brian has his passport.\n");
    printf("It only took %.0lf seconds.\n", difftime(end, start));
}
#endif  // and THIS compiler directive
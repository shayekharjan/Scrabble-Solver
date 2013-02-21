//Khandker Shayekh Arjan

// This program will help solve Scrabble words

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* The maximum word length. */
#define MAX_WORD_LEN 7


// Define the struct used for the linked list Nodes here.

typedef struct node
{
    char word[MAX_WORD_LEN+1];
    struct node *next;
} Node;





/* Creates a new Node, and returns a pointer to it.
 * Copies 's' into 'word', and sets next to NULL.
 * Nodes must be free()ed with destroyNode(). */
Node *createNode(const char *s);

/* Cleans up the specified Node by free()ing any necessary fields, and then free()ing
 * the Node itself.  Does nothing if passed NULL. */
void destroyNode(Node *node);

/* Prints out the contents of the Node in the format specified in the assignment handout. */
void printNode(const Node *node);



/* Adds a Node containing the string 's' to the end of the list 'head'.  Returns a pointer
 * to the head of the list.  If 'list' is NULL, then we create a new list of size 1 (i.e.,
 * consisting entirely of the new Node we just created), and return a pointer to that. */
Node *addToList(Node *head, const char *s);

/* Adds the linked list pointed to by `head2` on to the end of the linked list pointed to by
 * `head1`.  If `head1` is null, returns `head2`. */
Node *add(Node *head1, Node *head2);


/* Prints out the list pointed to by 'head' in the format specified in the assignment handout. */
void printList(const Node *head);




#define WORD_LIST "wordlist.txt"
#define WORD_LIST_PATH "/share/copy/aps105/A5/"
#define WORD_LIST_LEN 11895

/* Reads in the word list in the file file WORD_LIST, which must be located at either WORD_LIST_PATH
 * or in the current working directory.  Exits if it can't find the file.  The file must consist
 * of at most WORD_LIST_LEN lines, each of which has at one word of at most MAX_WORD_LEN characters.
 * The array we return is a ragged array of pointers to each string.  The array must be cleaned
 * up with destroyWordList(). */
char **readWordList(void);

/* Cleans up the specified word list. */
void destroyWordList(char **wordList);


/* Safely reads at most n-1 characters from stdin, and stores them in 's', followed by '\0'.  Removes the trailing '\n' character. */
void getLine(char *s, int n);

/* Additional prototypes. */

/* Generates all of the possible permutations (including permutations of
 * shorter substrings) of the characters in 's', and returns them as a linked
 * list of Nodes.  The Nodes in the returned list must later be free()ed by
 * destroyNode(). */
Node *generatePermutations(const char *s);

/* Generates all of the possible strings that can be created by inserting 'c'
 * at every possible position in 's', and returns them as a linked list of
 * Nodes.  This function may be written iteratively.  For more details, see the
 * assignment handout.  The Nodes in the returned list must later be free()ed
 * by destroyNode(). */
Node *generateInsertions(char c, const char *s);

/* Generates all of the possible strings that can be created by inserting 'c'
 * into every possible location of every string in the list 'list', and returns
 * them as a linked list. The Nodes in the returned list must later be free()ed
 * by destroyNode(). */
Node *insertAtEveryPosition(Node *list, char c);




#ifndef AUTOMARKER 

void comparison(char **wordList, Node *list)
{
    char *string = malloc(MAX_WORD_LEN* sizeof(char));
    int i;
    for (i = 0; i < WORD_LIST_LEN; i++)
    {
        if(strcmp(list -> word, wordList[i]) == 0)
        {
            printNode(list);
          //  free(string);
            return;
        }
    }
    free(string);
}

Node *goThroughWorldList(char **wordList, Node *list)
{
    
    if(list == NULL)
    {
        return list;
    }
    else
    {
        comparison(wordList, list);
        list = goThroughWorldList(wordList, list -> next);
    }
    return list;
}

int main(void)
{
  
    Node *headPointer = (Node *)malloc(sizeof(Node));
    Node *resultList = (Node *)malloc(sizeof(Node));
    
    char *inputString = malloc(MAX_WORD_LEN * sizeof(char));
    
    printf("Please enter letters (max 7): ");
    getLine(inputString, MAX_WORD_LEN);
    
    if(strlen(inputString) > MAX_WORD_LEN)
    {
        printf("string too long\n");
    }
    
    else
    {
        resultList = generatePermutations(inputString);
    }
    
    char **wordList = readWordList();
    
    if ( strcmp(inputString, "a") == 0)
    { 
         printf("a\n");
    }
    
    else
    {
         headPointer = goThroughWorldList(wordList, resultList);
    }
    destroyNode(resultList);
    free(inputString);
    destroyNode(headPointer);
    destroyWordList(wordList);
    
    return 0;
}



#endif 



Node *createNode(const char *s)
{
    Node *newNode = malloc(sizeof(Node));
    strncpy(newNode->word, s, MAX_WORD_LEN);
    newNode->next = NULL;
    return newNode; 
}

void destroyNode(Node *node)
{
    if(node != NULL)
    {
        free(node);
    }


 
}
void printNode(const Node *node)
{
       
        printf("%s\n", node->word);
       
 
}




Node *addToList(Node *head, const char *s)
{
    Node *new_Node = createNode(s);
    if ( head == NULL )
    {
        head = new_Node;
    }
    else
    {
 
          head -> next = addToList(head -> next, s);
         
    }

    return head;


}


Node *add(Node *head1, Node *head2)
{

    if ( head1 == NULL )
    {
        head1 = head2;
        
    }
    else
    {
    
         head1 -> next = add(head1 -> next, head2);
    }

    return head1; // DELETE THIS LINE



}

void printList(const Node *head)
{
     //printNode(current);
    if ( head == NULL )
    {
        printf("  [null]\n");
    }
    else
    {
         printf("---------\n");
         printf("Word: ");
         printNode(head);
         printf("---------\n");
         printf("    |\n");
         printf("    V\n");
         
       //head = head->next;
       printList(head->next);
    }



}


void getLine(char *s, int n)
{
    // Read in our string
    fgets(s, n, stdin);

    // If the last character is a \n, strip it by replacing it with a \0
    if (s[strlen(s) - 1] == '\n')
    {
        s[strlen(s) - 1] = '\0';
    }
}

char **readWordList(void)
{
    FILE *f;


    f = fopen(WORD_LIST, "r");

    if (f == NULL)
    {
        char fullPath[strlen(WORD_LIST) + strlen(WORD_LIST_PATH) + 1];
        strncpy(fullPath, WORD_LIST_PATH, sizeof(fullPath));
        strncat(fullPath, WORD_LIST, sizeof(fullPath) - strlen(fullPath) - 1);
        f = fopen(fullPath, "r");
    }

    // If f is still NULL, then we haven't been able to find it, so we exit
    if (f == NULL)
    {
        printf("Can't find wordlist file.\n");
        exit(0);
    }

    // Allocate our wordlist (+1 is for the NULL pointer at the end)
    char ** wordList = malloc( (WORD_LIST_LEN + 1) * sizeof(char *));

    // Allocate a buffer to hold each line of the file
    // First +1 is for the \n, second +1 is for the \0
    char buffer[MAX_WORD_LEN + 1 + 1] = "";

    // Read in lines one at a time
    int i;
    for (i = 0; i < WORD_LIST_LEN && fgets(buffer, sizeof(buffer), f) != NULL; i++)
    {
        // Delete a trailing newline, if it's there
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // Copy the word into the wordlist
        wordList[i] = malloc((MAX_WORD_LEN + 1) * sizeof(char));
        strncpy(wordList[i], buffer, MAX_WORD_LEN);
    }

    // NULL terminate the array so that we know where the end is
    wordList[i] = NULL;

    // Close our wordlist file
    fclose(f);

    return wordList;
}


void destroyWordList(char **wordList)
{
    for (int i = 0; i < WORD_LIST_LEN; i++)
    {
        free(wordList[i]);
    }

    free(wordList);
}



// Place any new helper functions here.
Node *generatePermutations(const char *s)
{
   Node *resultsList = NULL; 

   char removedChar; 

   char *removedCharString = malloc(1*sizeof(char));

   if (strlen(s)==1)
   {
 
       resultsList = addToList(resultsList,s);
   }
   else
   {

       removedChar = *s;
       *removedCharString = removedChar;
  
       resultsList= generatePermutations(s+1);
  
       resultsList = insertAtEveryPosition(resultsList, removedChar);

       resultsList = addToList(resultsList, removedCharString);
  
   }
 
   return resultsList;
}


Node *generateInsertions(char c, const char *s)
{
   char new_string[strlen(s)+2];
   strncpy(new_string,s,strlen(s));
   new_string[strlen(s)] = c;
   new_string[strlen(s)+1] = '\0';

   Node *head2;
   Node *insertlist = createNode(new_string);

   int i, j;
   for ( i = 0; i < strlen(s); i++ )
   {
       for ( j = 0; j < i; j++ )
       {
           new_string[j] = s[j];
       }
       
       new_string[i] = c;
       
       for ( j = i + 1; j < (strlen(s) + 1 ); j++ )
       {
           new_string[j] = s[j-1];
       }
       
       new_string[strlen(s) + 1]='\0';

       head2 = insertlist;

       while( head2 -> next != NULL )
       {
           head2 = head2 -> next;
       }
       //printf("%s\n", new_string);
       head2 -> next = createNode(new_string);
   }
  // printList(insertlist);
   return insertlist;
}



Node *insertAtEveryPosition(Node *list, char c)
{
   Node *results = malloc(sizeof(Node));

    if ( list -> next == NULL )
    {
        results = generateInsertions(c,list->word);
        list = add(list, results );
       
    }
    else
    {
        list->next = insertAtEveryPosition(list->next, c);
        results = generateInsertions(c,list->word);
        list = add(list, results);
    }
   
    return list;
}

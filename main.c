/*  Name : Sara Shrouf
     ID :1220481
     SEC: 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 100
#define TABLE_SIZE 1024
#define Double 2
#define WordMaxLength 50 // the maximum length for any word
int   deleteSuccess ;//to cheak if The word I want to delete exists
int HashDoubleTableCapacity=311;//double table maximum size
//hash table creation
typedef struct HashEntry {
    char key[WordMaxLength];
    int freq;//Variable for the number of sentence repetitions
    int status;  // 0 = empty, 1 = filled, -1 = deleted
} HashEntry ;

 HashEntry * doubleHashTable;// define a "HashTable" which is an array of Hash values
 //creat a struct of Avl Tree
typedef struct AVLnode *AVLNode;//define a "Avl tree" just to make it easy to write

struct AVLnode {
    char Element[WordMaxLength];
    AVLNode Left;
    AVLNode Right;
    int Height; // Balance information
    int freq;
};
AVLNode root = NULL;
//GLOBAL VARIABLES
int doubleSize=0; //current size of the double hash table
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AVLNode MakeEmpty(AVLNode T);
AVLNode Find(char *X, AVLNode T);
AVLNode FindMin(AVLNode T);
AVLNode FindMax(AVLNode T);
AVLNode SingleRotateWithLeft(AVLNode K2);
AVLNode SingleRotateWithRight(AVLNode K1);
AVLNode DoubleRotateWithLeft(AVLNode K3);
AVLNode DoubleRotateWithRight(AVLNode K1);
AVLNode Insert(char *X, AVLNode T);
void PrintInOrder(AVLNode T);
void reedfromefile();
AVLNode Delete(const char *X, AVLNode T);
void doubleHashInitial();
float loadFactor(int capacity, int size);
int hashFunction(char word[WordMaxLength]);
void doubleInsert(char key[WordMaxLength],int frq);
void insertAVLToHashTable(AVLNode node);
int doubleHashSearch(char key[WordMaxLength]);
int doubleKeyDelete(char key[WordMaxLength]);
void doubleReHash();
int getPrime(int n);
int ifPrime(int n);
void displayMainMenu();
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  //  AVLNode root = NULL;
   doubleHashInitial();//inslize double hash
 // char words[1000][MAX_WORD_LEN];
    int word_count;
    int choice;
    int countuniqe =0;//to find number of words have uniqe freq
    int counmor =0;//to find number of words have more  freq

    char word[MAX_WORD_LEN];
/*menu*/
    printf("---------------------------WELCOME TO MY PROGRAM---------------------------\n\n");
     displayMainMenu();
    scanf("%d",&choice);

  while(1){

        //check if the entered operation is valid or not
        while(choice <1 || choice >11){

            printf("INVALID OPERATION. TRY DIFFERENT NUMBER.\n");
            printf("\n---------------------------------------------------------------------------\n\n");

            displayMainMenu();
            scanf("%d",&choice);
            printf("\n---------------------------------------------------------------------------\n\n");
        }

        switch (choice) {
            case 1:
                //rede frome file amd insert te input to the tree
                reedfromefile();
                printf("\nWords loaded from file.\n\n");
                break;
            case 2:
                 printf("\nAVL tree created.\n\n");
                break;
            case 3:

                printf(" insert a new word : \n");
                scanf("%s",word);

        int len = strlen(word);
        int j = 0;
        for (int i = 0; i < len; i++) {
            if (((word[i] >= 'a' &&word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')))  {//to cheack if the words is alpha
              if((word[i] >= 'A' && word[i] <= 'Z')){//make the word small letters
                    word[j] = word[i]+32;

               }
              else{
                word[j] = word[i];//else if the word is already small
              }
               j++;
            }
            }
          word[j]='\0';
      root = Insert(word,root);
    printf("the word add\n");
                 break;
            case 4 :
                deleteSuccess =0;//if we delete it be equal 1
                char deletword[100];
                printf("enter  the sentence you want to delete : \n");
                scanf("%s",deletword);
                 root = Delete(deletword, root);
           if(deleteSuccess){
         printf("\n we will delete\n");
    printf("\n");
}
else{
    printf("the word does not exist");
}
           break;
            case 5:
                printf("Words in AVL tree (in-order traversal):\n");
               PrintInOrder(root);//print avl tree
                break;


            case 6:
               // Initialize the hash table

    // Transfer words from AVL tree to hash table
    insertAVLToHashTable(root);
    printf("we will creat hash table ...\n");
    // Example of how to print hash table contents
 /*  for (int i = 0; i < HashDoubleTableCapacity; i++) {
        if (doubleHashTable[i].status == 1) {
            printf("Word: %s, Frequency: %d\n", doubleHashTable[i].key, doubleHashTable[i].freq);
        }
    }*/

     break;

            case 7:

                printf("enter to add to the hashing : \n");
                scanf("%s",word);
                int len2 = strlen(word);
        int k = 0;
        for (int i = 0; i < len2; i++) {
            if (((word[i] >= 'a' &&word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')))  {//to cheack if the words is alpha
              if((word[i] >= 'A' && word[i] <= 'Z')){//make the word small letters
                    word[k] = word[i]+32;

               }
              else{
                word[k] = word[i];//else if the word is already small
              }
               k++;
            }
            }
          word[k]='\0';
                doubleInsert(word,1);
                for (int i = 0; i < HashDoubleTableCapacity; i++) {
        if (doubleHashTable[i].status == 1) {
            printf("Word: %s, Frequency: %d\n", doubleHashTable[i].key, doubleHashTable[i].freq);
        }
    }
             printf("Word inserted into hash table.\n");

            break;


            case 8:
                printf("enter the word to delete it : \n");
                scanf("%s",word);

                   if(doubleKeyDelete(word)==-1){
                    printf("the word has not found \n");
                   }
                   else {
                    printf("the word has deleted \n");
                   }
                      for (int i = 0; i < HashDoubleTableCapacity; i++) {
        if (doubleHashTable[i].status == 1) {
            printf("Word: %s, Frequency: %d\n", doubleHashTable[i].key, doubleHashTable[i].freq);
        }
    }

                 break;

            case 9:
                printf("enter the word to search it : \n");
                scanf("%s",word);
              int index=doubleHashSearch(word);//to return the index of word in hash
                   if(index==-1){
                    printf("the word has not found \n");
                   }
                   else {
                   printf("Word: %s, Frequency: %d\n", doubleHashTable[index].key, doubleHashTable[index].freq);
                   }

                break;

            case 10 :
                countuniqe =0;
                int maxfreq=doubleHashTable[0].freq;//make first word the highest freq
                int a=0;
                 int numfrequancy;
                 //////////////////////////////////////////////
                 printf("Words that have a uniqe frequency : \n");
                  for (int i = 0; i < HashDoubleTableCapacity; i++) {//traverse to print the uniqe freq
        if (doubleHashTable[i].freq==1) {
                countuniqe+=1;//number of word hae a uniqe freq

            printf("word : %s\t freq : % d \n", doubleHashTable[i].key, doubleHashTable[i].freq);
        }

                  else if(doubleHashTable[i].freq>1) {
                        counmor+=1;
                  }}

       printf("\n////////////////////////////////////////////////////////////////\n\n");
        for (int i = 0; i < HashDoubleTableCapacity; i++) {//traverse to find the word that have most freq
        if (maxfreq<doubleHashTable[i].freq) {
                maxfreq=doubleHashTable[i].freq;
                a=i;

        } }
        printf("\n the number of uniqe freq : %d\n\n",countuniqe);
        printf("\n the number of more freq : %d\n\n",counmor);
        printf("\n the word that have most freq : %s \t\t freq : %d",doubleHashTable[a].key,maxfreq);
        printf("\n/////////////////////////////////\n");

        printf("enter to the number if freq :");
        scanf("%d",&numfrequancy);
        int cheack=0;//flage If there is a word that has the input frequency
        for (int i = 0; i < HashDoubleTableCapacity; i++){
            if(numfrequancy< doubleHashTable[i].freq){
                    cheack=1;
                printf("%s ,  %d\n",doubleHashTable[i].key, doubleHashTable[i].freq);
            }

        }
        if(cheack==0){
            printf("no words have this freq \n");
        }


                break;

            case 11  :
                printf("---------------------------thank you to use my program---------------------------");
                exit(0);

                break;



                }
                  displayMainMenu();
        scanf("%d",&choice);
    }
    return 0;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//make the tree empty
AVLNode MakeEmpty(AVLNode T) {
    if (T != NULL) {
        MakeEmpty(T->Left);//
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

AVLNode Find(char *X, AVLNode T) {
    if (T == NULL)
        return NULL;
    if (strcmp(X, T->Element) < 0)
        return Find(X, T->Left);
    else if (strcmp(X, T->Element) > 0)
        return Find(X, T->Right);
    else
        return T;
}

AVLNode FindMin(AVLNode T) {
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

AVLNode FindMax(AVLNode T) {
    if (T != NULL)
        while (T->Right != NULL)
            T = T->Right;

    return T;
}

int Height(AVLNode P) {
    if (P == NULL)
        return -1;
    else
        return P->Height;
}

int Max(int Lhs, int Rhs) {
    return Lhs > Rhs ? Lhs : Rhs;
}

AVLNode SingleRotateWithLeft(AVLNode K2) {
    AVLNode K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
    K1->Height = Max(Height(K1->Left), K2->Height) + 1;

    return K1;  /* New root */
}

AVLNode SingleRotateWithRight(AVLNode K1) {
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
    K2->Height = Max(Height(K2->Right), K1->Height) + 1;

    return K2;  /* New root */
}

AVLNode DoubleRotateWithLeft(AVLNode K3) {
    K3->Left = SingleRotateWithRight(K3->Left);
    return SingleRotateWithLeft(K3);
}

AVLNode DoubleRotateWithRight(AVLNode K1) {
    K1->Right = SingleRotateWithLeft(K1->Right);
    return SingleRotateWithRight(K1);
}
//insert to the avl tree
AVLNode Insert(char *X, AVLNode T) {
    if (T == NULL) {
        T = (AVLNode)malloc(sizeof(struct AVLnode));
        if (T == NULL) {
            printf("Out of space!!!\n");
        }
        else  {
            strcpy(T->Element, X);
            T->Height = 0;
            T->Left = T->Right = NULL;
            T->freq=1;
        }
    } else if (strcmp(X, T->Element) < 0) {
        T->Left = Insert(X, T->Left);
        if (Height(T->Left) - Height(T->Right) == 2) {
            if (strcmp(X, T->Left->Element) < 0)
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
        }
    } else if (strcmp(X, T->Element) > 0) {
        T->Right = Insert(X, T->Right);
        if (Height(T->Right) - Height(T->Left) == 2) {
            if (strcmp(X, T->Right->Element) > 0)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    else {
        // // Else X is in the tree already exists, just increment frequency
        T->freq++;
    }


    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
}

// In-order print to see the elements
void PrintInOrder(AVLNode T) {
    if (T != NULL) {
        PrintInOrder(T->Left);
        printf("%s ->\t ,%d ->\n", T->Element,T->freq);
        PrintInOrder(T->Right);
    }
}

//function to read from file insert the string from file to tree
void reedfromefile(){
char word [100];
FILE*file=fopen("input.txt","r");
//to check if the file is empty
    if (file == NULL){
        printf("File does not exist");
        return (-1);
    }

 while(fscanf(file,"%s",word)!=EOF){
    int len=strlen(word);//find the length of the current word
    int index = 0;//Track the position in the cleaned words.
        for (int i = 0; i < len; i++) {//loop in each letters in the word
            if (((word[i] >= 'a' &&word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))) {//to cheack if the word is charecer
                    if((word[i] >= 'A' && word[i] <= 'Z')){
                         word[index]=word[i]+32;//to make the letter small

                    }
                    else{
                word[index] = word[i];//else if the word is already small
              }
                    index++;// increments the index.//just increment if the word is char
            }
        }
        word[index] = '\0';//Adds a null terminator to the end of the cleaned word
        if (index > 0) {//if the cleanedword is char
            root = Insert(word,root);//insert to the avl tree
        }
    }


    fclose(file);
 }
AVLNode Delete(const char *X, AVLNode T) {
    if (T == NULL) {
        deleteSuccess = 0;  //The deleted sentence not exists
        return NULL;
    }

    int cmp = strcmp(X, T->Element);
    if (cmp < 0) {
        T->Left = Delete(X, T->Left);
    } else if (cmp > 0) {
        T->Right = Delete(X, T->Right);
    } else {
        //If we find a sentence and it has a duplicate frequency, we reduce it
        if (T->freq > 1) {
            T->freq--;
            deleteSuccess = 1;// Decrease frequency the word exist
            return T;

        }
        // Node to be deleted found

        if (T->Left && T->Right) {

            // Node has two children
            AVLNode minRight = FindMin(T->Right);
            strcpy(T->Element, minRight->Element); // Copy the string
            T->Right = Delete(T->Element, T->Right);
        } else {

            AVLNode temp = T;
            if (T->Left == NULL) {
                T = T->Right;
            } else if (T->Right == NULL) {
                T = T->Left;
            }
            deleteSuccess = 1;//The deleted sentence exists
            free(temp);
        }
    }

    if (T == NULL) {
        return T;
    }

    // Update height
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

    // Rebalance if necessary
    int balance = Height(T->Left) - Height(T->Right);
    if (balance > 1) {
        if (Height(T->Left->Left) >= Height(T->Left->Right)) {
            T = SingleRotateWithLeft(T);
        } else {
            T = DoubleRotateWithLeft(T);
        }
    } else if (balance < -1) {
        if (Height(T->Right->Right) >= Height(T->Right->Left)) {
            T = SingleRotateWithRight(T);
        } else {
            T = DoubleRotateWithRight(T);
        }
    }

    return T;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void doubleHashInitial(){
 doubleHashTable = (HashEntry*) malloc(HashDoubleTableCapacity * sizeof(HashEntry));//// allocate a position in the memory
    if (doubleHashTable== NULL) {
        perror("Unable to allocate memory for hash table");
        exit(EXIT_FAILURE);
    }
   // fill them with NULL
    for(int counter = 0; counter<HashDoubleTableCapacity; counter++){
        doubleHashTable[counter].freq=0;//make the freq=0;
        doubleHashTable[counter].status=0; //empty
    }

}
//function to calculate load factor
//////////loadFactor//////////
float loadFactor(int capacity, int size){
    return ((float)size / (float)capacity);
}

//function to hash the key word
//////////hashFunction//////////
int hashFunction(char word[WordMaxLength]){
   long long int hashValue=0, counter=0;

   while(word[counter]!='\0'){
        hashValue = (hashValue*32) + (int)word[counter];
        counter++;

   }
    //printf("%lli\n",hashValue%HashDoubleTableCapacity);
   return (hashValue%HashDoubleTableCapacity);
}
//function to insert a key to the double hash table
//////////doubleInsert//////////
void doubleInsert(char key[WordMaxLength],int frq){

    int hash1 = hashFunction(key);
    int index = hash1;
    int i = 1;

float doubleLoadFactor=loadFactor(HashDoubleTableCapacity,doubleSize);
 if(doubleLoadFactor>0.80){
        //rehash
        doubleReHash();
    }
    if(doubleSize == HashDoubleTableCapacity){
        printf("\\nHash Table is full, cannot insert more items \\n");
        return;
    }
    //go through the table until we reach an empty node

    while(doubleHashTable[index].status == 1){
       if (strcmp(doubleHashTable[index].key, key) == 0) {
            doubleHashTable[index].freq++;
            return;
        }
        //prop the hash index
        index = (hash1 + i*(307 - (hash1%307))) % HashDoubleTableCapacity;

        if(index == hash1){
            printf("\full,,,, insert is failed\n");
            return;
        }
        i++;
    }

    //insert record into the table
   doubleHashTable[index].freq= frq;
    doubleHashTable[index].status = 1;//exist
    strcpy(doubleHashTable[index].key, key);
    doubleSize++;

}
//function to insert word from in order avl to hash
void insertAVLToHashTable(AVLNode node) {

    if (node!=NULL) {
        insertAVLToHashTable(node->Left);
        doubleInsert(node->Element, node->freq);
        insertAVLToHashTable(node->Right);
    }
}
// Function to search a key in the double hash table
int doubleHashSearch(char key[WordMaxLength]) {
    int hash1 = hashFunction(key);
    int index = hash1;
    int i = 1;

    if (doubleSize == 0) {
        printf("\nDOUBLE HASH TABLE IS EMPTY\n");
        return -1;
    }

    while (doubleHashTable[index].status != 0) {
        if (strcmp(doubleHashTable[index].key, key) == 0 && doubleHashTable[index].status == 1) {
            return index;
        }

        index = (hash1 + i * (307 - (hash1 % 307))) % HashDoubleTableCapacity;
        if (index == HashDoubleTableCapacity) {
            break;
        }
        i++;
    }
    return -1;
}

// Function to delete a key from the double hash table
int doubleKeyDelete(char key[WordMaxLength]) {
    int hash1 = hashFunction(key);
    int index = hash1;
    int i = 1;

    if (doubleSize == 0) {
        printf("\nDOUBLE HASH TABLE IS EMPTY\n");
        return -1;
    }

    while (doubleHashTable[index].status != 0) {
        if (strcmp(doubleHashTable[index].key, key) == 0 && doubleHashTable[index].status == 1) {
             /*   if(doubleHashTable[index].freq>1 ){
                    doubleHashTable[index].freq--;
                    doubleSize--;
                }*/
            doubleHashTable[index].status = -1;
            doubleHashTable[index].freq = 0;
            doubleSize--;
            return 1; // deleted
        }

        index = (hash1 + i * (307 - (hash1 % 307))) % HashDoubleTableCapacity;
        if (index == HashDoubleTableCapacity) {
            break;
        }
        i++;
    }
    return -1; // not found
}

void doubleReHash(){
    int temp=HashDoubleTableCapacity;
    HashDoubleTableCapacity = getPrime(2 * HashDoubleTableCapacity); //find the capacity of the new rehashed double table
    HashEntry * newDoubleHashTable; //creation of the new double hash table
    newDoubleHashTable=(HashEntry *)malloc(sizeof(struct HashEntry) * HashDoubleTableCapacity); //double hash table creation & initialization

    for(int i=0; i<temp; i++){
        newDoubleHashTable[i] = doubleHashTable[i];
        doubleHashTable[i].status = 0;
        doubleHashTable[i].freq = 0;
    }
    //doubleHashInitial(doubleHashTable);
    doubleSize = 0;
    for(int i=0; i<temp; i++) {
        if(newDoubleHashTable[i].status == 1){
            doubleInsert(newDoubleHashTable[i].key, newDoubleHashTable);
        }
    }
    printf("\nsize = %d  Capacity = %d,   \n", doubleSize, HashDoubleTableCapacity, doubleSize);
    printf("Rehashing DONE\n");
}

//function to get the prime number to the new rehashed table
//// build a function that takes an integer and returns the first prime greater that or equal to it
//////////getPrime//////////
int getPrime(int n){
    if(n % 2 == 0){
        n++;
    }
    for(; !ifPrime(n); n += 2);
    return n;
}
//build a function to check if a number is prime
int ifPrime(int n){
    int i;
    if(n == 1 || n == 0) {
        return 0;
    }
    for(i=2; i<n; i++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}

//function to display main menu of the program
//////////displayMainMenu//////////
void displayMainMenu(){
 printf("1. Load data from the file\n");
        printf("2. Create the AVL tree\n");
        printf("3. Insert a word to the AVL tree\n");
        printf("4. Delete a word from the AVL tree\n");
        printf("5. Print the words as sorted in the AVL tree\n");
        printf("6. Create the Hash Table\n");
        printf("7. Insert a word to the Hash table\n");
        printf("8. Delete a word from the hash table\n");
        printf("9. Search for a word in the hash table and print its frequency\n");
        printf("10. Print words statistics\n");
        printf("11. Exit the application\n");
        printf("Enter your choice: ");

}



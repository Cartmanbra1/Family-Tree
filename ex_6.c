// (89110, Spring 2023, Assignment #6, Roie Amsalem, 322535436, roieams)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_CHAR 1
#define LEGAL_MARRIAGE_AGE 18
#define BIG_ARRAY 100

typedef struct Family {
    char *name;
    unsigned int age;
    struct Family *parent, *secondParent;
    struct Family *spouse;
    struct Family *sibling;
    struct Family *child;
    struct Family *next;
} Family;

typedef struct HeadFamily {
    Family *familyHead;
    struct HeadFamily *list;
    struct HeadFamily *next;
} HeadFamily;

void menu();

void optionOne(HeadFamily **familyHead);

void optionTwo(HeadFamily **familyHead);

void optionThree(HeadFamily **familyHead);

void optionFour(HeadFamily **familyHead);

void optionFive(HeadFamily **familyHead);

void optionSix(HeadFamily **familyHead);

void optionSeven(HeadFamily **familyHead);

void cleanBuffer(char cleanBuffer);

char *makeString();

Family *getHead(HeadFamily **familyHead, char *name);

int makeFamilyHead(HeadFamily **familyHead);

void freeMemory(HeadFamily **familyHead);

void makeMarriedCouple(HeadFamily **familyHead, char *firstName, char *secondName);

int checkIfMarried(Family *person);

int checkLegalAge(unsigned int age);

char *findHead(HeadFamily **familyHead, char *name);

int marryNotHead(Family *personOne, Family *personTwo, HeadFamily **familyHead, char *firstName, char *secondName);

void freeArrays(char **firstPersonHeads, char **secondPersonHeads, int countOne, int countTwo);

int compareArrays(char **firstPersonHeads, char **secondPersonHeads, int countOne, int countTwo);

void makeHeadChild(char *firstName, char *secondName, char *offspringName, HeadFamily **familyHead);

void makeChild(char *firstName, char *secondName, char *offspringName, HeadFamily **familyHead);

void printFamily(HeadFamily **familyHead, char *name, int count, Family *person, Family *originalPerson);

void raiseAge(HeadFamily **familyHead);

void iterateTree(HeadFamily **familyHead, unsigned int aging);

void addToList(HeadFamily **familyHead, Family *person);

void countPeople(HeadFamily **familyHead);

Family *findPerson(HeadFamily **familyHead, char *name);

void printRelatives(HeadFamily **familyHead);

char **createRelativesArray(Family *person, unsigned int degree, int *count);

void
makeRelativesArray(Family *person, unsigned int degree, unsigned int degreeCpy, int *count, char **relativesArray);

char **sortRelatives(char **relativesArray, const int *count);

char **ensureArray(char **relativesArray, int *count, HeadFamily **familyHead);

int checkIfInArray(Family *person, char **relativesArray, int *count);

Family *setPerson(Family *person);

Family *setChild(Family *child, Family *parentOne, Family *parentTwo, char *offspringName);

void RelativeDegree(Family *person, unsigned int degree, int *count, char **relativesArray);

int main() {
    menu();
}

/**
 * @brief Displays a menu and performs actions based on user input.
 */
void menu() {
    char option;
    HeadFamily *familyHead = NULL;
    // Infinite loop until user breaks
    while (1) {
        // Print the menu and let the user choose an option
        printf("Choose an option:\n"
               "0. Exit\n"
               "1. Add a head\n"
               "2. Marry two people\n"
               "3. New offspring\n"
               "4. Print family top-down\n"
               "5. Years pass\n"
               "6. Count people\n"
               "7. Print cousins\n");
        scanf("%c", &option);
        // Split the cases
        if (option < '0' || option > '7') {
            // Split the inputs again, if its \n the user has another input
            if (option != '\n') {
                printf("Invalid option\n");
                cleanBuffer(0);
                // Skip to the next iteration of the loop
                continue;
            } else {
                cleanBuffer(0);
                printf("Invalid option\n");
                continue;
            }
        }
        // Split the cases, 0 breaks everything else sends to the relevant option
        if (option == '0') {
            break;
        } else if (option == '1') {
            optionOne(&familyHead);
        } else if (option == '2') {
            optionTwo(&familyHead);
        } else if (option == '3') {
            optionThree(&familyHead);
        } else if (option == '4') {
            optionFour(&familyHead);
        } else if (option == '5') {
            optionFive(&familyHead);
        } else if (option == '6') {
            optionSix(&familyHead);
        } else if (option == '7') {
            optionSeven(&familyHead);
        }
    }
    // Free the memory before exiting the program
    freeMemory(&familyHead);
}

/**
 * @brief Performs option one: Add a Family head
 *
 * This function prompts the user to enter a name for the Family head and adds it to the Family structure.
 * If the entered name is valid, the function cleans the input buffer.
 *
 * @param familyHead Pointer to the head of the Family heads structure.
 */
void optionOne(HeadFamily **familyHead) {
    int nameValid = 0;
    // Using nameValid to check if the name was valid and the process was completed.
    nameValid = makeFamilyHead(familyHead);
    // Clean the buffer only if the process was completed (because of the age scanf).
    if (nameValid == 0) {
        cleanBuffer(0);
    }
}


/**
 * @brief Performs option two: Marry two people.
 *
 * This function prompts the user to enter the names of two people and makes them a married couple in the Family structure.
 *
 * @param familyHead Pointer to the head of the Family heads structure.
 */
void optionTwo(HeadFamily **familyHead) {
    char *firstName, *secondName;
    // Prompt first name user input
    printf("Enter the name of the first person:\n");
    cleanBuffer(0);
    // Receive the first name from the user
    firstName = makeString();
    // Prompt second name user input
    printf("Enter the name of the second person:\n");
    // Receive the second name from the user
    secondName = makeString();
    // Call to makeMarriedCouple
    makeMarriedCouple(familyHead, firstName, secondName);
    free(firstName);
    free(secondName);
}


/**
 * @brief Performs option three: Add an offspring to the Family.
 *
 * This function prompts the user to enter the names of the two parents and the name of the offspring.
 * It then adds the offspring as a child to the specified parents in the Family structure.
 *
 * @param familyHead Pointer to the head of the Family heads structure.
 */
void optionThree(HeadFamily **familyHead) {
    char *firstName, *secondName, *offspringName;
    // Prompt first name insert
    printf("Enter the name of the first parent:\n");
    // Clean the buffer
    cleanBuffer(0);
    // Receive first name
    firstName = makeString();
    // Prompt second name insert
    printf("Enter the name of the second parent:\n");
    // Receive second name
    secondName = makeString();
    // Prompt third (offspring) name insert
    printf("Enter offspring's name:\n");
    // Receive offspring's name
    offspringName = makeString();
    // Call makeHeadChild
    makeHeadChild(firstName, secondName, offspringName, familyHead);
    // Free the names we allocated memory to
    free(firstName);
    free(secondName);
    free(offspringName);
}


/**
 * @brief Performs option four: Print Family top-down.
 *
 * This function prompts the user to enter the name of a person in the Family structure.
 * It then prints the Family hierarchy starting from that person's Family head in a top-down fashion.
 *
 * @param familyHead Pointer to the head of the Family heads structure.
 */
void optionFour(HeadFamily **familyHead) {
    char *name;
    // Prompt the user to insert a name and parse it
    printf("Enter the name of the person:\n");
    cleanBuffer(0);
    name = makeString();
    // Send the name and other variables to printFamily
    printFamily(familyHead, name, 0, NULL, NULL);
    // Free the name we allocated memory to
    free(name);
}

/**
 * @brief Performs option five: Raise the age of everyone in the program.
 *
 * @param familyHead Pointer to the head of the Family heads structure.
 */
void optionFive(HeadFamily **familyHead) {
    // Call to raiseAge
    raiseAge(familyHead);
}

/**
 * @brief Performs option six: count the amount of people in the program.
 *
 * @param familyHead Pointer to the head of the Family heads structure.
 */
void optionSix(HeadFamily **familyHead) {
    // Call to countPeople
    countPeople(familyHead);
    // Clean the buffer
    cleanBuffer(0);
}

/**
 * @brief Performs option seven: print the relatives of a person up to an input of degree.
 *
 * @param familyHead Pointer to the head of the Family heads structure.
 */
void optionSeven(HeadFamily **familyHead) {
    cleanBuffer(0);
    // Call to printRelatives
    printRelatives(familyHead);
    cleanBuffer(0);
}

/**
 * @brief Clears the input buffer.
 *
 * @param cleanBuffer A variable to store the cleaned input buffer.
 */
void cleanBuffer(char cleanBuffer) {
    // Parsing the buffer
    scanf("%c", &cleanBuffer);
    // Continuing to parse the buffer until '\n'
    while (cleanBuffer != '\n') {
        scanf("%c", &cleanBuffer);
    }
}

/**
 * @brief Creates a new Family head and adds it to the Family structure.
 *
 * This function prompts the user to enter a name for the Family head and adds it to the Family heads structure.
 * If the entered name is already taken, the function displays an error message and returns 1.
 *
 * @param familyHead Pointer to the head of the Family structure.
 * @return 0 if the Family head is successfully created and added, 1 if the name is already taken.
 */
int makeFamilyHead(HeadFamily **familyHead) {
    HeadFamily *head = *familyHead, *temp, *newHead;
    // Prompt insert name
    printf("Enter a name:\n");
    cleanBuffer(0);
    // If the heads list is empty create it
    if (head == NULL) {
        head = (HeadFamily *) malloc(sizeof(HeadFamily));
        // Check the memory was allocated successfully
        if (head == NULL) {
            exit(1);
        }
        // Allocate memory to the first Family* type struct field
        head->familyHead = (Family *) malloc(sizeof(Family));
        // Check memory was allocated correctly
        if (head->familyHead == NULL) {
            exit(1);
        }
        // Receive the name from the user
        head->familyHead->name = makeString();
        // Call to setPerson
        setPerson(head->familyHead);
        // Set head->next to NULL
        head->next = NULL;
        // Allocate memory to a seperate list of people to be used later
        head->list = (HeadFamily *) malloc(sizeof(HeadFamily));
        if (head->list == NULL){
            exit(1);
        }
        // Setting the linked list to its first element
        *familyHead = head;
        // allocating memory to the lists Family* element and setting it to NULL
        //head->list->familyHead = (Family *) malloc(sizeof(Family));
        head->list->familyHead = NULL;
        // Adding to the list
        addToList(&head, head->familyHead);
    } else {
        //Similar to head == NULL Using newHead to initialize it
        newHead = (HeadFamily *) malloc(sizeof(HeadFamily));
        newHead->familyHead = (Family *) malloc(sizeof(Family));
        if (newHead == NULL || newHead->familyHead == NULL){
            exit(1);
        }
        newHead->familyHead->name = makeString();
        newHead->next = NULL;
        // Copying the name
        setPerson(newHead->familyHead);
        //Freeing the name
        temp = head;
        // Check if the name is already taken
        Family *person;
        person = findPerson(familyHead, newHead->familyHead->name);
        if (person != NULL) {
            printf("The name is already taken\n");
            // Freeing all the newly allocated memory since the process was failed
            free(newHead->familyHead->name);
            free(newHead->familyHead);
            free(newHead);
            // Exiting and returning 1
            return 1;
        }
        // Find the last node in the existing linked list
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Connect the new node to the existing linked list
        temp->next = newHead;
        addToList(&head, newHead->familyHead);
    }
    // Prompt insert age
    printf("Enter age:\n");
    while (head->next != NULL) {
        head = head->next;
    }
    // parse age into the relevant head
    scanf("%u", &(head->familyHead->age));
    // Successfully linked the person
    return 0;
}


/**
 * @brief Sets the attributes of a person in the Family structure.
 *
 * This function sets the age, spouse, sibling, child, parent, second parent, and next attributes of a person
 * in the Family structure to their initial values.
 *
 * @param person Pointer to the person in the Family structure.
 * @return Pointer to the updated person with the attributes set.
 */
Family *setPerson(Family *person) {
    //Setting all of a person's info to NULL and age to 0
    person->age = 0;
    person->spouse = NULL;
    person->sibling = NULL;
    person->child = NULL;
    person->parent = NULL;
    person->secondParent = NULL;
    person->next = NULL;
    return person;
}

/**
 * @brief Reads a string from the user.
 *
 * @return The dynamically allocated string.
 */
char *makeString() {
    // Declare variables
    char *string;
    char character;
    int length = 0, count = 1;
    // Read the first character
    scanf("%c", &character);
    // Allocate memory for the string
    string = (char *) malloc(sizeof(char) * count + 1);
    // Read characters until a newline is encountered
    while (character != '\n') {
        // Store the character in the string
        string[length] = character;
        // Increment the length counter
        length++;
        // Check if the allocated memory is sufficient
        if (length >= SIZE_OF_CHAR * count) {
            // Increase the memory size
            count++;
            string = (char *) realloc(string, sizeof(char) * count + 1);
            // Check if memory reallocation was successful
            if (string == NULL) {
                free(string);
                exit(1);
            }
        }
        // Read the next character
        scanf("%c", &character);
    }
    // Add null terminator to mark the end of the string
    string[length] = '\0';
    // Return the dynamically allocated string
    return string;
}


/**
 * @brief Frees the memory allocated for the linked lists and account data.
 *
 * @param bank The bank structure.
 */
void freeMemory(HeadFamily **familyHead) {
    // Declare and initialize variables
    HeadFamily *head = *familyHead, *nextHead;
    Family *person, *next;
    // Free memory for the single linked list
    // Set person the the first person in the heads list
    person = head->familyHead;
    while (person != NULL) {
        // Iteratively go through all elements and free them
        next = person->next;
        free(person->name);
        free(person);
        person = next;
    }
    while (head != NULL) {
        nextHead = head->next;
        free(head);
        head = nextHead;
    }
}

/**
 * @brief Creates a married couple in the Family structure.
 *
 * This function creates a married couple in the Family structure using the provided first and second person names.
 * If either person is not a Family head, the function attempts to create the couple through the `marryNotHead` function.
 *
 * @param[in,out] familyHead Pointer to the head of the Family heads structure.
 * @param[in] firstName Name of the first person.
 * @param[in] secondName Name of the second person.
 */
void makeMarriedCouple(HeadFamily **familyHead, char *firstName, char *secondName) {
    HeadFamily *head = *familyHead, *secondHead = *familyHead;
    Family *personOne, *personTwo;
    // Check if the person being married is a head
    while (head != NULL) {
        // If the first person is a head, break out
        if (strcmp(head->familyHead->name, firstName) == 0) {
            break;
        }
            // If the second person is a head, break out
        else if (strcmp(head->familyHead->name, secondName) == 0) {
            break;
        }
        head = head->next;
    }
    // If neither person is a head, marry them through marryNotHead
    if (head == NULL) {
        personOne = personTwo = NULL;
        // Check if the marriage is possible through marryNotHead
        if (marryNotHead(personOne, personTwo, familyHead, firstName, secondName) == 1) {
            return;
        } else {
            // Find the persons in the Family linked list
            personOne = findPerson(familyHead, firstName);
            personTwo = findPerson(familyHead, secondName);
            // Update spouse information
            personOne->spouse = personTwo;
            personTwo->spouse = personOne;
            printf("%s and %s are now married\n", personOne->name, personTwo->name);
            return;
        }
    } else {
        // If the first person is a head
        if (strcmp(head->familyHead->name, firstName) == 0) {
            // Find the second person in the Family linked list
            while (secondHead != NULL) {
                if (strcmp(secondHead->familyHead->name, secondName) == 0) {
                    break;
                }
                secondHead = secondHead->next;
            }
        } else if (strcmp(head->familyHead->name, secondName) == 0) {
            // If the second person is a head, find the first person in the Family linked list
            while (secondHead != NULL) {
                if (strcmp(secondHead->familyHead->name, firstName) == 0) {
                    break;
                }
                secondHead = secondHead->next;
            }
        }
        // If the second person is not a head, use marryNotHead
        if (secondHead == NULL) {
            personOne = personTwo = NULL;
            // Check if the marriage is possible through marryNotHead
            if (marryNotHead(personOne, personTwo, familyHead, firstName, secondName) == 1) {
                return;
            } else {
                // Find the persons in the Family linked list
                personOne = findPerson(familyHead, firstName);
                personTwo = findPerson(familyHead, secondName);
                // Update spouse information
                personOne->spouse = personTwo;
                personTwo->spouse = personOne;
                // Print the newly-wed couple
                printf("%s and %s are now married\n", personOne->name, personTwo->name);
                return;
            }
        }
        // Check for invalid marriage conditions
        if (checkIfMarried(head->familyHead) == 1 || checkIfMarried(secondHead->familyHead) == 1 ||
            checkLegalAge(head->familyHead->age) == 1 ||
            checkLegalAge(secondHead->familyHead->age) == 1) {
            printf("Invalid marriage\n");
            return;
        }
        // Update spouse information
        secondHead->familyHead->spouse = head->familyHead;
        head->familyHead->spouse = secondHead->familyHead;
        // Print the newly-wed couple
        printf("%s and %s are now married\n", head->familyHead->name, secondHead->familyHead->name);
    }
}

/**
 * @brief Check if a person is married.
 *
 * This function checks if a person in the Family structure is married by examining their spouse pointer.
 *
 * @param[in] person Pointer to the person to be checked.
 * @return 1 if the person is married, 0 otherwise.
 */
int checkIfMarried(Family *person) {
    // Check if a person is married. Return 1 for yes/0 for no
    if (person->spouse != NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Check if a person's age meets the legal marriage age requirement.
 *
 * This function checks if a person's age meets the legal marriage age requirement.
 *
 * @param[in] age The age of the person to be checked.
 * @return 1 if the age is below the legal marriage age, 0 otherwise.
 */
int checkLegalAge(unsigned int age) {
    // Check if a person is of legal age to marry. return 1 if they are/0 if not
    if (age < LEGAL_MARRIAGE_AGE) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Find the head of the Family to which a person belongs.
 *
 * This function finds the head of the Family to which a person belongs based on their name.
 *
 * @param[in] familyHead Pointer to the head of the Family structure.
 * @param[in] name The name of the person whose Family head is to be found.
 * @return Pointer to the name of the Family head if found, or NULL if not found.
 */
char *findHead(HeadFamily **familyHead, char *name) {
    HeadFamily *head = *familyHead;
    Family *person;
    person = head->familyHead;
    // Traverse down to the leaf node of the Family tree
    while (person->child != NULL) {
        person = person->child;
    }
    // Start searching for the person's name in the Family tree
    while (1) {
        // Traverse through siblings
        while (person->sibling != NULL) {
            if (strcmp(person->name, name) == 0) {
                return head->familyHead->name;
            }
            person = person->sibling;
        }
        // Check the current person
        if (strcmp(person->name, name) == 0) {
            return head->familyHead->name;
        }
        // Move up to the parent node
        if (person->parent != NULL) {
            person = person->parent;
        } else {
            return NULL; // Person is not found in the Family tree
        }
    }
}

/**
 * @brief Marry two non-head individuals.
 *
 * This function marries two individuals who are not Family heads. It checks if the individuals
 * are already married or if they are not of legal age. It also verifies they aren't related.
 *
 * @param[out] personOne Pointer to the first person to be married.
 * @param[out] personTwo Pointer to the second person to be married.
 * @param[in] familyHead Pointer to the head of the Family heads structure.
 * @param[in] firstName The name of the first person.
 * @param[in] secondName The name of the second person.
 * @return 1 if the marriage is invalid, 0 otherwise.
 */
int marryNotHead(Family *personOne, Family *personTwo, HeadFamily **familyHead, char *firstName, char *secondName) {
    char **firstPersonHeads = NULL, **secondPersonHeads = NULL, *temp;
    int i = 0, k = 0, headCount = 0;
    HeadFamily *head = *familyHead, *headCpy = *familyHead, *secondHead = *familyHead;
    // finding the 2 people we know aren't heads
    personOne = findPerson(familyHead, firstName);
    personTwo = findPerson(familyHead, secondName);
    if (personOne == NULL || personTwo == NULL) {
        printf("One of the persons does not exist\n");
        return 1;
    }
    // check if they are already married or if they aren't of legal age
    if (checkIfMarried(personOne) == 1 || checkIfMarried(personTwo) == 1 ||
        checkLegalAge(personOne->age) == 1 ||
        checkLegalAge(personTwo->age) == 1) {
        printf("Invalid marriage\n");
        return 1;
    }
    // count the amount of total heads
    while (headCpy != NULL) {
        headCount++;
        headCpy = headCpy->next;
    }
    // allocating memory to an array of an array of chars, holding all families head's names.
    firstPersonHeads = malloc(headCount * sizeof(char *));
    if (firstPersonHeads == NULL){
        exit(1);
    }
    // a while loop going through all heads
    while (head != NULL) {
        // Using the find head function to compare all names under a head's Family to the name we are looking for
        // if there is a match we receive back the name of the head of that Family, knowing our person is from that Family
        temp = findHead(&head, firstName);
        if (temp != NULL) {
            // allocating memory to a string, inserting it into the array
            firstPersonHeads[i] = (char *) malloc(strlen(temp) + 1);
            strcpy(firstPersonHeads[i], temp);
            i++;
        }
        head = head->next;
    }
    // same as before but for the second person.
    secondPersonHeads = malloc(headCount * sizeof(char *));
    if (secondPersonHeads == NULL){
        exit(1);
    }
    while (secondHead != NULL) {
        temp = findHead(&secondHead, secondName);
        if (temp != NULL) {
            secondPersonHeads[k] = (char *) malloc(strlen(temp) + 1);
            strcpy(secondPersonHeads[k], temp);
            k++;
        }
        secondHead = secondHead->next;
    }
    // Check if the arrays share an element
    if (compareArrays(firstPersonHeads, secondPersonHeads, i, k) == 1) {
        // If they do return 1, else 0
        printf("Invalid marriage\n");
        return 1;
    } else {
        return 0;
    }
}


/**
 * @brief Compare two arrays of strings.
 *
 * This function compares two arrays of strings and checks if there are any matching strings between them.
 *
 * @param[in] firstPersonHeads The first array of strings.
 * @param[in] secondPersonHeads The second array of strings.
 * @param[in] countOne The number of elements in the first array.
 * @param[in] countTwo The number of elements in the second array.
 * @return 1 if there is a match between the arrays, 0 otherwise.
 */
int compareArrays(char **firstPersonHeads, char **secondPersonHeads, int countOne, int countTwo) {
    // Iterate over the elements of the first array
    for (int i = 0; i < countOne; i++) {
        // Iterate over the elements of the second array
        for (int k = 0; k < countTwo; k++) {
            // Compare the strings
            if (strcmp(firstPersonHeads[i], secondPersonHeads[k]) == 0) {
                // Free the allocated memory before returning
                freeArrays(firstPersonHeads, secondPersonHeads, countOne, countTwo);
                // Common element found
                return 1;
            }
        }
    }
    // Free the allocated memory before returning
    freeArrays(firstPersonHeads, secondPersonHeads, countOne, countTwo);
    // No common elements found
    return 0;
}

/**
 * @brief Free the memory allocated for two arrays of strings.
 *
 * This function frees the memory allocated for two arrays of strings.
 *
 * @param[in] firstPersonHeads The first array of strings.
 * @param[in] secondPersonHeads The second array of strings.
 * @param[in] countOne The number of elements in the first array.
 * @param[in] countTwo The number of elements in the second array.
 */
void freeArrays(char **firstPersonHeads, char **secondPersonHeads, int countOne, int countTwo) {
    // Free memory for each element in the first array
    for (int i = 0; i < countOne; i++) {
        free(firstPersonHeads[i]);
    }
    // Free memory for the first array itself
    free(firstPersonHeads);
    // Free memory for each element in the second array
    for (int k = 0; k < countTwo; k++) {
        free(secondPersonHeads[k]);
    }
    // Free memory for the second array itself
    free(secondPersonHeads);
}

/**
 * @brief Make a child under the specified head parents.
 *
 * This function creates a child under the specified head parents.
 *
 * @param[in] firstName The name of the first parent.
 * @param[in] secondName The name of the second parent.
 * @param[in] offspringName The name of the child.
 * @param[in] familyHead The pointer to the head of the Family.
 */
void makeHeadChild(char *firstName, char *secondName, char *offspringName, HeadFamily **familyHead) {
    HeadFamily *head = *familyHead;
    Family *parentOne, *parentTwo, *child = NULL;
    // Get the names of the parents only if they are heads
    parentOne = getHead(&head, firstName);
    parentTwo = getHead(&head, secondName);
    // If they aren't heads, go to the general function makeChild
    if (parentOne == NULL || parentTwo == NULL) {
        // Function for general parents (find person depends on the existence of a child to a parent)
        makeChild(firstName, secondName, offspringName, familyHead);
        return;
    } else {
        // Check if the parents are married
        if (parentOne->spouse != parentTwo && parentTwo->spouse != parentOne) {
            // If they aren't prompt and return
            printf("The parents are not married\n");
            return;
        }
        // Check if the offspring name is already taken
        if (findPerson(familyHead, offspringName) != NULL) {
            // If it isn't prompt and return
            printf("The name is already taken\n");
            return;
        }
        // Create a child and set its properties
        child = setChild(child, parentOne, parentTwo, offspringName);
        // add the child to the list
        addToList(&head, child);
    }
}


/**
 * @brief Set the properties of a child and link it to the specified parents.
 *
 * This function sets the properties of a child and links it to the specified parents.
 *
 * @param[in] child The pointer to the child structure.
 * @param[in] parentOne The pointer to the first parent structure.
 * @param[in] parentTwo The pointer to the second parent structure.
 * @param[in] offspringName The name of the child.
 * @return The pointer to the created child.
 */
Family *setChild(Family *child, Family *parentOne, Family *parentTwo, char *offspringName) {
    Family *sibling;
    // If the head has no children, add the first one through a new linked list of children
    if (parentOne->child == NULL) {
        // allocate memory to the child and his name
        child = (Family *) malloc(sizeof(Family));
        if (child == NULL){
            exit(1);
        }
        child->name = malloc(strlen(offspringName) + 1);
        // Copy the name to child->name
        strcpy(child->name, offspringName);
        // Set child's information to point to his parents, age is 0 everything else NULL
        child->age = 0;
        child->parent = parentOne;
        child->secondParent = parentTwo;
        child->sibling = NULL;
        child->child = NULL;
        child->spouse = NULL;
        parentOne->child = child;
        parentTwo->child = child;
        // Prompt child was born
        printf("%s was born\n", child->name);
        // Return a pointer to child
        return child;
    } else {
        // If the parent has children, travel to the end of their children list and link the new child
        sibling = parentOne->child;
        while (sibling->sibling != NULL) {
            sibling = sibling->sibling;
        }
        // Similar to before, only difference is linking to the siblings list
        sibling->sibling = (Family *) malloc(sizeof(Family));
        if (sibling->sibling == NULL){
            exit(1);
        }
        child = sibling->sibling;
        child->name = malloc(strlen(offspringName) + 1);
        strcpy(child->name, offspringName);
        child->age = 0;
        child->parent = parentOne;
        child->secondParent = parentTwo;
        child->sibling = NULL;
        child->child = NULL;
        child->spouse = NULL;
        printf("%s was born\n", child->name);
        return child;
    }
}

/**
 * @brief Get the head of the Family with the specified name.
 *
 * This function searches for the head of the Family with the specified name
 * within the linked list of Family heads.
 *
 * @param[in] familyHead The pointer to the head of the Family linked list.
 * @param[in] name The name of the head to search for.
 * @return The pointer to the head of the Family if found, otherwise NULL.
 */
Family *getHead(HeadFamily **familyHead, char *name) {
    HeadFamily *head = *familyHead;
    // Traveling through the heads list
    while (head != NULL) {
        // If we find a fitting head, return a pointer to him
        if (strcmp(head->familyHead->name, name) == 0) {
            return head->familyHead;
        }
        // Iterate next head
        head = head->next;
    }
    // If we didn't find the name return NULL
    return NULL;
}

/**
 * @brief Make a child between two parents and add them to the Family.
 *
 * This function creates a child between two parents and adds the child to the Family.
 * It performs various checks, such as verifying the existence of parents, their marital status,
 * and the availability of the given offspring name.
 *
 * @param[in] firstName The name of the first parent.
 * @param[in] secondName The name of the second parent.
 * @param[in] offspringName The name of the child.
 * @param[in] familyHead The pointer to the head of the Family linked list.
 */
void makeChild(char *firstName, char *secondName, char *offspringName, HeadFamily **familyHead) {
    HeadFamily *head = *familyHead;
    Family *parentOne, *parentTwo, *child = NULL;
    // Find the first parent by name
    parentOne = findPerson(familyHead, firstName);
    // Find the second parent by name
    parentTwo = findPerson(familyHead, secondName);
    // If either parent is NULL, they don't exist
    if (parentOne == NULL || parentTwo == NULL) {
        printf("One of the parents does not exist\n");
        return;
    }
    // Check if the parents are not married
    if (parentOne->spouse != parentTwo && parentTwo->spouse != parentOne) {
        printf("The parents are not married\n");
        return;
    }
    // Check if the offspring name is already taken
    if (findPerson(familyHead, offspringName) != NULL) {
        printf("The name is already taken\n");
        return;
    } else {
        // If the name is available, create the child and add to the list
        child = setChild(child, parentOne, parentTwo, offspringName);
        addToList(&head, child);
        return;
    }
}

/**
 * @brief Print the Family tree of a person.
 *
 * This function prints the Family tree of a person, starting from the given person's name.
 * It recursively traverses the Family tree and prints each person along with their spouse (if any).
 *
 * @param[in] familyHead The pointer to the head of the Family linked list.
 * @param[in] name The name of the person to start printing the Family tree from.
 * @param[in] count The indentation level for proper tree structure (default: 0).
 * @param[in,out] person The pointer to the current person being printed (default: NULL).
 */
void printFamily(HeadFamily **familyHead, char *name, int count, Family *person, Family *originalPerson) {
    HeadFamily *head = *familyHead;
    int countCopy;
    person = findPerson(familyHead, name);
    if (count == 0) {
        originalPerson = person;
    }
    countCopy = count;
    // Print the person and their spouse (if any)
    if (person == NULL) {
        printf("The person does not exist\n");
        return;
    }
    // Check if the person has a spouse
    if (person->spouse != NULL) {
        // If they do iterate through the amount of /t needed at print, then print both of them
        while (countCopy > 0) {
            printf("\t");
            countCopy--;
        }
        printf("%s (%u) - %s (%u)\n", person->name, person->age, person->spouse->name, person->spouse->age);
    } else {
        // Else iterate for /ts and print the person alone
        while (countCopy > 0) {
            printf("\t");
            countCopy--;
        }
        printf("%s (%u)\n", person->name, person->age);
    }
    // Recursively print the Family tree of the child (if any)
    if (person->child != NULL) {
        printFamily(&head, person->child->name, ++count, person->child, originalPerson);
        count--;
    }
    // Recursively print siblings that aren't the original person's
    if (person->sibling != NULL && person != originalPerson) {
        printFamily(&head, person->sibling->name, count, person->sibling, originalPerson);
    }
    // A stop condition when the person has been printed and has no siblings/children
    if (person->child == NULL && person->sibling == NULL) {
        return;
    }
}


/**
 * @brief Increase the age of all persons in the Family trees.
 *
 * This function prompts the user to enter the number of years by which the age of all persons in the Family tree should be increased.
 * It then calls the `iterateTree` function to traverse the general persons linked list and update the age of each person.
 *
 * @param[in] familyHead The pointer to the head of the Family linked list.
 */
void raiseAge(HeadFamily **familyHead) {
    // Declare variable of aging
    unsigned int aging = 0;
    // Prompt user to insert a number of years to age
    printf("Enter number of years:\n");
    cleanBuffer(0);
    scanf("%u", &aging);
    cleanBuffer(0);
    // Call to iterateTree to age the people
    iterateTree(familyHead, aging);
}

/**
 * @brief Iterate through the Family tree and increase the age of all persons.
 *
 * This function recursively traverses the Family tree and updates the age of each person by adding the specified number of years.
 *
 * @param[in] familyHead The pointer to the head of the Family linked list.
 * @param[in] aging The number of years to add to the age of each person.
 */
void iterateTree(HeadFamily **familyHead, unsigned int aging) {
    HeadFamily *listNode = *familyHead;
    // Setting person to be the head of the single linked list
    Family *person = listNode->familyHead;
    // Iterate through all people in the program and age them by 'aging'
    while (person != NULL) {
        person->age += aging;
        person = person->next;
    }
}


/**
 * @brief Add a person to the Family list.
 *
 * This function adds a person to the Family list within the Family head. If the list is empty, the person becomes the head of the list. Otherwise, the person is appended to the end of the list.
 *
 * @param[in] familyHead The pointer to the head of the Family linked list.
 * @param[in] person The person to be added to the Family list.
 */
void addToList(HeadFamily **familyHead, Family *person) {
    HeadFamily *head = *familyHead;
    Family *listHead;
    // If the list is empty set its first person to person
    if (head->list->familyHead == NULL) {
        head->list->familyHead = person;
        // Set next to NULL
        head->list->familyHead->next = NULL;
    } else {
        // Else iterate through the list then add the new person to the end of the list
        listHead = head->list->familyHead;
        while (listHead->next != NULL) {
            listHead = listHead->next;
        }
        listHead->next = person;
        listHead->next->next = NULL;
    }
}

/**
 * @brief Count the number of people in the Family tree.
 *
 * This function counts the number of people in the Family tree.
 *
 * @param[in] familyHead The pointer to the head of the Family tree.
 */
void countPeople(HeadFamily **familyHead) {
    int count = 0;
    HeadFamily *listNode = *familyHead;
    // Check if the Family linked list is empty
    if (listNode == NULL) {
        printf("There are 0 people\n");
        return;
    }
    // Check if the Family linked list has a first person and isn't NULL
    if (listNode->familyHead != NULL) {
        Family *person = listNode->familyHead;
        // Traverse the Family linked list and count the number of people
        while (person != NULL) {
            person = person->next;
            count++;
        }
        // Display the appropriate message based on the count
        if (count == 1) {
            printf("There is one person\n");
        } else {
            printf("There are %d people\n", count);
        }
    }
}

/**
 * @brief Find a person in the Family tree by name.
 *
 * This function searches for a person with the given name in the Family trees.
 *
 * @param[in] familyHead The pointer to the head of the Family heads.
 * @param[in] name The name of the person to find.
 * @return A pointer to the found person, or NULL if the person is not found.
 */
Family *findPerson(HeadFamily **familyHead, char *name) {
    HeadFamily *listNode = *familyHead;
    Family *person = listNode->familyHead;
    // Check if the input name is NULL
    if (name == NULL) {
        return NULL;
    }
    // Traverse the Family linked list and search for the person by name
    while (person != NULL) {
        if (strcmp(person->name, name) == 0) {
            // Person found, return the pointer to the person
            return person;
        }
        person = person->next;
    }
    // Person not found, return NULL
    return NULL;
}

/**
 * @brief Print relatives of a person up to a certain degree.
 *
 * This function prompts the user to enter the name of a person and the desired degree of relationship.
 * It then retrieves and prints the relatives of the person up to the specified degree.
 *
 * @param[in] familyHead The pointer to the head of the Family tree.
 */
void printRelatives(HeadFamily **familyHead) {
    char *name, **relativesArray;
    unsigned int degree = 0;
    int count = 0;
    Family *person;
    // Prompt user to enter the name of the person
    printf("Enter the name of the person:\n");
    name = makeString();  // Assuming makeString() is a function that reads a string from input
    // Find the person in the Family tree
    person = findPerson(familyHead, name);
    if (person == NULL) {
        printf("The person does not exist\n");
        free(name);
        return;
    }
    // Prompt user to enter the degree of cousins
    printf("Enter degree:\n");
    scanf("%u", &degree);
    // Create an array of relatives up to the specified degree
    relativesArray = createRelativesArray(person, degree, &count);
    // Ensure the relatives array contains valid pointers to Family members
    relativesArray = ensureArray(relativesArray, &count, familyHead);
    // Sort the relatives array in alphabetical order
    relativesArray = sortRelatives(relativesArray, &count);
    // Print the cousins
    printf("Cousins:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", relativesArray[i]);
    }
     //Free the memory allocated for relatives' names
    for (int i = 0; i < count; i++) {
        free(relativesArray[i]);
    }
     //Free the memory allocated for the relatives array itself
    free(relativesArray);
     //Free the memory allocated for the person's name
    free(name);
}


/**
 * @brief Create an array of relatives for a person up to a certain degree.
 *
 * This function creates an array of relatives for a given person up to a specified degree of relationship.
 * The array includes the person and their relatives such as siblings, cousins, etc.
 *
 * @param[in] person The pointer to the person for whom the relatives array is created.
 * @param[in] degree The maximum degree of relationship to consider.
 * @param[out] count A pointer to an integer to store the count of relatives in the array.
 *
 * @return The dynamically allocated array of relatives.
 It includes the person and their relatives up to the specified degree.
 */
char **createRelativesArray(Family *person, unsigned int degree, int *count) {
    // Array toif (store the relatives' names
    char **relativesArray = NULL;
    // Name of the person
    char *name = person->name;
    // Allocate memory for relativesArray
    relativesArray = malloc(sizeof(char *) * BIG_ARRAY);
    // Allocate memory for the person's name
    relativesArray[*count] = malloc((strlen(name) + 1));
    // Copy the person's name to relativesArray
    strcpy(relativesArray[*count], name);
    // Increment the count of relatives
    (*count)++;
    // If degree is 0, return the relativesArray
    if (degree == 0) {
        return relativesArray;
    } else {
        // Call makeRelativesArray function to populate the relativesArray with more relatives
        for (unsigned int i = 1; i <= degree; i++) {
            makeRelativesArray(person, i, i, count, relativesArray);
        }
    }
    return relativesArray;
}


/**
 * @brief Creates an array of relatives based on the given person and degree of relationship.
 *
 * @param person: Pointer to the current Family member.
 * @param degree: Degree of relationship to consider.
 * @param degreeCpy: Copy of the original degree value.
 * @param count: Pointer to an integer keeping track of the number of relatives.
 * @param relativesArray: Array to store the relatives.
 *
 * @return Pointer to the relativesArray.
 */
void
makeRelativesArray(Family *person, unsigned int degree, unsigned int degreeCpy, int *count, char **relativesArray) {
    // Check if the person is NULL as an exit condition
    if (person == NULL) {
        return;
    }
    // Check if the degree is 0 as a condition to go to the second recursive function to traverse down the tree
    if (degree == 0) {
        // Make sure to go through all the siblings in each level of the family
        while (person != NULL) {
            // Call to RelativeDegree to add relatives to the array recursively
            RelativeDegree(person, degreeCpy, count, relativesArray);
            // Make sure person->sibling isn't NULL if not head to the next sibling
            if (person->sibling != NULL){
                person = person->sibling;
            } else {
                break;
            }
        }
    }
    // Recursively call makeRelativesArray for the parent
    makeRelativesArray(person->secondParent, degree - 1, degreeCpy, count, relativesArray);
    // Recursively call makeRelativesArray for the second parent
    makeRelativesArray(person->parent, degree - 1, degreeCpy, count, relativesArray);
}

/**
 * @brief Traverses a family tree to find relatives up to a specified degree.
 *
 * This function traverses down the family tree, starting from the given person, and collects relatives up to a specified degree.
 *
 * @param person A pointer to the starting person in the family tree.
 * @param degree The degree of relatives to collect.
 * @param count A pointer to an integer to keep track of the number of relatives found.
 * @param relativesArray An array of strings to store the names of relatives.
 *
 * @note The function assumes that `relativesArray` has enough memory to hold the names of all relatives.
 * @note The function assumes that `count` points to a valid memory location.
 *
 * @see checkIfInArray
 */
void RelativeDegree(Family *person, unsigned int degree, int *count, char **relativesArray) {
    // If degree is 0, we traversed down the tree and check if we add to the array
    if (degree == 0) {
        // While loop to check all siblings of a person
        while (person != NULL) {
            // Check if the person is in the array, if not insert into the array
            if (checkIfInArray(person, relativesArray, count) == 0) {
                // Allocate memory for a new name
                relativesArray[(*count)] = malloc(strlen(person->name) + 1);
                if (relativesArray[(*count)] == NULL) {
                    exit(1);
                }
                strcpy(relativesArray[*count], person->name);
                // Increment count
                (*count)++;
            }
            // Go to the next sibling
            person = person->sibling;
        }
    }
    // Only recursively call if the person has a child and isn't NULL
    if (person != NULL && person->child != NULL) {
        RelativeDegree(person->child, degree - 1, count, relativesArray);
    }
}


/**

 * @brief Sorts the relativesArray in alphabetical order.
 *
 * @param relativesArray: Array of relatives to be sorted.
 * @param count: Pointer to an integer representing the number of relatives.
 *
 * @return Pointer to the sorted relativesArray.
 */
char **sortRelatives(char **relativesArray, const int *count) {
    char *temp;
    // Perform bubble sort to sort the relativesArray in alphabetical order
    for (int i = 0; i < *count - 1; i++) {
        for (int j = i + 1; j < *count; j++) {
            if (strcmp(relativesArray[j], relativesArray[i]) < 0) {
                // Swap the relatives if they are out of order
                temp = relativesArray[i];
                relativesArray[i] = relativesArray[j];
                relativesArray[j] = temp;
            }
        }
    }
    return relativesArray;
}

/**

 * @brief that the relativesArray contains all the siblings of the relatives in the array.
 *
 * @param relativesArray: Array of relatives.
 * @param count: Pointer to an integer representing the number of relatives in the array.
 * @param familyHead: Pointer to the head of the Family.
 *
 * @return Pointer to the updated relativesArray.
 */
char **ensureArray(char **relativesArray, int *count, HeadFamily **familyHead) {
    int counter = 0, countMax = *count;
    Family *person = NULL;
    // Iterate through each relative in the relativesArray
    for (int i = 0; i < *count; i++) {
        // Find the corresponding person in the Family tree
        person = findPerson(familyHead, relativesArray[i]);
        // Traverse through the person's siblings and add them to the relativesArray if not already present
        while (person != NULL) {
            if (person->sibling != NULL) {
                person = person->sibling;
            } else {
                break;
            }
            // Check if the sibling is already in the relativesArray
            counter = checkIfInArray(person, relativesArray, count);
            // Add the sibling to the relativesArray if not already present
            if (counter == *count) {
                relativesArray[*count] = (char *) malloc(strlen(person->name) + 1);
                strcpy(relativesArray[*count], person->name);
                (*count)++;
            }
            counter = 0;
        }
        // If the number of relatives has reached the maximum count, return the relativesArray
        if (i == countMax) {
            return relativesArray;
        }
    }
    return relativesArray;
}

/**
 * @brief if a person's name exists in the relativesArray.
 *
 * @param person: Pointer to the Family member to check.
 * @param relativesArray: Array of relatives.
 * @param count: Pointer to an integer representing the number of relatives in the array.
 *
 * @return The position of the person's name in the relativesArray if found, otherwise the count value.
 */
int checkIfInArray(Family *person, char **relativesArray, int *count) {
    // Iterate through each name in the relativesArray and compare it with the person's name
    for (int k = 0; k < *count; k++) {
        if (strcmp(person->name, relativesArray[k]) == 0) {
            // If the person's name is found in the relativesArray, break out of the loop
            return 1;
        }
    }
    return 0;
}
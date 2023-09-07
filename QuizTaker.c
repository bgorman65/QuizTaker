// Importing needed libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Making needed macros
#define FILE_SOURCE "C:\\users\\barry\\CLionProjects\\QuizTaker\\quiz.txt"
#define QUIZ_TYPE "C:\\users\\barry\\CLionProjects\\QuizTaker\\quiztype.txt"

// Function to calculate percentage of test
float percentage(int right, int total){
    float percentage;
    percentage = (float)right/total * 100;
    return percentage;
}

// Function to clear the quiz
void clearQuiz(const char *fileName){
    // Opening file in write mode will clear the file by default
    FILE *input = fopen(fileName, "w");
    fclose(input);
}

// Function to create file
void createFile(char *fileName){
    // Creating file if one does not exist
    FILE *input = fopen(fileName, "a+");
    if(input == NULL){
        printf("Error Creating File\n");
    }
    fclose(input);
}

// Function to create quiz type file
void createQuizFile(char *fileName, char *type){
    // Creating file if one does not exist
    FILE *input = fopen(fileName, "w");
    if(input == NULL){
        printf("Error Creating File\n");
    }
    // Entering key for Type
    fputs(type, input);
    fclose(input);
}

// Function to check if file exists
int checkFile(char *fileName){
    // Opening file to make sure it exists
    FILE *input = fopen(fileName, "r");
    if(input == NULL){
        printf("Error Opening File\n");
        return 1;
    }
    fclose(input);
    return 0;
}

// Function to create muiltiple choice question
void createMultQuestion(char *fileName){
    // Opening file and initializing needed variables
    FILE *input = fopen(fileName, "a");
    char *question, *ans1, *ans2, *ans3, *ans4, *key;
    // Gathering question and asnwers from user
    printf("Enter the Question:");
    scanf("%s", &question);
    printf("Enter the First Answer:");
    scanf("%s", &ans1);
    printf("Enter the Second Answer:");
    scanf("%s", &ans2);
    printf("Enter the Third Answer:");
    scanf("%s", &ans3);
    printf("Enter the Fourth Answer:");
    scanf("%s", &ans4);
    printf("Enter the Correct Answer:");
    scanf("%s", &key);
    // Writing question to file and closing file
    fprintf(input,"%s,%s,%s,%s,%s,%s ", &question, &ans1, &ans2, &ans3, &ans4, &key);
    fclose(input);
}

// Function to create T/F question
void createTFQuestion(char *fileName){
    // Opening file and creating needed variables
    FILE *input = fopen(fileName, "a");
    char *question, *key;
    // Gathering question from user
    printf("Enter the Question:");
    scanf("%s", &question);
    printf("Enter T/F:");
    scanf("%s", &key);
    // Writing question to file and closing file
    fprintf(input,"%s,%s ", &question, &key);
    fclose(input);
}

// Function to create fill in the blank question
void createBlankQuestion(char *fileName){
    // Opening file and creating needed variables
    FILE *input = fopen(fileName, "a");
    char *question, *key;
    // Gathering question from user
    printf("Enter the Question:");
    scanf("%s", &question);
    printf("Enter the answer:");
    scanf("%s", &key);
    // Writing question to file and closing file
    fprintf(input,"%s,%s ", &question, &key);
    fclose(input);
}

// Function to take multiple choice quiz
void takeMultQuiz(char *fileName){
    // Initializing needed variables
    int counter = 0, correct = 0;
    char *question, *one, *two, *three, *four, *key, *answer;
    // Opening file and creating loop to take the quiz
    FILE *input = fopen(fileName, "r");
    while(fscanf(input,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^ ] ", &question, &one, &two, &three, &four, &key) == 6){
        // Incrementing counter
        counter++;
        // Printing question and answer choices
        printf("\nQ%d: %s", counter, &question);
        printf("\n  A: %s", &one);
        printf("\n  B: %s", &two);
        printf("\n  C: %s", &three);
        printf("\n  D: %s", &four);
        printf("\nEnter Answer");
        scanf("%s", &answer);
        // Checking if answer is correct
        if(!strcmp(&key, &answer)){
            correct++;
            printf("Right");
        }
    }
    fclose(input);
    // Printing results from the quiz
    printf("\n***You Got %d Out Of %d Right or a %.2f%%***\n", correct, counter, percentage(correct,counter));
}

// Function to take T/F quiz
void takeTFQuiz(char *fileName){
    // Initializing needed variables
    int counter = 0, correct = 0;
    char *question, *key, *answer;
    // Opening file and creating loop to take the quiz
    FILE *input = fopen(fileName, "r");
    while(fscanf(input,"%[^,],%[^ ] ", &question, &key) == 2){
        // Incrementing counter
        counter++;
        // Printing question and T/F
        printf("\nQ%d: %s", counter, &question);
        printf("\nEnter Answer T/F:");
        scanf("%s", &answer);
        // Checking if answer is correct
        if(!strcmp(&key, &answer)){
            correct++;
            printf("Right");
        }
    }
    fclose(input);
    // Printing results from the quiz
    printf("\n***You Got %d Out Of %d Right or a %.2f%%***\n", correct, counter, percentage(correct,counter));
}

// Function to take fill in the blank quiz
void takeBlankQuiz(char *fileName){
    // Initializing needed variables
    int counter = 0, correct = 0;
    char *question, *key, *answer;
    // Opening file and creating loop to take the quiz
    FILE *input = fopen(fileName, "r");
    while(fscanf(input,"%[^,],%[^ ] ", &question, &key) == 2){
        // Incrementing counter
        counter++;
        // Printing question and answer prompt
        printf("\nQ%d: %s", counter, &question);
        printf("\nEnter Answer:");
        scanf("%s", &answer);
        // Checking if answer is correct
        if(!strcmp(&key, &answer)){
            correct++;
            printf("Right");
        }
    }
    fclose(input);
    // Printing results from the quiz
    printf("\n***You Got %d Out Of %d Right or a %.2f%%***\n", correct, counter, percentage(correct,counter));
}

// Function to create quiz
void createQuiz(const char *fileName,const char *questionFile, int type){
    // Modifying quiz type file and creating question based off type of quiz
    if(type == 1){
        createQuizFile(fileName, "M");
        createMultQuestion(questionFile);
    }else if(type == 2){
        createQuizFile(fileName, "T");
        createTFQuestion(questionFile);
    }else if(type == 3){
        createQuizFile(fileName, "B");
        createBlankQuestion(questionFile);
    }
}

// Function to take quiz
void takeQuiz(const char *typeFile,const char *questionFile){
    // Opening quiz type file
    FILE *input = fopen(typeFile, "r");
    char *type;
    // Gathering type of quiz
    fscanf(input, "%s", &type);
    // Navigating to take quiz based off quiz type
    if(!strcmp(&type,"M")){
        takeMultQuiz(questionFile);
    }else if(!strcmp(&type,"T")){
        takeTFQuiz(questionFile);
    }else if(!strcmp(&type,"B")){
        takeBlankQuiz(questionFile);
    }
}

// Main Function
int main() {
    printf("****Quiz Taker and Manager****\n\n");
    // Creating file to store quiz in
    createFile(FILE_SOURCE);
    // If file does not exist returning one and exiting the program
    if(checkFile(FILE_SOURCE)){
        return 1;
    }
    // Creating loop to handle options in the program
    int action;
    do{
        printf("*****Main Menu*****\n");
        printf("1: Create A Multiple Choice Quiz\n");
        printf("2: Create A True/False Quiz\n");
        printf("3: Create A Fill In The Blank Quiz\n");
        printf("4: Take the Quiz\n");
        printf("5: Clear The Quiz\n");
        printf("6: Exit\n");
        printf("Enter an Action:");
        scanf("%d", &action);
        switch(action){
            case 1:
                createQuiz(QUIZ_TYPE, FILE_SOURCE, 1);
                break;
            case 2:
                createQuiz(QUIZ_TYPE, FILE_SOURCE, 2);
                break;
            case 3:
                createQuiz(QUIZ_TYPE, FILE_SOURCE, 3);
                break;
            case 4:
                takeQuiz(QUIZ_TYPE, FILE_SOURCE);
                break;
            case 5:
                clearQuiz(FILE_SOURCE);
                break;
        }
    }while(action < 6);
    return 0;
}
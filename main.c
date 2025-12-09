#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

// FUNCTION DECLARATIONS
void loadSentence(char *sentence);
void countdown();
void printColored(char expected, char typed);
double realTimeTyping(char *sentence, char *typed, int *mistakes);
double calculateAccuracy(char *sentence, char *typed);
double calculateWPM(char *sentence, double timeTaken);
void printResults(double timeTaken, double accuracy, double wpm, int mistakes);

// New game modes
void randomWordGame();
void randomLetterGame();

// Load sentence from file
void loadSentence(char *sentence)
{
    FILE *fp = fopen("sentence.txt", "r");
    if (!fp)
    {
        printf("Could not open file\n");
        exit(1);
    }
    fgets(sentence, 200, fp);
    sentence[strcspn(sentence, "\n")] = 0;
    fclose(fp);
}

// Countdown
void countdown()
{
    printf("Starting in:\n");
    for (int i = 3; i >= 1; i--)
    {
        printf("%d...\n", i);
        Sleep(1000);
    }
    printf("Go!\n\n");
}

// Print colored char
void printColored(char expected, char typed)
{
    if (typed == expected)
        printf(GREEN "%c" RESET, typed);
    else
        printf(RED "%c" RESET, typed);
}

// REAL-TIME TYPING WITH BACKSPACE
double realTimeTyping(char *sentence, char *typed, int *mistakes)
{
    int index = 0;
    int len = strlen(sentence);

    time_t start = time(NULL);

    while (index < len)
    {
        char c = getch();

        if (c == 8)
        {
            if (index > 0)
            {
                printf("\b \b");
                index--;
            }
            continue;
        }

        typed[index] = c;

        if (c == sentence[index])
            printColored(sentence[index], c);
        else
        {
            printColored(sentence[index], c);
            (*mistakes)++;
        }

        index++;
    }

    typed[index] = '\0';
    time_t end = time(NULL);
    return difftime(end, start);
}

// Accuracy
double calculateAccuracy(char *sentence, char *typed)
{
    int len = strlen(sentence);
    int correct = 0;
    for (int i = 0; i < len; i++)
        if (sentence[i] == typed[i])
            correct++;
    return (double)correct / len * 100.0;
}

// WPM
double calculateWPM(char *sentence, double timeTaken)
{
    int words = 1;
    for (int i = 0; sentence[i]; i++)
        if (sentence[i] == ' ')
            words++;
    return (words / (timeTaken / 60.0));
}

// Results
void printResults(double timeTaken, double accuracy, double wpm, int mistakes)
{
    printf("\n\n===== RESULTS =====\n");
    printf("Time: %.2f sec\n", timeTaken);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Mistakes: %d\n", mistakes);
    printf("WPM: %.2f\n", wpm);
}

/* =====================================================
        🎮 GAME MODE 1 : RANDOM WORD TYPING TEST
   ===================================================== */
void randomWordGame()
{
    printf("\n\n===== RANDOM WORD TYPING TEST (10 WORDS) =====\n");
    printf("You will get 10 random words.\n");
    printf("Type each word and press SPACE or ENTER.\n");
    printf("Press any key to start...");
    getch();

    countdown();

    int totalWords = 10;
    char generated[20], typed[20];
    int correctWords = 0, mistakes = 0;
    time_t start = time(NULL);

    for (int w = 1; w <= totalWords; w++)
    {
        // generate random word (3–10 letters)
        int length = 3 + rand() % 8;
        for (int i = 0; i < length; i++)
            generated[i] = 'a' + rand() % 26;
        generated[length] = '\0';

        printf("\nWord %d: %s\n", w, generated);
        printf("Type: ");

        scanf("%s", typed);

        if (strcmp(generated, typed) == 0)
        {
            correctWords++;
        }
        else
        {
            mistakes++;
        }
    }

    time_t end = time(NULL);
    double timeTaken = difftime(end, start);

    double accuracy = ((double)correctWords / totalWords) * 100.0;
    double wpm = (totalWords / (timeTaken / 60.0));

    printf("\n\n===== RESULTS =====\n");
    printf("Words typed: %d\n", totalWords);
    printf("Correct words: %d\n", correctWords);
    printf("Mistakes: %d\n", mistakes);
    printf("Time: %.2f sec\n", timeTaken);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("WPM: %.2f\n", wpm);
}

/* =====================================================
        🎯 GAME MODE 2 : RANDOM LETTER REACTION TEST
   ===================================================== */

void randomLetterGame()
{
    printf("\n\n===== RANDOM LETTER REACTION TEST (10 LETTERS) =====\n");
    printf("A random *uppercase or lowercase* letter will appear.\n");
    printf("Type the SAME letter as fast as possible.\n");
    printf("Press any key to start...");
    getch();

    countdown();

    int totalLetters = 10;
    int correct = 0, mistakes = 0;

    time_t start = time(NULL);

    for (int i = 1; i <= totalLetters; i++)
    {
        // Random uppercase or lowercase letter
        char letter;
        if (rand() % 2 == 0)
            letter = 'A' + rand() % 26; // uppercase
        else
            letter = 'a' + rand() % 26; // lowercase

        printf("\nLetter %d: %c\n", i, letter);

        char typed = getch();

        printf("You pressed: %c\n", typed);

        if (typed == letter)
            correct++;
        else
            mistakes++;
    }

    time_t end = time(NULL);
    double timeTaken = difftime(end, start);

    double accuracy = ((double)correct / totalLetters) * 100.0;
    double lpm = (totalLetters / (timeTaken / 60.0)); // letters per minute

    printf("\n\n===== RESULTS =====\n");
    printf("Total letters: %d\n", totalLetters);
    printf("Correct: %d\n", correct);
    printf("Mistakes: %d\n", mistakes);
    printf("Time taken: %.2f sec\n", timeTaken);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("Speed: %.2f LPM (letters per minute)\n", lpm);
}

/* =====================================================
                     MAIN MENU
   ===================================================== */
int main()
{
    srand(time(0));

    while (1)
    {
        printf("\n\n===== SELECT A GAME MODE =====\n");
        printf("1. Real-time sentence typing test\n");
        printf("2. Random word typing test\n");
        printf("3. Random letter reaction test\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        int choice;
        scanf("%d", &choice);
        getchar(); // remove newline

        if (choice == 1)
        {
            char sentence[200], typed[200];
            int mistakes = 0;

            loadSentence(sentence);

            printf("\n===== REAL-TIME TYPING TEST =====\n");
            printf("Type this:\n\n%s\n\n", sentence);

            printf("Press ENTER to start...");
            getchar();

            countdown();

            double timeTaken = realTimeTyping(sentence, typed, &mistakes);
            double accuracy = calculateAccuracy(sentence, typed);
            double wpm = calculateWPM(sentence, timeTaken);

            printResults(timeTaken, accuracy, wpm, mistakes);
        }
        else if (choice == 2)
        {
            randomWordGame();
        }
        else if (choice == 3)
        {
            randomLetterGame();
        }
        else if (choice == 4)
        {
            printf("Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <time.h>

int main()
{

    FILE *fp = fopen("sentence.txt", "r");
    if (fp == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    char sentence[200], typed[200];
    fgets(sentence, sizeof(sentence), fp); // read one sentence
    fclose(fp);

    // Remove newline
    sentence[strcspn(sentence, "\n")] = 0;

    printf("===== Typing Speed Test =====\n");
    printf("Type this sentence:\n\n%s\n\n", sentence);

    printf("Press ENTER to start...");
    getchar(); // wait

    time_t start = time(NULL);

    printf("\nStart typing:\n");
    fgets(typed, sizeof(typed), stdin);

    time_t end = time(NULL);
    double timeTaken = difftime(end, start);

    // Accuracy calculation
    int correct = 0, len = strlen(sentence);
    for (int i = 0; i < len; i++)
    {
        if (typed[i] == sentence[i])
        {
            correct++;
        }
    }
    double accuracy = (double)correct / len * 100;

    // Word count
    int words = 1;
    for (int i = 0; sentence[i]; i++)
    {
        if (sentence[i] == ' ')
            words++;
    }

    double wpm = (words / (timeTaken / 60.0));

    printf("\n===== RESULT =====\n");
    printf("Time: %.2f sec\n", timeTaken);
    printf("Accuracy: %.2f%%\n", accuracy);
    printf("WPM: %f\n", wpm);

    return 0;
}
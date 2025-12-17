#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void save_score(int w, int l) {
    FILE *f = fopen("score.txt", "w");
    if (f != NULL) {
        fprintf(f, "%d %d", w, l);
        fclose(f);
    }
}

void high_score(int w, int l){
    FILE *f = fopen("highscore.txt", "r");
    int high_w = 0, high_l = 0;
    if (f != NULL) {
        fscanf(f, "%d %d", &high_w, &high_l);
        fclose(f);
    }

    if(w > high_w){
        f = fopen("highscore.txt", "w");
        if (f != NULL) {
            fprintf(f, "%d %d", w, l);
            fclose(f);
            printf("New High Score! Wins: %d | Losses: %d\n", w, l);
        }
    } else {
        printf("High Score remains - Wins: %d | Losses: %d\n", high_w, high_l);
    }
}

void load_score(int *w, int *l) {
    FILE *f = fopen("score.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d %d", w, l);
        fclose(f);
    } else {
        *w = 0;
        *l = 0;
    }
}

void printHangman(int livesLeft) {
    int wrong = 6 - livesLeft;
    printf("---------\n");
    printf("|       |\n");
    if (wrong >= 1) printf("|       O\n");
    else            printf("|        \n");
    if (wrong == 2)      printf("|       |\n");
    else if (wrong == 3) printf("|      /|\n");
    else if (wrong >= 4) printf("|      /|\\\n");
    else                 printf("|        \n");
    if (wrong == 5)      printf("|      /\n");
    else if (wrong >= 6) printf("|      / \\\n");
    else                 printf("|        \n");
    printf("|\n");
    printf("=============\n\n");
}

/* Here sizes are hardcoded: up to 100 words, each up to 49 chars (+ '\0') */
int load_technology(char words[][50], char hints[][50]) {
    FILE *f = fopen("words.txt", "r");
    if (!f) {
        printf("Could not open words.txt\n");
        return 0;
    }

    int count = 0;
    while (count < 100 && fscanf(f, "%49s %49[^\n]", words[count], hints[count]) == 2) {
        count++;
    }

    fclose(f);
    return count;
}

int load_countries(char words[][50], char hints[][50]) {
    FILE *f = fopen("countries.txt", "r");
    if (!f) {
        printf("Could not open countries.txt\n");
        return 0;
    }

    int count = 0;
    while (count < 100 && fscanf(f, "%49s %49[^\n]", words[count], hints[count]) == 2) {
        count++;
    }

    fclose(f);
    return count;
}

int load_fruits(char words[][50], char hints[][50]) {
    FILE *f = fopen("fruits.txt", "r");
    if (!f) {
        printf("Could not open fruits.txt\n");
        return 0;
    }

    int count = 0;
    while (count < 100 && fscanf(f, "%49s %49[^\n]", words[count], hints[count]) == 2) {
        count++;
    }

    fclose(f);
    return count;
}
int load_animals(char words[][50], char hints[][50]) {
    FILE *f = fopen("animals.txt", "r");
    if (!f) {
        printf("Could not open animals.txt\n");
        return 0;
    }

    int count = 0;
    while (count < 100 && fscanf(f, "%49s %49[^\n]", words[count], hints[count]) == 2) {
        count++;
    }

    fclose(f);
    return count;
}
int load_movies(char words[][50], char hints[][50]) {
    FILE *f = fopen("movies.txt", "r");
    if (!f) {
        printf("Could not open movies.txt\n");
        return 0;
    }

    int count = 0;
    while (count < 100 && fscanf(f, "%49s %49[^\n]", words[count], hints[count]) == 2) {
        count++;
    }

    fclose(f);
    return count;
}

int main() {
    int w, l;
    load_score(&w, &l);

    int mode;
    printf("Select Mode:\n1. Single Player\n2. Multiplayer \nEnter choice: ");
    scanf("%d", &mode);
    
if(mode == 2){
        char word[50];
        char hint[100];
        printf("Player 1, enter the word to be guessed: ");
        scanf("%49s", word);
        printf("Player 1, enter a hint for the word: ");
        scanf(" %99s", hint);


    // Convert word to lowercase to match guess logic
    for (int i = 0; word[i]; i++) {
        word[i] = (char)tolower(word[i]);
    }

        int wordLength = strlen(word);
        char guessed[50];
        for (int i = 0; i < wordLength; i++) {
            guessed[i] = '_';
        }
        guessed[wordLength] = '\0';

        int lives = 7;
        int won = 0;
        char guess;
        int found;
        time_t start = time(NULL);
        int time_limit = 60; // seconds for each session

        printf("\n*** WELCOME TO HANGMAN GAME - MULTIPLAYER ***\n");
        printf("Player 2, guess the word letter by letter!\n"); 
        printf("You have %d lives.\n", lives);
        printf("Hint: %s\n\n", hint);
        while (lives > 0) {
            time_t now = time(NULL);
            int elapsed = (int)(now - start);
            if (elapsed >= time_limit) {
                printf("\nTime's up! You ran out of time.\n");
                break;  // exits loop, counts as not won
            }

            printf("Time remaining: %d seconds\n", time_limit - elapsed);

            printHangman(lives);
            printf("\nWord: ");
            for (int i = 0; i < wordLength; i++) {
                printf("%c ", guessed[i]);
            }
            printf("\n");

            if (strcmp(word, guessed) == 0) {
                won = 1;
                break;
            }

            printf("Lives remaining: %d\n", lives);
            printf("Enter a letter: ");
            scanf(" %c", &guess);
            guess = tolower(guess);

            int border = 0;
            for (int i = 0; i < wordLength; i++) {
                if (guess == guessed[i]) {
                    border = 1;
                }
            }

            if (border == 1) {
                printf("You already guessed that letter! Try again.\n");
                continue;
            }

            found = 0;
            for (int i = 0; i < wordLength; i++) {
                if (word[i] == guess) {
                    guessed[i] = guess;
                    found = 1;
                }
            }

            if (found == 0) {
                printf("\nWrong guess! You lose a life.\n");
                Beep(500, 1000);
                lives--;
            } else {
                printf("\nGood guess!\n");
                Beep(1000, 500);
            }
        }
        printf("\n=====================================\n");
        if (won == 1) {
            printf(" CONGRATULATIONS! YOU WON! \n");
            printf("The word was: %s\n", word);
            w++;
        } else {
            printf("GAME OVER! You lost!\n");
            printf("The word was: %s\n", word);
            l++;
        }
        main();
    
    }
else{
    char words[100][50];
    char hints[100][50];
    char choice[20];
    int total = 0;
    printf("What category would you like to choose? (Countries, Technology, Animals, Fruits, Movies): ");
    scanf("%19s", &choice);

    for (int i = 0; choice[i]; i++) {
        choice[i] = tolower(choice[i]);
    }
    printf("%s\n", choice);

    if(strcmp(choice,"countries")==0){
        total = load_countries(words, hints);
        printf("Loaded Countries!\n");
    }
    else if(strcmp(choice,"movies")==0){
        total = load_movies(words, hints);
        printf("Loaded Movies!\n");
    } 
    else if(strcmp(choice,"technology")==0){
        total = load_technology(words, hints);
        printf("Loaded Technology!\n");
    }
    else if(strcmp(choice,"animals")==0){
        total = load_animals(words, hints);
        printf("Loaded Animals!\n");
    }
    else if(strcmp(choice,"fruits")==0){
        total = load_fruits(words, hints);
        printf("Loaded Fruits!\n");
    }
    
    else{
        printf("Invalid choice. Defaulting to Technology.\n");
        total = load_technology(words, hints);
        printf("Loaded Technology!\n");
    }

    if(total == 0) {
        printf("No words loaded. Exiting.\n");
        return 1;
    }
    char difficulty[10];
    int lives;
    int time_limit;

    printf("Choose difficulty (Easy, Medium, Hard): ");
    scanf("%9s", difficulty);
    for (int i = 0; difficulty[i]; i++) {
        difficulty[i] = tolower(difficulty[i]);
    }

    if (strcmp(difficulty, "easy") == 0) {
        time_limit = 60; // seconds for each session
        lives = 10;
    } else if (strcmp(difficulty, "medium") == 0) {
        time_limit = 45; // seconds for each session
        lives = 7;
    } else if (strcmp(difficulty, "hard") == 0) {
        time_limit = 30; // seconds for each session
        lives = 5;
    } else {
        printf("Invalid choice. Defaulting to Medium.\n");
        time_limit = 45; // seconds for each session
        lives = 7;
    }

    srand(time(NULL));
    int idx = rand() % total;

    char word[50];
    strcpy(word, words[idx]);
    char hint[50];
    strcpy(hint, hints[idx]);

    int wordLength = strlen(word);

    char guessed[50];
    for (int i = 0; i < wordLength; i++) {
        guessed[i] = '_';
    }
    guessed[wordLength] = '\0';

    int won = 0;
    char guess;
    int found;
    time_t start = time(NULL);

    printf("\n*** WELCOME TO HANGMAN GAME ***\n");
    printf("Guess the word letter by letter!\n");
    printf("You have %d lives.\n", lives);
    printf("Hint: %s\n\n", hint);

    while (lives > 0) {
         time_t now = time(NULL);
        int elapsed = (int)(now - start);
        if (elapsed >= time_limit) {
            printf("\nTime's up! You ran out of time.\n");
            break;  // exits loop, counts as not won
        }

        printf("Time remaining: %d seconds\n", time_limit - elapsed);

        printHangman(lives);
        printf("\nWord: ");
        for (int i = 0; i < wordLength; i++) {
            printf("%c ", guessed[i]);
        }
        printf("\n");

        if (strcmp(word, guessed) == 0) {
            won = 1;
            break;
        }

        printf("Lives remaining: %d\n", lives);
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        int border = 0;
        for (int i = 0; i < wordLength; i++) {
            if (guess == guessed[i]) {
                border = 1;
            }
        }

        if (border == 1) {
            printf("You already guessed that letter! Try again.\n");
            continue;
        }

        found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess) {
                guessed[i] = guess;
                found = 1;
            }
        }

        if (found == 0) {
            printf("\nWrong guess! You lose a life.\n");
            // PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Beep(500, 1000);
            lives--;
        } else {
            printf("\nGood guess!\n");
            // PlaySound(TEXT("correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Beep(1000, 500);
        }
    }

    printf("\n=====================================\n");
    if (won == 1) {
        printf(" CONGRATULATIONS! YOU WON! \n");
        printf("The word was: %s\n", word);
        w++;
    } else {
        printf("GAME OVER! You lost!\n");
        printf("The word was: %s\n", word);
        l++;
    }

    printf("Wins: %d | Losses: %d\n", w, l);
    printf("Winning percentage : %.2f\n", (float)w / (w + l) * 100);
    printf("=====================================\n\n");

    char play_again;
    printf("Wanna Play Again? (Y/N): ");
    scanf(" %c", &play_again);
    play_again = tolower(play_again);

    if (play_again == 'y') {
        save_score(w, l);
        main();
    } 
    else if (play_again == 'n') {
        high_score(w, l);
        printf("\nThanks for playing!\n");
        save_score(0, 0);
        return 0;
    }

    return 0;
}
}

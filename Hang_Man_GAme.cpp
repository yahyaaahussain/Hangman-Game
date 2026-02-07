#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<vector<string>> categories = {
    {"apple", "banana", "cherry", "grape", "kiwi", "melon"},
    {"ferrari", "toyota", "bmw", "audi", "ford", "mercedes"},
    {"artificial", "quantum", "robotics", "nanotech", "cyber", "blockchain"},
    {"harley", "ducati", "yamaha", "kawasaki", "honda", "suzuki"},
    {"lipstick", "foundation", "blush", "mascara", "eyeshadow", "highlighter"},
    {"iphone", "samsung", "nokia", "oneplus", "xiaomi", "oppo"},
    {"macbook", "dell", "hp", "lenovo", "acer", "asus"},
    {"soccer", "basketball", "cricket", "baseball", "tennis", "rugby"},
    {"brazil", "canada", "india", "france", "germany", "japan"},
    {"inception", "matrix", "gladiator", "avatar", "joker", "titanic"}
};

const vector<int> maxAttempts = {8, 6, 4};

void drawHangman(int attemptsLeft);
void displayInfo(const string& category, int level, int stage, const string& currentWord, int attemptsLeft, const vector<char>& guessedLetters);
string getRandomWord(const vector<string>& words);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    char playAgain;

    do {
        int level = 1, stage = 1, attemptsLeft = maxAttempts[0];
        string category = "Fruits";
        string secretWord = getRandomWord(categories[0]);
        string currentWord(secretWord.length(), '_');
        vector<char> guessedLetters;

        cout << "Welcome to Hangman!\n";

        while (stage <= 3 && level <= 10 && attemptsLeft > 0) {
            displayInfo(category, level, stage, currentWord, attemptsLeft, guessedLetters);

            char guess;
            cout << "Guess a letter: ";
            cin >> guess;

            if (!isalpha(guess)) {
                cout << "Please enter a valid letter.\n";
                continue;
            }

            guess = tolower(guess);

            if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                cout << "You've already guessed that letter.\n";
                continue;
            }

            guessedLetters.push_back(guess);
            bool correct = false;

            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == guess) {
                    currentWord[i] = guess;
                    correct = true;
                }
            }

            if (correct) {
                cout << "Good guess!\n";
                if (currentWord == secretWord) {
                    cout << "Congratulations! You guessed the word!\n";
                    if (++level > 10) {
                        cout << "You won the game!\n";
                        break;
                    }

                    stage++;
                    category = vector<string>{"Fruits", "Cars", "Technology", "Bikes", "Makeup", "Mobiles", "Laptops", "Sports", "Countries", "Movies"}[level - 1];
                    secretWord = getRandomWord(categories[level - 1]);
                    currentWord = string(secretWord.length(), '_');
                    guessedLetters.clear();
                    attemptsLeft = maxAttempts[min(level / 4, 2)];
                    system("cls");
                }
            } else {
                cout << "Incorrect guess.\n";
                drawHangman(--attemptsLeft);
            }
        }

        if (attemptsLeft == 0) {
            cout << "You've run out of attempts. The word was: " << secretWord << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (tolower(playAgain) == 'y');

    cout << "Thank you for playing Hangman! Goodbye!\n";
    return 0;
}

void drawHangman(int attemptsLeft) {
    if (attemptsLeft == 8) {
        cout << "   " << endl;
        cout << "  |     " << endl;
        cout << "  |     " << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 7) {
        cout << "   _____" << endl;
        cout << "  |     " << endl;
        cout << "  |     " << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 6) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     " << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
    else if (attemptsLeft == 5) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    } else if (attemptsLeft == 4) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |     |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    } else if (attemptsLeft == 3) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    } else if (attemptsLeft == 2) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|\\" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    } else if (attemptsLeft == 1) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|\\" << endl;
        cout << "  |    /" << endl;
        cout << "  |" << endl;
        cout << "  |" << endl;
    } else if (attemptsLeft == 0) {
        cout << "   _____" << endl;
        cout << "  |     |" << endl;
        cout << "  |     O" << endl;
        cout << "  |    /|\\" << endl;
        cout << "  |    / \\ "<<endl;      
        cout << "  |" << endl;
        cout << "  |" << endl;
    }
}

void displayInfo(const string& category, int level, int stage, const string& currentWord, int attemptsLeft, const vector<char>& guessedLetters) {
    cout << "Category: " << category << endl;
    cout << "Level: " << level << ", Stage: " << stage << endl;
    cout << "Word: " << currentWord << endl;
    cout << "Attempts left: " << attemptsLeft << endl;
    cout << "Guessed letters: ";
    for (char letter : guessedLetters) cout << letter << " ";
    cout << endl;
}

string getRandomWord(const vector<string>& words) {
    return words[rand() % words.size()];
}

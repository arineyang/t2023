#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#define M 10
#define N 5

int main()
{
    srand(time(NULL)); // seed random number generator with current time
    string choice;

    //-------------------------PT1-------------------------
    cout << "Do you wanna take vocabulary test of basic level (Yes/No) ? ";
    getline(cin, choice);
    if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "Y" || choice == "y")
    {
        vector<vector<string>> wordsBasic(M); // vector of words for each level
        string filename;
        for (int i = 0; i < M; i++)
        {
            filename = "level" + to_string(i + 1) + ".txt"; // level1.txt, level2.txt, ...
            ifstream infile(filename);
            if (!infile.is_open())
            {
                cout << "Error opening file " << filename << endl;
                return 1;
            }
            string word;
            while (infile >> word)
            {
                wordsBasic[i].push_back(word);//push_back() is used to push elements into a vector from the back
            }
            infile.close();
        }

        int score = 0;
        for (int i = 0; i < M; i++)
        {
            cout << "Test of Basic Level " << i + 1 << endl;
            for (int j = 0; j < M; j++)
            {
                int index = rand() % wordsBasic[i].size(); // randomly choose a word from the current level
                cout << "Do you know the word \"" << wordsBasic[i][index] << "\"? (1. master! /2. only a little bit/3. idk): ";
                getline(cin, choice);
                if (choice == "master" || choice == "1")
                {
                    score += 3;
                }
                else if (choice == "only" || choice == "only a little bit" || choice == "2")
                {
                    score += 1;
                }
                // if the user chooses "don't know", no points are awarded
            }
        }

        cout << "Your score of basic level is: " << score << "!\n"
            << "Congratulations! you have an estimated vocabulary of " << (int)((float)(score) / 300.0 * 10000.0) << " words!\n\n" << endl;

    }
    //if no, skip


    //-------------------------PT2-------------------------
    cout << "Do you wanna take vocabulary test of advanced level (Yes/No) ? ";
    getline(cin, choice);
    if (choice == "yes" || choice == "Yes" || choice == "YES" || choice == "Y" || choice == "y")
    {
        vector<vector<string>> wordsAdvanced(N); // vector of words for each level
        string filename;
        for (int i = 0; i < N; i++)
        {
            filename = "vlevel" + to_string(i + 1) + ".txt"; // vlevel1.txt, vlevel2.txt, ...
            ifstream infile(filename);
            if (!infile.is_open())
            {
                cout << "Error opening file " << filename << endl;
                return 1;
            }
            string word;
            while (infile >> word)
            {
                wordsAdvanced[i].push_back(word);//push_back() is used to push elements into a vector from the back
            }
            infile.close();
        }

        int score = 0;
        string choice;
        for (int i = 0; i < N; i++)
        {
            cout << "Test of Advanced Level " << i + 1 << endl;
            for (int j = 0; j < N; j++)
            {
                int index = rand() % wordsAdvanced[i].size(); // randomly choose a word from the current level
                cout << "Do you know the word \"" << wordsAdvanced[i][index] << "\"? (1. master! /2. only a little bit/3. idk): ";
                getline(cin, choice);
                if (choice == "master" || choice == "1")
                {
                    score += 3;
                }
                else if (choice == "only" || choice == "only a little bit" || choice == "2")
                {
                    score += 1;
                }
                // if the user chooses "don't know", no points are awarded
            }
        }

        cout << "Your score of advanced level is: " << score << "!\n"
            << "Congratulations! you have an estimated vocabulary of " << (int)((float)(score) / 150.0 * 50000.0) << " words!\n\n" << endl;
    }
    //if no, skip

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

vector<string> splitBySpace(string sentence)
{
    stringstream ss(sentence);
    vector<string> words;
    string word;

    while (ss >> word)
    {
        words.push_back(word);
    }

    return words;
}

int canBeTypedWords(string text, string brokenLetters)
{

    unordered_set<char> setBroken;
    for (char &l : brokenLetters)
    {
        setBroken.insert(l);
    }

    bool isBroken = false;
    int count = 0;

    for (char &c : text)
    {

        if (c == ' ')
        {
            if (!isBroken)
            {
                count++;
            }
            isBroken = false;
            continue;
        }

        if (setBroken.find(c) != setBroken.end())
        {
            isBroken = true;
        }
    }

    if (!isBroken)
    {
        count++;
    }

    return count;
}

int main()
{
    return 0;
}
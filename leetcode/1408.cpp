#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <map>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
using namespace std;

struct SuffixTreeNode
{
    map<char, SuffixTreeNode> child;
    // Stores indexes of words that pass through this node
    vector<int> wordIndexs;
};

class SuffixTree {
    private:
     SuffixTreeNode* root;

    void insert(const string &word, int wordIndex)
    {
        for (int i = 0; i < word.size(); i++)
        {
            SuffixTreeNode *current = root;
            for(auto &c : word){

            }
        }
    }
};


vector<string> stringMatching(vector<string> &words)
{
    // std::sort(words.begin(), words.end(), [](const string &a, const string &b)
    //           { return a.size() < b.size(); });

    vector<string> rs;
    unordered_set<string> memo;

    for (int i = 0; i < words.size(); i++)
    {
        for (int j = 0; j < words.size(); j++)
        {
            if (i == j)
                continue;

            if (words[j].find(words[i]) != std::string::npos)
            {
                rs.push_back(words[i]);

                break;
            }
        }
    }

    return rs;
}
int main()
{
    vector<string> words;
    cout << stringMatching(words);
    return 0;
}
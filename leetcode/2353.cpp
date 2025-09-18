#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>

using namespace std;

// summarize we have 3 list contain n elements: foods is name of dish , cuisines is type of food[i], then ratings is list contain rating of food with i-index

// initial object.
// change rating of food.
// find highest rating of food by cuisine, if tie , return name food lexicographically in alphabet

class Food
{
public:
    int rating;
    string name;

    Food(int foodRating, string foodName)
    {
        this->rating = foodRating;
        this->name = foodName;
    }

    bool operator<(const Food &other) const
    {
        if (rating == other.rating)
            return name > other.name;

        return rating < other.rating;
    }
};
class FoodRatings
{
private:
    int N;

    vector<string> foods;
    vector<string> cuisines;
    vector<int> ratings;

    unordered_map<string, string> mapFoodCuisine;

    unordered_map<string, std::priority_queue<Food>> mapHighestRate;

    unordered_map<string, int> mapFoodIndex;

    bool isLexicographically(string a, string b) { return a > b; }

public:
    FoodRatings(vector<string> &foods, vector<string> &cuisines,
                vector<int> &ratings)
    {

        this->foods = foods;
        this->cuisines = cuisines;
        this->ratings = ratings;

        N = foods.size();

        for (int i = 0; i < N; i++)
        {
            string cuisine = cuisines[i];

            mapFoodCuisine[foods[i]] = cuisines[i];
            mapFoodIndex[foods[i]] = i;
            mapHighestRate[cuisine].push(Food(ratings[i], foods[i]));
        }
    }

    void changeRating(string food, int newRating)
    {
        int index = mapFoodIndex[food];
        this->ratings[index] = newRating;
        string cuisine = cuisines[index];
        auto &pg = mapHighestRate[cuisine];

        pg.push(Food(this->ratings[index], foods[index]));
    }

    string highestRated(string cuisine)
    {
        auto &pq = mapHighestRate[cuisine];
        auto highestRate = pq.top();
        int index = mapFoodIndex[highestRate.name];

        while (highestRate.rating != ratings[index])
        {
            pq.pop();
            highestRate = pq.top();
        }

        return highestRate.name;
    }
};
int main()
{
    return 0;
}
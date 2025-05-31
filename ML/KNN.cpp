#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <queue>
#include <limits>

using namespace std;

struct DataPoint
{
    vector<double> features;
    string label;
    double value;
    bool isRegression;
};

struct DistanceIndex
{
    double distance;
    size_t index;

    bool operator<(const DistanceIndex &other) const
    {
        return distance < other.distance;
    }
};

class KNNBasic
{

private:
    vector<DataPoint> trainingData;
    int k;
    bool isRegression;

    // Calculate Euclidean distance between two feature vectors
    double euclideanDistance(const vector<double> &a, const vector<double> &b)
    {
        if (a.size() != b.size())
        {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        double sum = 0.0;
        for (size_t i = 0; i < a.size(); i++)
        {
            sum += pow(a[i] - b[i], 2);
        }

        return sqrt(sum);
    }

    /**
     * @brief Alternate distance metrics can be added here
     */
    double manhattanDistance(const std::vector<double> &a, const std::vector<double> &b)
    {
        if (a.size() != b.size())
        {
            throw std::invalid_argument("Vectors must have the same dimension");
        }

        double sum = 0.0;
        for (size_t i = 0; i < a.size(); i++)
        {
            sum += std::abs(a[i] - b[i]);
        }

        return sum;
    }

public:
    KNNBasic(int kValue, bool regression = false) : k(kValue), isRegression(regression)
    {
        if (k <= 0)
        {
            throw std::invalid_argument("k must be positive");
        }
    }

    int getK()
    {
        return k;
    }

    void setK(int value)
    {
        if (value < 0)
        {
            throw invalid_argument("K must  > 0");
        }
        k = value;
    }

    void addTrainingExample(const vector<double> &features, const string &label)
    {
        DataPoint point;
        point.features = features;
        point.isRegression = false;
        point.label = label;
        trainingData.push_back(point);
    }

    void addTrainingExample(const std::vector<double> &features, const double value)
    {
        DataPoint point;
        point.features = features;
        point.value = value;
        point.isRegression = true;
        trainingData.push_back(point);
    }

    std::string predict(const vector<double> features)
    {
        if (trainingData.empty())
        {
            throw std::runtime_error("No training data provided");
        }

        if (isRegression)
        {
            throw std::runtime_error("Model was initialized for regression, not classification");
        }

        vector<DistanceIndex> distances;

        for (size_t i = 0; i < trainingData.size(); i++)
        {
            double dist = euclideanDistance(features, trainingData[i].features);
            distances.push_back({dist, i});
        }

        std::sort(distances.begin(), distances.end());

        std::map<string, int> labelCount;

        for (int i = 0; i < k && i < distances.size(); i++)
        {
            size_t index = distances[i].index;
            labelCount[trainingData[index].label]++;
        }

        string predictLabel;

        int maxCount = 0;

        for (auto &pair : labelCount)
        {
            if (pair.second > maxCount)
            {
                maxCount = pair.second;
                predictLabel = pair.first;
            }
        }

        return predictLabel;
    }

    double predictValue(const vector<double> features)
    {
        if (trainingData.empty())
        {
            throw std::runtime_error("No training data provided");
        }

        if (!isRegression)
        {
            throw std::runtime_error("Model was initialized for classification, not regression");
        }

        std::priority_queue<DistanceIndex> distances;
        // vector<double> distances;

        for (int i = 0; i < trainingData.size(); i++)
        {
            double dist = euclideanDistance(features, trainingData[i].features);
            if (distances.size() < k)
            {
                distances.push({dist, i});
            }
            else if (dist < distances.top().distance)
            {
                distances.pop();
                distances.push({dist, i});
            }
        }

        double sum = 0.0;
        int count = distances.size();

        while (!distances.empty())
        {
            size_t idx = distances.top().index;
            distances.pop();
            sum += trainingData[idx].value;
        }

        return sum / count;
    }
};

int main()
{
    KNNBasic classifier(3);

    // Add training data (Iris dataset simplified)
    // Features: [sepal length, sepal width, petal length, petal width]

    classifier.addTrainingExample({5.1, 3.5, 1.4, 0.2}, "setosa");
    classifier.addTrainingExample({4.9, 3.0, 1.4, 0.2}, "setosa");
    classifier.addTrainingExample({7.0, 3.2, 4.7, 1.4}, "versicolor");
    classifier.addTrainingExample({6.4, 3.2, 4.5, 1.5}, "versicolor");
    classifier.addTrainingExample({6.3, 3.3, 6.0, 2.5}, "virginica");
    classifier.addTrainingExample({5.8, 2.7, 5.1, 1.9}, "virginica");

    // Predict new examples
    std::cout << "Classification example:" << std::endl;
    std::cout << "Predicted class for [5.0, 3.6, 1.4, 0.2]: "
              << classifier.predict({5.0, 3.6, 1.4, 0.2}) << std::endl;
    std::cout << "Predicted class for [6.7, 3.1, 4.4, 1.4]: "
              << classifier.predict({6.7, 3.1, 4.4, 1.4}) << std::endl;
    std::cout << "Predicted class for [6.5, 3.0, 5.8, 2.2]: "
              << classifier.predict({6.5, 3.0, 5.8, 2.2}) << std::endl;

    std::cout << "\nRegression example:" << std::endl;
    KNNBasic regressor(3, true);

    // Add training data (house prices example)
    // Features: [sqft, bedrooms, bathrooms]
    regressor.addTrainingExample({1400, 3, 2}, 250000);
    regressor.addTrainingExample({1800, 4, 2}, 300000);
    regressor.addTrainingExample({1500, 3, 2}, 280000);
    regressor.addTrainingExample({2000, 4, 3}, 350000);
    regressor.addTrainingExample({1200, 2, 1}, 220000);

    // Predict house price
    std::cout << "Predicted price for house [1600, 3, 2]: $"
              << regressor.predictValue({1600, 3, 2}) << std::endl;

    return 0;
}
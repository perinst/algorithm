#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <random>
#include <memory>
#include <limits>

// Forward declarations
class Node;
class DecisionTree;

// Define the data types we'll use
using FeatureValue = double; // Could be either numerical or categorical (encoded)
using FeatureVector = std::vector<FeatureValue>;
using Dataset = std::vector<FeatureVector>;
using Labels = std::vector<int>;
using FeatureNames = std::vector<std::string>;

// Node class representing a node in the decision tree
class Node
{
public:
    bool isLeaf;
    int featureIndex;
    FeatureValue threshold;
    int predictedClass;
    double impurity;
    std::unique_ptr<Node> leftChild;
    std::unique_ptr<Node> rightChild;

    // Constructor for a leaf node
    Node(int predictedClass, double impurity)
        : isLeaf(true), featureIndex(-1), threshold(0),
          predictedClass(predictedClass), impurity(impurity),
          leftChild(nullptr), rightChild(nullptr) {}

    // Constructor for a decision node
    Node(int featureIndex, FeatureValue threshold, double impurity)
        : isLeaf(false), featureIndex(featureIndex), threshold(threshold),
          predictedClass(-1), impurity(impurity),
          leftChild(nullptr), rightChild(nullptr) {}

    // Destructor will handle cleanup of children through unique_ptr
    ~Node() = default;
};

// DecisionTree class for classification
class DecisionTree
{
private:
    std::unique_ptr<Node> root;
    int maxDepth;
    int minSamplesSplit;
    int minSamplesLeaf;
    double minImpurityDecrease;

    // Split dataset based on a feature and threshold
    std::pair<Dataset, Dataset> splitDataset(const Dataset &data, const Labels &labels,
                                             int featureIndex, FeatureValue threshold,
                                             Labels &leftLabels, Labels &rightLabels)
    {
        Dataset leftData, rightData;

        for (size_t i = 0; i < data.size(); ++i)
        {
            if (data[i][featureIndex] <= threshold)
            {
                leftData.push_back(data[i]);
                leftLabels.push_back(labels[i]);
            }
            else
            {
                rightData.push_back(data[i]);
                rightLabels.push_back(labels[i]);
            }
        }

        return {leftData, rightData};
    }

    // Calculate the Gini impurity of a set of labels
    double calculateGiniImpurity(const Labels &labels)
    {
        if (labels.empty())
            return 0.0;

        // Count instances of each class
        std::map<int, int> classCounts;
        for (int label : labels)
        {
            classCounts[label]++;
        }

        double impurity = 1.0;
        double numSamples = static_cast<double>(labels.size());

        for (const auto &pair : classCounts)
        {
            double probability = pair.second / numSamples;
            impurity -= probability * probability;
        }

        return impurity;
    }

    /**
     * @brief Find the best split for a dataset
     *
     * @param data
     * @param labels
     * @return std::tuple<int, FeatureValue, double, Labels, Labels>
     */
    std::tuple<int, FeatureValue, double, Labels, Labels> findBestSplit(
        const Dataset &data, const Labels &labels)
    {

        int bestFeature = -1;
        FeatureValue bestThreshold = 0.0;
        double bestGain = -1.0;
        Labels bestLeftLabels, bestRightLabels;

        double currentImpurity = calculateGiniImpurity(labels);

        for (size_t featureIdx = 0; featureIdx < data[0].size(); ++featureIdx)
        {
            // Get unique values for the feature
            std::set<FeatureValue> uniqueValues;
            for (const auto &sample : data)
            {
                uniqueValues.insert(sample[featureIdx]);
            }

            if (uniqueValues.size() <= 1)
                continue;

            // Try different thresholds
            std::vector<FeatureValue> thresholds;

            // Convert set to vector for easier processing
            std::vector<FeatureValue> values(uniqueValues.begin(), uniqueValues.end());

            // Calculate potential thresholds as midpoints between consecutive values
            for (size_t i = 0; i < values.size() - 1; ++i)
            {
                thresholds.push_back((values[i] + values[i + 1]) / 2.0);
            }

            for (FeatureValue threshold : thresholds)
            {
                Labels leftLabels, rightLabels;
                auto [leftData, rightData] = splitDataset(data, labels, featureIdx,
                                                          threshold, leftLabels, rightLabels);

                // Skip if split doesn't meet minimum samples requirement
                if (leftLabels.size() < minSamplesLeaf || rightLabels.size() < minSamplesLeaf)
                {
                    continue;
                }

                // Calculate weighted impurity after split
                double leftImpurity = calculateGiniImpurity(leftLabels);
                double rightImpurity = calculateGiniImpurity(rightLabels);

                double leftWeight = static_cast<double>(leftLabels.size()) / labels.size();
                double rightWeight = static_cast<double>(rightLabels.size()) / labels.size();

                double weightedImpurity = leftWeight * leftImpurity + rightWeight * rightImpurity;
                double impurityDecrease = currentImpurity - weightedImpurity;

                // Update best split if this is better
                if (impurityDecrease > bestGain && impurityDecrease >= minImpurityDecrease)
                {
                    bestGain = impurityDecrease;
                    bestFeature = featureIdx;
                    bestThreshold = threshold;
                    bestLeftLabels = leftLabels;
                    bestRightLabels = rightLabels;
                }
            }
        }

        return {bestFeature, bestThreshold, bestGain, bestLeftLabels, bestRightLabels};
    }

    /**
     * @brief Get the most common class in a set of labels
     *
     * @param labels
     * @return int
     */
    int getMajorityClass(const Labels &labels)
    {
        std::map<int, int> classCounts;
        for (int label : labels)
        {
            classCounts[label]++;
        }

        int majorityClass = -1;
        int maxCount = 0;

        for (const auto &pair : classCounts)
        {
            if (pair.second > maxCount)
            {
                maxCount = pair.second;
                majorityClass = pair.first;
            }
        }

        return majorityClass;
    }

    // Build the decision tree recursively
    std::unique_ptr<Node> buildTree(const Dataset &data, const Labels &labels, int depth)
    {
        double currentImpurity = calculateGiniImpurity(labels);

        // Check stopping criteria
        if (depth >= maxDepth || labels.size() < minSamplesSplit ||
            currentImpurity == 0.0)
        {
            int majorityClass = getMajorityClass(labels);
            return std::make_unique<Node>(majorityClass, currentImpurity);
        }

        // Find best split
        auto [bestFeature, bestThreshold, bestGain, leftLabels, rightLabels] =
            findBestSplit(data, labels);

        // If no good split found, create a leaf node
        if (bestFeature == -1)
        {
            int majorityClass = getMajorityClass(labels);
            return std::make_unique<Node>(majorityClass, currentImpurity);
        }

        // Split the data
        Labels leftLabelsTemp, rightLabelsTemp;
        auto [leftData, rightData] = splitDataset(data, labels, bestFeature,
                                                  bestThreshold, leftLabelsTemp, rightLabelsTemp);

        // Create a decision node
        auto node = std::make_unique<Node>(bestFeature, bestThreshold, currentImpurity);

        // Recursively build children
        node->leftChild = buildTree(leftData, leftLabelsTemp, depth + 1);
        node->rightChild = buildTree(rightData, rightLabelsTemp, depth + 1);

        return node;
    }

    /**
     * @brief   // Predict class for a single sample using the decision tree
     *
     * @param sample
     * @param node
     * @return int
     */
    int predictSample(const FeatureVector &sample, const Node *node) const
    {
        if (node->isLeaf)
        {
            return node->predictedClass;
        }

        if (sample[node->featureIndex] <= node->threshold)
        {
            return predictSample(sample, node->leftChild.get());
        }
        else
        {
            return predictSample(sample, node->rightChild.get());
        }
    }

    void printTreeRecursive(const Node *node, const FeatureNames &featureNames, int depth = 0) const
    {
        std::string indent(depth * 4, ' ');

        if (node->isLeaf)
        {
            std::cout << indent << "Leaf: Class = " << node->predictedClass
                      << ", Impurity = " << node->impurity << std::endl;
            return;
        }

        std::string featureName = featureNames.empty() ? "Feature " + std::to_string(node->featureIndex) : featureNames[node->featureIndex];

        std::cout << indent << "Decision: " << featureName << " <= " << node->threshold
                  << ", Impurity = " << node->impurity << std::endl;

        std::cout << indent << "Left branch:" << std::endl;
        printTreeRecursive(node->leftChild.get(), featureNames, depth + 1);

        std::cout << indent << "Right branch:" << std::endl;
        printTreeRecursive(node->rightChild.get(), featureNames, depth + 1);
    }

public:
    DecisionTree(int maxDepth = 10, int minSamplesSplit = 2, int minSamplesLeaf = 1,
                 double minImpurityDecrease = 0.0)
        : root(nullptr), maxDepth(maxDepth), minSamplesSplit(minSamplesSplit),
          minSamplesLeaf(minSamplesLeaf), minImpurityDecrease(minImpurityDecrease) {}

    // Train the decision tree
    void fit(const Dataset &data, const Labels &labels)
    {
        if (data.empty() || labels.empty() || data.size() != labels.size())
        {
            throw std::invalid_argument("Invalid training data");
        }

        root = buildTree(data, labels, 0);
    }

    /**
     * @brief   // Make predictions for the entire dataset
     *
     * @param data
     * @return Labels
     */
    Labels predict(const Dataset &data) const
    {
        if (!root)
        {
            throw std::runtime_error("Model not trained");
        }

        Labels predictions;
        for (const auto &sample : data)
        {
            predictions.push_back(predictSample(sample, root.get()));
        }

        return predictions;
    }

    /**
     * @brief // Calculate the accuracy of the model
     *
     * @param data
     * @param trueLabels
     * @return double
     */
    double score(const Dataset &data, const Labels &trueLabels) const
    {
        if (data.size() != trueLabels.size())
        {
            throw std::invalid_argument("Data and labels size mismatch");
        }

        Labels predictions = predict(data);
        int correctCount = 0;

        for (size_t i = 0; i < predictions.size(); ++i)
        {
            if (predictions[i] == trueLabels[i])
            {
                correctCount++;
            }
        }

        return static_cast<double>(correctCount) / predictions.size();
    }

    // Print the decision tree
    void printTree(const FeatureNames &featureNames = {}) const
    {
        if (!root)
        {
            std::cout << "Tree is not trained" << std::endl;
            return;
        }

        std::cout << "Decision Tree:" << std::endl;
        printTreeRecursive(root.get(), featureNames);
    }
};

std::tuple<Dataset, Labels, FeatureNames> readCSV(const std::string &filename,
                                                  bool hasHeader = true, int labelColumn = -1)
{

    Dataset data = {
        {5.1, 3.5, 1.4, 0.2},
        {4.9, 3.0, 1.4, 0.2},
        {4.7, 3.2, 1.3, 0.2},
        {7.0, 3.2, 4.7, 1.4},
        {6.4, 3.2, 4.5, 1.5},
        {6.9, 3.1, 4.9, 1.5},
        {6.3, 3.3, 6.0, 2.5},
        {5.8, 2.7, 5.1, 1.9},
        {7.1, 3.0, 5.9, 2.1}};

    Labels labels = {0, 0, 0, 1, 1, 1, 2, 2, 2}; // Iris dataset classes
    FeatureNames featureNames = {"sepal_length", "sepal_width", "petal_length", "petal_width"};

    return {data, labels, featureNames};
}

int main()
{
    auto [data, labels, featureNames] = readCSV("iris.csv", true, 4);

    // Create training and test sets (simplified, no shuffling)
    size_t trainSize = data.size() * 0.7;
    Dataset trainData(data.begin(), data.begin() + trainSize);
    Labels trainLabels(labels.begin(), labels.begin() + trainSize);

    Dataset testData(data.begin() + trainSize, data.end());
    Labels testLabels(labels.begin() + trainSize, labels.end());

    // Create and train decision tree
    DecisionTree tree(5, 2, 1, 0.0);
    tree.fit(trainData, trainLabels);

    // Print the tree
    tree.printTree(featureNames);

    // Make predictions and evaluate
    Labels predictions = tree.predict(testData);

    std::cout << "Predictions:" << std::endl;
    for (size_t i = 0; i < predictions.size(); ++i)
    {
        std::cout << "Sample " << i << ": predicted = " << predictions[i]
                  << ", actual = " << testLabels[i] << std::endl;
    }

    double accuracy = tree.score(testData, testLabels);
    std::cout << "Accuracy: " << accuracy * 100 << "%" << std::endl;

    return 0;
}
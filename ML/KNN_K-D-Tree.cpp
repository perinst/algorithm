#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <limits>

using namespace std;

struct Point
{
    std::vector<double> features;
    int label; // or double value for regression
};

class KDNode
{
public:
    Point point;
    KDNode *left;
    KDNode *right;
    int axis;

    KDNode(const Point &pt, int ax) : point(pt), left(nullptr), right(nullptr), axis(ax) {}
    ~KDNode()
    {
        delete left;
        delete right;
    }
};

class KDTree
{
private:
    KDNode *root;
    int dimensions;

    KDNode *buildTree(std::vector<Point> &points, int depth, int start, int end)
    {
        if (start >= end)
            return nullptr;

        int axis = depth % dimensions;
        int mid = (end + start) / 2;

        // Sort points along the current axis
        std::nth_element(points.begin() + start,
                         points.begin() + mid,
                         points.begin() + end,
                         [axis](const Point &a, const Point &b)
                         {
                             return a.features[axis] < b.features[axis];
                         });

        // Create node and construct subtrees
        KDNode *node = new KDNode(points[mid], axis);
        node->left = buildTree(points, depth + 1, start, mid);
        node->right = buildTree(points, depth + 1, mid + 1, end);

        return node;
    }

    void findNearestNeighbors(KDNode *node, const std::vector<double> &query,
                              std::priority_queue<std::pair<double, Point>> &pq, int k)
    {
        if (!node)
            return;

        // Calculate distance to current point
        double distance = euclideanDistance(query, node->point.features);

        // If we have less than k points or this point is closer than the furthest in our queue
        if (pq.size() < k)
        {
            pq.push(std::make_pair(distance, node->point));
        }
        else if (distance < pq.top().first)
        {
            pq.pop();
            pq.push(std::make_pair(distance, node->point));
        }

        // Calculate distance to splitting plane
        int axis = node->axis;
        double planeDistance = query[axis] - node->point.features[axis];

        // Determine which subtree to search first (near side)
        KDNode *nearSubtree = (planeDistance <= 0) ? node->left : node->right;
        KDNode *farSubtree = (planeDistance <= 0) ? node->right : node->left;

        // Recursively search the near side
        findNearestNeighbors(nearSubtree, query, pq, k);

        // Only search the far side if it could contain points closer than our current kth nearest
        if (pq.size() < k || std::abs(planeDistance) < pq.top().first)
        {
            findNearestNeighbors(farSubtree, query, pq, k);
        }
    }

    double euclideanDistance(const std::vector<double> &a, const std::vector<double> &b)
    {
        double sum = 0.0;
        for (size_t i = 0; i < a.size(); i++)
        {
            double diff = a[i] - b[i];
            sum += diff * diff;
        }
        return std::sqrt(sum);
    }

public:
    KDTree(std::vector<Point> &points)
    {
        if (points.empty())
        {
            root = nullptr;
            dimensions = 0;
            return;
        }

        dimensions = points[0].features.size();
        root = buildTree(points, 0, 0, points.size());
    }

    ~KDTree()
    {
        delete root;
    }

    std::vector<Point> kNearestNeighbors(const std::vector<double> &query, int k)
    {
        // Max heap to store k nearest neighbors
        std::priority_queue<std::pair<double, Point>> pq;

        findNearestNeighbors(root, query, pq, k);

        // Extract results
        std::vector<Point> result;
        while (!pq.empty())
        {
            result.push_back(pq.top().second);
            pq.pop();
        }

        // Reverse to get neighbors in ascending order of distance
        std::reverse(result.begin(), result.end());
        return result;
    }
};

class KNN_KDTree
{
private:
    KDTree *tree;
    int k;
    std::vector<Point> trainingData;

public:
    KNN_KDTree(int kValue) : k(kValue), tree(nullptr) {}

    ~KNN_KDTree()
    {
        delete tree;
    }

    void train(const std::vector<Point> &data)
    {
        trainingData = data;
        tree = new KDTree(trainingData);
    }

    int predict(const std::vector<double> &features)
    {
        std::vector<Point> neighbors = tree->kNearestNeighbors(features, k);

        // Count label frequencies
        std::map<int, int> counts;
        for (const Point &p : neighbors)
        {
            counts[p.label]++;
        }

        // Find the most common label
        int maxCount = 0;
        int prediction = -1;
        for (const auto &pair : counts)
        {
            if (pair.second > maxCount)
            {
                maxCount = pair.second;
                prediction = pair.first;
            }
        }

        return prediction;
    }
};
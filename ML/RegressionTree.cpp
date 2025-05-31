#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct TreeNode
{
    double value;         // Giá trị dự đoán nếu là nút lá
    double split_feature; // Feature dùng để chia
    double split_value;   // Giá trị chia
    TreeNode *left;
    TreeNode *right;

    TreeNode(double val) : value(val), split_feature(-1), split_value(-1), left(nullptr), right(nullptr) {}
};

double calculate_rss(vector<pair<double, double>> &data)
{
    double mean = 0.0, rss = 0.0;
    for (const auto &d : data)
        mean += d;
    mean /= data.size();

    for (const auto &d : data)
        rss += pow(d.second - mean, 2);

    return rss;
}

pair<double, double> find_best_split(const vector<pair<double, double>> &data)
{
    double min_rss = numeric_limits<double>::max();
    double best_split_value = -1;

    for (size_t i = 1; i < data.size(); i++)
    {
        double split_val = (data[i - 1].first + data[i].first) / 2;

        vector<pair<double, double>> left, right;

        for (const auto &d : data)
        {
            if (d.first < split_val)
                left.push_back(d);
            else
                right.push_back(d);
        }

        if (left.empty() || right.empty())
            continue;

        double left_rss = calculate_rss(left);
        double right_rss = calculate_rss(right);
        double total_rss = left_rss + right_rss;

        if (total_rss < min_rss)
        {
            min_rss = total_rss;
        }
    }
}

TreeNode *build_tree(const vector<pair<double, double>> data, int min_samples = 3, double min_rss = 1e-3)
{

    if (data.size() <= min_samples)
    {
        double mean = 0;
        for (const auto &d : data)
            mean += d.second;

        mean /= data.size();

        return new TreeNode(mean);
    }

    auto [rss, split_value] = find_best_split(data);

    if (rss < min_rss)
    {
        double mean = 0.0;
        for (const auto &d : data)
            mean += d.second;
        mean /= data.size();
        return new TreeNode(mean);
    }

    vector<pair<double, double>> left, right;

    for (const auto &d : data)
    {
        if (d.first <= spl)
            left.push_back(d);
        else
            right.push_back(d);
    }

    TreeNode *node = new TreeNode(0);
    node->split_value = split_value;
    node->left = build_tree(left, min_samples, min_rss);
    node->right = build_tree(right, min_samples, min_rss);

    return node;
}

int main()
{
    // Dữ liệu: (feature, target)
    vector<pair<double, double>> data = {{1, 1.5},
                                         {2, 2.3},
                                         {3, 2.7},
                                         {4, 3.1},
                                         {5, 4.0},
                                         {6, 4.8},
                                         {7, 5.1},
                                         {8, 5.6}};

    TreeNode *root = build_tree(data);

    cout << "Dự đoán cho x=4.5: " << predict(root, 4.5) << endl;
    cout << "Dự đoán cho x=6.5: " << predict(root, 6.5) << endl;

    return 0;
}
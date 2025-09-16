
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#define FOR(i, a, b)                \
    for (int i = (a); i < (b); i++) \
        ;

using namespace std;

int minimumTeachings(int n, vector<vector<int>> &languages, vector<vector<int>> &friendships)
{
    // Bước 1: Tạo bảng ngôn ngữ của từng người
    unordered_map<int, unordered_set<int>> userLang;
    for (int i = 0; i < languages.size(); ++i)
    {
        for (int lang : languages[i])
        {
            userLang[i + 1].insert(lang); // người dùng đánh số từ 1
        }
    }

    // Bước 2: Tìm các cặp bạn bè không thể giao tiếp
    unordered_set<int> needTeach;
    for (auto &pair : friendships)
    {
        int u = pair[0], v = pair[1];
        bool canCommunicate = false;
        for (int lang : userLang[u])
        {
            if (userLang[v].count(lang))
            {
                canCommunicate = true;
                break;
            }
        }
        if (!canCommunicate)
        {
            needTeach.insert(u);
            needTeach.insert(v);
        }
    }

    // Bước 3: Đếm số người đã biết từng ngôn ngữ trong nhóm cần dạy
    vector<int> langCount(n + 1, 0); // ngôn ngữ đánh số từ 1 đến n
    for (int user : needTeach)
    {
        for (int lang : userLang[user])
        {
            langCount[lang]++;
        }
    }

    // Bước 4: Tìm ngôn ngữ phổ biến nhất
    int maxKnown = 0;
    for (int i = 1; i <= n; ++i)
    {
        maxKnown = max(maxKnown, langCount[i]);
    }

    // Kết quả: số người cần dạy = tổng số người - số người đã biết ngôn ngữ phổ biến
    return needTeach.size() - maxKnown;
}

void solve()
{
}

int main()
{

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}
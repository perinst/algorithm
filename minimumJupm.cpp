#include <iostream>
#include <vector>

using namespace std;

vector<int> minJumpsToEnd(int N, vector<int> &ropes)
{
    int maxReach = 0; // Vị trí xa nhất có thể đạt được từ vị trí hiện tại
    int steps = 0;    // Số lần chuyền

    int currentEnd = 0; // Điểm kết thúc của lần chuyền hiện tại

    vector<int> jumps; // Lưu trữ các vị trí chuyền

    for (int i = 0; i < N - 1; ++i)
    {
        maxReach = max(maxReach, i + ropes[i]); // Cập nhật vị trí xa nhất có thể đạt được từ vị trí hiện tại

        if (maxReach == i && ropes[i] == 0)
        {              // Nếu không thể tiến xa hơn
            return {}; // Không thể đến đích, trả về vector rỗng
        }

        if (i == currentEnd)
        {                              // Nếu đạt được điểm kết thúc của lần chuyền hiện tại
            ++steps;                   // Tăng số lần chuyền
            jumps.push_back(ropes[i]); // Lưu vị trí chuyền vào vector
            currentEnd = maxReach;     // Cập nhật điểm kết thúc của lần chuyền hiện tại
        }
    }

    jumps.push_back(N - 1); // Thêm vị trí cuối cùng vào vector
    return jumps;
}

int main()
{
    int N;
    cin >> N; // Nhập khoảng cách cần di chuyển

    vector<int> ropes(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> ropes[i]; // Nhập độ dài của dây tại từng vị trí
    }

    vector<int> minJumps = minJumpsToEnd(N, ropes);
    if (minJumps.empty())
    {
        cout << "CANNOT GET DESTINATION" << endl; // Nếu không thể đến đích
    }
    else
    {
        cout << "Duong chuyen ngan nhat: ";
        for (int i = 0; i < minJumps.size(); ++i)
        {
            cout << minJumps[i] << " "; // In ra các vị trí chuyền
        }
        cout << endl;
    }

    return 0;
}

#define ll long long;
#define vi vector<int>;
#define vii vector<vi>;
#define pii pair<int, int>;

#define pb push_back // Thêm phần tử vào vector
#define mp make_pair // Tạo cặp số

#define FOR(i, a, b) \
 for (int i = (a); i < (b); i++) \
 ;

#define RFOR(i, a, b) \
 for (int i = (a); i >= (b); i--) \
 ;

#define CINARR(arr) \
 FOR(i, 0, arr.size()) { std::cin >> arr[i]; }

#define COUTARR(arr) \
 FOR(i, 0, arr.size()) { std::cout << arr[i] << " "; }

#define read(...) \
 **VA_ARGS**; \
 cin >> **VA_ARGS**;
#define write(...) cout << **VA_ARGS** << endl;

#define all(x) (x).begin(), (x).end();

#define MOD 1000000007;
#define endl '\n';

#define DEGUG(x) cout << '>' << #x << ':' << x << endl;

// fast input output

        static const auto speedup = []() {
            std::ios::sync_with_stdio(false);
            std::cin.tie(nullptr);
            std::cout.tie(nullptr);
            return 0;
        }();

//
// Template overload for operator<< to print any type of std::vector
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
// Overload the << operator for vector<int>
std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec) {
os << "[";
for (size_t i = 0; i < vec.size(); ++i) {
os << vec[i];
if (i != vec.size() - 1) {
os << ", ";
}
}
os << "]";
return os;
}

// Overload the << operator for vector<vector<int>>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& vec) {
os << "[\n";
for (size_t i = 0; i < vec.size(); ++i) {
os << " " << vec[i];
if (i != vec.size() - 1) {
os << ",\n";
}
}
os << "\n]";
return os;
}

void runTestCases(const string& filePath) {
ifstream inputFile(filePath); // Open the file
if (!inputFile) {
cerr << "Error: File not found or could not be opened." << endl;
return;
}

    int T; // Number of test cases
    inputFile >> T;

    for (int i = 1; i <= T; ++i) {
        int a, b;
        inputFile >> a >> b; // Read the two integers
        int totalProblems = a + b;
        cout << "Case " << i << ": " << totalProblems << endl;
    }

    inputFile.close(); // Close the file

}

// template
{
"Problem Solving Skeleton": {
"prefix": "pskel",
"body": [
"#include <iostream>",
"#include <vector>",
"#include <string>",
"",
"using namespace std;",
"",
"// Fast I/O",
"#define fast*io \\",
" ios_base::sync_with_stdio(false); \\",
" cin.tie(NULL); \\",
" cout.tie(NULL)",
"",
"void solve()",
"{",
" int N;",
" cin >> N;",
" vector<int> nums(N);",
" for (int i = 0; i < N; i++)",
" {",
" cin >> nums[i];",
" }",
" ",
" // TODO: implement logic here",
"}",
"",
"int main()",
"{",
" // fast_io;",
"",
" int T = 1;",
" // cin >> T;",
"",
" while (T--)",
" {",
" solve();",
" }",
"",
" return 0;",
"}"
],
"description": "C++ competitive programming problem solving template"
},
"Debug Template": {
"prefix": "dbgtemp",
"body": [
"#define DEBUG true",
"",
"int depth = 0;",
"",
"// Print function entry with parameters",
"#define REC_ENTER(func_name, ...) \\",
" if (DEBUG) \\",
" { \\",
" cout << string(depth * 2, ' ') << \"-> \" << func*name << \"(\"; \\",
" print_params(**VA_ARGS**); \\",
" cout << \")\" << endl; \\",
" depth++; \\",
" }",
"",
"#define REC_EXIT(func_name, result) \\",
" if (DEBUG) \\",
" { \\",
" depth--; \\",
" cout << string(depth * 2, ' ') << \"<- \" << func*name << \" = \" << result << endl; \\",
" }",
"",
"// Print memo hit",
"#define MEMO_HIT(key, value) \\",
" if (DEBUG) \\",
" { \\",
" cout << string(depth * 2, ' ') << \" [MEMO HIT] \" << key << \" -> \" << value << endl; \\",
" }",
"",
"// Print memo store",
"#define MEMO*STORE(key, value) \\",
" if (DEBUG) \\",
" { \\",
" cout << string(depth * 2, ' ') << \" [MEMO STORE] \" << key << \" -> \" << value << endl; \\",
" }"
],
"description": "Recursive + memoization debug macros"
},
"Common Defines Template": {
"prefix": "defs",
"body": [
"// Common typedefs",
"typedef long long ll;",
"typedef unsigned long long ull;",
"typedef pair<int, int> pii;",
"typedef pair<ll, ll> pll;",
"typedef vector<int> vi;",
"typedef vector<ll> vll;",
"typedef vector<string> vs;",
"typedef vector<pii> vpii;",
"",
"// Common constants",
"const int MOD = 1e9 + 7;",
"const int INF = 1e9;",
"const ll LINF = 1e18;",
"const double EPS = 1e-9;",
"",
"// Utility macros",
"#define all(x) (x).begin(), (x).end()",
"#define rall(x) (x).rbegin(), (x).rend()",
"#define sz(x) ((int)(x).size())",
"#define pb push_back",
"#define mp make_pair",
"#define fi first",
"#define se second",
"",
"#define FOR(i, a, b) \\\\",
" for (int i = (a); i < (b); i++) \\\\",
" ;",
"",
"#define RFOR(i, a, b) \\\\",
" for (int i = (a); i >= (b); i--) \\\\",
" ;",
"",
"#define CINARR(arr) \\\\",
" FOR(i, 0, arr.size()) { std::cin >> arr[i]; }",
"",
"#define COUTARR(arr) \\\\",
" FOR(i, 0, arr.size()) { std::cout << arr[i] << \" \"; }"
],
"description": "Common typedefs, constants, and utility macros for C++"
}
}
//

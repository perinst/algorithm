#include <iostream>
#include <vector>

using namespace std;
class ProductOfNumbers
{
public:
    vector<int> prefixProduct;
    int size;

    ProductOfNumbers()
    {
        prefixProduct = {1};
        this.size = 0;
    }

    void add(int num)
    {
        if (num == 0)
        {
            prefixProduct = {1};
            size = 0;
        }
        prefixProduct.push_back(prefixProduct[size] * num);
        size++;
    }

    int getProduct(int k)
    {
        if (k > size)
            return 0;
        return prefixProduct[size - 1] / prefixProduct[size - k];
    }
};

int main()
{

    return 0;
}
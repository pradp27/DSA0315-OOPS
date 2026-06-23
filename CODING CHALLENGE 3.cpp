#include <iostream>
using namespace std;

class Product
{
public:
    string name;
    float price;
    int qty;

    float sales()
    {
        return price * qty;
    }
};

int main()
{
    int stores, products;

    cout << "Enter number of stores: ";
    cin >> stores;

    cout << "Enter number of products per store: ";
    cin >> products;

    Product p[10][10];

    float overallSales = 0;
    float bestStoreSale = 0;
    int bestStore = 0;

    string bestProduct;
    float bestProductSale = 0;

    for(int i = 0; i < stores; i++)
    {
        cout << "\nStore " << i + 1 << endl;

        for(int j = 0; j < products; j++)
        {
            cout << "Enter Product Name: ";
            cin >> p[i][j].name;

            cout << "Enter Price: ";
            cin >> p[i][j].price;

            cout << "Enter Quantity Sold: ";
            cin >> p[i][j].qty;
        }
    }

    for(int i = 0; i < stores; i++)
    {
        float storeSales = 0;

        for(int j = 0; j < products; j++)
        {
            float sale = p[i][j].sales();

            storeSales += sale;

            if(sale > bestProductSale)
            {
                bestProductSale = sale;
                bestProduct = p[i][j].name;
            }
        }

        cout << "Store " << i + 1 << " Sales = " << storeSales << endl;

        overallSales += storeSales;

        if(storeSales > bestStoreSale)
        {
            bestStoreSale = storeSales;
            bestStore = i + 1;
        }
    }

    cout << "\nOverall Sales = " << overallSales << endl;
    cout << "Best Store = " << bestStore << endl;
    cout << "Best Product = " << bestProduct << endl;

    return 0;
}

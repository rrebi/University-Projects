#include <iostream>
#include <thread>
#include <random>
#include <mutex>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <Windows.h>
using namespace std;

// problem 1
// several types of products, each having a known, constant, unit price
// each bill is a list of products and quantities sold in a single operation, and their total price

// sale operations running concurrently, on several threads
// each sale decreases the amounts of available products (corresponding to the sold items),
// increases the amount of money, and adds a bill to a record of all sales

// an inventory check operation shall be run - random time
// all the sold products and all the money are justified by the recorded bills.

class Product{
public:
    void setQuantity(int newQ) { this->quantity = newQ; }
    void subtractFromQuantity(int subtractedQuantity) { this->quantity = this->quantity - subtractedQuantity; }
    int getQuantity() { return this->quantity;}

    void setPrice(long long int newPrice) { this->price = newPrice; }
    long long int getPrice() { return this->price; }

    void setId(int newId) { this->id = newId; }
    int getId() { return this->id; }

private:
    string name;
    int id;
    long long int price;
    int quantity;
};

class Bill
{
public:
    vector<Product*> getProducts() { return this->myProducts; }
    void addProduct(Product* p) { this->myProducts.push_back(p); addToTotal(p->getPrice() * p->getQuantity()); }

    long long int getTotal() { return this->total; }
    void addToTotal(long long int newProductPrice) { this->total=this->total+newProductPrice; }

private:
    long long int total=0;
    vector<Product*> myProducts;
};


// generate a random no between 0-9
int generateNumberOfProducts()
{
    srand(time(0));
    int noProds = rand() % 100;
    int secondary = (rand() % 100) * (rand() % 100);
    noProds = noProds * secondary;
    noProds = noProds % 10;
    return noProds;
}


int noProdsGlobal = generateNumberOfProducts();
int noThreadsQuit = 0; // ++ when threads finish 'shopping'
vector<mutex> mutexes(noProdsGlobal); // one mutex for each product
mutex marketBillsMutex;
vector<Bill*> marketBills;
vector <Product*> marketInventory;
long long int marketTotalProfit = 0;


void startShopping(int id) {

    srand(id);
    int randomProductId;
    bool NoQuantity = false;
    int randomQuantityToBuy;
    int priceOfProduct;

    // cont shopping + multiple bills
    while (true) {
        // current bill + the random number of products
        Bill* currentBill = new Bill();
        int randomNoProdsPerBill = rand() % 10;

        while (randomNoProdsPerBill != 0)
        {
            // buy random product
            randomProductId = rand() % (marketInventory.size());

            // only one thread access this prod quantity
            mutexes[randomProductId].lock();

            if (marketInventory[randomProductId]->getQuantity() > 0)
            {
                // set the quantity to buy random/1
                if (marketInventory[randomProductId]->getQuantity() == 1)
                {
                    randomQuantityToBuy = 1;
                }
                else
                {
                    randomQuantityToBuy = rand() % marketInventory[randomProductId]->getQuantity();
                }

                priceOfProduct = marketInventory[randomProductId]->getPrice();
                // -- quantity
                marketInventory[randomProductId]->subtractFromQuantity(randomQuantityToBuy);

                // create + add product to the bill
                Product* newProduct = new Product();
                newProduct->setId(marketInventory[randomProductId]->getId());
                newProduct->setPrice(priceOfProduct);
                newProduct->setQuantity(randomQuantityToBuy);

                currentBill->addProduct(newProduct);
            }
            else
            {
                NoQuantity = true;
            }

            // purchase done => mutex unlock
            mutexes[randomProductId].unlock();
            randomNoProdsPerBill--;
        }

        // add bill to market's bill record
        marketBillsMutex.lock();
        marketBills.push_back(currentBill);
        marketTotalProfit = marketTotalProfit + currentBill->getTotal();

        // print info about the purchase
        cout << "Purchase in value of " << currentBill->getTotal() << " for bill " << marketBills.size() - 1 << " has been made by thread "<< id;
        cout << ". Market profit is now: " << marketTotalProfit << endl;
        if (NoQuantity)
            cout << "Thread with ID: " << id << " will quit.\n";
        noThreadsQuit++;

        // allow other threads to modify the market's bill
        marketBillsMutex.unlock();

        // if the prod's quantity is 0 => stop
        if (NoQuantity)
            break;

        // wait before creating another bill
        Sleep(rand());
    }
}

void randomInventoryCheck(int noThreads)
{
    // periodically checks the market's inventory
    while (true) {
        // wait before checking
        Sleep(rand());

        for (int i = 0; i < noProdsGlobal; i++)
        {
            // lock the mutex for each product => access to each product
            mutexes[i].lock();
        }

        // lock market's bill records mutex => access to each bill
        marketBillsMutex.lock();

        // print that the thread is checking
        cout << "Checking all bills within the market record...\n";

        // loop through all the bills
        long long int calculatedMarketTotal=0;
        for(int i = 0; i < marketBills.size(); i++)
        {
            // get the total amount for the bill
            long long int totalPerBill = marketBills[i]->getTotal();
            long long int calculatedBillTotal=0;

            // products for the current bill
            vector<Product*> productsPerBill = marketBills[i]->getProducts();

            // loop through all products for one bill
            for(int j = 0; j < productsPerBill.size(); j++)
            {
                // total for a bill, product by product
                calculatedBillTotal = calculatedBillTotal +
                                      (productsPerBill[j]->getQuantity() * productsPerBill[j]->getPrice());
            }

            // verify bill
            if (totalPerBill == calculatedBillTotal)
            {
                cout << "Total for bill " << i << " is valid" << endl;
            }
            else
            {
                cout << "Total for bill " << i << " is wrong. Please stop stealing from our shop!" << endl;
            }

            // add bill total amount of current bill to total profit
            calculatedMarketTotal = calculatedMarketTotal + totalPerBill;
        }
        // verify profit
        if (marketTotalProfit == calculatedMarketTotal)
        {
            cout << "Profit was legally acquired for this market. Profit is: "<<marketTotalProfit << endl;
        }
        else
        {
            cout << "Profit was not legally acquired for this market. Calling ANAF..." << endl;
        }

        // unlock => allow threads to access the market's bill records
        marketBillsMutex.unlock();

        // unlock all mutexes fot the products => threads can access the products
        for (int i = 0; i < noProdsGlobal; i++)
        {
            mutexes[i].unlock();
        }

        // quit if all threads completed shopping
        if(noThreadsQuit == noThreads)
            break;
        if (noThreads == 0)
            break;
    }
}


// initializes product entities, creates threads to 'shop',
// wait for them to complete + periodically checks
int main()
{
    int newQuantity;
    long long int newPrice;
    srand(time(0));
    vector<thread> threads; // 'customers'
    cout << "No of product entities available:" << noProdsGlobal << endl;

    for (int i = 0; i < noProdsGlobal; i++)
    {
        // generate new products
        newPrice = rand() % 10;
        newQuantity = rand();

        Product* newProduct = new Product();
        newProduct->setPrice(newPrice);
        newProduct->setQuantity(newQuantity);
        newProduct->setId(i);
        marketInventory.push_back(newProduct);

    }

    // the number of threads used
    int noThreads = 2 * noProdsGlobal;
    cout << "No of threads used:" << noThreads << endl;

    // checking the market's inventory and bills
    thread periodicCheck(randomInventoryCheck,noThreads);

    for (int i = 0; i < noThreads; i++)
    {
        // start threads
        threads.emplace_back(startShopping,i);
    }

    for (int i = 0; i < noThreads; i++)
    {
        // wait for threads
        threads[i].join();
    }

    periodicCheck.join();
    cout << "\nAll threads have ended! Making final check \n";

    // end check, after waiting for the final check
    thread finalCheck(randomInventoryCheck,0);
    finalCheck.join();

    return 0;
}
// Create two threads, a producer and a consumer, with the producer feeding the consumer.
// Requirement: Compute the scalar product of two vectors.
// Create two threads. The first thread (producer) will compute the products of pairs of elements
// - one from each vector - and will feed the second thread. The second thread (consumer) will sum up
// the products computed by the first one. The two threads will behind synchronized with a condition variable and a mutex.
// The consumer will be cleared to use each product as soon as it is computed by the producer thread.

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;

vector<int> v1 = {1, 2, 3, 4, 5};
vector<int> v2 = {1, 2, 3, 4, 5};
vector<int> products;

bool producerReady = false;
bool producerDone = false;
condition_variable conditionVariable;
mutex mtx;

void producer()
{
    for (int i = 0; i < v1.size(); i++)
    {
        unique_lock<mutex> lock(mtx);
        int result = v1[i] * v2[i];
        products.push_back(result);
        producerReady = true;
        if (i == v1.size() - 1)
            producerDone = true;
        cout << "Producer (product) " << i << ": " << v1[i]<<"*"<<v2[i]<<"="<<result << endl;

        conditionVariable.notify_one();  // Notify the waiting consumer thread
    }
}

void consumer()
{
    int scalarProduct = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        unique_lock<mutex> lock(mtx);
        conditionVariable.wait(lock, []{ return producerReady || producerDone; });
        scalarProduct += products[i];
        producerReady = false;
        cout << "Consumer (sum) " << i << ": " << scalarProduct << endl;

    }
    cout << "Final scalar product: " << scalarProduct << endl;
}

int main(int argc, char *argv[])
{
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    // result: (1 * 1) + (2 * 2) + (3 * 3) + (4 * 4) + (5 * 5) = 1 + 4 + 9 + 16 + 25 = 55

    return 0;
}
//This program simulates 9 lines for 9 cashiers
//A new customer arrives every second and the screen refreshes
//Every 2-4 seconds, a customer will leave
//The lines use a queue structure, and all queues are held in a vector
//SDEV345-81
//Kodi Lein
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

/* TIMER */
int seconds = 0; // seconds of timer 

void displayClock()  //displays timer 
{
    cout << setfill(' ') << setw(55) << "         TIMER         \n";
    cout << setfill(' ') << setw(55) << " --------------------------\n";
    cout << setfill(' ') << setw(29);
    cout << "| " << setfill(' ') << setw(10) << "   | ";
    cout << setfill('0') << setw(2) << seconds << " sec |";
    cout << "  " << setfill(' ') << setw(6) << "   |" << endl;
    cout << setfill(' ') << setw(55) << " --------------------------\n";
}
void wait(int wait_time) //define wait time
{
    long* start_time = new long;
    *start_time = time(0);

    while ((*start_time + wait_time) > time(0)) {};

    delete start_time;
};
/* END TIMER */

/* QUEUE CLASS */
class Q
{
private:
    int maxSize = 20; //define max size as 20
    vector<int> queVect; 
    int front;
    int rear;
    int nItems;
public:
    //------------------------------------------------------------
                                    //constructor
    Q() : front(0), rear(-1), nItems(0)
    {
        queVect.resize(maxSize);
    }
    //------------------------------------------------------------
    void insert(int j)           //put item at rear of queue
    {
        if (rear == maxSize - 1)         //deal with wraparound
            rear = -1;
        queVect[++rear] = j;          //increment rear and insert
        nItems++;                     //one more item
    }
    //------------------------------------------------------------
    int remove()                 //take item from front of queue
    {
        int temp = queVect[front++];  //get value and incr front
        if (front == maxSize)          //deal with wraparound
            front = 0;
        nItems--;                     //one less item
        return temp;
    }
    //------------------------------------------------------------
    bool isEmpty()               //true if queue is empty
    {
        return (nItems == 0);
    }
    //------------------------------------------------------------
    int size()                   //number of items in queue
    {
        return nItems;
    }
    //------------------------------------------------------------
    void print()
    {
        for (int i = 0; i < nItems; i++)
            cout << " * ";
    }
};  //end class Queue

/* VECTOR CLASS */
class Vec
{
private:
    vector<Q> q; //vector of the queue class = vector of queues
public:
    Vec(size_t queue) : q(queue) //constructor
    {}

    void insertCustomer(int customer)
    {
        auto iter = min_element(q.begin(), q.end(), [](Q& l, Q& r) { return l.size() < r.size(); }); //inserts element to smallest queue
        iter->insert(customer);
    }

    void removeCust()
    {
        auto iter = max_element(q.begin(), q.end(), [](Q& l, Q& r) { return l.size() < r.size(); }); //remove element from larger queue
        iter->remove();
    }

    void display() //displays queue information
    {
        size_t index = 0;
        cout << "---------------------------" << endl;
        for (auto& i : q)
        {
            ++index;
            std::cout << "Cashier " << index << " " ; //output cashier number
            i.print();                                //prints ' * ' for each individual customer
            cout << endl;
        }
        cout << "---------------------------" << endl;
    }
};

/* MAIN */
int main()
{
    Vec queues(9); //nine queues
    int random = rand() % (2 + 4); //random number from 2-4

    for (int count = 0; count < 30; count++) //run program for 30 seconds
    {
        wait(1); //wait 1 second for each loop
        system("cls"); //screen clears
        displayClock(); //timer display

        queues.insertCustomer(count); //add customer to queue
        queues.display();

        seconds++; //add seconds to timer

        if (seconds % random == 0) //if number of seconds passed = randomized number
        {
            queues.removeCust(); //remove customer from queue
            queues.removeCust();
        }
    }
};
// challenge_10.cpp

#include "cmpt_error.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Primes {
private:
    vector<int> primes;
    vector<int> prodPrimes;
    int max; //1000000
public:
    //Default Constructor
    Primes()
    : primes(), prodPrimes(), max(1000000)
    {}

    //Fills vector with prime numbers from 0 to max
    void fillPrimes(){
        primes.push_back(1);

        for(int n = 2;n <= max;n++){
            int aPrime = 0;
            for(int i = 2; i <= (n/2); i++){  
                if(n % i == 0){  
                    aPrime = 1;
                    break;  
                }
            }
            if(aPrime == 0){ //if n is a prime number
                primes.push_back(n); 
            }
        }
    }

    //Shows all the primes numbers from 0 to max
    void printPrimes(){
        for(int x : primes){
            cout << x << " ";
        }
        cout << endl;
    }

    //Checks if a number is prime, returns true for prime numbers
    bool isPrime(int n){
        //This function can use a simplifed version of
        //fillPrimes() since we are returning values

        //Edge case
        if(n < 1) return false;

        //Check from 2 to n-1
        for(int i = 2; i < n; i++){
            if (n % i == 0) return false;
        }
        return true;
    }

    //Find the Productive prime numbers by checking products of digits
    void findProdPrimes(){
        vector<int> prods;

        //Set i=1 since first element of primes is 0
        for(int i = 1;i < primes.size();i++){
            int product = 1;
            while(primes[i] != 0){
                //get the rightmost digit by 'dividing' by 10
                product *= (primes[i] % 10);
                //decrement the while loop
                primes[i] = primes[i]/10;
            }
            prods.push_back(product+1);
        }

        for(int x : prods){
            //if it is a prime number, then add to vector
            if(isPrime(x)) prodPrimes.push_back(x);
        }
    }

    //Shows all the Productive Prime numbers from 0 to max
    void printProdPrimes(){
        for(int x : prodPrimes){
            cout << x << " ";
        }
        cout << endl;
    }

    //get the Sum of all productive prime numbers
    void sumProdPrimes(){
        int sum = 0;
        for(int i = 0;i < prodPrimes.size();i++){
            sum += prodPrimes[i];
        }
        cout << "Sum: " << sum << endl;
    }

    //Destructor
    ~Primes(){};
}; //class Primes

int main() {
	Primes p;
    p.fillPrimes();
    //p.printPrimes();
    p.findProdPrimes();
    //p.printProdPrimes();
    p.sumProdPrimes();
}
//hash.h
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const unsigned scale = 225;
const unsigned M = 3739; //personal modulus 3739
const int CARR = 63; //char array size
const char c[CARR] = { '0', '1','2','3','4','5','6','7','8','9',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '_'
};

// Desc:  Dynamic Set of strings using a Hash Table (generic version)
//  Pre:  class T must have an attribute key of type string
template <class T>
class Set {
    private:
        //attributes
        T* A[M];
        vector<T*> htElements;
        //helper methods
        unsigned hashFunction(string s) const ;
        void vPointers(T* x);

    public:
        //Desc:  Default constructor.  Initialize table to NULL.
        Set(){
            memset(A, 0, sizeof(T*)*M); 
        }

        //Desc: Destructor
        ~Set(){
            int vSize = htElements.size();
            for(int i = 0;i < vSize;i++){
                delete htElements[i];
            }
        }

        //Desc:  Insert x into the Set, according to its ->key.
        //       If ->key is already present, then replace it by x.
        //       Collisions are resolved via quadratic probing sequence.
        //Post:  returns the table index where x was inserted
        //       returns -1 if x was not inserted
        int insert(T* x);

        //Desc:  Returns T * x such that x->key == key, if and only if 
        //       key is in the Set.
        //       Returns NULL if and only if key is not in the Set.
        //Post:  Set is unchanged
        T* search(string key) const;
};

//*Private Methods
//Desc: takes string s and creates a hash value used for indexing within the HashTable
//Post: returns a hashValue based on the input string s
template <class T>
unsigned Set<T>::hashFunction(string s) const {
    const int LEN = s.size();
    int arr[LEN]; //holds string sequence
    unsigned hv = 0; //hash value

    //getting string sequence
    for(int j = 0; j < LEN; j++){ 
        for (int i = 0; i < CARR; i++) {
            if (s[j] == c[i]) {
                arr[j] = i;
            }
        }
    }
    //calculating hash function
    int j = LEN-1;
    for(int i = 0; i < LEN-1; i++){
        hv += (arr[i] * pow(64, j));
        hv = hv % M;
        j--;
    }
    hv += arr[LEN-1];
    hv = (scale * hv) % M;

    return hv;
}

//Desc: fills htElements with pointers to all values in hash table
template <class T>
void Set<T>::vPointers(T* x){
    htElements.push_back(x);
} //vPointers

//*Public Methods
// Desc:  Insert x into the Set, according to its ->key.
//        If ->key is already present, then replace it by x.
//        Collisions are resolved via quadratic probing sequence.
// Post:  returns the table index where x was inserted
//        returns -1 if x was not inserted
template <class T>
int Set<T>::insert(T* x) {
    //Computing the hash value
    unsigned hv = hashFunction(x->key);

    //Insert in the table if there is no collision
    if(A[hv] == nullptr){
        A[hv] = x;
        vPointers(x);
        return hv;
    }
    else{
        //If key already exists
        if(x->key == A[hv]->key){
            A[hv] = x;
            vPointers(x);
            return hv;
        }
        //If there is a collision iterating through all possible quadratic values
        for(unsigned j = 0; j < M/2+1; j++){
            //Computing the new hash value
            int t = (hv + j * j) % M;
            if(A[t] == nullptr){
                //Break the loop after insertion
                A[t] = x;
                vPointers(x);
                return t;
            }
            if(x->key == A[hv]->key){ //already exists
                A[hv] = x;
                vPointers(x);
                return hv;
            }
        }
    }
    return -1; //if probe failed to find spot
}


// Desc:  Returns T * x such that x->key == key, if and only if 
//        key is in the Set.
//        Returns NULL if and only if key is not in the Set.
// Post:  Set is unchanged
template <class T>
T* Set<T>::search(string key) const {
    unsigned hIndex = hashFunction(key); //hash index
    if(A[hIndex] == nullptr){
        return nullptr;
    }
    if(key == A[hIndex]->key){
        return A[hIndex];
    }
    else{
        if(A[hIndex]->key == key){
            return A[hIndex];
        }
        else{
            //Quadratic Probing to find key: If you reach
            //the hash value you started with, stop probing
            for(unsigned j = 0; j < M; j++){
                //Computing the new hash value
                unsigned t = (hIndex + j * j) % M;
                if(A[t] == nullptr){ 
                    return nullptr;
                }
                else if(A[t]->key == key){
                    return A[hIndex];
                }
            }
        }
    }
    return nullptr;
}
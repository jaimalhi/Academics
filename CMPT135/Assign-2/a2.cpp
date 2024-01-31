// a2.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Jaivir Malhi
// St.# : 301457742
// Email: jma225@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

// These are the only permitted includes: don't include anything else.
#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class str_vec {
//private members can only be accessed by could in str_vec
private:
    string* arr;    // pointer to the underlying array
    int cpcy;   // length of underlying array (capacity1)
    int sz;       // # of elements from user's perspective (size)

//public members can be accessed by any code.
public:
    //Default Constructor
    str_vec()
    : cpcy(10), sz(0)
    { 
        arr = new string[cpcy];
    }

    //Constructor
    str_vec(int n, string s)
    : cpcy(2*n + 1), sz(n)  // initializer list
    {
        if (n < 0) cmpt::error("str_vec(int n, string s): n must be 0 or greater");
        arr = new string[cpcy];
        for(int i = 0;i < sz;i++){
            arr[i] = s;
        }
    }

    //Copy constructor: has its own array
    str_vec(const str_vec& other)
    : cpcy(other.cpcy), sz(other.sz)  // initializer list
    {
        arr = new string[cpcy];
        for (int i = 0; i < sz; i++) {
            arr[i] = other.arr[i];
        }
    }

    //A getter: returns the numbers of strings in the str_vec
    int size() const {
        return sz;
    }

    //A getter: returns the capacity of the str_vec
    int capacity() const {
        return cpcy;
    }

    //A getter: returns the percentage (from 0.0 to 1.0) of the underlying array
    //that is in use, the size divided by the capacity
    double pct_used() const {
        double pct_used = double(sz) / double(cpcy);
        return pct_used;
    }

    //Non-Mutating Method: combines all the strings in str_vec into a single long
    //string, with every string, except the first one, beginning with sep
    string join(string sep) {
        string big_string = "";

        for(int i = 0;i < sz;i++){
            big_string += arr[i];
            big_string += sep;
        }
        //Get rid of extra sep at the end of big_string
        big_string.resize(big_string.size() - sep.size());

        return big_string;
    }

    //Non-Mutating Method: returns a string representation of the str_vec
    string to_str() const {
        string str = "";
        string result = "";

        for (int i = 0; i < sz; i++) {
            str += "\"";
            str += arr[i];
            str += "\"";
            //Add commas after all, except last
            if (i != sz - 1) {
                str += ", ";
            }
        }
        result = "{ " + str + " }\n";
        return result;
    }

    //Non-mutating Method: a void method that prints the string representation 
    //of the str_vec to cout
    void print() const {
        cout << "{ ";
        for (int i = 0; i < sz; i++) {
            cout << "\"" << arr[i] << "\"";

            if (i != sz-1) {
                cout << ", ";
            }
        }
        cout << " }";
    }

    //Non-mutating Method: a void method that does the same thing as print(),
    //but also prints a \n at the end
    void println() const {
        print();
        cout << endl;
    }

    //A getter: returns the string at index location i of the str_vec. Just as 
    //with arrays, the first index location is 0
    string get(int i) const {
        if (i < 0 || i >= sz) cmpt::error("get: index out of bounds");
        return arr[i];
    }

    //A setter: that sets index location i to be a copy of string s
    void set(int i, string s) {
        if (i < 0 || i >= sz) cmpt::error("set: index out of bounds");
        arr[i] = s;
    }

    //Mutating Method: adds the string s to the right end (the back) of the 
    //str_vec, increasing the sz by 1
    void append(string s) {
        if(sz >= cpcy){
            //create a temp array tiwce the sz of the orginal
            cpcy *= 2;
            string* new_arr = new string[cpcy];

            //copy elements from old array into temp
            for(int i = 0;i < sz;i++){
                new_arr[i] = arr[i];
            }

            //de-allocate the old array
            delete[] arr;

            //make arr point to temp (bigger array)
            arr = new_arr;
        }
        arr[sz] = s;
        sz++;
    }

    //Mutating Method: same as append(s), but s is only appended if it's not 
    //already in the str_vec; if s is already there, append_new(s) does nothing
    int append_new(string s) {
        for(int i = 0;i < sz;i++){
            if(s == arr[i]){
                return 0;
            }
        }
        append(s);
        return 0;
    }

    //Mutating Method: removes any leading and trailing spaces from all the 
    //elements of the str_vec
    void trim_all() {
        for(int i = 0;i < sz;i++) {
            //get the word at index i
            string word = get(i);

            int begin = 0;
            while (begin < word.size() && word[begin] == ' ') begin++;
            int end = word.size() - 1;
            while (end >= 0 && word[end] == ' ') end--;

            string str = arr[i];
            str = str.substr(begin, end-begin+1);
            arr[i] = str;
        }
    } 

    //Mutating Method: removes the string at index location i. All the strings 
    //to the right are moved down one position to fill in the gap, and the size
    //of the str_vec is decreased by 1
    void remove(int i) {
        if (i < 0 || i >= sz) cmpt::error("remove: index out of bounds");

        for(int j = 0;j < sz;j++){
            arr[i+j] = arr[(i+1)+j];
        }
        sz--;
    }

    //Mutating Method: keeps only strings that start with char c, and removes any others
    void keep_all_starts_with(char c) {
        for(int i = 0;i < sz;i++){
            //get the word at index i
            string word = get(i);

            //If str_vec is filled with empty strings
            if(word == ""){
                break;
            }
            //If the first char doesnt start with 'c'
            else if(word[0] != c){
                //remove word at index i
                remove(i);
            }
        }
    }

    //Mutating Method: removes all elements from the str_vec so its size is 0
    void clear() {
        sz = 0;
    }

    //Mutating Method: will, if necessary, re-size the underlying array so that
    //the size and capacity are the same. The elements in the array are the same 
    //(and in the same order) after squishing as before
    void squish() {
        if(cpcy > sz) cpcy = sz;
        else cout << "capacity already equal to size\n";
    }

    //Destructor
    ~str_vec(){
        delete[] arr;
    }
}; // class str_vec

//Operator Overload: returns true if the str_vec a and the str_vec b have
//the same elements in the same order, and false otherwise
bool operator==(const str_vec& a, const str_vec& b){
    string a_str = a.to_str();
    string b_str = b.to_str();

    if(a_str == b_str) return true;
    else return false;
}

//Operator Overload: returns true if the str_vec a and the str_vec b don't 
//have the same elements in the same order, and false otherwise
bool operator!=(const str_vec& a, const str_vec& b){
    string a_str = a.to_str();
    string b_str = b.to_str();

    if(a_str != b_str) return true;
    else return false;
}

//Test Functions
void test_default_constructor(){
    str_vec a; 
    assert(a.size() == 0);
    assert(a.capacity() == 10);

    str_vec b;
    assert(b.size() == 0);
    assert(b.capacity() == 10);
}

void test_constructor(){
    str_vec a(5,"cat"); 
    assert(a.size() == 5);
    assert(a.capacity() == 11);

    str_vec b(2,"dog"); 
    assert(b.get(0) == "dog");
    assert(b.get(1) == "dog");
}

void test_copy_constructor(){
    str_vec a(5,"cat"); 
    str_vec b(a);
    assert(b.size() == 5);
    assert(b.capacity() == 11);

    str_vec c(2,"dog"); 
    str_vec d(c);
    assert(d.get(0) == "dog");
    assert(d.get(1) == "dog");
}

void test_size_capacity_pctused(){
    str_vec a(5,"cat"); 
    assert(a.size() == 5);
    assert(a.capacity() == 11);
    assert(a.pct_used() == 5.0/11.0);

    str_vec b(2,"cat"); 
    assert(b.size() == 2);
    assert(b.capacity() == 5);
    assert(b.pct_used() == 2.0/5.0);
}

void test_join(){
    str_vec a(4,"home"); 
    assert(a.join("-") == "home-home-home-home");

    str_vec b(3,"space"); 
    assert(b.join(", ") == "space, space, space");

    str_vec c(2,"code"); 
    assert(c.join("") == "codecode");
}

void test_get_set(){
    str_vec a(4,"code");
    a.set(1, "mode");
    a.set(2, "load");

    assert(a.get(0) == "code");
    assert(a.get(1) == "mode");
    assert(a.get(2) == "load");

    //a.set(5, "toad"); //should thow error
}

void test_append_appendnew(){
    str_vec a(2,"code"); //size=2, capacity=5

    a.append("toad");
    assert(a.get(2) == "toad");
    assert(a.size() == 3);
    a.append("mode");
    assert(a.get(3) == "mode");
    assert(a.size() == 4);
    a.append("load");
    assert(a.get(4) == "load");
    assert(a.size() == 5);
    a.append("road");
    assert(a.get(5) == "road");
    assert(a.size() == 6);
    assert(a.capacity() == 10);

    a.append_new("toad"); //should do nothing
    assert(a.size() == 6);
    
    a.append_new("node");
    assert(a.get(6) == "node");
    assert(a.size() == 7);
}

void test_trim_all(){
    str_vec test(3," dog");
    test.set(1, "dog ");
    test.set(2, " dog ");

    test.trim_all();

    assert(test.get(0) == "dog");
    assert(test.get(1) == "dog");
    assert(test.get(2) == "dog");
}

void test_remove(){
    str_vec test(5,"dog");
    test.set(1, "cat");
    test.set(2, "bird");
    test.set(3, "rat");
    test.set(4, "owl");

    test.remove(2);

    assert(test.size() == 4);
    assert(test.get(0) == "dog");
    assert(test.get(1) == "cat");
    assert(test.get(2) == "rat");
    assert(test.get(3) == "owl");
}

void test_keep_all_starts_with(){
    str_vec test(5,"hat");
    test.set(1, "book");
    test.set(2, "horse");
    test.set(3, "house");
    test.set(4, "Hot!");

    test.keep_all_starts_with('h');
    assert(test.get(0) == "hat");
    assert(test.get(1) == "horse");
    assert(test.get(2) == "house");

    str_vec test1(5,"");
    test1.keep_all_starts_with('t');
    assert(test1.get(0) == "");
    assert(test1.get(1) == "");
    assert(test1.get(2) == "");
    assert(test1.get(3) == "");
    assert(test1.get(4) == "");
}

void test_clear_squish(){
    str_vec test;
    test.append("a");  // {"a"}, size 1, capacity 10
    test.append("b");  // {"a", "b"}, size 2, capacity 10

    assert(test.capacity() == 10);
    assert(test.size() == 2);

    test.squish();     // {"a", "b"}, size 2, capacity 2
    test.clear();      // {}, size 0, capacity 2

    assert(test.capacity() == 2);
    assert(test.size() == 0);
}

void test_operators_overloads(){
    str_vec a(3, "cat"); 
    str_vec b(3, "cat");

    if (a == b) cout << "same\n";       // prints same
    if (a != b) cout << "error\n";  // prints error
    a.set(0, "feline");
    if (a == b) cout << "error\n";       // prints error
    if (a != b) cout << "different\n";  // prints different
    a.set(0, "cat");
    b.set(2, "feline");
    if (a == b) cout << "error\n";       // prints error
    if (a != b) cout << "different\n";  // prints different
    b.set(2, "cat");
    if (a == b) cout << "same\n";       // prints same
    if (a != b) cout << "error\n";  // prints error
}

int main() {
    //All test function calls
    // test_default_constructor();
    // test_constructor();
    // test_copy_constructor();
    // test_size_capacity_pctused();
    // test_join();
    // test_get_set();
    // test_append_appendnew();
    // test_trim_all();
    // test_remove();
    // test_keep_all_starts_with();
    // test_clear_squish();
    // test_operators_overloads();
}


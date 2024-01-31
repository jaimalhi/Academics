// a4.cpp

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
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

// Don't put main() in this file. It goes in a4_main.cpp.
// All questions in a4.h
#include "a4.h"  // no other includes are allowed!
using namespace std;

//Sum of Squares
int sum_of_squares(int n){
    if(n < 0) cmpt::error("n less than 0");

    if(n == 0) return 0; //Base case
    else return (n*n) + sum_of_squares(n-1);
}

void sum_of_squares_test(){
    assert(sum_of_squares(3) == 14);
    assert(sum_of_squares(0) == 0);
    assert(sum_of_squares(8) == 204);
}

//Count Strange
int count_strange(int n){
    if(n <= 0) cmpt::error("n less than or equal to 0");
    if(n == 1) return 1; //base case
    
    if((n % 2 == 0) && (n % 5 != 0)){ //is even
        return count_strange(n - 1);
    }
    else if((n % 2 != 0) && (n % 5 != 0)) { //is odd
        return count_strange(n - 1) + 1;
    }
    else{
        return count_strange(n - 1);
    }
}

void count_strange_test(){
    assert(count_strange(1) == 1);
    assert(count_strange(11) == 5);
    assert(count_strange(15) == 6);
    assert(count_strange(24) == 10);
}

//All sfu
bool all_sfu(const string& s, int i){
    if(s.size() <= 0) return true;

    if(s.size() > i){
        if(s[i] == 's' || s[i] == 'f' || s[i] == 'u'){
            return all_sfu(s, i+1);
        }
        else return false;
    }
    return true;
}

bool all_sfu(const string& s){
    return all_sfu(s, 0);
}

void all_sfu_test(){
    assert(all_sfu("uuu") == true);
    assert(all_sfu("") == true);
    assert(all_sfu("sufufs") == true);
    assert(all_sfu("Sfu") == false);
    assert(all_sfu("sfu ") == false);
    assert(all_sfu("suFufs") == false);
}

//is int
bool is_int(const string& s, int i){
    if(s.size() <= 0) return false;

    if(s.size() > i){
        if(s[i] == '-' && s[i+1] == '-') return false;
        else if(s[i] == '-' || s[i] == '0' || s[i] == '1' || 
                s[i] == '2' || s[i] == '3' || s[i] == '4' ||
                s[i] == '5' || s[i] == '6' || s[i] == '7' ||
                s[i] == '8' || s[i] == '9')
                {
                    return is_int(s, i+1);
                }
        else return false;
    }
    return true;
}

bool is_int(const string& s){
    return is_int(s, 0);
}

void is_int_test(){
    assert(is_int("911") == true);
    assert(is_int("-27") == true);
    assert(is_int("000") == true);
    assert(is_int("51284") == true);
    assert(is_int("--2") == false);
    assert(is_int("2e5") == false);
    assert(is_int("31 4") == false);
    assert(is_int(" 911") == false);
}

//strip
string strip(const string& s, int begin, int end, string temp){
    if(begin < s.size() && s[begin] == ' '){
        return strip(s, begin+1, end, temp);
    }
    else if(end >= 0 && s[end] == ' '){
        return strip(s, begin, end-1, temp);
    }
    temp = s.substr(begin, end-begin+1);

    return temp;
}

string strip(const string& s){
    return strip(s, 0, s.size()-1,"");
}

void strip_test(){
    assert(strip("  ") == "");
    assert(strip(" a b c ") == "a b c");
    assert(strip("  xyz") == "xyz");
    assert(strip(" 1  2  3  4  ") == "1  2  3  4");
}

//Sum negative numbers
int sum_neg(const vector<int>& v, int begin, int end) {
    if(begin >= end){
        return 0;
    } 
    else if(v[begin] < 0){
        return v[begin] + sum_neg(v, begin + 1, end);
    } 
    else{
        return sum_neg(v, begin + 1, end);
    }
}

int sum_neg(const vector<int>& v){
    return sum_neg(v, 0, v.size());
}

void sum_neg_test(){
    vector<int> a = {};
    vector<int> b = {-1,-5,3,1,0};
    vector<int> c = {-1, 2, -3};
    vector<int> d = {1, 2, 3};
    assert(sum_neg(a) == 0);
    assert(sum_neg(b) == -6);
    assert(sum_neg(c) == -4);
    assert(sum_neg(d) == 0);
}

//Max vector
vector<int> max_vec(const vector<int>& a, const vector<int>& b, vector<int>& c, int begin, int end){
    if(a.size() != b.size() || a.size() <= 0){
        cmpt::error("invalid inputs");
    }

    if(begin < end){
        c.push_back(max(a[begin], b[begin]));
        max_vec(a, b, c, begin+1, end);
    }
    return c;
}

vector<int> max_vec(const vector<int>& a, const vector<int>& b){
    vector<int> c;
    return max_vec(a, b, c, 0, a.size());
}

void max_vec_test(){
    vector<int> a = {3, 4, 1};
    vector<int> b = {2, 5, 2};
    vector<int> key1 = {3, 5, 2};
    assert(max_vec(a, b) == key1);

    vector<int> c = {3, 6, 9};
    vector<int> d = {1, 7, 11};
    vector<int> key2 = {3, 7, 11};
    assert(max_vec(c, d) == key2);
}

//count
int count(const vector<string>& v, const string& s, int begin, int end){
    if(begin < end){
        if(s == v[begin]){
            return count(v, s, begin+1, end) + 1;
        }
        else{
            return count(v, s, begin+1, end);
        }
    }
    return 0;
}

int count(const vector<string>& v, const string& s){
    return count(v, s, 0, v.size());
}

void count_test(){
    vector<string> v = {"cat","dog","dog","","red","red","red"};
    assert(count(v, "") == 1);
    assert(count(v, "cat") == 1);
    assert(count(v, "dog") == 2);
    assert(count(v, "blue") == 0);
    assert(count(v, "red") == 3);
}

//Zip
vector<string> zip(const string& s, const string& t, vector<string>& v, int begin, int end, string temp){
    if(s.size() != t.size()) cmpt::error("string sizes differ");

    if(s.size() <= 0) return v;
    if(begin < end){
        temp += s[begin];
        temp += t[begin];
        v.push_back(temp);
        zip(s, t, v, begin+1, end, "");
    }
    return v;
}

vector<string> zip(const string& s, const string& t){
    vector<string> v;
    return zip(s, t, v, 0, s.size(), "");
}

void zip_test(){
    vector<string> key1 = {"ax", "by", "cz"};
    vector<string> key2;
    assert(zip("abc", "xyz") == key1);
    assert(zip("", "") == key2);
}

//Join test
string join(const vector<string>& v, const string& sep, string s, int begin){
    if(v.size() <= 0) return s;

    if(begin < v.size()){
        s = v[begin];
        if(begin == v.size()-1){
            return join(v, sep, s, begin+1);
        }
        return s + sep + join(v, sep, s, begin+1);
    }
    return s;
}

string join(const vector<string>& v, const string& sep){
    return join(v, sep, "", 0);
}

void join_test(){
    vector<string> a = {"one"};
    vector<string> b = {"up", "dog"};
    vector<string> c = {"he", "we", "see"};
    assert(join(a, ", ") == "one");
    assert(join(b, ", ") == "up, dog");
    assert(join(c, "-") == "he-we-see");
    assert(join(c, "") == "hewesee");
}
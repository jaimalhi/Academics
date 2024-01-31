// a3.cpp

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

#include "cmpt_error.h"    
#include "List_base.h"     
#include <iostream>        
#include <string>          
#include <vector>          
#include <cassert>

using namespace std;

//Bullet_list publicly inherits from List_base
class Bulleted_list : public List_base {
private:
    string bullet;
    vector <string> items;
public:
    //default constructor
    Bulleted_list()
    : bullet("- "), items()
    {} 

    //Setter, change bullet string
    void set_bullet(string s) { bullet = s; }

    //Getter, returns current bullet
    string get_bullet() const { return bullet; }

    //Returns the number of items in this list.
    int size() const { return items.size(); }

    //Returns item i of this list
    string get(int i) const { return items[i]; }

    //Inserts a new item s at the start of the list.
    void add_to_start(const string& s) { items.insert(items.begin(), s); }

    //Inserts a new item s at the end of the list.
    void add_to_end(const string& s) { items.push_back(s); }

    //Reverses the order of a list
    void reverse_order() { 
        vector <string> temp;
        int end = items.size() - 1;
        int start = 0;
        
        for(int i = end;i >= start;i--){
            string s = items[i];
            temp.push_back(s);
        }
        items = temp;
    }

    //Returns a string representation of this list
    string to_str() const { 
        string indent = get_indent();
        string s = "";

        for(int i = 0;i < items.size();i++){
            s += indent + bullet + items[i] + "\n";
        }
        return s;
    }

    //Returns an HTML string representation of this list
    string to_html_str() const { 
        string s = "";

        s += "<ul>\n";
        for(int i = 0;i < items.size();i++){
            s += "  <li>" + items[i] + "</li>\n";
        }
        s += "</ul>\n";

        return s;
    }

    //Destructor
    ~Bulleted_list(){
        //Destroyed
    }
};

//Numbered_list publicly inherits from List_base
class Numbered_list : public List_base {
private:
    int number;
    string sep;
    int reverse;
    vector <string> items;
public:
    //default constructor
    Numbered_list()
    : number(1),sep(". "),reverse(0), items()
    {}

    //Setter, set the seperator to s
    void set_num_sep(string s) { sep = s; }

    //Getter, gets the current seperator
    string get_num_sep() const {
        return sep;
    }

    //Setter, sets the starting number to n
    void set_start_num(int n) {
        if(n < 0) number = 0;
        else number = n;
    }

    //Getter, returns the starting number
    int get_start_num() const { return number; }

    //Returns the number of items in this list.
    int size() const { return items.size(); }
    
    //Returns item i of this list
    string get(int i) const { return items[i]; }

    //Inserts a new item s at the start of the list.
    void add_to_start(const string& s) { items.insert(items.begin(), s); }

    //Inserts a new item s at the end of the list.
    void add_to_end(const string& s) { items.push_back(s); }

    //Reverses the order of a list
    void reverse_order() {
        vector <string> temp;
        int end = items.size() - 1;
        int start = 0;
        reverse++;
        
        for(int i = end;i >= start;i--){
            string s = items[i];
            temp.push_back(s);
        }
        items = temp;
    }

    //Returns a string representation of this list
    string to_str() const { 
        string indent = get_indent();
        string s = "";
        int j = 0;

        if(reverse % 2 != 0){ //if reversed
            for(int i = (items.size()-1)+number; i >= number; i--){
                string num = to_string(i); //Item numbers
                s += indent + num + sep + items[j] + "\n"; 
                j++; //proper index
            }
        }
        else{ //If not reversed
            for(int i = number; i < items.size()+number; i++){
                string num = to_string(i); //Item numbers
                s += indent + num + sep + items[j] + "\n";
                j++; //proper index
            }
        }
        return s;
    }

    string to_html_str() const {
        string s = "";

        if(reverse % 2 != 0) s += "<ol reversed>\n";
        else s += "<ol>\n";

        for(int i = 0;i < items.size();i++){
            s += "  <li>" + items[i] + "</li>\n";
        }
        s += "</ol>\n";

        return s;
    }

    //Destructor
    ~Numbered_list(){
        //Destroyed
    }
};

//Test functions
void test_bullet_to_str(){ 
    Bulleted_list lst;
    lst.add_to_start("apples");
    lst.add_to_end("oranges");
    lst.add_to_end("pears");
    lst.add_to_end("grapes");

    lst.set_indent(3);
    lst.reverse_order();

    string s = "   - grapes\n"
               "   - pears\n"
               "   - oranges\n"
               "   - apples\n";
    assert(lst.to_str() == s);
}

void test_bullet_to_html_str(){
    Bulleted_list lst;
    lst.add_to_start("apples");
    lst.add_to_end("oranges");
    lst.add_to_end("pears");
    lst.add_to_end("grapes");

    string s = "<ul>\n"
               "  <li>apples</li>\n"
               "  <li>oranges</li>\n"
               "  <li>pears</li>\n"
               "  <li>grapes</li>\n"
               "</ul>\n";

    assert(lst.to_html_str() == s);
}

void test_numbered_to_str(){
    Numbered_list lst;
    lst.add_to_start("apples");
    lst.add_to_end("oranges");
    lst.add_to_end("pears");
    lst.add_to_end("grapes");

    //Assertion 1
    lst.set_num_sep(") ");
    lst.set_start_num(3);
    string s = "3) apples\n"
               "4) oranges\n"
               "5) pears\n"
               "6) grapes\n";
    assert(lst.to_str() == s);

    //Assertion 2
    lst.set_start_num(1);
    lst.reverse_order();
    s = "4) grapes\n"
        "3) pears\n"
        "2) oranges\n"
        "1) apples\n";
    assert(lst.to_str() == s);
}

void test_numbered_to_html_str(){ 
    Numbered_list lst;
    lst.add_to_start("apples");
    lst.add_to_end("oranges");
    lst.add_to_end("pears");
    lst.add_to_end("grapes");

    //Assertion 1
    string s = "<ol>\n"
               "  <li>apples</li>\n"
               "  <li>oranges</li>\n"
               "  <li>pears</li>\n"
               "  <li>grapes</li>\n"
               "</ol>\n";
    assert(lst.to_html_str() == s);

    //Assertion 2
    lst.reverse_order();
    s = "<ol reversed>\n"
        "  <li>grapes</li>\n"
        "  <li>pears</li>\n"
        "  <li>oranges</li>\n"
        "  <li>apples</li>\n"
        "</ol>\n";
    assert(lst.to_html_str() == s);
}

int main() {
    test_bullet_to_str();
    test_bullet_to_html_str();
    test_numbered_to_str();
    test_numbered_to_html_str();
}
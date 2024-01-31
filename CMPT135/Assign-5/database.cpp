//database.cpp
#include "database.h"
using namespace std;

//Create definitions here
Database::Database(){}

void Database::check_record_size() const {
    //test case of vector sizes being different
    if(name.size() != artist.size() || name.size() != date.size() 
    || name.size() != rating.size() || artist.size() != rating.size() 
    || artist.size() != date.size() || date.size() != rating.size())
    {
        cout << "Something went wrong, \n";
        cmpt::error("some record is missing information!");
    }
}

void Database::add_records(string n, string a, int d, char r){
    cout << "==========================\n";
    //To check if record already exists
    for(int i = 0;i < name.size();i++){
        if(name[i] == n && artist[i] == a && date[i] == d){
            cout << "This record already exists in the database\n";
            return;
        }
    }
    name.push_back(n);
    artist.push_back(a);
    date.push_back(d);
    rating.push_back(r);
    cout << "The record has been added!\n";
}
//===============================================================
void Database::find_rName() const {
    string s, temp;
    int count = 0;
    cout << "Enter desired Song name: ";
    cin >> s;
    cout << "-------------------------\n";
    cout << "Showing records with '" << s << "'\n";

    //Check for exact match or substring matches
    for(int i = 0;i < name.size();i++){
        temp = name[i];
        //change to all lowercase letters
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        if(temp == s){ //exact match
            print_single_record(i);
            count++;
        }
        else if(temp.find(s) != std::string::npos){ //substring match
            print_single_record(i);
            count++;
        }
    }
    if(count == 0){
        cout << "No record containing '" << s << "' could be found\n";
    }
}

void Database::find_rArtist() const {
    string s, temp;
    int count = 0;
    cout << "Enter desired Artist name: ";
    cin >> s;
    cout << "---------------------------\n";
    cout << "Showing records with '" << s << "'\n";

    //Check for exact match or substring matches
    for(int i = 0;i < artist.size();i++){
        temp = artist[i];
        //change to all lowercase letters
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        if(temp == s){ //exact match
            print_single_record(i);
            count++;
        }
        else if(temp.find(s) != std::string::npos){ //substring match
            print_single_record(i);
            count++;
        }
    }
    if(count == 0){
        cout << "No record containing '" << s << "' could be found\n";
    }
}

void Database::find_rDate() const {
    cout << "search for a (S)pecific date\n";
    cout << "search for a date (R)ange\n";
    cout << "Enter desired search option: ";

    while(true){
        char c;
        if(!(cin >> c)){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(c == 's' || c == 'S'){
            int n, count = 0;
            cout << "Enter desired date: ";
            cin >> n;
            cout << "--------------------\n";
            cout << "Showing records released in '" << n << "'\n";

            for(int i = 0;i < date.size();i++){
                if(date[i] == n){
                    print_single_record(i);
                    count++;
                }
            }
            if(count == 0){
                cout << "No record released in" << n << "found\n";
            }
            break;
        }
        else if(c == 'r' || c == 'R'){
            int n1, n2, count = 0;
            cout << "Enter earliest date: ";
            cin >> n1;
            cout << "Enter latest date: ";
            cin >> n2;
            cout << "---------------------\n";
            cout << "Showing records released from " << n1 << " to " << n2 << endl;

            for(int i = 0;i < date.size();i++){
                if(n1 <= date[i] && date[i] <= n2){
                    print_single_record(i);
                    count++;
                }
            }
            if(count == 0){
                cout << "No records released from " << n1 << " to " << n2 << " were found\n";
            }
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Database::find_rRating() const {
    int count = 0;
    char c;
    cout << "Enter desired release Rating: ";
    cin >> c;
    cout << "------------------------------\n";
    if(c == 'e' || c == 'E') cout << "Showing records rated Explicit\n";
    if(c == 'c' || c == 'C') cout << "Showing records rated Clean\n";

    //Check for exact match or substring matches
    for(int i = 0;i < rating.size();i++){
        if(rating[i] == toupper(c)){ //exact match
            print_single_record(i);
            count++;
        }
    }
    if(count == 0){
        if(c == 'e' || c == 'E') cout << "No Explicit record could be found\n";
        if(c == 'c' || c == 'C') cout << "No Clean record could be found\n";
    }
}
//===============================================================
void Database::del_record(vector<int> v){
    char c;
    cout << "--------------------\n";
    cout << "Are you sure you want to delete these records, (Y)es or (N)o: ";

    while(true){
        int size = 0; //Every erase call decreases vector size, this accomodates that
        if(!(cin >> c)){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(c == 'y' || c == 'Y'){
            //delete the record
            for(int x : v){
                name.erase(name.begin() + (x-size)); 
                artist.erase(artist.begin() + (x-size));
                date.erase(date.begin() + (x-size));
                rating.erase(rating.begin() + (x-size));
                size++;
            }
            cout << "Records have been deleted!\n";
            break;
        }
        else if(c == 'n' || c == 'N'){
            //dont delete record, return to menu
            cout << "Records will not be deleted!\n";
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Database::del_rName(){
    vector<int> deleting;
    string s, temp;
    int count = 0;
    cout << "Enter desired Song name: ";
    cin >> s;
    cout << "-------------------------\n";
    cout << "Showing records with '" << s << "'\n";

    //Check for exact match or substring matches
    for(int i = 0;i < name.size();i++){
        temp = name[i];
        //change to all lowercase letters
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        if(temp == s){ //exact match
            print_single_record(i); //show records user is deleting
            deleting.push_back(i);
            count++;
        }
        else if(temp.find(s) != std::string::npos){ //substring match
            print_single_record(i); //show records user is deleting
            deleting.push_back(i);
            count++;
        }
    }
    if(count > 0){
        del_record(deleting); //delete records
    }
    else{
        cout << "No record containing '" << s << "' could be found\n";
    }
}

void Database::del_rArtist(){
    vector<int> deleting;
    string s, temp;
    int count = 0;
    cout << "Enter desired Artist name: ";
    cin >> s;
    cout << "---------------------------\n";
    cout << "Showing records with '" << s << "'\n";

    //Check for exact match or substring matches
    for(int i = 0;i < artist.size();i++){
        temp = artist[i];
        //change to all lowercase letters
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        if(temp == s){ //exact match
            print_single_record(i); //show records user is deleting
            deleting.push_back(i);
            count++;
        }
        else if(temp.find(s) != std::string::npos){ //substring match
            print_single_record(i); //show records user is deleting
            deleting.push_back(i);
            count++;
        }
    }
    if(count > 0){
        del_record(deleting); //delete records
    }
    else{
        cout << "No record containing '" << s << "' could be found\n";
    }
}

void Database::del_rDate(){
    vector<int> deleting;
    cout << "search for a (S)pecific date\n";
    cout << "search for a date (R)ange\n";

    while(true){
        char c;
        cout << "Enter desired search option: ";
        if(!(cin >> c)){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(c == 's' || c == 'S'){
            int n, count = 0;
            cout << "Enter desired date: ";
            cin >> n;
            cout << "--------------------\n";
            cout << "Showing records released in '" << n << "'\n";

            for(int i = 0;i < date.size();i++){
                if(date[i] == n){
                    print_single_record(i); //show records user is deleting
                    deleting.push_back(i);
                    count++;
                }
            }
            if(count > 0){
                del_record(deleting); //delete records
            }
            else{
                cout << "No record released in '" << n << "' found\n";
            }
            break;
        }
        else if(c == 'r' || c == 'R'){
            int n1, n2, count = 0;
            cout << "Enter earliest date: ";
            cin >> n1;
            cout << "Enter latest date: ";
            cin >> n2;
            cout << "---------------------\n";
            cout << "Showing records released from " << n1 << " to " << n2 << endl;

            for(int i = 0;i < date.size();i++){
                if(n1 <= date[i] && date[i] <= n2){
                    print_single_record(i); //show records user is deleting
                    deleting.push_back(i);
                    count++;
                }
            }
            if(count > 0){
                del_record(deleting); //delete records
            }
            else{
                cout << "No records released from " << n1 << " to " << n2 << " were found\n";
            }
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Database::del_rRating(){
    vector<int> deleting;
    int count = 0;
    char c;
    cout << "Enter desired release Rating: ";
    cin >> c;
    cout << "-----------------------------------\n";
    if(c == 'e' || c == 'E') cout << "Showing records rated Explicit\n";
    if(c == 'c' || c == 'C') cout << "Showing records rated Clean\n";

    //Check for exact match or substring matches
    for(int i = 0;i < rating.size();i++){
        if(rating[i] == toupper(c)){ //exact match
            print_single_record(i); //show records user is deleting
            deleting.push_back(i);
            count++;
        }
    }
    if(count > 0){
        del_record(deleting); //delete records
    }
    else{
        if(c == 'e' || c == 'E') cout << "No Explicit record could be found\n";
        if(c == 'c' || c == 'C') cout << "No Clean record could be found\n";
    }
}
//===============================================================
void Database::list_byName() const {
    vector<string> temp = name; //copy of name vector
    std::sort(temp.begin(), temp.end());

    while(true){
        char c;
        cout << "List records (A)lphabetically or (R)everse-Alphabetically: ";
        if(!(cin >> c)){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(c == 'a' || c == 'A'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //alphabetical order
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < name.size();j++){
                    //Find returns index.end() if element j is not found
                    if(name[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << temp[i-1] << " (" << rating[index[i]] << "), "
                    << artist[index[i]] << ", " << date[index[i]] << "\n";
            }
            break;
        }
        else if(c == 'r' || c == 'R'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //reverse-alphabetical order
            std::reverse(temp.begin(), temp.end());
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < name.size();j++){
                    //Find returns index.end() if element j is not found
                    if(name[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << temp[i-1] << " (" << rating[index[i]] << "), "
                    << artist[index[i]] << ", " << date[index[i]] << "\n";
            }
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Database::list_byArtist() const {
    vector<string> temp = artist; //copy of artist vector
    std::sort(temp.begin(), temp.end());

    while(true){
        char c;
        cout << "List records (A)lphabetically or (R)everse-Alphabetically: ";
        if(!(cin >> c)){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(c == 'a' || c == 'A'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //alphabetical order
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < artist.size();j++){
                    //Find returns index.end() if element j is not found
                    if(artist[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << name[index[i]] << " (" << rating[index[i]] << "), "
                    << temp[i-1] << ", " << date[index[i]] << "\n";
            }
            break;
        }
        else if(c == 'r' || c == 'R'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //reverse-alphabetical order
            std::reverse(temp.begin(), temp.end());
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < artist.size();j++){
                    //Find returns index.end() if element j is not found
                    if(artist[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << name[index[i]] << " (" << rating[index[i]] << "), "
                    << temp[i-1] << ", " << date[index[i]] << "\n";
            }
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Database::list_byDate() const {
    vector<int> temp = date; //copy of date vector
    std::sort(temp.begin(), temp.end());

    while(true){
        char c;
        cout << "List records in (A)scending or (D)escending order: ";
        if(!(cin >> c)){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(c == 'a' || c == 'A'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //ascending order
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < date.size();j++){
                    //Find returns index.end() if element j is not found
                    if(date[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << name[index[i]] << " (" << rating[index[i]] << "), "
                    << artist[index[i]] << ", " << temp[i-1] << "\n";
            }
            break;
        }
        else if(c == 'd' || c == 'D'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //descending order
            std::reverse(temp.begin(), temp.end());
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < date.size();j++){
                    //Find returns index.end() if element j is not found
                    if(date[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << name[index[i]] << " (" << rating[index[i]] << "), "
                    << artist[index[i]] << ", " << temp[i-1] << "\n";
            }
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void Database::list_byRating() const { 
    vector<char> temp = rating; //copy of rating vector
    std::sort(temp.begin(), temp.end());

    while(true){
        char c;
        cout << "List records (A)lphabetically or (R)everse-Alphabetically: ";
        if(!(cin >> c)){
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(c == 'a' || c == 'A'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //alphabetical order
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < rating.size();j++){
                    //Find returns index.end() if element j is not found
                    if(rating[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << name[index[i]] << " (" << temp[i-1] << "), "
                    << artist[index[i]] << ", " << date[index[i]] << "\n";
            }
            break;
        }
        else if(c == 'r' || c == 'R'){
            vector<int> index = {-1}; //holds index locations of each copied element
            //reverse-alphabetical order
            std::reverse(temp.begin(), temp.end());
            for(int i = 0;i < temp.size();i++){ 
                for(int j = 0;j < rating.size();j++){
                    //Find returns index.end() if element j is not found
                    if(rating[j] == temp[i] && (find(index.begin(), index.end(), j) == index.end())){
                        index.push_back(j);
                        break;
                    }
                }
            }
            for(int i = 1;i < index.size();i++){
                cout << "   ";
                cout << name[index[i]] << " (" << temp[i-1] << "), "
                    << artist[index[i]] << ", " << date[index[i]] << "\n";
            }
            break;
        }
        else{
            cout << "Invalid Input! ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}
//===============================================================
void Database::print_unordered_records() const {
    int size = name.size(); //size is same for all vectors
    cout << "\nPrinting Unordered Records:\n";

    for(int i = 0;i < size;i++){
        cout << "   ";
        cout << name[i] << " (" << rating[i] << "), "
             << artist[i] << ", " << date[i] << "\n";
    }
}

void Database::print_single_record(int i) const {
    cout << "   ";
    cout << name[i] << " (" << rating[i] << "), "
         << artist[i] << ", " << date[i] << "\n";
}

void Database::init_database(){
    fstream file;
    string line;

    file.open("database.txt", ios::in);
    if(file.is_open()){
        //Grab entire line
        while(getline(file, line)){
            std::stringstream stream(line);
            string field;
            int fieldNum = 0;

            //grab each field
            while(getline(stream, field ,',')){
                if(fieldNum == 0){
                    name.push_back(trim(field));
                }
                else if(fieldNum == 1){
                    artist.push_back(trim(field));
                }
                else if(fieldNum == 2){
                    date.push_back(stoi(trim(field)));
                }
                else if(fieldNum == 3){
                    string trimmed = trim(field);
                    char c = trimmed[0];
                    if(c == ' ') cmpt::error("Some record has an incorrect rating!\n");

                    rating.push_back(c);
                } 
                fieldNum++;
            }
        }
    }
    else{
        cout << "File could not be opened!\n";
    }
    file.close();
}

void Database::save_records(){
    fstream file;
    int size = name.size(); //all vectors are of same size
    string s;

    //Write from file, If file doesnt exist it will be created
    file.open("database.txt", ios::out);
    if(file.is_open()){
        for(int i = 0;i < size;i++){
            file << name[i] << ", " << artist[i] << ", "
                 << date[i] << ", " << rating[i] << "\n"; 
        }
    }
    else{
        cout << "File could not be opened!\n";
    }
    file.close();
}

Database::~Database(){}

string trim(const string& s) {
    int begin = 0;
    while (begin < s.size() && s[begin] == ' ') begin++;
    int end = s.size() - 1;
    while (end >= 0 && s[end] == ' ') end--;

    return s.substr(begin, end - begin + 1);
}
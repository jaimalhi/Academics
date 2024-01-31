#include "Stack.h"
#include <iostream>
using namespace std;


int main () {
    Stack stk;

    // push 1, 2, 3, 4, 5
    cout << "=====================\n";
    cout << "1st Push Test\n";
    cout << "=====================\n";
    for (int i = 1; i <= 5; i++) {
        stk.push(i);
        cout << "push " << i << endl;
    }
    cout << "=====================\n";
    cout << "1st Push Test End\n";
    cout << "=====================\n";

    // pop top two
    cout << "=====================\n";
    cout << "1st Pop Test\n";
    cout << "=====================\n";
    for (int i = 0; i < 2; i++) {
        int x = stk.pop();
        int y = stk.peek();
        cout << "pop " << x << ", top " << y << endl;
    }
    cout << "=====================\n";
    cout << "1st Pop Test End\n";
    cout << "=====================\n";

    // push 6, 7, 8, 9, 10
    cout << "=====================\n";
    cout << "2st Push Test\n";
    cout << "=====================\n";
    for (int i = 6; i <= 10; i++) {
        stk.push(i);
        cout << "push " << i << endl;
    }
    cout << "=====================\n";
    cout << "2st Push Test End\n";
    cout << "=====================\n";

    // pop all
    cout << "=====================\n";
    cout << "Pop All test\n";
    cout << "=====================\n";
    while (!stk.isEmpty()) {
        int x = stk.pop();
        cout << "pop " << x << endl;
    }
    cout << "=====================\n";
    cout << "Pop All test End\n";
    cout << "=====================\n";

    return 0;
}


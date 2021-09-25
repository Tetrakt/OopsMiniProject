#include <iostream>

using namespace std;

int main()
{
    int ch = 0;
    while (ch != 3)
    {
        cout << "Enter 1 or 3" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "1" << endl;
            break;
        case 3:
            cout << "exit";
            break;
        default:
            cout << "lol" << endl;
            break;
        }
    }
    return 0;
}
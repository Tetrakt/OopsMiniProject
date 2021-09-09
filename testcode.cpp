#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    char dept[3];
    cout << "Entder dept : " << endl;
    //cin >> dept;
    cin.getline(dept, 4);
    cout << endl;
    cout << dept;
    return 0;
}
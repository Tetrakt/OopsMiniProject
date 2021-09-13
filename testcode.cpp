#include <iostream>

using namespace std;

int main()
{
    int arr[4];
    int t, i;
    for (i = 0; i < 4; i++)
    {
        cout << "Enter grade 0 to 100 \n";
        cin >> t;
        if (t >= 0 && t <= 100)
            arr[i] = t;
        else
        {
            cout << "invalid, try again, i--" << endl;
            i--;
        }
    }

    cout << "Print test" << endl;
    for (i = 0; i < 4; i++)
        cout << arr[i] << endl;
    return 0;
}
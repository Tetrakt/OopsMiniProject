//same as og
#include <iostream>
#include <string.h>

using namespace std;

class student
{
private:
    int num;

public:
    void printnum(student);
    void set(student *);
};

void student::printnum(student obj)
{
    cout << obj.num << endl;
    cout << "";
}
void student::set(student obz[])
{
    obz[0].num = 0;
    obz[1].num = 1;
    obz[2].num = 2;
}

int main()
{
    student obz[3];
    obz->set(obz);
    obz->printnum(obz[0]);
    obz->printnum(obz[1]);
    obz->printnum(obz[2]);

    return 0;
}
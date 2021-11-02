#include <iostream>
//#include <bits/stdc++.h>
#include <string.h>

#define STUDENT_COUNT 20
#define FACULTY_COUNT 5

#define SDB_PASSKEY "LOL"
#define FDB_PASSKEY "LOL"

using namespace std;
//define global array for id

int uIDlist[25];
int db_count = 0;
//find better soln.
void uIDlist_set()
{
    for (int i = 0; i < 25; i++)
        uIDlist[i] = 0;
}
void uIdlist_insert(int id)
{
    uIDlist[db_count] = id;
}
bool uIDlist_isUniqe(int id)
{
    for (int i = 0; i < 25; i++)
    {
        if (uIDlist[i] == id)
            return false;
    }
    return true;
}
class DataBase //25 instances
{
protected: // protected not private
    string name;
    int age;
    char gender;
    int birthyear;
    int rollNum;
    char role; // student or faculty
    DataBase()
    {
        name = " ";
        age = 0;
        gender = ' ';
        birthyear = 0000;
        role = ' ';
        rollNum = 0;
    }

public:
    // void display(DataBase);
    // void printAll(DataBase *);
    friend class Student; // thus db can access
};

class Student : protected DataBase //20instances, subclass
{
private:
    char section;
    char subj[6][3];
    int grades[6];

public:
    void createStudent();
    void displayStudent(Student);
    void printStudentDB(Student *);
    void modifyStudent(Student);
};

class Faculty : protected DataBase //5 instances //subclass
{
protected:
    int salary;
    char dept[3];

public:
    void display();
};

int main()
{
    return 0;
}
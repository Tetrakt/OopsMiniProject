/* functions to manage data
* show data on certain parameter
*store data for each in a given file
*student and faculty file, maybe more files?
* teacher guardian implementation?
* grades of students, calculate max, min, etc
* fixed size of students and faculty,
*/
#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#include <cstdio>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>

#define STUDENTS_COUNT 100
#define FACULTY_COUNT 10

using namespace std;

class Student
{
private:
    string Name;
    static int studentCount; // stores count of students as ID
    int age;
    char section;
    char gender;
    int birthYear;
    char dept1[3];
    char dept2[3];
    char dept3[3];

public:
    Student() // default constructor
    {
        studentCount = 0;
        Name = " ";
        age = 0;
        section = ' ';
        gender = ' ';
        birthYear = 0000;
        dept1[0] = dept1[1] = dept1[2] = 'A';
        dept2[0] = dept2[1] = dept2[2] = 'A';
        dept3[0] = dept3[1] = dept3[2] = 'A';
    }
    void createStudent();
    void displayStudent();
    void modifyStudent();
    void gradeSummary();
    void printDepartments();
};

void Student::createStudent()
{
    cout << "\n CREATING A STUDENT..." << endl;
    cout << "Enter Student Name: ";
    getline(cin, Name);
    //enter uniqueID
    cout << "\nEnter age : ";
    cin >> age;
    cout << "\nEnter Section : ";
    cin >> section;
    cout << "\n Enter gender: ";
    cin >> gender;
    cout << "\n Dept1 : ";
    cin >> dept1;
    cout << "\n Department 2 : ";
    cin >> dept2;
    cout << "\nDepartment 3 : ";
    cin >> dept3;
}
void Student::displayStudent()
{
    cout << "Name : " << Name << endl;
    //cout unique id
    cout << " Age : " << age << endl;
    cout << "Section : " << section << endl;
    cout << "Gender : " << gender << endl;
    cout << "Department 1 : " << dept1 << endl;
    cout << "Department 2 : " << dept2 << endl;
    cout << "Department 3 : " << dept3 << endl;
}
class Faculty
{
private:
public:
};

void main()
{
    Student StudentObj[STUDENTS_COUNT];
    Faculty FacultyObj[FACULTY_COUNT];
}
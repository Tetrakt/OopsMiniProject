/* functions to manage data
* show data on certain parameter
*store data for each in a given file
*student and faculty file, maybe more files?
* teacher guardian implementation?
* grades of students, calculate max, min, etc
* fixed size of students and faculty,
* added few changes
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
// CSV ? Maybe even see how much data is there??
// non temporary data storage mgmt
#define STUDENTS_COUNT 100
#define FACULTY_COUNT 10

using namespace std;

class Student
{
private:
    string Name;
    static int studentCount;             // stores count of students as ID
    static unordered_set<int> StudentID; //hash set
    int uniqueSID;                       // unique student ID
    int age;
    char section;
    char gender;
    int birthYear;
    char subj1[3]; //might get renamed to subj
    char subj2[3];
    char subj3[3];
    int grades[6];

public:
    Student() // default constructor
    {
        studentCount = 0;
        Name = " ";
        age = 0;
        section = ' ';
        gender = ' ';
        birthYear = 0000;
        subj1[0] = subj1[1] = subj1[2] = 'A';
        subj2[0] = subj2[1] = subj2[2] = 'A';
        subj3[0] = subj3[1] = subj3[2] = 'A';
    }

    //modiy parameters any time
    void createStudent();
    void displayStudent(Student);
    void printStdDatabase(Student *); // prints all
    void modifyStudent(Student);
    void updateGrades(Student);
    // void gradeSummary();
    void printDepartments(); //depts for a student
    //void deleteStudent();
    bool isUniqueSID(int);
};

void Student::createStudent()
{
    int t;
    //consider piping output to csv file?
    cout << "\n CREATING A STUDENT..." << endl;
    cout << "Enter Student Name: ";
    getline(cin, Name);
    //enter uniqueID, if not uq, exit this func
    cout << "\n Enter Unique Student ID : ";
    cin >> t; // store input temporaily
    if (isUniqueSID(t))
        uniqueSID = t;
    else
    {
        cout << "\n ID entered already exists.";
        exit(0);
    }
    cout << "\nEnter age : ";
    cin >> age;
    cout << "\nEnter Birth Year";
    cin >> birthYear;
    cout << "\nEnter Section : ";
    cin >> section;
    cout << "\n Enter gender: ";
    cin >> gender;
    cout << "\n Subject 1 : ";
    cin >> subj1;
    cout << "\n Subject 2 : ";
    cin >> subj2;
    cout << "\n Subject 3 : ";
    cin >> subj3;
    cout << " * STUDENT DATA CREATED SUCCESFULLY \n";
}
void Student::displayStudent(Student obj) // displays one student
{
    cout << "Name : " << obj.Name << endl;
    //cout unique id
    cout << " Age : " << obj.age << endl;
    cout << "Section : " << obj.section << endl;
    cout << "Gender : " << obj.gender << endl;
    cout << "Subjectt 1 : " << obj.subj1 << endl;
    cout << "Subeject 2 : " << obj.subj2 << endl;
    cout << "Subject 3 : " << obj.subj3 << endl;
}
void Student::modifyStudent(Student obj) // or student id
{
    //recieves uid, then gives list of options that can be updated
    // gives list as to what can be changed.
    // then changes accordingly, uses switch case
    int ch;
    cout << "*STUDENT TO BE MODIFIED*" << endl;
    displayStudent(obj);
    cout << "\n menu list" << endl;
    cout << " 1. Section " << endl;
    cout << " 2. Subject 1 " << endl;
    cout << " 3. Subject 2 " << endl;
    cout << " 4. Subject 3 " << endl;
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        cout << "Enter new Section : ";
        cin >> obj.section;
    }
    break;
    case 2:
    {
        cout << "Enter new subject 1 : ";
        cin >> obj.subj1;
    }
    break;
    case 3:
    {
        cout << "Enter new Subject 2 : ";
        cin >> obj.subj2;
    }
    break;
    case 4:
    {
        cout << "Enter new Subject 3 : ";
        cin >> obj.subj3;
    }
    break;
    default:
    {
        cout << "Invalid Option, Please try again ";
    }
    break;
    }
}

void Student::updateGrades(Student obj)
{
    int t;
    cout << "\n Enter the marks of 6 subjects (0-100) ";
    for (int i = 0; i < 6; i++)
    {
        cin >> t;
        if (t >= 0 && t <= 100)
            obj.grades[i] = t;
        else
        {
            cout << "invalid input,try again \n";
            i--;
        }
    }
}
void Student::printStdDatabase(Student StudentObj[])
{
    for (int i = 0; i < studentCount; i++)
        displayStudent(StudentObj[i]);
}
bool Student::isUniqueSID(int id)
{
    if (StudentID.find(id) == StudentID.end())
        return false;
    else
        return true;
}
class Faculty
{
private:
    string Name;
    static int facultyCount;             // stores count of students as ID
    static unordered_set<int> FacultyID; //hash set
    int uniqueFID;                       // unique student ID
    int age;
    //char section;
    char gender;
    int birthYear;
    char dept[3];
    int salary;

public:
    Faculty()
    {
        Name = " ";
        age = 0;
        gender = ' ';
        birthYear = 0000;
        dept[0] = dept[1] = dept[2] = 'A';
        salary = 0;
    }
    void createFaculty();
    void displayFaculty(Faculty);
    void printFctDatabase(Faculty FacultyObj[]);
    void modifyFaculty(Faculty);
    void printDepartment(); //depts for a faculty
    void deleteFaculty();
    bool isUniqueFID(int);
};
void Faculty::createFaculty()
{
    int t;
    //consider piping output to csv file?
    cout << "\n CREATING A Faculty..." << endl;
    cout << "Enter Faculty Name: ";
    getline(cin, Name);
    //enter uniqueID, if not uq, exit this func
    cout << "\n Enter Unique Faculty ID : ";
    cin >> t; // store input temporaily
    if (isUniqueFID(t))
        uniqueFID = t;
    else
    {
        cout << "\n ID entered already exists.";
        exit(0);
    }
    cout << "\nEnter age : ";
    cin >> age;
    cout << "\n Enter Birth Year : ";
    cin >> birthYear;
    cout << "\n Enter gender: ";
    cin >> gender;
    cout << "\n Department : ";
    cin >> dept;
    cout << "\n Enter salary : ";
    cin >> salary;
    cout << " * FACULTY DATA CREATED SUCCESFULLY \n";
}

void Faculty::displayFaculty(Faculty obj)
{
    cout << "Name : " << obj.Name << endl;
    cout << " Unique Faculty ID : " << obj.uniqueFID << endl;
    cout << " Age : " << obj.age << endl;
    cout << "Birth Year : " << obj.birthYear << endl;
    cout << "Gender : " << obj.gender << endl;
    cout << "Department 1 : " << obj.dept << endl;
    cout << "Salary : " << obj.salary << endl;
}

void Faculty::printFctDatabase(Faculty FacultyObj[])
{
    for (int i = 0; i < facultyCount; i++)
        displayFaculty(FacultyObj[i]);
}

bool Faculty::isUniqueFID(int id)
{
    if (FacultyID.find(id) == FacultyID.end())
        return false;
    else
        return true;
}

void main()
{
    Student StudentObj[STUDENTS_COUNT];
    Faculty FacultyObj[FACULTY_COUNT];
    //menu to view student or faculty data base
    //password protected?
    //then call related functions
}
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
    void modifyStudent();
    // void gradeSummary();
    void printDepartments(); //depts for a student
    void deleteStudent();
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
bool Student::isUniqueSID(int id)
{
    if (StudentID.find(id) == StudentID.end())
        return false;
    else
        return true;
}
void Student::printStdDatabase(Student StudentObj[])
{
    for (int i = 0; i < studentCount; i++)
        displayStudent(StudentObj[i]);
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
    void printFctDatabase();
    void modifyFaculty(Faculty);
    void printDepartment(); //depts for a faculty
    void deleteFaculty();
    bool isUniqueFID(int);
};
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
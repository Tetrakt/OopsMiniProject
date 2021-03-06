
#include <iostream>
#include <string.h>

#define STUDENTS_COUNT 100
#define FACULTY_COUNT 10

#define FDD_PASSKEY "Faculty@737" //passkey for faculty db
#define SDB_PASSKEY "Student#000" //passkey for Student db

using namespace std;

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
    uIDlist[db_count++] = id;
}
bool uIDlist_isUnique(int id)
{
    for (int i = 0; i < 25; i++)
    {
        if (uIDlist[i] == id)
            return false;
    }
    return true;
}

class Student
{
private:
    string Name;
    static int studentCount; // stores count of students as ID
    int uniqueSID;           // unique student ID
    int rollID;
    int age; // becomes the friend func
    char section;
    char gender; // male,female, other, used for friend function
    int birthYear;
    char subj1[3]; //might get renamed to subj
    char subj2[3];
    char subj3[3];
    int grades[6];
    const int valx; //batch year

public:
    Student() : valx(15) // default constructor + init list
    {
        //studentCount = 0;
        Name = " ";
        age = 0;
        section = ' '; // one param
        gender = ' ';
        birthYear = 0000;
        subj1[0] = subj1[1] = subj1[2] = 'A';
        subj2[0] = subj2[1] = subj2[2] = 'A';
        subj3[0] = subj3[1] = subj3[2] = 'A';
        //StudentID.insert(NULL);
    }
    Student(int birthYear) : valx(15)
    {
        this->birthYear = birthYear;
    }

    void createStudent();
    void displayStudent(Student);
    void printStdDatabase(Student *); // prints all
    void modifyStudent(Student);
    void updateGrades(Student); // convert to a friend?
    void gradeSummary(Student);
    void printDepartments(); //depts for a student
    friend void printGender(Student);
    ~Student()
    {
        cout << "Student Destructor, student deleted";
    }
};
int Student::studentCount = 1;

void Student::createStudent()
{
    int t;
    cout << "\n CREATING A STUDENT..." << endl;
    cout << "Enter Student Name: ";
    cin >> Name;
    //enter uniqueID, if not uq, exit this func
    cout << "\nEnter Unique Student ID : ";
    cin >> t; // store input temporaily
    if (uIDlist_isUnique(t))
    {
        uniqueSID = t;
        //insert into it
        uIdlist_insert(t);
    }
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
    Student::studentCount++;
    rollID = Student::studentCount;
    cout << "Roll ID assigned : " << rollID << endl;
    cout << " * STUDENT DATA CREATED SUCCESFULLY \n";
}
void Student::displayStudent(Student obj) // displays one student
{
    cout << "Name : " << obj.Name << endl;
    //cout unique id
    cout << "Unique ID : " << obj.uniqueSID << endl;
    cout << "Roll Number : " << obj.rollID << endl;
    cout << "Age : " << obj.age << endl;
    cout << "Section : " << obj.section << endl;
    cout << "Gender : " << obj.gender << endl;
    cout << "Subject 1 : " << obj.subj1 << endl;
    cout << "Subject 2 : " << obj.subj2 << endl;
    cout << "Subject 3 : " << obj.subj3 << endl;
}
void Student::printStdDatabase(Student StudentObj[])
{
    for (int i = 0; i < Student::studentCount; i++)
        displayStudent(StudentObj[i]);
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
void Student::gradeSummary(Student obj)
{
    int sum = 0, min = 0, max = 0, i;
    min = max = obj.grades[0];
    float gpa, gradePercent, avg;
    for (i = 0; i < 6; i++)
    {
        if (obj.grades[i] > max)
            max = obj.grades[i];
        if (obj.grades[i] < min)
            min = obj.grades[i];
        sum += obj.grades[i];
    }
    avg = (float)sum / 6;
    gradePercent = (float)sum / 600.0;
    gpa = gradePercent / 10.0;

    cout << "Grade Summary of Student : " << obj.Name << endl;
    cout << "GPA : " << gpa << endl;
    cout << "Highest Marks : " << max << endl;
    cout << "Lowest Marks : " << min << endl;
    cout << "Average Marks : " << avg;
    cout << "Overall Percentage : " << gradePercent << " % " << endl;
}
void printGender(Student obj)
{
    if (obj.gender == 'M' || obj.gender == 'm')
        cout << "male" << endl;
    else if (obj.gender == 'F' || obj.gender == 'f')
        cout << "female" << endl;
    else
        cout << "Other gender" << endl;
}
class Faculty
{
private:
    string Name;
    static int facultyCount;
    int uniqueFID;
    int rollID;
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
    Faculty(int salary)
    {
        this->salary = salary;
    }
    void createFaculty();
    void displayFaculty(Faculty);
    void printFctDatabase(Faculty FacultyObj[]);
    void modifyFaculty(Faculty);
    void printDepartment(); //depts for a faculty
    friend void printGender(Faculty);
    ~Faculty()
    {
        cout << "Faculty deleted";
    }
};
int Faculty::facultyCount = 1;
void Faculty::createFaculty()
{
    int t;
    cout << "\n CREATING A Faculty..." << endl;
    cout << "Enter Faculty Name: ";
    cin >> Name;
    cout << "\n Enter Unique Faculty ID : ";
    cin >> t; // store input temporaily
    if (uIDlist_isUnique(t))
    {
        uniqueFID = t;
        uIdlist_insert(t);
    }
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
    cout << "Unique Faculty ID : " << obj.uniqueFID << endl;
    cout << "Age : " << obj.age << endl;
    cout << "Birth Year : " << obj.birthYear << endl;
    cout << "Gender : " << obj.gender << endl;
    cout << "Department : " << obj.dept << endl;
    cout << "Salary : " << obj.salary << endl;
}
void Faculty::printFctDatabase(Faculty FacultyObj[])
{
    for (int i = 0; i < facultyCount; i++)
        displayFaculty(FacultyObj[i]);
}
void Faculty::modifyFaculty(Faculty obj) // or student id
{
    //recieves uid, then gives list of options that can be updated
    // gives list as to what can be changed.
    // then changes accordingly, uses switch case
    int ch;
    cout << "*Faculty TO BE MODIFIED*" << endl;
    displayFaculty(obj);
    cout << "\n menu list" << endl;
    cout << " 1. Department " << endl;
    cout << " 2. Salary " << endl;
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        cout << "Enter new Department : ";
        cin >> obj.dept;
    }
    break;
    case 2:
    {
        cout << "Enter new Salary : ";
        cin >> obj.salary;
    }
    break;
    default:
    {
        cout << "Invalid Option, Please try again ";
    }
    break;
    }
}
void printGender(Faculty obj)
{
    if (obj.gender == 'M' || obj.gender == 'm')
        cout << "male" << endl;
    else if (obj.gender == 'F' || obj.gender == 'f')
        cout << "female" << endl;
    else
        cout << "Other gender" << endl;
}
inline void printMenu(int ch) //student menu
{
    if (ch == 1)
    {
        cout << "1. enter data" << endl;
        cout << "2. print all" << endl;
        cout << "3. select 1" << endl; //  input for key
        cout << "4. modify" << endl;
        cout << "5. update grades" << endl;
        cout << "6. grade summary" << endl;
        cout << "7. gender detail" << endl;
        cout << "0. Exit " << endl;
    }
    else if (ch == 2)
    {
        //faculty menu
        cout << "1. enter data" << endl;
        cout << "2. print all" << endl;
        cout << "3. select 1" << endl; //
        cout << "4. modify" << endl;
        cout << "0. Exit" << endl;
    }
}
inline void printMenu() //db menu, student or faculty
{
    //student or faculty
    cout << " 1. student db" << endl;
    cout << " 2. faculty db" << endl;
    cout << " 3. exit " << endl;
}

int main()
{
    Student *StudentObj = new Student[STUDENTS_COUNT];
    Faculty *FacultyObj = new Faculty[FACULTY_COUNT];
    for (int i = 0; i < STUDENTS_COUNT; i++)
    {
        Student(2000);
        //or
        //Student(i+1); setting roll number too.
    }
    for (int i = 0; i < FACULTY_COUNT; i++)
    {
        Faculty(50000);
    }
    int t1, t2, t3; //rename
    int ch1 = -1, ch2 = -1;
    cout << "University DataBase Management System" << endl;
    //passkey verification ?
    printMenu();
    cin >> ch1;
    while (ch1 != 3)
    {
        if (ch1 == 1)
        {
            while (ch2 != 0) // exit is zero is given
            {
                printMenu(ch1); //convert to inline
                cin >> ch2;
                switch (ch2)
                {
                case 0:
                    break;
                case 1:
                    StudentObj->createStudent();
                    break;
                case 2:
                    StudentObj->printStdDatabase(StudentObj); //pass array of objs
                    break;
                case 3:
                    cout << "Enter Roll Number 1 to student count : ";
                    cin >> t1;
                    StudentObj->displayStudent(StudentObj[t1 - 1]); //t1-1 as roll num from 1, but array from 0
                    break;
                case 4:
                    cout << "Enter Roll Number to modify : ";
                    cin >> t1;
                    StudentObj->modifyStudent(StudentObj[t1 - 1]);
                case 5:
                    cout << "Enter roll id to update grades : ";
                    cin >> t1;
                    StudentObj->updateGrades(StudentObj[t1 - 1]);
                    break;
                case 6:
                    cout << "Enter roll id for grade Summary : ";
                    cin >> t1;
                    StudentObj->gradeSummary(StudentObj[t1 - 1]);
                    break;
                case 7:
                    cout << "Enter roll ID for gender : ";
                    cin >> t1;
                    printGender(StudentObj[t1 - 1]);
                    break;
                default:
                    break;
                }
            }
        }
        else if (ch1 == 2)
        {
            while (ch2 != 0)
            {
                printMenu(ch1);
                cin >> ch2;
                switch (ch2)
                {
                case 0:
                    break;
                case 1:
                    FacultyObj->createFaculty();
                    break;
                case 2:
                    FacultyObj->printFctDatabase(FacultyObj);
                    break;
                case 3:
                    cout << "Enter Faculty roll number : ";
                    cin >> t1;
                    FacultyObj->displayFaculty(FacultyObj[t1 - 1]);
                    break;
                case 4:
                    cout << "Enter Roll number to modify : ";
                    cin >> t1;
                    FacultyObj->modifyFaculty(FacultyObj[t1 - 1]);
                    break;
                default:
                    break;
                }
            }
        }
        printMenu();
        cin >> ch1;
        ch2 = -1;
    }
    delete[] StudentObj;
    delete[] FacultyObj;
    return 0;
}
//i hope this is final lol
#include <iostream>
#include <string.h>

#define STUDENTS_COUNT 5 //max of each
#define FACULTY_COUNT 2
#define PHD_COUNT 1

#define FDD_PASSKEY "Faculty@737" //passkey for faculty db
#define SDB_PASSKEY "Student#000" //passkey for Student db

using namespace std;

int uIDlist[25]; //student,faculty,phd count
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
class DataBase //25 instances
{
protected: // protected not private
    string name;
    int age;
    char gender;
    int birthYear;
    int rollNum;  //auto generated
    int uniqueID; //given on input
    char role;    // S,F or P
    DataBase()
    {
        name = " ";
        age = 0;
        gender = ' ';
        birthYear = 0000;
        role = ' ';
        rollNum = 0;
        uniqueID = 0;
    }

public:
    void display(DataBase);    //todo
    void printAll(DataBase *); //todo
    friend class Student;      // thus db can access
    friend class Faculty;
};

class Student : protected DataBase //20instances, subclass
{
private:
    char section;
    int grades[6];
    char subj1[3]; //might get renamed to subj
    char subj2[3];
    char subj3[3];
    int grades[6];
    const int batchyr; //batch year
    static int studentCount;

public:
    Student() : batchyr(18) // default constructor + init list
    {
        age = 0;
        section = ' '; // one param
        gender = ' ';
        subj1[0] = subj1[1] = subj1[2] = 'A';
        subj2[0] = subj2[1] = subj2[2] = 'A';
        subj3[0] = subj3[1] = subj3[2] = 'A';
    }
    Student(int birthYear) : batchyr(18)
    {
        this->birthYear = birthYear;
    }
    void createStudent();
    void displayStudent();
    void printStudentDB(Student *);
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
    cin >> name;
    //enter uniqueID, if not uq, exit this func
    cout << "\nEnter Unique Student ID : ";
    cin >> t; // store input temporaily
    if (uIDlist_isUnique(t))
    {
        uniqueID = t;
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
    //Student::studentCount++;
    rollNum = Student::studentCount++;
    cout << "Roll ID assigned : " << rollNum << endl;
    cout << " * STUDENT DATA CREATED SUCCESFULLY \n";
}
void Student::displayStudent()
{
    cout << "Name : " << this->name << endl;
    cout << "Unique ID : " << this->uniqueID << endl;
    cout << "Roll Number : " << this->rollNum << endl;
    cout << "Age : " << this->age << endl;
    cout << "Section : " << this->section << endl;
    cout << "Gender : " << this->gender << endl;
    cout << "Subject 1 : " << this->subj1 << endl;
    cout << "Subject 2 : " << this->subj2 << endl;
    cout << "Subject 3 : " << this->subj3 << endl;
}

class Faculty : protected DataBase //5 instances //subclass
{
protected:
    int salary;
    char dept[3];

public:
    //void display();
};

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
        cout << "3. select 1" << endl;
        cout << "4. modify" << endl;
        cout << "0. Exit" << endl;
    }
    else if (ch == 3)
    {
        //phd menu
        cout << "1. " << endl;
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
        //  Faculty(50000);
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
                    StudentObj->printStudentDB(StudentObj); //pass array of objs
                    break;
                case 3:
                    cout << "Enter Roll Number 1 to student count : ";
                    cin >> t1;
                    //StudentObj->displayStudent(StudentObj[t1 - 1]); //t1-1 as roll num from 1, but array from 0
                    StudentObj[t1 - 1].displayStudent();
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
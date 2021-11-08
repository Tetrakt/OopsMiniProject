//i hope this is final lol
#include <iostream>
#include <string.h>
#include <fstream>

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
    //int rollNum;  //auto generated
    int uniqueID; //given on input
    char role;    // S,F or P
    DataBase()
    {
        name = " ";
        age = 0;
        gender = ' ';
        birthYear = 0000;
        role = ' ';
        uniqueID = 0;
    }

public:
    void display(DataBase);    //todo
    void printAll(DataBase *); //todo
    friend class Student;      // thus db can access
    friend class Faculty;
};

class Student : virtual protected DataBase //20 instances, subclass
{
private:
    char section;
    int grades[6];
    char subj1[3]; //might get renamed to subj
    char subj2[3];
    char subj3[3];
    const int batchyr; //batch year
    int rollNum;
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
    void modifyStudent();
    void updateGrades(); // convert to a friend?
    void gradeSummary();
    void printDepartments(); //depts for a student
    void writeToFile_stud(Student *);
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
void Student::printStudentDB(Student StudentObj[])
{
    for (int i = 0; i < Student::studentCount; i++)
        StudentObj[i].displayStudent();
}
void Student::modifyStudent()
{
    //Choose basis of roll num?? sent from main()?
    int ch;
    cout << "*STUDENT TO BE MODIFIED*" << endl;
    cout << "Name : " << this->name << endl;
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
        cin >> this->section;
    }
    break;
    case 2:
    {
        cout << "Enter new subject 1 : ";
        cin >> this->subj1;
    }
    break;
    case 3:
    {
        cout << "Enter new Subject 2 : ";
        cin >> this->subj2;
    }
    break;
    case 4:
    {
        cout << "Enter new Subject 3 : ";
        cin >> this->subj3;
    }
    break;
    default:
    {
        cout << "Invalid Option, Please try again ";
    }
    break;
    }
}
void Student::updateGrades()
{
    int t;
    cout << "\n Enter the marks of 6 subjects (0-100) ";
    for (int i = 0; i < 6; i++)
    {
        cin >> t;
        if (t >= 0 && t <= 100)
            this->grades[i] = t;
        else
        {
            cout << "invalid input,try again \n";
            i--;
        }
    }
}
void Student::gradeSummary()
{
    int sum = 0, min = 0, max = 0, i;
    min = max = this->grades[0];
    float gpa, gradePercent, avg;
    for (i = 0; i < 6; i++)
    {
        if (this->grades[i] > max)
            max = this->grades[i];
        if (this->grades[i] < min)
            min = this->grades[i];
        sum += this->grades[i];
    }
    avg = (float)sum / 6;
    gradePercent = (float)sum / 600.0;
    gpa = gradePercent / 10.0;
    cout << "Grade Summary of Student : " << this->name << endl;
    cout << "GPA : " << gpa << endl;
    cout << "Highest Marks : " << max << endl;
    cout << "Lowest Marks : " << min << endl;
    cout << "Average Marks : " << avg;
    cout << "Overall Percentage : " << gradePercent << " % " << endl;
}

void Student::writeToFile_stud(Student StudentObj[])
{
    ofstream file_obj;                      // Object to write in file
    file_obj.open("Stud_db.txt", ios::out); // Opening file in append mode
    for (int i = 0; i < Student::studentCount; i++)
    {
        file_obj << StudentObj[i].name << " ";
        file_obj << StudentObj[i].uniqueID << " ";
        file_obj << StudentObj[i].rollNum << " ";
        file_obj << StudentObj[i].age << " ";
        file_obj << StudentObj[i].section << " ";
        file_obj << StudentObj[i].gender << " ";
        file_obj << StudentObj[i].subj1 << " ";
        file_obj << StudentObj[i].subj2 << " ";
        file_obj << StudentObj[i].subj3 << endl;
        //file_obj.write((char*)&StudentObj[i], sizeof(StudentObj[i]));
    }
    file_obj.close();
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
class Faculty : virtual protected DataBase //5 instances //subclass
{
protected:
    int salary;
    char dept[3];
    static int facultyCount;
    int rollNum;

public:
    //void display();
    void createFaculty();
    void displayFaculty();
    void printFacultyDB(Faculty *);
    void modifyFaculty();
    void writeToFile_faculty(Faculty *);
    //print dept, for student?
    Faculty()
    {
        name = " ";
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
    ~Faculty()
    {
        cout << "Faculty destructor";
    }
};
int Faculty::facultyCount = 1;
void Faculty::createFaculty()
{
    int t;
    cout << "\n CREATING A Faculty..." << endl;
    cout << "Enter Faculty Name: ";
    cin >> name;
    cout << "\n Enter Unique Faculty ID : ";
    cin >> t; // store input temporaily
    if (uIDlist_isUnique(t))
    {
        uniqueID = t;
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
    rollNum = Faculty::facultyCount++;
    cout << "Roll ID assigned : " << rollNum << endl;
    cout << " * FACULTY DATA CREATED SUCCESFULLY \n";
}
void Faculty::displayFaculty()
{
    cout << "Name : " << this->name << endl;
    cout << "Unique Faculty ID : " << this->uniqueID << endl;
    cout << "Age : " << this->age << endl;
    cout << "Birth Year : " << this->birthYear << endl;
    cout << "Gender : " << this->gender << endl;
    cout << "Department : " << this->dept << endl;
    cout << "Salary : " << this->salary << endl;
}
void Faculty::printFacultyDB(Faculty FacultyObj[])
{
    for (int i = 0; i < facultyCount; i++)
        FacultyObj[i].displayFaculty();
}
void Faculty::modifyFaculty()
{
    int ch;
    cout << "*Faculty TO BE MODIFIED*" << endl;
    cout << "Name : " << this->name << endl;
    cout << "\n menu list" << endl;
    cout << " 1. Department " << endl;
    cout << " 2. Salary " << endl;
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        cout << "Enter new Department : ";
        cin >> this->dept;
    }
    break;
    case 2:
    {
        cout << "Enter new Salary : ";
        cin >> this->salary;
    }
    break;
    default:
    {
        cout << "Invalid Option, Please try again ";
    }
    break;
    }
}

void Faculty::writeToFile_faculty(Faculty FacultyObj[])
{
    ofstream file_obj;                      // Object to write in file
    file_obj.open("Faculty_db.txt", ios::out); // Opening file in append mode
    for (int i = 0; i < Faculty::facultyCount; i++)
    {
        file_obj << FacultyObj[i].name << " ";
        file_obj << FacultyObj[i].uniqueID << " ";
        file_obj << FacultyObj[i].rollNum << " ";
        file_obj << FacultyObj[i].age << " ";
        file_obj << FacultyObj[i].dept << " ";
        file_obj << FacultyObj[i].gender << " ";
        file_obj << FacultyObj[i].salary << endl;
    }
    file_obj.close();
}

class Masters : public Student, public Faculty
{
private:
    char section;
    int grade;
    char subj[3];      //masters to be done in 1 subj only
    const int batchyr; //batch year
    int rollNum;
    static int masterCount;

public:
    //functions
    Masters() : batchyr(14) // default constructor + init list
    {
        age = 0;
        section = ' '; // one param
        gender = ' ';
        subj[3] = 'A';
    }
    Masters(int birthYear) : batchyr(14)
    {
        this->birthYear = birthYear;
    }
    void createMaster();
    void displayMaster();
    void printMasterDB(Masters *);
    void modifyMaster();
    void updateMasterGrade(); // convert to a friend?
    //void gradeSummary(); no need here
    void printDepartments(); //depts for a master
    void writeToFile_masters(Masters *);
    friend void printGender(Masters);
    ~Masters()
    {
        cout << "Masters Destructor, Masters deleted";
    }
};
int Masters::masterCount = 1;
void Masters::createMaster()
{
    int u;
    cout << "\n CREATING A MASTER..." << endl;
    cout << "Enter Master Name: ";
    cin >> name;
    //enter uniqueID, if not uq, exit this func
    cout << "\nEnter Unique Master ID : ";
    cin >> u; // store input temporaily
    if (uIDlist_isUnique(u))
    {
        uniqueID = u;
        uIdlist_insert(u);
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
    cout << "\n Subject : ";
    cin >> subj;
    //Student::studentCount++;
    rollNum = Masters::masterCount++;
    cout << "Roll ID assigned : " << rollNum << endl;
    cout << " * MASTER DATA CREATED SUCCESFULLY \n";
}
void Masters::displayMaster()
{
    cout << "Name : " << this->name << endl;
    cout << "Unique ID : " << this->uniqueID << endl;
    cout << "Roll Number : " << this->rollNum << endl;
    cout << "Age : " << this->age << endl;
    cout << "Section : " << this->section << endl;
    cout << "Gender : " << this->gender << endl;
    cout << "Subject : " << this->subj << endl;
}
void Masters::printMasterDB(Masters MastersObj[])
{
    for (int i = 0; i < Masters::masterCount; i++)
        MastersObj[i].displayMaster();
}
void Masters::modifyMaster()
{
    //Choose basis of roll num?? sent from main()?
    int ch;
    cout << "*MASTER TO BE MODIFIED*" << endl;
    cout << "Name : " << this->name << endl;
    cout << "\n menu list" << endl;
    cout << " 1. Section " << endl;
    cin >> ch;
    switch (ch)
    {
        {
        case 1:
            cout << "Enter new Section: ";
            cin >> this->section;
        }
        break;
    default:
    {
        cout << "Invalid Option";
    }
    break;
    }
}
void Masters::updateMasterGrade()
{
    int u;
    cout << "\n Enter marks of the subject";
    if (u >= 0 && u <= 100)
    {
        grade = u;
    }
    else
    {
        cout << "Invalid input \n";
    }
}
void Masters::writeToFile_masters(Masters MastersObj[])
{
    ofstream file_obj;                      // Object to write in file
    file_obj.open("Masters_db.txt", ios::out); // Opening file in append mode
    for (int i = 0; i < Masters::masterCount; i++)
    {
        file_obj << MastersObj[i].name << " ";
        file_obj << MastersObj[i].uniqueID << " ";
        file_obj << MastersObj[i].rollNum << " ";
        file_obj << MastersObj[i].age << " ";
        file_obj << MastersObj[i].dept << " ";
        file_obj << MastersObj[i].gender << " ";
        file_obj << MastersObj[i].subj << " ";
        file_obj << MastersObj[i].grade << " ";
        file_obj << MastersObj[i].salary << endl;
    }
    file_obj.close();
}
void printGender(Masters obj)
{
    if (obj.gender == 'M' || obj.gender == 'm')
        cout << "male" << endl;
    else if (obj.gender == 'F' || obj.gender == 'f')
        cout << "female" << endl;
    else
        cout << "Other gender" << endl;
}

inline void printMenu(int ch)
{
    if (ch == 1) //student menu
    {
        cout << "1. enter data" << endl;
        cout << "2. print all" << endl;
        cout << "3. select 1" << endl; //  input for key
        cout << "4. modify" << endl;
        cout << "5. update grades" << endl;
        cout << "6. grade summary" << endl;
        cout << "7. gender detail" << endl;
        cout << "8. update database" << endl;
        cout << "0. Exit " << endl;
    }
    else if (ch == 2)
    {
        //faculty menu
        cout << "1. enter data" << endl;
        cout << "2. print all" << endl;
        cout << "3. select 1" << endl;
        cout << "4. modify" << endl;
        cout << "5.update database" << endl;
        cout << "0. Exit" << endl;
    }
    else if (ch == 3)
    {
        //phd menu
        cout << "1. enter data" << endl;
        cout << "2. print all" << endl;
        cout << "3. select 1" << endl; //  input for key
        cout << "4. modify" << endl;
        cout << "5. update grade" << endl;
        cout << "7. gender detail" << endl;
        cout << "8. update database" << endl;
        cout << "0. Exit " << endl;
    }
}
inline void printMenu() //db menu, student or faculty
{
    //student, faculty or phd
    cout << " 1. student db" << endl;
    cout << " 2. faculty db" << endl;
    cout << " 3. PHD db" << endl;
    cout << " 4. exit " << endl;
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
                    StudentObj[t1 - 1].modifyStudent();
                case 5:
                    cout << "Enter roll id to update grades : ";
                    cin >> t1;
                    StudentObj[t1 - 1].updateGrades();
                    break;
                case 6:
                    cout << "Enter roll id for grade Summary : ";
                    cin >> t1;
                    StudentObj[t1 - 1].gradeSummary();
                    break;
                case 7:
                    cout << "Enter roll ID for gender : ";
                    cin >> t1;
                    printGender(StudentObj[t1 - 1]);
                    break;
                case 8:
                    StudentObj->writeToFile_stud(StudentObj);
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
                    FacultyObj->printFacultyDB(FacultyObj);
                    break;
                case 3:
                    cout << "Enter Faculty roll number : ";
                    cin >> t1;
                    FacultyObj[t1 - 1].displayFaculty();
                    break;
                case 4:
                    cout << "Enter Roll number to modify : ";
                    cin >> t1;
                    FacultyObj[t1 - 1].modifyFaculty();
                    break;
                case 8:
                    FacultyObj->writeToFile_faculty(FacultyObj);
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
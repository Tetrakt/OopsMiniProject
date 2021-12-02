#include <iostream>
#include <string.h>
#include <fstream>

#define STUDENTS_COUNT 25 //max of each
#define FACULTY_COUNT 2
#define PHD_COUNT 1

using namespace std;

int uIDlist[25]; //student,faculty,phd count
int db_count = 0;

class Faculty; // needed to make student faculty friend function work
class Student;

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
    virtual void display() = 0; //pure virtual function
    virtual void create() = 0;
    virtual void modify() = 0;
    void printAll(DataBase *); //todo
};

class uID_Exception
{
public:
    int uID;
    uID_Exception(int i)
    {
        uID = i;
    }
};

class Student : virtual protected DataBase //20 instances, subclass
{
private:
    char section;
    int grades[6];
    string subj1, subj2, subj3;
    const int batchyr; //batch year
    int rollNum;

public:
    static int studentCount;
    Student() : batchyr(18) // default constructor + init list
    {
        age = 0;
        section = ' '; // one param
        gender = ' ';
    }
    Student(int birthYear) : batchyr(18)
    {
        this->birthYear = birthYear;
    }
    void create();
    void display();
    void printStudentDB(Student *);
    void modify();
    void updateGrades(); // convert to a friend?
    void gradeSummary();
    void printDepartments(); //depts for a student
    void writeToFile_stud(Student *);
    friend void printBasicData(Student);
    void getFacultyDept(Faculty);
    //friend void Faculty::getStudentGrades(Student);
    friend class Faculty;
    ~Student()
    {
        //cout << "Student Destructor, student deleted";
    }
};
int Student::studentCount = 0;
void Student::create()
{
    int t;
    cout << "\n CREATING A STUDENT..." << endl;
    cout << "Enter Student Name: ";
    cin >> name;
    //enter uniqueID, if not uq, exit this func
    try
    {
        cout << "\nEnter Unique Student ID : ";
        cin >> t; // store input temporaily
        if (!uIDlist_isUnique(t))
        {
            throw uID_Exception(t);
        }
        uniqueID = t;
        //insert into it
        uIdlist_insert(t);
    }
    catch (uID_Exception e)
    {
        cout << "\n ID entered " << e.uID << " already exists.";
        exit(0);
    }
    cout << "\n Enter age : ";
    cin >> age;
    cout << "\n Enter Birth Year : ";
    cin >> birthYear;
    cout << "\n Enter Section : ";
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
    rollNum = ++Student::studentCount;
    cout << "Roll ID assigned : " << rollNum << endl;
    cout << " * STUDENT DATA CREATED SUCCESFULLY \n";
}
inline void StudentTable() // small helper function to format output
{
    cout << "Name Unique ID RollNum Age Section Gender Subject1 Subject2 Subject3" << endl;
}
void Student::display()
{
    cout << this->name;
    cout << "\t" << this->uniqueID;
    cout << "\t" << this->rollNum;
    cout << "\t" << this->age;
    cout << "\t" << this->section;
    cout << "\t" << this->gender;
    cout << "\t" << this->subj1;
    cout << "\t" << this->subj2;
    cout << "\t" << this->subj3 << endl;
}
void Student::printStudentDB(Student StudentObj[])
{
    StudentTable();
    for (int i = 0; i < Student::studentCount; i++)
        StudentObj[i].display();
}
void Student::modify()
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
        //can replace blank with , to make it a csv
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
void printBasicData(Student obj)
{
    cout << "Name : " << obj.name << endl;
    cout << " Age : " << obj.age << endl;
}

class Faculty : virtual protected DataBase //5 instances //subclass
{
protected:
    int salary;
    char dept[3];

    int rollNum;

public:
    //void display();
    static int facultyCount;
    void create();
    void display();
    void printFacultyDB(Faculty *);
    void modify();
    void writeToFile_faculty(Faculty *);
    // friend void printBasicData(Faculty);
    friend void Student::getFacultyDept(Faculty);
    void getStudentGrades(Student);

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
        //cout << "Faculty destructor";
    }
};
int Faculty::facultyCount = 0;

void Faculty::create()
{
    int t;
    cout << "\n CREATING A Faculty..." << endl;
    cout << "Enter Faculty Name: ";
    cin >> name;
    try
    {
        cout << "\nEnter Unique Faculty ID : ";
        cin >> t; // store input temporaily
        if (!uIDlist_isUnique(t))
        {
            throw uID_Exception(t);
        }
        uniqueID = t;
        //insert into it
        uIdlist_insert(t);
    }
    catch (uID_Exception e)
    {
        cout << "\n ID entered " << e.uID << " already exists.";
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
    rollNum = ++Faculty::facultyCount;
    cout << "Roll ID assigned : " << rollNum << endl;
    cout << " * FACULTY DATA CREATED SUCCESFULLY \n";
}
inline void FacultyTable()
{
    cout << "Name Unique ID RollNum Age Section Gender Department  Subject1" << endl;
}
void Faculty::display()
{
    cout << this->name;
    cout << "\t" << this->uniqueID;
    cout << "\t" << this->age;
    cout << "\t" << this->gender;
    cout << "\t" << this->dept;
    cout << "\t" << this->salary << endl;
}
void Faculty::printFacultyDB(Faculty FacultyObj[])
{
    FacultyTable();
    for (int i = 0; i < facultyCount; i++)
        FacultyObj[i].display();
}
void Faculty::modify()
{
    int ch;
    cout << "*Faculty TO BE MODIFIED*" << endl;
    cout << "Name : " << this->name << endl;
    cout << "\n MENU LIST" << endl;
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
    ofstream file_obj;                         // Object to write in file
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

//FS LINKING friend functions.
//integrate to menu
void Student::getFacultyDept(Faculty obj)
{
    cout << "Faculty dept : " << obj.dept << endl;
}
void Faculty::getStudentGrades(Student obj)
{
    //grade summary?
    obj.gradeSummary();
}

class Masters : public Student, public Faculty
{
private:
    char section;
    int grade;
    char subj[3];      //masters to be done in 1 subj only
    const int batchyr; //batch year
    int rollNum;

public:
    //functions
    static int masterCount;
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
    void create();
    void display();
    void printMasterDB(Masters *);
    void modify();
    void updateMasterGrade();
    void printDepartments(); //depts for a master
    void writeToFile_masters(Masters *);
    ~Masters()
    {
        //cout << "Masters Destructor, Masters deleted";
    }
};
int Masters::masterCount = 0;
void Masters::create()
{
    int u;
    cout << "\n CREATING A MASTER..." << endl;
    cout << "Enter Master Name: ";
    cin >> name;
    //enter uniqueID, if not uq, exit this func
    try
    {
        cout << "\nEnter Unique Master ID : ";
        cin >> u; // store input temporaily
        if (!uIDlist_isUnique(u))
        {
            throw uID_Exception(u);
        }
        uniqueID = u;
        //insert into it
        uIdlist_insert(u);
    }
    catch (uID_Exception e)
    {
        cout << "\n ID entered " << e.uID << " already exists.";
        exit(0);
    }
    cout << "\nEnter age : ";
    cin >> age;
    cout << "\nEnter Birth Year :";
    cin >> birthYear;
    cout << "\nEnter Section : ";
    cin >> section;
    cout << "\n Enter gender: ";
    cin >> gender;
    cout << "\n Subject : ";
    cin >> subj;
    rollNum = ++Masters::masterCount;
    cout << "Roll ID assigned : " << rollNum << endl;
    cout << " * MASTER DATA CREATED SUCCESFULLY \n";
}
inline void MasterTable()
{
    cout << "Name Unique ID RollNum Age Section Gender Subject" << endl;
}
void Masters::display()
{
    cout << this->name;
    cout << "\t" << this->uniqueID;
    cout << "\t" << this->rollNum;
    cout << "\t" << this->age;
    cout << "\t" << this->section;
    cout << "\t" << this->gender;
    cout << "\t" << this->subj << endl;
}
void Masters::printMasterDB(Masters MastersObj[])
{
    MasterTable();
    for (int i = 0; i < Masters::masterCount; i++)
        MastersObj[i].display();
}
void Masters::modify()
{
    //Choose basis of roll num?? sent from main()?
    int ch;
    cout << "* MASTER TO BE MODIFIED *" << endl;
    cout << "Name : " << this->name << endl;
    cout << "\n MENU" << endl;
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
    ofstream file_obj;                         // Object to write in file
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

inline void printMenu(int ch)
{
    if (ch == 1) //student menu
    {
        cout << "STUDENT MENU : " << endl;
        cout << "1. New Entry" << endl;
        cout << "2. Print All Entries" << endl;
        cout << "3. Print one Entry" << endl; //  input for key
        cout << "4. Modify enty" << endl;
        cout << "5. Update grades" << endl;
        cout << "6. Grade summary" << endl;
        cout << "7. Print Public Data" << endl;
        cout << "8. Update database to file" << endl;
        cout << "9. Profesor Department" << endl;
        cout << "0. Exit " << endl;
    }
    else if (ch == 2)
    {
        //faculty menu
        cout << "1. New Entry" << endl;
        cout << "2. Print All Entries" << endl;
        cout << "3. Print One Entry" << endl;
        cout << "4. Modify Entry" << endl;
        cout << "5. Update database to file" << endl;
        cout << "6. Grade Summary of Student" << endl;
        cout << "0. Exit" << endl;
    }
    else if (ch == 3)
    {
        //phd menu
        cout << "PHD MENU " << endl;
        cout << "1. New Entry" << endl;
        cout << "2. Print All Entries" << endl;
        cout << "3. Print one Entry" << endl; //  input for key
        cout << "4. Modify Entry" << endl;
        cout << "5. update grade" << endl;
        cout << "6. Print Public Data" << endl;
        cout << "7. Update database" << endl;
        cout << "0. Exit " << endl;
    }
}
inline void printMenu() //db menu, student or faculty
{
    //student, faculty or phd
    cout << "University DataBase System" << endl;
    cout << " 1. Student db" << endl;
    cout << " 2. Faculty db" << endl;
    cout << " 3. PHD db" << endl;
    cout << " 4. Exit " << endl;
}

int main()
{
    Student *StudentObj = new Student[STUDENTS_COUNT];
    Faculty *FacultyObj = new Faculty[FACULTY_COUNT];
    Masters *MasterObj = new Masters[PHD_COUNT];
    for (int i = 0; i < STUDENTS_COUNT; i++)
    {
        Student(2000);
        //Student(i+1); setting roll number too.
    }
    for (int i = 0; i < FACULTY_COUNT; i++)
    {
        Faculty(50000);
    }
    for (int i = 0; i < PHD_COUNT; i++)
    {
        Masters(1986);
    }
    int t1, t2, t3;
    int ch1 = -1, ch2 = -1;
    cout << "University DataBase Management System" << endl;

    printMenu();
    cin >> ch1;
    while (ch1 != 4)
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
                    //StudentObj->createStudent();
                    // t2 = Student::studentCount + 1;
                    StudentObj[Student::studentCount].create();
                    break;
                case 2:
                    StudentObj->printStudentDB(StudentObj); //pass array of objs
                    break;
                case 3:
                    cout << "Enter Roll Number 1 to student count : ";
                    cin >> t1;
                    //StudentObj->displayStudent(StudentObj[t1 - 1]); //t1-1 as roll num from 1, but array from 0
                    StudentTable();
                    StudentObj[t1 - 1].display();
                    break;
                case 4:
                    cout << "Enter Roll Number to modify : ";
                    cin >> t1;
                    StudentObj[t1 - 1].modify();
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
                    printBasicData(StudentObj[t1 - 1]);
                    break;
                case 8:
                    StudentObj->writeToFile_stud(StudentObj);
                    break;
                case 9:
                    cout << "Enter Professor Roll ID: ";
                    cin >> t1;
                    StudentObj[0].getFacultyDept(FacultyObj[t1 - 1]);

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
                    FacultyObj[Faculty::facultyCount].create();
                    break;
                case 2:
                    FacultyObj->printFacultyDB(FacultyObj);
                    break;
                case 3:
                    cout << "Enter Faculty roll number : ";
                    cin >> t1;
                    FacultyTable();
                    FacultyObj[t1 - 1].display();
                    break;
                case 4:
                    cout << "Enter Roll number to modify : ";
                    cin >> t1;
                    FacultyObj[t1 - 1].modify();
                    break;
                case 5:
                    FacultyObj->writeToFile_faculty(FacultyObj);
                    break;
                case 6:
                    //grade summary of student
                    cout << "Enter Roll number of Student: ";
                    cin >> t1;
                    FacultyObj[0].getStudentGrades(StudentObj[t1 - 1]);
                    break;
                default:
                    break;
                }
            }
        }
        else if (ch1 == 3)
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
                    MasterObj[Masters::masterCount].create();
                    break;
                case 2:
                    MasterObj->printMasterDB(MasterObj); //pass array of objs
                    break;
                case 3:
                    cout << "Enter Roll Number 1 to master count : ";
                    cin >> t1;
                    //MasterObj->displayMaster(MasterObj[t1 - 1]); //t1-1 as roll num from 1, but array from 0
                    MasterTable();
                    MasterObj[t1 - 1].display();
                    break;
                case 4:
                    cout << "Enter Roll Number to modify : ";
                    cin >> t1;
                    MasterObj[t1 - 1].modify();
                case 5:
                    cout << "Enter roll id to update grades : ";
                    cin >> t1;
                    MasterObj[t1 - 1].updateMasterGrade();
                    break;
                case 6:
                    cout << "Enter roll ID for SOMETHING : ";
                    cin >> t1;
                    //printGender(MasterObj[t1 - 1]); FIX THIS BIT
                    break;
                case 7:
                    MasterObj->writeToFile_stud(MasterObj);
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
    delete[] MasterObj;
    return 0;
}
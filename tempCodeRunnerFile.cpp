class student
{
public:
    void getfacultyDept();
    friend void faculty::getStudentGrades();
};

class faculty
{
public:
    friend void student::getfacultyDept();
    void getStudentGrades();
};

void student::getfacultyDept()
{
}
void faculty::getStudentGrades()
{
    
}
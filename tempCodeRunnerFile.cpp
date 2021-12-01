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
    needs roll num of faculty, and faculty obj.so pass obj only, this->dept;
}
void faculty::getStudentGrades()
{
}
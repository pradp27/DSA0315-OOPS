#include <iostream>
using namespace std;

class Student
{
public:
    string name;
    int mark;
};

class Department
{
public:
    Student s[100];
    int n;
    static int totalStudents;

    void getData()
    {
        cin >> n;
        for(int i=0;i<n;i++)
        {
            cin >> s[i].name;
            cin >> s[i].mark;
            totalStudents++;
        }
    }
    void topper()
    {
        if(n==0)
        {
            cout<<"Department Empty\n";
            return;
        }
        int max=s[0].mark;
        string top=s[0].name;

        for(int i=1;i<n;i++)
        {
            if(s[i].mark>max)
            {
                max=s[i].mark;
                top=s[i].name;
            }
        }
        cout<<"Department Topper: "<<top<<" "<<max<<endl;
    }
    float passPercent()
    {
        int pass=0;

        for(int i=0;i<n;i++)
        {
            if(s[i].mark>=40)
                pass++;
        }

        if(n==0)
            return 0;

        return (pass*100.0)/n;
    }

    int getTopMark()
    {
        int max=-1;

        for(int i=0;i<n;i++)
        {
            if(s[i].mark>max)
                max=s[i].mark;
        }

        return max;
    }

    string getTopName()
    {
        int pos=0;

        for(int i=1;i<n;i++)
        {
            if(s[i].mark>s[pos].mark)
                pos=i;
        }

        return s[pos].name;
    }
};

int Department::totalStudents=0;

int main()
{
    int d;
    cin>>d;

    Department dep[20];

    for(int i=0;i<d;i++)
        dep[i].getData();

    int overall=-1;
    string topper;
    for(int i=0;i<d;i++)
    {
        dep[i].topper();
        cout<<"Pass Percentage = "<<dep[i].passPercent()<<"%\n";

        if(dep[i].getTopMark()>overall)
        {
            overall=dep[i].getTopMark();
            topper=dep[i].getTopName();
        }
    }
    cout<<"Overall University Topper: "<<topper<<" "<<overall<<endl;
    cout<<"Total Students: "<<Department::totalStudents<<endl;

    return 0;
}

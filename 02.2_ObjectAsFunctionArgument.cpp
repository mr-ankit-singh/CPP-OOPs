/*
#__ Object as Function Argument __#


    

*/


#include <iostream>
using namespace std;

class Studentt {
public:
    int marks;

    Studentt(int m) {
        marks = m;
    }
};

void calculateAverage(const Studentt& s1, const Studentt& s2) {
    float average = (s1.marks + s2.marks) / 2.0;
    cout << "Average Marks = " << average << endl;
}

int main() {
    Studentt student1(89), student2(56);

    calculateAverage(student1, student2);

    return 0;
}


/*=====================================================================================================*/

// C++ Return Object from a Function

#include <iostream>
using namespace std;

class Student {
   public:
    double marks1, marks2;
};

// function that returns object of Student
Student createStudent() {
    Student student;

    // Initialize member variables of Student
    student.marks1 = 96.5;
    student.marks2 = 75.0;

    // print member variables of Student
    cout << "Marks 1 = " << student.marks1 << endl;
    cout << "Marks 2 = " << student.marks2 << endl;

    return student;
}

int main() {
    Student student1;

    // Call function
    student1 = createStudent();

    return 0;
}


/*=====================================================================================================*/

// Program to find sum of weight 

#include<iostream>
using namespace std;

class Weight{
    private:
    int kilogram;
    int gram;

    public:
    void putData();
    void getData();
    void sum_weight(Weight,Weight);

};

void Weight::putData(){
    cout << "Enter kilogram and Gram : " << endl ;
    cin >> kilogram >> gram ;
}
void Weight::getData(){
    cout << "Kilogram : " << kilogram << "Gram : " << gram ;
}
void Weight :: sum_weight(Weight w1,Weight w2) {
    gram = w1.gram + w2.gram;
    kilogram=gram/1000;
    gram=gram%1000;
    kilogram+=w1.kilogram+w2.kilogram;
}
int main () {
    Weight w1,w2 ,w3; 
    cout<<"Enter weight in kilograms and grams\n";
    cout<<"\n Enter weight #1" ;
    w1.getData();
    cout<<" \n Enter weight #2" ;
    w2.getData();
    w3.sum_weight(wl,w2);
    cout<<"/n Weight #1 = ";
    w1.putData();
    cout<<"Weight #2 = ";
    w2.putData();
    cout<<"Total Weight = ";
    w3.putData();
    return 0;
}


/*=====================================================================================================*/
/*
#__ Array of Objects __#

   -When a class is defined, only the specification for the object is defined; 
   -no memory or storage is allocated. 
   -To use the data and access functions defined in the class, you need to create objects.

   -The Array of Objects stores objects. 
   -An array of a class type is also known as an array of objects.

    Syntax:
        class_name array_name [size] ;

    Advantages of Array of Objects: 
        -The array of objects represent storing multiple objects in a single name.
        -In an array of objects, the data can be accessed randomly by using the index number.
        -Reduce the time and memory by storing the data in a single variable.

*/


#include <iostream>
using namespace std;

class student
{
    // public member by default
    int roll_no;
    char name[20];

    public: // public member declaration
        void get_record(void);
        void show_record(void);
};

void student::get_record(){ // get record by user

    cout << "\nEnter roll no: ";
    cin >> roll_no;
    cout << "Enter Name : ";
    gets(name);
}

void student::show_record(){ // display record
    cout << "\nRoll no: " << roll_no;
    cout << "\nName : " << name;
}

// main function
int main()
{

    student obj[2]; // 2 students

    for (int i = 0; i < 2; i++){
        cout << "Enter " << i + 1 << " student record: ";
        obj[i].get_record();
    }

    for (int j = 0; j < 2; j++){
        cout << "\ndisplay " << j + 1 << " student record: ";
        obj[j].show_record();
    }
    return 0;
}

/*----------------------------------------------*/

#include <iostream>
#include <new>
using namespace std;

class Rectangle
{
    int width;
    int height;

public:
    Rectangle(){
        width = height = 0;
        cout << "Constructing " << width << " by " << height << " rectangle.\n";
    }
    Rectangle(int w, int h){
        width = w;
        height = h;
        cout << "Constructing " << width << " by " << height << " rectangle.\n";
    }

    ~Rectangle(){
        cout << "Destructing " << width << " by " << height << " rectangle.\n";
    }

    void set(int w, int h){
        width = w;
        height = h;
    }
    int area(){
        return width * height;
    }
};

int main(){

    Rectangle *p;

    try{
        p = new Rectangle[3];
    }
    catch (bad_alloc xa){
        cout << "Allocation Failure\n";
        return 1;
    }

    cout << "\n";

    p[0].set(3, 4);
    p[1].set(10, 8);
    p[2].set(5, 6);

    for (int i = 0; i < 3; i++)
        cout << "Area is " << p[i].area() << endl;

    delete[] p;

    return 0;
}
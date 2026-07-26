

#include<bits/stdc++.h>
using namespace std;

class Student {
public:
    int id ;
    string name ;
private:
    string gf ;
public:
    Student(int id , string name , string gf){
        this->id = id ;
        this->name = name ;
        this->gf = gf ;
    }

    void detail(){
        cout << "Name " << this->name << endl;
        this->gfName();
    }

private:
    void gfName(){
        cout << "GF Name " << this->gf ;
    }



};


int main(){
    Student Ankit(1 , "Ankit Singh" , "Nandini Jain");
    Ankit.detail();
    

    return 0;
}
#include <iostream>

struct A
{
    A(int a=0): a_(a){}
    int get() const
    {
         return a_;
    }

    void print() const
    {
       std::cout<<"a = "<<a_<<std::endl;
    }

    void set(int a)
    {
        a_ = a;
    }
    

private:
    int a_;    
};


int main()
{
    A a;
    a.print();
    std::cout<<"Pump it"<<std::endl;
    return 0;
}
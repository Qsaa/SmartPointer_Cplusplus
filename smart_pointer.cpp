#include <iostream>

using namespace std;

struct AA
{
    AA(int a=0): a_(a){}
    int get() const
    {
         return a_;
    }

    void print() const
    {
       std::cout<<"a = "<<a_<<std::endl;
    }

    void set(int a){a_ = a;}

    std::ostream& operator<< (std::ostream& out)
    {
        return out<<a_;
    }

private:
    int a_;    
};

std::ostream& operator<< (std::ostream& out, const AA& a)
{
    return out<<a.get();
}


struct ScopedPtr
{
    explicit 
    ScopedPtr(AA* ptr = nullptr) : ptr_(ptr){};
    ~ScopedPtr()
    {
        delete ptr_;
    }

    AA* get() const
    {
        return ptr_;
    }

    void reset(AA* ptr)
    {
        delete ptr_;
        ptr_ = ptr;
    }

    AA* release()
    {
        AA* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    AA& operator*() const
    {
        return *ptr_;
    }

    AA* operator->()const
    {
        return ptr_;
    }
    private:
    ScopedPtr(const ScopedPtr& ptr);
    //ScopedPtr& operator=(const ScopedPtr& ptr);
    AA* ptr_;
};


int main()
{
    ScopedPtr p(new AA(12));
    ScopedPtr p1;
    p1 = p;
    cout<<*(p.release())<<endl;
    cout<<*(p.release())<<endl;

    cout<<*(p1.release())<<endl;
    //A a(12);
    //std::cout<<a;
    return 0;
}
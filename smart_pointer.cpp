#include <iostream>

using namespace std;

struct Expression
{
    explicit Expression(string a = "99") : a_(a) {}
    string get() const
    {
        return a_;
    }

    void print() const
    {
        std::cout << "a = " << a_ << std::endl;
    }

    void set(int a) { a_ = a; }

    std::ostream& operator<< (std::ostream& out)
    {
        return out << a_;
    }

private:
    string a_;
};

std::ostream& operator<< (std::ostream& out, const Expression& a)
{
    return out<<a.get();
}


struct ScopedPtr
{
    explicit 
    ScopedPtr(Expression* ptr = nullptr) : ptr_(ptr){};
    ~ScopedPtr()
    {
        delete ptr_;
    }

    Expression* get() const
    {
        return ptr_;
    }

    void reset(Expression* ptr)
    {
        delete ptr_;
        ptr_ = ptr;
    }

    Expression* release()
    {
        Expression* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    Expression& operator*() const
    {
        return *ptr_;
    }

    Expression* operator->()const
    {
        return ptr_;
    }

private:
    ScopedPtr(const ScopedPtr& ptr);
    ScopedPtr& operator=(const ScopedPtr& ptr);
    Expression* ptr_;
};


struct SharedPtr
{
    explicit SharedPtr(Expression* ptr = nullptr) : ptr_(ptr), counter_(new size_t(0)){}
    ~SharedPtr()
    {
        if (*counter_ == 0)
        {
            delete ptr_;
            delete counter_;
        }
        else
        {
            --(*counter_);
        }
  
    }
    SharedPtr(const SharedPtr& old)
    {
        this->ptr_ = old.ptr_;
        this->counter_ = old.counter_;
        ++(*counter_);
    }
    SharedPtr& operator=(const SharedPtr& old)
    {
        if (this->ptr_ != old.ptr_)
        {
            this->~SharedPtr();
            this->ptr_ = old.ptr_;
            this->counter_ = old.counter_;
            ++(*counter_);
        }
        return *this;
    }

    Expression* get() const
    {
        return this->ptr_;
    }

    void reset(Expression* ptr = nullptr)
    {
        if (ptr_ != ptr)
        {
            this->~SharedPtr();
            ptr_ = ptr;
            counter_ = new size_t(0);
        }
    }

    Expression& operator*() const
    {
        return *ptr_;
    }

    Expression* operator->() const
    {
        return ptr_;
    }

private:
    Expression* ptr_;
    mutable size_t* counter_;
};


void tests1()
{
    SharedPtr p1;
    {
        SharedPtr p2(new Expression("expr1"));
        SharedPtr p3(new Expression("expr2"));
        SharedPtr p4(p2);
        SharedPtr p5;
        p5 = p2;
        p5 = p4;
        p1 = p5;
        p5.reset(NULL);
        SharedPtr p6;
        SharedPtr p7;
        p7 = p7;
        p7.reset(NULL);
        p7.reset(new Expression("expr3"));
        SharedPtr p8(new Expression("expr4"));
        p8.reset(NULL);
    }
    p1 = p1;
}


void memory_check()
{
    if (_CrtDumpMemoryLeaks())
        std::cout << "memory leak is detected" << std::endl;
    else
        std::cout << "no memory leaks" << std::endl;
}


int main()
{
    tests1();
    memory_check();
    system("pause");
    return 0;
}
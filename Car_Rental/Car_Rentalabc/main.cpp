template class <T>

class Auto_ptr1{
    T* m_ptr;
public:
    Auto_ptr1(T* ptr=nullptr) : m_ptr(ptr) {}
    ~Auto_ptr1() {delete m_ptr; }
    T& operator* () const {return *m_ptr;}
    T* operator-> () const {return m_ptr;}
};

class Resource{
    Resource() { cout<< "Resource acquired.\n";}
    ~Resource() {cour<< "Resource destroyed.\n";}
    void sayHi() {cout<< "Hi\n";}
};

void someFunction(){
    Auto_ptr1<Resource> ptr(new Resource());
    int x;
    cout<< "Enter an integer:";
    cin>> x;
    if(x==0) return;
    ptr->sayHi();
}

int main(){
    void someFunction();
    return 0;
}

    


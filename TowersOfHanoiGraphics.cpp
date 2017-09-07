#include <iostream>
#include <windows.h>

using namespace std;

COORD coord={0,0};

void gotoxy(int x1,int y1){
    coord.X=x1;
    coord.Y=y1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class node{
    private:
        int data;
        node *next;
    public:
        node(int d,node *n){
            data=d;
            next=n;
        }
        int getData(){return data;}
        void setNext(node *n){next=n;}
        node* getNext(){return next;}
};

class stack{
    private:
        node *first;
    public:
        stack(){first=NULL;}
        void print(int a1,int b1);
        void insert(int x);
        void destroy();
        void setup(int u);
        node* getFirst(){return first;}
        int getLastDat(){
            node *current=first;
            while(current->getNext()){
                current=current->getNext();
            }
            return current->getData();
        }
};

class tower{
    private:
        stack s1,s2,s3;
        int num;
        int count;
    public:
        tower(int n){
            s1.setup(n);
            num=n;
        }
        void execute(int n);
        void move1(stack &start,stack &end);
        void move2(stack &start,stack &end,stack &temp);
        void move3(stack &start,stack &end,stack &temp);
        void move4(stack &start,stack &end,stack &temp);
        void display();
};

void stack::print(int x2,int y2){
    node *current=first;
    int botSize=0;
    int tick=0;
    if(!first){
        cout<<" "<<endl;
        botSize=0;
    }
    else{
        botSize=first->getData();
        while(current){
            gotoxy(x2-(current->getData()),y2-tick);
            for(int i=0;i<current->getData();i++){
                cout<<char(219)<<char(219);
            }
            current=current->getNext();
            tick++;
        }
        cout<<endl;
    }
}

void stack::insert(int x){
    node *current=first;
    if(!first){
        first=new node(x,NULL);
    }
    else{
        node *temp=new node(x,NULL);
        while(current->getNext()){

            current=current->getNext();
        }
        current->setNext(temp);
    }
}

void stack::destroy(){
    node *current=first;
    if(!first){
        cout<<"No Node to Delete"<<endl;
    }
    else if(!first->getNext()){
        first=NULL;
    }
    else{
        while(current->getNext()->getNext()){
            current=current->getNext();
        }
        current->setNext(NULL);
    }
}

void stack::setup(int u){
    for(int i=u;i>0;i--){
        insert(i);
    }
}

void tower::move1(stack &s,stack &e){
    e.insert(s.getLastDat());
    s.destroy();
    display();
    count++;
    Sleep(1000);
}

void tower::move2(stack &s,stack &e,stack &t){
    move1(s,t);
    move1(s,e);
    move1(t,e);
}

void tower::move3(stack &s,stack &e,stack &t){
    move2(s,t,e);
    move1(s,e);
    move2(t,e,s);
}

void tower::move4(stack &s,stack &e,stack &t){
    move3(s,t,e);
    move1(s,e);
    move3(t,e,s);
}

void tower::execute(int n){
    count=0;
    display();
    Sleep(1000);
    count++;
    if(n==1){
        move1(s1,s2);
    }
    else if(n==2){
        move2(s1,s2,s3);
    }
    else if(n==3){
        move3(s1,s2,s3);
    }
    else if(n==4){
        move4(s1,s2,s3);
    }
    gotoxy(0,24);
}

void tower::display(){
    gotoxy(0,0);
    for(int i=0;i<21;i++){
        cout<<"                                                     "<<endl;
    }
    gotoxy(0,20);
    cout<<"_______________   _______________   _______________"<<endl;
    cout<<"      s1                 s2                s3      "<<endl;
    s1.print(7,19);
    s2.print(26,19);
    s3.print(44,19);
    gotoxy(0,12);cout<<"moves: "<<count;
}

int main(){
    int height;
    cout<<"enter stack height"<<endl;
    cin>>height;
    tower l(height);
    l.execute(height);
    return 0;
}

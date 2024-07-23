#pragma once
#include <vector>

using namespace std;

class Observer {

public:
    Observer()=default;
    virtual void update() = 0;
    virtual ~Observer()=default;

};

class Subject
{
private:
    std::vector<Observer*> observers;

public:
    Subject()=default;
    void addObserver(Observer *o){
        this->observers.push_back(o);

    };
    void notifyAllObservables(){
        for(auto o:this->observers)
            o->update();

    };
    ~Subject()=default;
};


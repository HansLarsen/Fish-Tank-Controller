#ifndef TASK_H
#define TASK_H

class Task
{
public:
    virtual void run() = 0;
    virtual void dateRun();
};

class ButtonReturnClass : public Task
{   
public:
    virtual void run() = 0;
    virtual void dateRun();

    virtual void topButton();
    virtual void changeButton();

    virtual void topFloat(bool);
    virtual void bottomFloat(bool);
};

#endif
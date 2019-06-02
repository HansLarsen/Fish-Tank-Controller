#ifndef TASK_H
#define TASK_H

class Task
{
public:
    virtual void run() = 0;
    virtual void dateRun(int) = 0;
};

class ButtonReturnClass : public Task
{   
public:
    virtual void run() = 0;
    virtual void dateRun(int) = 0;

    virtual void topButton() = 0;
    virtual void changeButton() = 0;

    virtual void topFloat(bool) = 0;
    virtual void bottomFloat(bool) = 0;
};

#endif
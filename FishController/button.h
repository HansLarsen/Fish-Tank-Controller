#ifndef BUTTON_H
#define BUTTON_H

class Button
{
public:
    Button(int time, int currentTime)
    {
        interval = time;
        startTime = currentTime;
    }
    bool canRun(int currentTime)
    {
        if  (currentTime - startTime >= interval)
        {
            return true;
        }
        return false;
    }
protected:
    int startTime = 0;
    int interval = 0;
};

#endif
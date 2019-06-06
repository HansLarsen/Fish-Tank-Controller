#include "FilterManager.h"

FilterManager::FilterManager(IOManager* _IOManager)
{
    IOManagerSave = _IOManager;
}

void FilterManager::run()
{
    if(!IOManagerSave->getHeaterStatus())
    {
        IOManagerSave->setHeater(false);
        IOManagerSave->setFilter(false);
        IOManagerSave->buzzer();
    }
    else
    {
        IOManagerSave->setHeater(true);
        IOManagerSave->setFilter(true);
    }
}

void FilterManager::dateRun(int hour)
{

}
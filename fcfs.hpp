#include <iostream>
#include <list>
#include <iterator>
#include<stdlib.h>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <string>

typedef enum STATE{
    running,
    sleeping,
    idle,
    stopped,
    zombie
}STATUS;

typedef struct PROCESS{

    int id;
    int user;
    time_t runtime;
    STATE state;
    PROCESS * parent;
<<<<<<< HEAD
    int arrival_time;
=======
    time_t arrival_time;
>>>>>>> 3d0404f05580b93c20d3cbd6a0cf41229193d34c
    std::string command;

} PROCESS;

void fcfs();

std::list<PROCESS*>::iterator find_min(std::list<PROCESS*> data);

bool operator<(PROCESS p1, PROCESS p2);
std::ostream& operator<< (std::ostream& os, const PROCESS &p);


std::list<PROCESS*> load();

void del_list(std::list<PROCESS*> proc);



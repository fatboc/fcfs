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
    time_t arrival_time;
    std::string command;

} PROCESS;

void fcfs();

std::list<PROCESS*>::iterator find_min(std::list<PROCESS*> data);

bool operator<(PROCESS p1, PROCESS p2);
std::ostream& operator<< (std::ostream& os, const PROCESS &p);


std::list<PROCESS*> load();

void del_list(std::list<PROCESS*> proc);



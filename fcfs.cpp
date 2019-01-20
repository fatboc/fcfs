#include "fcfs.hpp"

void fcfs(){

    std::list<PROCESS*> proc = load();

    while(proc.size()>0){
        proc.sort();
        //std::list<PROCESS*>::iterator it = proc.
        PROCESS * p = proc.back();
        std::cout << "Wykonywanie procesu nr " << *p << std::endl;
        proc.pop_back();

    }

    del_list(proc);
}

std::list<PROCESS*>::iterator find_min(std::list<PROCESS*> data){

    std::list<PROCESS*>::iterator emin = data.begin();
    std::list<PROCESS*>::iterator it = data.begin();

    while(it!=data.end()){
        if(*(*it)<*(*emin))
            emin=it;
        it++;
    }

    return emin;
}

bool operator< (PROCESS p1, PROCESS p2){
    return p1.arrival_time<p2.arrival_time;
}

std::ostream& operator<< (std::ostream& os, const PROCESS &p){
    return os << p.id;
}

std::list<PROCESS*> load(){
    std::ifstream proc_list;
    std::string line;
    std::list<PROCESS*> proc;

    int _pid, _uid, _ppid;
    std::string _comm, _ctime;
    char _state;
    time_t _rtime;

    proc_list.open("proc.txt");

    if (!getline(proc_list, line)){
        std::cerr << "Blad odczytu pliku\n";
        return proc;
    }

    while(proc_list >> _pid >> _uid >> _ctime>> _state >> _ppid >> _comm >> _rtime){
        PROCESS * p = new PROCESS;
        p->id=_pid;
        p->user=_uid;
        switch (_state){
            case 'S':
                p->state = sleeping;
                break;
            case 'I':
                p->state = idle;
                break;
            default :
                break;
        }
        std::list<PROCESS*>::iterator res = std::find_if(std::begin(proc), std::end(proc), [=](PROCESS * const p){return p->id == _ppid;});

        if (res!=std::end(proc))
            p->parent= &(**res);
        else
            p->parent=NULL;

        p->arrival_time = _rtime;
        tm tmp;
        strptime(_ctime.c_str(), "%H:%M:%S", &tmp);


        p->runtime=(tmp.tm_sec) + (60*tmp.tm_min) + (3600*tmp.tm_hour);


        std::cout << p->runtime << std::endl;

        proc.push_back(p);
    }

    return proc;
}

void del_list(std::list<PROCESS*> proc){
    for(std::list<PROCESS*>::iterator i=proc.begin(); i!=proc.end(); i++){
        delete &(*i);
        std::advance(i, 1);
    }
}

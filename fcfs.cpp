#include "fcfs.hpp"

void fcfs(){

    std::list<PROCESS*> proc = load();

    while(proc.size()>0){
        std::list<PROCESS *>::iterator curr=find_min(proc);
        PROCESS * p = *curr;
        std::cout << "Wykonywanie procesu nr " << *p;
        proc.pop_back();

    }

    del_list(proc);
}

std::list<PROCESS*>::iterator find_min(std::list<PROCESS*> data){

    std::list<PROCESS*>::iterator emin = data.begin();
    std::list<PROCESS*>::iterator it = data.begin();

    for(int i=0; i<data.size(); i++){
        if(*(*it)<*(*emin))
            emin=it;
        std::advance(it, 1);
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

    while(proc_list >> _pid >> _uid >> _ctime>> _state >> _comm >> _rtime){
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
        auto res = std::find_if(std::begin(proc), std::end(proc), [&](PROCESS * const p){return p->id == _ppid;});
        if (res!=std::end(proc))
            p->parent= &(**res);
        else
            p->parent=NULL;

        p->arrival_time = _rtime;

        std::string chrs(_ctime, 0, 2);
        std::string cmin(_ctime, 3, 2);
        std::string csec(_ctime, 6, 2);
        tm *tmp = NULL;
        tmp->tm_hour = atoi(chrs.c_str());
        tmp->tm_min = atoi(cmin.c_str());
        tmp->tm_sec = atoi(csec.c_str());

        p->runtime = mktime(tmp);

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

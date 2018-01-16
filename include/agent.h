#ifndef AGENT_H
#define AGENT_H

#include "sphinx.h"


namespace AgentSpace {
    
    using namespace std;
    
    class Agent
    {
    public:
        Agent() = default;
        Agent(string a_name): name(a_name){};
        void set_agent_wakeup_keyword(string a_name);
        string get_agent_wakeup_keyword(void) const;
    private:
        string name;
    };
}
#endif /* AGENT_H */
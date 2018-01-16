#include "agent.h"

using namespace AgentSpace;

void Agent::set_agent_wakeup_keyword(string a_name)
{
	name = a_name;
}

string Agent::get_agent_wakeup_keyword(void) const
{
	return name;
}
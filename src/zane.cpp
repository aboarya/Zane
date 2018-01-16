#include <iostream>
#include <fstream>

#include "detector.h"
#include "json.hpp"

int main()
{
	using namespace AgentSpace;
	using namespace DetectorSpace;
	using namespace std;
	using json = nlohmann::json;

	Detector detector;
	vector<Agent> agents;

	

	std::ifstream ifs("../data/agents.json");
	json j = json::parse(ifs);

	// range-based for
	for (auto& elm : j) {
  		agents.push_back(Agent(elm["name"].get<std::string>()));

	}
	for (auto& agent : agents)
	{
		cout << agent.get_agent_wakeup_keyword().c_str() << endl;;
	}
	return 0;
}
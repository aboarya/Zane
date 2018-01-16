

// class CommandAnalysis
// {
    
// public:

//     CommandAnalysis() = default;
//     CommandAnalysis(std::string command__keywords) : command_keywords(command__keywords){}

//     // bool find(std::string speech) const {return this->command_keywords.find(speech) != std::string::npos;}

//     std::string keywords(void) const {return command_keywords;}

// private:
//     std::string command_keywords;

//     // bool operator==(string speech) const { return this->command_keywords.find(speech);}

// };

// class CommandResponse
// {
//     std::string response;
// };

class CommandExecution
{
    std::string cmd;

    void execute(void);
};

class Command
{
public:

    Command() = default;
    Command(const std::string c_phrase) : phrase(c_phrase) {}
    void execute(void);

private:
    const std::string phrase;
    std::vector<Command> sub_commands;
    CommandResponse response;
    CommandExecution execution;
    CommandAnalysis analysis;

};

// int main()
// {
//     // spoken phrase will have many words
//     // my map keys are single word
//     Command one(std::string("command one"));
//     Command two(std::string("command two"));

//     std::map<std::string, Command, classcomp> commands;
//     commands[one.keywords()] = one;
//     commands[two.keywords()] = two;

//     auto search = commands.find("one");

//     if(search != commands.end()) {
//         std::cout << "Found " << std::endl;
//     }
//     else {
//         std::cout << "Not found\n";
//     }
// }
#include "flite.h"

extern "C"
{
    // cst_voice* register_cmu_us_kal();
    cst_voice* register_cmu_us_awb(const char *voxdir);
}

class CommandResponse
{
public:
    CommandResponse() = default;
    CommandResponse(std::string r_phrase);
    void speak(void);
private:
    cst_voice* voice;
    const std::string response_phrase;
};

CommandResponse::CommandResponse(std::string r_phrase, std::string r_agent = string("zane")) : response_phrase(r_phrase)
{
    // init flite library
    // flite_init();


    voice = register_cmu_us_awb(NULL);
    flite_text_to_speech("hello world",voice,"play");

}

void CommandResponse::speak(void)
{

}

void CommandResponse::set_response_voice(void)
{
    if (agent == )
}
#include "detector.h"

using namespace DetectorSpace;

Detector::Detector(const char* jsgf_filepath, const vector<AgentSpace::Agent> &agents)
{
    // Load the configuration structure - ps_args() passes the default values
    config = cmd_ln_init(NULL, ps_args(), TRUE,
        "-hmm", MODELDIR "/en-us/en-us",
        "-dict", MODELDIR "/en-us/cmudict-en-us.dict",
        "-logfn", "/dev/null",
        NULL);

    // initialize the pocketsphinx decoder
    ps = ps_init(config);
    // open default microphone at default samplerate
    ad = ad_open_dev("sysdefault", (int) cmd_ln_float32_r(config, "-samprate"));
    
    // create grammer and wake up word search
    ps_set_jsgf_file(ps, modes[Detector::command], jsgf_filepath);
    
    for (auto const &agent : agents)
    {
        //get the name of the agent (provided during init via json files)
        const char* name = agent.get_agent_wakeup_keyword().c_str();
        // set the name of search and the wakeup work to name of agent
        ps_set_keyphrase(ps, name, name);   
    }

    // initial detection mode is keyphrase
    mode = keyphrase;
}

void Detector::set_current_detection_mode(Detector::Mode d_mode)
{
    mode = d_mode;
}

const char* Detector::get_current_detection_mode(void)
{
    return modes[mode];
}

bool Detector::is_wakeup_spoken()
{
    return false;
}

string Detector::detect_from_microphone(void)
{
    // set search mode to either keyphrase or grammer
    ps_set_search(ps, get_current_detection_mode());
    // start recording
    ad_start_rec(ad);
    // mark the start of the utterance
    ps_start_utt(ps);
    // clear the utt_started flag
    utt_started = FALSE;

    while(1) {
        // capture the number of frames in the audio buffer                
        k = ad_read(ad, adbuf, 4096);
        // send the audio buffer to the pocketsphinx decoder
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);
        // test to see if speech is being detected
        in_speech = ps_get_in_speech(ps);

        // if speech has started and utt_started flag is false
        if (in_speech && !utt_started) {
            // then set the flag
            utt_started = TRUE;
        }
 
        // if speech has ended and the utt_started flag is true
        if (!in_speech && utt_started) {
            // then mark the end of the utterance
            ps_end_utt(ps);
             // stop recording
            ad_stop_rec(ad);
            // query pocketsphinx for "hypothesis" of decoded statement
            hyp = ps_get_hyp(ps, NULL);
            // converting from c-style string to c++ string with NULL is a problem
            string str(hyp ? hyp : " ");
            return str;
        }
    }

}
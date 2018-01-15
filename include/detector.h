#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>

#include <string>

class Detector
{
public:
	Detector() = default;
	~Detector() = default;

	Detector(const char* jsgf_filepath);

	/* detect speech from default microphone */
	std::string detect_from_microphone(void);

	/* enumerated modes of detection */
	enum Mode { keyphrase = 0, command = 1 };

	/* setting detection mode: from wake up to command */
	void set_detection_mode(Detector::Mode);

private:

	// pointer to "hypothesis" (best guess at the decoded result)
	const char* hyp;
	/* pocketsphinx decoder structure */
	ps_decoder_t *ps;
	/* pocketsphinx configuration structure */
	cmd_ln_t *config;
	/* audio recording structure - for use with ALSA functions */
	ad_rec_t *ad;
	/* buffer array to hold audio data */
	int16 adbuf[4096];
	/* flags for tracking active speech */
	uint8 utt_started, in_speech;
	/* holds the number of frames in the audio buffer */
	int32 k;
	/* current mode enum value */
	Detector::Mode mode;
	/* internal string representaion of Mode ENUM */
	const char* const modes[2] = { "keyphrase", "command" };
	/* return the current mode of detection */
	const char* get_current_detection_mode(void);

};
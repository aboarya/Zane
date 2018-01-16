#ifndef DETECTOR_H
#define DETECTOR_H

#include "sphinx.h"
#include "agent.h"

namespace DetectorSpace
{
	using namespace std;

	class Detector
	{
	public:
		Detector() = default;
		~Detector() = default;

		Detector(const char* jsgf_filepath, const vector<AgentSpace::Agent> &agents);

		/* detect speech from default microphone */
		string detect_from_microphone(void);

		/* enumerated modes of detection */
		enum Mode { keyphrase = 0, command = 1 };

		/* setting detection mode: from wake up to command */
		void set_detection_mode(Detector::Mode);

		void set_current_detection_mode(Detector::Mode d_mode);

		bool is_wakeup_spoken();

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
}

#endif /* DETECTOR_H */

#include "SynthVoice.h"

SynthVoice::waveFlag SynthVoice::currentWaveFlag = SynthVoice::waveFlag::Pulse25;
SynthVoice::tremoloDurFlag SynthVoice::currentTremoloDurFlag = SynthVoice::tremoloDurFlag::Whole;
SynthVoice::noteSlideDurFlag SynthVoice::currentNoteSlideDurFlag = SynthVoice::noteSlideDurFlag::Whole;
#include "SynthVoice.h"

SynthVoice::waveFlag SynthVoice::curWaveFlag = SynthVoice::waveFlag::Pulse25;
SynthVoice::tremoloDurFlag SynthVoice::curTremoloDurFlag = SynthVoice::tremoloDurFlag::Whole;
SynthVoice::noteSlideDurFlag SynthVoice::curNoteSlideDurFlag = SynthVoice::noteSlideDurFlag::Whole;
SynthVoice::vibratoDurFlag SynthVoice::curVibratoDurFlag = SynthVoice::vibratoDurFlag::Whole;
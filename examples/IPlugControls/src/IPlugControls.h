#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "IControls.h"
#include "IPlugPaths.h"

const int kNumPrograms = 1;

enum EParams
{
  kParamGain = 0,
  kParamMode,
  kParamFreq1,
  kParamFreq2,
  kNumParams
};

enum EControlTags
{
  kCtrlTagDialogResult = 0,
  kCtrlTagVectorButton,
  kCtrlTagVectorSlider,
  kCtrlTagTabSwitch,
  kCtrlTagRadioButton,
  kCtrlTagScope,
  kCtrlTagDisplay,
  kCtrlTagMeter,
  kCtrlTagRTText,
  kCtrlTagRedLED,
  kCtrlTagGreenLED,
  kCtrlTagBlueLED,
  kCtrlTags
};

using namespace iplug;
using namespace igraphics;

class IPlugControls final : public Plugin
{
public:
  IPlugControls(const InstanceInfo& info);

#if IPLUG_EDITOR
  void FlashBlueLED();
  void OnMidiMsgUI(const IMidiMsg& msg) override;
#endif
  
#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnIdle() override;
private:
  IBufferSender<2> mScopeSender;
  IBufferSender<1> mDisplaySender;
  IPeakSender<2> mMeterSender;
  ISender<1> mRTTextSender;
  ISenderData<1> mLastOutputData = { kCtrlTagRTText, 1, 0 };
#endif
};

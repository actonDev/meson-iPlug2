#include "IPlugReaperExtension.h"
#include "ReaperExt_include_in_plug_src.h"

// #include "IControls.h"

IPlugReaperExtension::IPlugReaperExtension(reaper_plugin_info_t* pRec)
: ReaperExtBase(pRec)
{
  //Use IMPAPI to register any Reaper APIs that you need to use
  IMPAPI(GetNumTracks);
  IMPAPI(CountTracks);
  IMPAPI(InsertTrackAtIndex);
  
  // mMakeGraphicsFunc = [&]() {
    // return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS);
  // };
  
  //Define some lambdas that can be called from either GUI widgets or in response to commands
  auto action1 = [](){
    MessageBox(gParent, "Action 1!", "Reaper extension test", MB_OK); //gParent
  };
  
  auto action2 = [](){
    InsertTrackAtIndex(GetNumTracks(), false);
  };
  
  //Register an action. args: name: lambda, add menu item,
  RegisterAction("IPlugReaperExtension: Action 1 - MsgBox", action1, true);
  RegisterAction("IPlugReaperExtension: Action 2 - AddTrack", action2);
  // RegisterAction("IPlugReaperExtension: Action 3 - Show/Hide UI", [&]() { ShowHideMainWindow(); mGUIToggle = !mGUIToggle; }, true, &mGUIToggle);
}

void IPlugReaperExtension::OnIdle()
{
  int tracks = CountTracks(0);
  
  if(tracks != mPrevTrackCount) {
    mPrevTrackCount = tracks;
    
    // if(GetUI()) {
    //   dynamic_cast<ITextControl*>(GetUI()->GetControlWithTag(kCtrlTagText))->SetStrFmt(64, "NumTracks: %i", tracks);
    // }
  }
}
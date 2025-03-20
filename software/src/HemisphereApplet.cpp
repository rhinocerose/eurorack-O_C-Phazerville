#include "HemisphereApplet.h"

HS::IOFrame HS::frame;
HS::ClockManager HS::clock_m;

int HemisphereApplet::cursor_countdown[APPLET_SLOTS + 1];
int16_t HemisphereApplet::cursor_start_x;
int16_t HemisphereApplet::cursor_start_y;
const char* HemisphereApplet::help[HELP_LABEL_COUNT];
HS::EncoderEditor HemisphereApplet::enc_edit[APPLET_SLOTS + 1];

void HemisphereApplet::BaseView(bool full_screen, bool parked) {
    //if (HS::select_mode == hemisphere)
    gfxHeader(applet_name(), (HS::ALWAYS_SHOW_ICONS || full_screen) ? applet_icon() : nullptr);
    // If active, draw the full screen view instead of the application screen
    if (full_screen) {
      if (parked)
        this->DrawFullScreen();
      else
        DrawConfigHelp();
    }
    else this->View();
}

/*
 * Has the specified Digital input been clocked this cycle?
 *
 * If physical is true, then logical clock types (master clock forwarding and metronome) will
 * not be used.
 *
 * You DON'T usually want to call this more than once per tick for each channel!
 * It modifies state by eating boops and updating cycle_ticks. -NJM
 */
bool HemisphereApplet::Clock(int ch, bool physical) {
  return frame.clocked[ch + io_offset];
}

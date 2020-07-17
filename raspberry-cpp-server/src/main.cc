#include "activity_interface.pb.h"
#include <fstream>

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  Esp8266Alert::AlertThresholdCross alert = Esp8266Alert::AlertThresholdCross();
  alert.set_crossed_thresh(20);
  std::ofstream ofs("alert.data", std::ios_base::out | std::ios_base::binary);
  alert.SerializeToOstream(&ofs);
}

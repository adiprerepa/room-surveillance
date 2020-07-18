#include <iostream>
#include "activity_interface.pb.h"

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  Esp8266Alert::AlertThresholdCross alert = Esp8266Alert::AlertThresholdCross();
  alert.set_crossed_thresh(20);
  std::string bytes = alert.SerializeAsString();
  const char* arr = bytes.data();
  int size = arr.size();
  std::cout << size << std::endl;
}

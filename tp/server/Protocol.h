#include <string>
#include "rapidjson/document.h"

class Protocol {
public:
  static rapidjson::Document Parse(std::string& x);

  static std::string ToJSON(Car& x);
};

#include <string>
#include "rapidjson/document.h"

class Protocol {
public:
  static rapidjson::Document Parse(std::string& x);

  static std::string ToJSON(Car& x);
};

// static std::string ToJSON(Modifier& x);
// static std::string ToJSON(Track& x);
// static std::string ToJSON(UserIntent& x);
// static std::string ToJSON(std::vector<Game>& x);

// {
//   "type": "disconnect",
//   "client-id", 1
// }

// {
//   "type": "intent",
//   "intent": "GasOn",
//   "client-id": 3
// }
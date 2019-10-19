#include "string.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

vector<string> split(const string& s, char delim) {
  vector<string> r;
  std::size_t current, previous = 0;
  current = s.find(delim);
  while (current != std::string::npos) {
      r.push_back(s.substr(previous, current - previous));
      previous = current + 1;
      current = s.find(delim, previous);
  }
  r.push_back(s.substr(previous, current - previous));
  return r;
}

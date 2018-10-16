#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <regex>

#define h VNode

class VNode {
public:
  VNode(
    const std::string _element,
    const std::map<std::string, std::string> _props,
    const std::vector<VNode> _children
  ) { }
  VNode(
    const std::string _element,
    const void* _noprops
  ) { }
  VNode(
    const std::string _element,
    const void* _noprops,
    const std::vector<VNode> _children
  ) { }
  VNode(
    const std::string _element,
    const std::map<std::string, std::string> _props
  ) { }
  VNode(
    const std::string _text
  ) { }
  VNode(
    const char* _text
  ) { }
};

int main() {

  VNode n = h("html", nullptr, {
    
  });

}
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <regex>

#define h Element

const std::regex whitespace("\\s{2,}");

std::string html_purge(const std::string& _text) {
  return std::regex_replace(_text, whitespace, " ");
}

struct Element {
  bool is_text = false;
  std::string text_value;

  std::string element;
  std::map<std::string, std::string> props;
  std::vector<Element> children;

  template<typename... Ts>
  Element(
    const std::string _element,
    const std::map<std::string, std::string> _props,
    const Ts&... _children
  ) {
    element = _element;
    props = _props;
    children = {_children...};
  }

  Element(const std::string& _text_value) {
    is_text = true;
    text_value = _text_value;
  }

  Element(const char* _text_value) {
    is_text = true;
    text_value = _text_value;
  }

  Element(const int _value) {
    is_text = true;
    text_value = std::to_string(_value);
  }

  Element(const double _value) {
    is_text = true;
    text_value = std::to_string(_value);
  }

  friend std::ostream& operator<<(std::ostream& os, const Element& e) {
    os << e.to_string();
    return os;
  }

  std::string to_string(int _indent = 0, int _level = 0) const {
    auto padding = std::string(_level * _indent, ' ');
    using namespace std::string_literals;
    if (is_text)
      return padding + html_purge(text_value);
    else {
      std::stringstream ss;
      ss << padding << "<" << element;

      for (auto i = props.begin(); i != props.end(); ++i)
        ss << ' ' << i->first << "=\"" << i->second << '"';

      if (children.empty())
        ss << "></" << element << ">";
      else {
        ss << ">";
        bool prev_was_text = false;
        for (auto child = children.begin(); child != children.end(); ++child) {
          bool text_stitch = prev_was_text && child->is_text;
          if (text_stitch)
            ss << ' ';
          else if (_indent)
            ss << '\n';
          ss << child->to_string(text_stitch ? 0 : _indent, _level + 1);
          prev_was_text = child->is_text;
        }
        if (_indent) ss << '\n';
        ss << padding << "</" << element << ">";
      }

      return ss.str();
    }
  }
};

int main() {
  std::cout <<
    h("html", {
        { "lang", "ru" },
        { "lang", "ru" },
        { "lang", "ru" },
      },
      h("script", { { "src", "https://unpkg.com/react@16/umd/react.development.js" } }),
      h("body", {}, 
        "Hello, world!"
      ),
      h("div", {}),
      h("div", {},
        "My",
        "name ",
        h("i", {{"style", "color: red"}}, "is"),
        " bob",
        123e+1,
        R"(
          // JSX
          <ul id="bestest-menu">
            {items.map( item =>
              <li className=".item" {...attrs(item.id)}>{item.title}</li>
            )}
          </ul>
          vs

          // hyperscript-helpers
          ul('#bestest-menu', items.map( item =>
            li('.item', attrs(item.id), item.title))
          );
          Quote from the article:

          "Neither of these two are unreadable (as long as you know the
          language), yet JSX is more verbose. < and > add no value,
          they are noise, among other quirks like { } blocks."
        )"
      )
    ).to_string(2);
}
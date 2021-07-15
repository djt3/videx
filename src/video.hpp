#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <string>

namespace videx {
  struct video {
    std::string url;
    std::string title;
    std::string length;
    std::string thumbnail;
    std::string channel;
    std::string channel_url;

    void cleanup_title() {
      auto pos = title.find("&quot;");
      while (pos != std::string::npos) {
        title.replace(pos, 6, "\"");
        pos = title.find("&quot;");
      }

      pos = title.find("&#");
      while (pos != std::string::npos) {
        if (title[pos + 4] == ';') {
          char character = std::stoi(title.substr(pos + 2, 2));
          title.replace(pos, 5, std::string(character, 1));
        } else
          break;

        pos = title.find("&#");
      }

      pos = title.find("&amp;");
      while (pos != std::string::npos) {
        title.replace(pos, 5, "&");
        pos = title.find("&amp;");
      }

      pos = title.find("–");
      while (pos != std::string::npos) {
        title.replace(pos, 3, "-");
        pos = title.find("–");
      }

      pos = title.find("…");
      while (pos != std::string::npos) {
        title.replace(pos, 3, "...");
        pos = title.find("…");
      }

      pos = title.find("’");
      while (pos != std::string::npos) {
        title.replace(pos, 3, "'");
        pos = title.find("’");
      }

      std::string ret;

      // unescape unicode characters
      for (int i = 0; i < title.size(); i++) {
        if (i < title.size() - 5 && title[i] == '\\' && title[i + 1] == 'u') {
          long value = strtol(title.substr(i + 2, 4).c_str(), nullptr, 16);

          ret += (char)value;

          i += 5;
        }

        else {
          ret += title[i];
        }
      }

      title = ret;
    }
  };
} // namespace videx

#endif

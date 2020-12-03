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
    }
  };
}

#endif

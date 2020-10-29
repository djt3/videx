#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <string>

namespace videx {
  struct video {
    std::string url;
    std::string title;
    std::string length;
  };
}

#endif

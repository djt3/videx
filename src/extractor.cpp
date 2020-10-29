#include "extractor.hpp"
#include "requests.hpp"

#include <iostream>
#include <vector>
#include <cstring>

namespace videx::extractors::yt {
  std::vector<video> extract_videos(const std::string& url) {
    std::string src = requests::make_request(url);

    std::size_t index = 0;

    std::vector<video> videos;

    while (index != std::string::npos) {
      bool compact = false;

      std::size_t temp_index = src.find("compactVideoRenderer\":{\"videoId", index);
      if (temp_index == std::string::npos) {
        index = src.find("videoRenderer\":{\"videoId", index);

        if (index == std::string::npos)
          break;
      }
      else {
        index = temp_index;
        compact = true;
      }

      video video;

      index = src.find("\"videoId\"", index) + strlen("\"videoId\":\"");
      video.url = +"https://youtube.com/watch?v=" + src.substr(index, 11);

      if (compact)
        index = src.find("simpleText", index) + strlen("simpleText\":\"");
      else
        index = src.find("\"title\":{\"runs\":[{\"text\":\"", index) + strlen("\"title\":{\"runs\":[{\"text\":\"");

      video.title = src.substr(index, src.find("\"", index) - index);

      index = src.find("lengthText", index);
      index = src.find("simpleText", index) + strlen("simpleText\":\"");

      video.length = src.substr(index, src.find("\"", index) - index);

      videos.push_back(video);
    }

    for (const auto& video : videos)
      std::cout << video.url << " - " << video.title << " - " << video.length << std::endl;

    return videos;
  }

  std::string extract_playback(const std::string& url) {
    std::string src = requests::make_request(url);

    std::size_t index = src.find("googlevideo.com\\/videoplayback");
    if (index != std::string::npos) {
      index -= 30;
      index = src.find("https:", index);

      std::string watch_url = src.substr(index, src.find("\"", index) - index - 1);

      while ((index = watch_url.find("\\/")) != std::string::npos)
        watch_url.replace(index, strlen("\\/"), "/");

      while ((index = watch_url.find("\\\\u0026")) != std::string::npos)
        watch_url.replace(index, strlen("\\\\u0026"), "&");

      return watch_url;
    }

    return "";
  }
}

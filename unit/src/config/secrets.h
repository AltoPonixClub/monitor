#ifndef MONITOR_SECRETS_H
#define MONITOR_SECRETS_H

#include <string>

class Secrets {
  public:
    static void configure();

    class Uploader {
      public:
        static inline const std::string kMonitorPassword = "";
    };
};

#endif // MONITOR_SECRETS_H

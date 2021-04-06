#ifndef OBSERVER_H
#define OBSERVER_H

#include <getopt.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

/**
 * @brief Main class
 * 
 * @details This class contains main methods of program 
 */
class Observer
{
public:
    static Observer& getObserver()
    {
        static Observer instance;
        return instance;
    }

    ~Observer();

    void init(int argc, char *argv[]);
private:
    Observer();
    Observer(const Observer& other) = default;
    Observer& operator=(const Observer& other) = default;
    Observer(const Observer&& other) = delete;
    Observer& operator=(const Observer&& other) = delete;

    void listDevicesAndExit();

private:
    char *_device;
};

#endif // OBSERVER_H
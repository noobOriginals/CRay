#ifndef THREADEDEXEC_HPP
#define THREADEDEXEC_HPP
#include <util/types.h>

#include <functional>

// typedef void(*callback)();
typedef std::function<void()> callback;

// Std includes
#include <string>
#include <thread>

class ThreadedExecution {
public:
    ThreadedExecution();
    ThreadedExecution(std::string name);
    ThreadedExecution(callback callback);
    ThreadedExecution(std::string name, callback callback);
    void execute(callback callback);
    void start();
    void run();
    bool isDone();
    callback getCallback();
    std::string getName();

private:
    callback c;
    std::thread thread;
    volatile bool running;
    std::string name;
};

#endif
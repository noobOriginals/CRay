#include <threadedExec.hpp>

#include <stdexcept>

ThreadedExecution::ThreadedExecution() {
    name = "";
    running = false;
}
ThreadedExecution::ThreadedExecution(std::string name) {
    this->name = name;
    running = false;
}
ThreadedExecution::ThreadedExecution(callback callback) {
    c = callback;
    name = "";
    running = false;
}
ThreadedExecution::ThreadedExecution(std::string name, callback callback) {
    c = callback;
    this->name = name;
    running = false;
}
void ThreadedExecution::execute(callback callback) {
    c = callback;
    start();
}
void ThreadedExecution::start() {
    if (c == nullptr) {
        throw std::runtime_error("Method callback was null!");
    }
    running = true;
    thread = std::thread(&ThreadedExecution::run, this);
}
void ThreadedExecution::run() {
    if (c == nullptr) {
        throw std::runtime_error("Method callback was null!");
    }
    c();
    running = false;
}
bool ThreadedExecution::isDone() {
    return !running;
}
callback ThreadedExecution::getCallback() {
    return c;
}
std::string ThreadedExecution::getName() {
    return name;
}
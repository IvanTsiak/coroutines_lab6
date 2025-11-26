#pragma once

#include <coroutine>
#include <exception>

struct Task {
    struct promise_type {
        Task get_return_object() {
            return Task(std::coroutine_handle<promise_type>::from_promise(*this));
        }
        std::suspend_always initial_suspend() {
            return {};
        }
        std::suspend_always final_suspend() noexcept {
            return {};
        }
        void return_void() {};
        void unhandled_exception() {
            std::terminate();
        }
        std::suspend_always yield_value(int) {
            return {};
        }
    };

    std::coroutine_handle<promise_type> handle;
    
    Task(std::coroutine_handle<promise_type> h) : handle(h) {}

    Task(Task const &) = delete;
    Task &operator=(Task const &) = delete;
    
    ~Task() {
        if (handle) handle.destroy();
    }

    void resume() {
        if (handle && !handle.done()) {
            handle.resume();
        }
    }

    bool done() const {
        return !handle || handle.done();
    }
};
#pragma once

enum class event {
    NONE,
    EXIT,
    PLAY,
    GAME_PONG,
    GAME_OVER,
    RESTART
};

class Observer {
    enum event event = event::NONE;
public:
    Observer() {}
    void update(const enum event p_event) noexcept
    { event = p_event; }
    enum event getEvent() noexcept
    { 
        enum event ret_event = event;
        event = event::NONE;
        return ret_event; 
    }
};

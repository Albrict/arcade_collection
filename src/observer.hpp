#pragma once

enum class event {
    NONE,
    EXIT,
    BACK_TO_THE_GAME_CHOOSE,
    BACK_TO_THE_MAIN_MENU,
    PLAY,
    GAME_PONG,
    GAME_ARKANOID,
    GAME_SPACE_INVADERS,
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

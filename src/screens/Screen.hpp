
#pragma once

class Screen
{
    public:
        Screen()=default;
        virtual ~Screen()=default;
        virtual void Enter() = 0;
        virtual void Leave() = 0;
};


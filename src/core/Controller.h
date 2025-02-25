#pragma once

#include "utils/Macros.h"

namespace core
{

    enum class Control
    {
        NONE,

        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        ACTION_MAIN,
        ACTION_SECONDARY,
        ACTION_NEXT_ITEM,

        MENU_OPEN,
        MENU_NEXT,
        MENU_PREV,
        MENU_ACTION,

        ZOOM_IN,
        ZOOM_OUT,
    };

    class Controller
    {
    private:
    public:
        Controller() {}

        virtual ~Controller() {}

        virtual bool down(Control control)
        {
            __unused(control);

            return false;
        }

        virtual bool pressed(Control control)
        {
            __unused(control);

            return false;
        }
    };

} // namespace core

#ifndef INC_CJOYSTICK_H
#define INC_CJOYSTICK_H

class IJoystickHandler 
{
    public:
        virtual ~IJoystickHandler() {};

        virtual void onLeftIn() = 0;
        virtual void onLeftOut() = 0;
        virtual void onRightIn() = 0;
        virtual void onRightOut() = 0;
        virtual void onDownIn() = 0;
        virtual void onDownOut() = 0;
        virtual void onUpIn() = 0;
        virtual void onUpOut() = 0;
        virtual void onSwitchDown() = 0;
        virtual void onSwitchUp() = 0;
        virtual void onChanged() = 0;
};

class CSerialJoystickHandler : public IJoystickHandler {
    virtual void onLeftIn();
    virtual void onLeftOut();
    virtual void onRightIn();
    virtual void onRightOut();
    virtual void onDownIn();
    virtual void onDownOut();
    virtual void onUpIn();
    virtual void onUpOut();
    virtual void onSwitchDown();
    virtual void onSwitchUp();
    virtual void onChanged();
};

class CJoystick {
    private:
        int m_x_pin = 0; 
        int m_y_pin = 0;
        int m_switch_pin = 0;

        int m_left_level_in     = 200;  // if x level below this value, we are entering the "left" area
        int m_left_level_out    = 300; // if x level upper this value, we are leaving the "left" area

        int m_right_level_in    = 4000;  // if x level upper this value, we are entering the right area
        int m_right_level_out   = 3900; // if x level below this value, we are leaving the right area

        int m_down_level_in     = 200;  // if y level below this value, we are entering the "down" area
        int m_down_level_out    = 300; // if y level upper this value, we are leaving the "down" area

        int m_up_level_in       = 4000;  // if y level upper this value, we are entering the "upper" area
        int m_up_level_out      = 3900; // if y level below this value, we are leaving the "upper" area

        int m_x = 0;
        int m_y = 0;
        int m_s = 0;

        IJoystickHandler *m_joystick_handler = NULL;

    protected:
        bool handleXAxis();
        bool handleYAxis();
        bool handleSwitch();

    public:
        CJoystick(int x_pin, int y_pin, int switch_pin);
        void read();
        void print();

        void setJoyStickHandler(IJoystickHandler *joystick_handler);

        void onLeftIn();
        void onLeftOut();
        void onRightIn();
        void onRightOut();
        void onDownIn();
        void onDownOut();
        void onUpIn();
        void onUpOut();
        void onSwitchDown();
        void onSwitchUp();
        void onChanged();
};

#endif
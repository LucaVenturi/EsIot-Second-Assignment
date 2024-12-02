#ifndef __DOOR__
#define __DOOR__

class Door
{
    public:
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void reverse() = 0;
        virtual void on() = 0;
        virtual void off() = 0;
        virtual bool isMoving() = 0;

};

#endif // __DOOR__

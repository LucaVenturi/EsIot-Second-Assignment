#if !defined(__DOOR__)
#define __DOOR__

class Door
{
    public:
        Door();
        virtual void open() = 0;
        virtual void close() = 0;
        virtual void reverse() = 0;

};

#endif // __DOOR__

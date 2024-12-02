#if !defined(__SYNCH__)
#define __SYNCH__

class Synchronizable {
    public: 
        virtual void sync() = 0;
        virtual long getLastSyncTime();
    protected:
        virtual void updateSyncTime();
    private:
        long lastTimeSync;
};


#endif // __SYNCH__
#pragma once
#ifndef ID_tracker_hpp
#define ID_tracker_hpp

#include <set>

class ID_tracker
{
public:
    static ID_tracker& idtr_get_id_tracker()
    {
        static ID_tracker instance;
        return instance;
    }

    int get_new_id();

    void free_id(int i_id);

private:
    ID_tracker() 
    {
        last_open_id = 0;

        set_i_open_ids = std::set<int>();
    }

    int last_open_id;

    std::set<int> set_i_open_ids;
};

#endif
#include "ID_tracker.hpp"

int ID_tracker::get_new_id()
{
	int temp = -1;
	if (set_i_open_ids.size() == 0)
	{
		temp = last_open_id;
		last_open_id = last_open_id + 1;
		return temp;
	}
	else
	{
		auto auto_auto = set_i_open_ids.begin();
		temp = *auto_auto;
		set_i_open_ids.erase(auto_auto);
		return temp;
	}
}

void ID_tracker::free_id(int i_id)
{
	set_i_open_ids.insert(i_id);
}
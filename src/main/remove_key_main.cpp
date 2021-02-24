#include "jump_dir_core.h"
#include <iostream>


int main(int argc, char *argv[])
{
    status return_value = NOT_OK;

    if (argc >= 3)
    {
        std::string const config_file = argv[1];
        std::string const key_to_remove = argv[2];
        return_value = remove_key(config_file, key_to_remove);
        if (return_value == NOT_OK)
        {
            std::cout << "Failed to remove key" << std::endl;
        }
    }

    return return_value;
}
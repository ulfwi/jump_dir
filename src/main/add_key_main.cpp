#include "jump_dir_core.h"
#include <iostream>


int main(int argc, char *argv[])
{
    int return_value = 1;

    if (argc >= 4)
    {
        std::string const config_file = argv[1];
        std::string const new_key = argv[2];
        std::string const new_path = argv[3];
        return_value = add_key(config_file, new_key, new_path);
        if (return_value == 0)
        {
            std::cout << "Key \'" << new_key << "\' with path \'" << new_path << "\' added to config file" << std::endl;
        }
        else
        {
            std::string path;
            get_path_from_key(config_file, new_key, path);
            std::cout <<  "Key \'" << new_key << "\' already exists with path \'" << path << "\'" << std::endl;
        }
    }

    return return_value;
}
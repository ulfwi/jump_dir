#include "jump_dir_core.h"
#include <iostream>


int main(int argc, char *argv[])
{
    int return_value = 1;

    if (argc >= 3)
    {
        std::string const config_file = argv[1];
        std::string const input_key = argv[2];
        std::string output_str;
        return_value = get_path_from_key(config_file, input_key, output_str);
        std::cout << output_str;
    }

    return return_value;
}
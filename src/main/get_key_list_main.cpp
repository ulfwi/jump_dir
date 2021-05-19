#include "jump_dir_core.h"
#include <iostream>


int main(int argc, char *argv[])
{
    status return_value = NOT_OK;

    if (argc >= 2)
    {
        std::string const config_file{argv[1]};
        std::string output_str;
        return_value = get_key_list(config_file, output_str);
        std::cout << output_str;
    }

    return return_value;
}
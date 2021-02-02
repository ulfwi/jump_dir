#include "jump_dir_core.h"
#include <string>


int main(int argc, char *argv[])
{
    int return_value = 1;

    if (argc >= 3)
    {
        std::string const config_file = argv[1];
        std::string const input_key = argv[2];
        if (key_exists(config_file, input_key))
        {
            return_value = 0;
        }
        else
        {
            return_value = 1;
        }
    }

    return return_value;
}
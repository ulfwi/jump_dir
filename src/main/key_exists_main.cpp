#include "jump_dir_core.h"
#include <string>


int main(int argc, char *argv[])
{
    status return_value = NOT_OK;

    if (argc >= 3)
    {
        std::string const config_file = argv[1];
        std::string const input_key = argv[2];
        if (key_exists(config_file, input_key))
        {
            return_value = OK;
        }
        else
        {
            return_value = NOT_OK;
        }
    }

    return return_value;
}
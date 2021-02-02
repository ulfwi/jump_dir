#include "jump_dir_core.h"
#include <string>


int main(int argc, char *argv[])
{
    int return_value = 1;

    if (argc >= 2)
    {
        std::string const config_file = argv[1];
        if (is_config_file_valid(config_file))
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
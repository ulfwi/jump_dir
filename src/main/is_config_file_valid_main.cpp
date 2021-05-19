#include "jump_dir_core.h"
#include <string>


int main(int argc, char *argv[])
{
    status return_value = NOT_OK;

    if (argc >= 2)
    {
        std::string const config_file{argv[1]};
        if (is_config_file_valid(config_file))
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
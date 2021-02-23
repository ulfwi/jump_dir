#include "jump_dir_core.h"
#include <string>


int main(int argc, char *argv[])
{
    status return_value = NOT_OK;

    if (argc >= 2)
    {
        std::string const config_file = argv[1];
        return_value = print_config_file(config_file);
    }

    return return_value;
}

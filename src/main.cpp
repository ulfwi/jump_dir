#include "jump_dir_core.h"
#include <iostream>


int main(int argc, char *argv[])
{
    int return_value = 1;

    #ifdef GET_PATH_FROM_KEY
    if (argc >= 3)
    {
        std::string const config_file = argv[1];
        std::string const input_key = argv[2];
        std::string output_str;
        return_value = get_path_from_key(config_file, input_key, output_str);
        std::cout << output_str;
    }
    #endif // GET_PATH_FROM_KEY

    #ifdef GET_KEY_LIST
    if (argc >= 2)
    {
        std::string const config_file = argv[1];
        std::string output_str;
        return_value = get_key_list(config_file, output_str);
        std::cout << output_str;
    }
    #endif // GET_KEY_LIST

    #ifdef KEY_EXISTS
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
    #endif // KEY_EXISTS

    #ifdef ADD_KEY
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
    #endif // ADD_KEY

    #ifdef REMOVE_KEY
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
    #endif // REMOVE_KEY

    #ifdef IS_CONFIG_FILE_VALID
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
    #endif // IS_CONFIG_FILE_VALID

    return return_value;
}

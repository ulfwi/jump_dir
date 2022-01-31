#include "jump_dir_core.h"
#include <iostream>
#include <string>
#include <vector>


status key_exists_main(std::vector<std::string> const args)
{
    status return_value = NOT_OK;

    if (args.size() >= 2)
    {
        std::string const config_file{args[0]};
        std::string const input_key{args[1]};
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

status get_key_list_main(std::vector<std::string> const args)
{
    status return_value = NOT_OK;

    if (args.size() >= 1)
    {
        std::string const config_file{args[0]};
        std::string output_str;
        return_value = get_key_list(config_file, output_str);
        std::cout << output_str;
    }

    return return_value;
}

status add_key_main(std::vector<std::string> const args)
{
    status return_value = NOT_OK;

    if (args.size() >= 3)
    {
        std::string const config_file{args[0]};
        std::string const new_key{args[1]};
        std::string const new_path{args[2]};
        return_value = add_key(config_file, new_key, new_path);
        if (return_value == OK)
        {
            std::cout << "Key \'" << new_key << "\' with path \'" << new_path << "\' added to config file" << std::endl;
        }
        else
        {
            std::string path;
            get_path_from_key(config_file, new_key, path);
            std::cout << "Key \'" << new_key << "\' already exists with path \'" << path << "\'" << std::endl;
        }
    }

    return return_value;
}

status get_path_from_key_main(std::vector<std::string> const args)
{
    status return_value = NOT_OK;

    if (args.size() >= 2)
    {
        std::string const config_file{args[0]};
        std::string const input_key{args[1]};
        std::string output_str;
        return_value = get_path_from_key(config_file, input_key, output_str);
        std::cout << output_str;
    }

    return return_value;
}

status is_config_file_valid_main(std::vector<std::string> const args)
{
    status return_value = NOT_OK;

    if (args.size() >= 1)
    {
        std::string const config_file{args[0]};
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

status print_config_file_main(std::vector<std::string> const args)
{
    status return_value = NOT_OK;

    if (args.size() >= 1)
    {
        std::string const config_file{args[0]};
        return_value = print_config_file(config_file);
    }

    return return_value;
}

status remove_key_main(std::vector<std::string> const args)
{
    status return_value = NOT_OK;

    if (args.size() >= 2)
    {
        std::string const config_file{args[0]};
        std::string const key_to_remove{args[1]};
        return_value = remove_key(config_file, key_to_remove);
        if (return_value == NOT_OK)
        {
            std::cout << "Failed to remove key" << std::endl;
        }
    }

    return return_value;
}


int main(int argc, char *argv[])
{
    status return_value = NOT_OK;

    if (argc < 2)
    {
        std::cout << "No input arguments." << std::endl;
        return NOT_OK;
    }

    // Read input arguments
    std::string const command{argv[1]};

    std::vector<std::string> args;
    for (int i = 2; i < argc; i++)
    {
        args.push_back(argv[i]);
    }

    if (command == "key_exists")
    {
        return_value = key_exists_main(args);
    }
    else if (command == "get_key_list")
    {
        return_value = get_key_list_main(args);
    }
    else if (command == "add_key")
    {
        return_value = add_key_main(args);
    }
    else if (command == "get_path_from_key")
    {
        return_value = get_path_from_key_main(args);
    }
    else if (command == "is_config_file_valid")
    {
        return_value = is_config_file_valid_main(args);
    }
    else if (command == "print_config_file")
    {
        return_value = print_config_file_main(args);
    }
    else if (command == "remove_key")
    {
        return_value = remove_key_main(args);
    }
    else
    {
        std::cout << "Invalid command." << std::endl;
    }

    return return_value;
}
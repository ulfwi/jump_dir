#include "jump_dir_core.h"
#include <fstream>
#include <iostream>
#include <sstream>


namespace
{
// Create a string containing repetitions of a character.
std::string repeat(char const character, uint8_t const nbr_repetitions)
{
    return std::string(nbr_repetitions, character);
}
} // namespace

status get_path_from_key(std::string const& config_file, std::string const& input_key, std::string& output_str)
{
    std::ifstream infile(config_file, std::ios::in);
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line, std::ios::in);

        // Read words into variables
        std::string key;
        std::string path;
        if (iss >> key >> path)
        {
            if (input_key == key)
            {
                output_str.assign(path);
                return OK;
            }
        }
        else
        {
            // std::cout << "Error while parsing file " << config_file << std::endl;
            return NOT_OK;
        }
    }

    return NOT_OK;
}

status get_key_list(std::string const& config_file, std::string& output_str)
{
    std::ifstream infile(config_file, std::ios::in);
    if (infile.fail())
    {
        // Failed to open file
        return NOT_OK;
    }

    std::string line;
    bool first_line = true;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line, std::ios::in);

        // Read words into variables
        std::string key;
        std::string path;
        if (iss >> key >> path)
        {
            if (!first_line)
            {
                output_str.append(" ");
            }
            else
            {
                first_line = false;
            }

            output_str.append(key);
        }
        else
        {
            // std::cout << "Error while parsing file " << config_file << std::endl;
            return NOT_OK;
        }
    }

    return OK;
}

bool key_exists(std::string const& config_file, std::string const& input_key)
{
    // Check return status to see if it was found
    std::string output_str;
    bool const key_found = (get_path_from_key(config_file, input_key, output_str) == OK);
    return key_found;
}

status add_key(std::string const& config_file, std::string const& new_key, std::string const& new_path)
{
    if (new_key.empty() || new_path.empty())
    {
        return NOT_OK;
    }

    status operation_status = NOT_OK;
    if (!key_exists(config_file, new_key))
    {
        // Open config file in append mode
        std::ofstream out(config_file, std::ios::app);
        out << new_key << " " << new_path << std::endl;
        operation_status = OK;
    }
    else
    {
        operation_status = NOT_OK;
    }

    return operation_status;
}

status remove_key(std::string const& config_file, std::string const& key_to_remove)
{
    status removal_status = NOT_OK;
    if (key_exists(config_file, key_to_remove))
    {
        std::ifstream infile(config_file, std::ios::in);
        std::string temp_file = config_file;
        temp_file.append(".temp");
        std::ofstream outfile(temp_file, std::ios::out);

        if (outfile.fail())
        {
            // Failed to open file
            return NOT_OK;
        }

        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line, std::ios::in);
            std::string key;
            if (iss >> key)
            {
                // Write all lines except the one we should remove from
                // config to temporary file
                if (key_to_remove != key)
                {
                    outfile << line << std::endl;
                }
            }
            else
            {
                // std::cout << "Error while parsing file " << config_file << std::endl;
                return NOT_OK;
            }
        }

        // Remove old config and rename temp file
        remove(config_file.c_str());
        rename(temp_file.c_str(), config_file.c_str());

        removal_status = OK;
    }
    else
    {
        removal_status = NOT_OK;
    }

    return removal_status;
}

bool is_config_file_valid(std::string const& config_file)
{
    std::ifstream infile(config_file, std::ios::in);
    if (!infile)
    {
        // File doesn't exist
        return false;
    }

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line, std::ios::in);

        // Read words into variables
        std::string key;
        std::string path;
        if (iss >> key >> path)
        {
            // Valid line
        }
        else
        {
            // std::cout << "Error while parsing file " << config_file << std::endl;
            return false;
        }
    }

    return true;
}

status print_config_file(std::string const& config_file)
{
    std::ifstream infile(config_file, std::ios::in);
    if (!infile)
    {
        // File doesn't exist
        return NOT_OK;
    }

    constexpr int path_offset = 20;

    std::cout << "Key" << repeat(' ', std::max(path_offset - 3, 1)) << "Path" << std::endl;
    std::cout << "-------" << repeat(' ', std::max(path_offset - 7, 1)) << "-------" << std::endl;

    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line, std::ios::in);

        // Read words into variables
        std::string key;
        std::string path;
        if (iss >> key >> path)
        {
            // Print content of line
            int const nbr_spaces = path_offset - static_cast<int>(key.length());
            std::cout << key << repeat(' ', std::max(nbr_spaces, 1)) << path << std::endl;
        }
        else
        {
            // std::cout << "Error while parsing file " << config_file << std::endl;
            return NOT_OK;
        }
    }

    return OK;
}

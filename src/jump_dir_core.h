#ifndef JUMP_DIR_CORE_H
#define JUMP_DIR_CORE_H

#include <string>

enum status
{
    OK = 0,
    NOT_OK = 1
};

status get_path_from_key(std::string const& config_file, std::string const& input_key, std::string& output_str);
status get_key_list(std::string const& config_file, std::string& output_str);
bool key_exists(std::string const& config_file, std::string const& input_key);
status add_key(std::string const& config_file, std::string const& new_key, std::string const& new_path);
status remove_key(std::string const& config_file, std::string const& key_to_remove);
bool is_config_file_valid(std::string const& config_file);

#endif // JUMP_DIR_CORE_H

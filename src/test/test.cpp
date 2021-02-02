#include "jump_dir_core.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include "test.h"


TEST(key_exists)
{
    std::string const temp_config_file = "temp.config";
    std::ofstream outfile(temp_config_file, std::ios::app);
    outfile << "test_key" << " " << "path/for/test" << std::endl;

    ASSERT_TRUE(key_exists(temp_config_file, "test_key"));
    ASSERT_FALSE(key_exists(temp_config_file, "boop"));
    ASSERT_FALSE(key_exists(temp_config_file, ""));

    remove(temp_config_file.c_str());
}

TEST(add_key)
{
    std::string const temp_config_file = "temp.config";

    ASSERT_EQUAL(add_key(temp_config_file, "boop", "path/to/dir"), OK);
    ASSERT_EQUAL(add_key(temp_config_file, "boop", "path/to/dir"), NOT_OK);
    ASSERT_EQUAL(add_key(temp_config_file, "broom", "path/from/dir"), OK);
    ASSERT_EQUAL(add_key(temp_config_file, "", "rom/dir"), NOT_OK);
    ASSERT_EQUAL(add_key(temp_config_file, "lol", ""), NOT_OK);
    ASSERT_EQUAL(add_key(temp_config_file, "", ""), NOT_OK);

    remove(temp_config_file.c_str());
}

TEST(get_path_from_key)
{
    std::string const temp_config_file = "temp.config";
    std::ofstream outfile(temp_config_file, std::ios::app);
    std::string output_str;

    // Test getting paths from empty config file
    ASSERT_EQUAL(get_path_from_key(temp_config_file, "", output_str), NOT_OK);
    ASSERT_EQUAL(get_path_from_key(temp_config_file, "test_key", output_str), NOT_OK);
    ASSERT_STRING_EQUAL(output_str, "");

    // Test getting paths from keys
    outfile << "test_key" << " " << "path/for/test" << std::endl;
    outfile << "test_key1" << " " << "path/for/test1" << std::endl;

    ASSERT_EQUAL(get_path_from_key(temp_config_file, "test_key", output_str), OK);
    ASSERT_STRING_EQUAL(output_str, "path/for/test");
    ASSERT_EQUAL(get_path_from_key(temp_config_file, "test_key1", output_str), OK);
    ASSERT_STRING_EQUAL(output_str, "path/for/test1");

    // Test faulty config file
    ASSERT_EQUAL(get_path_from_key("", "test_key", output_str), NOT_OK);

    outfile << "hej" << " " << "" << std::endl;

    ASSERT_EQUAL(get_path_from_key(temp_config_file, "hej", output_str), NOT_OK);

    remove(temp_config_file.c_str());
}

TEST(remove_key)
{
    std::string const temp_config_file = "hej.config";
    std::ofstream outfile(temp_config_file, std::ios::app);

    outfile << "test_key" << " " << "path/for/test" << std::endl;
    outfile << "test_key1" << " " << "path/for/test1" << std::endl;
    outfile << "test_key2" << " " << "path/for/test2" << std::endl;

    ASSERT_EQUAL(remove_key(temp_config_file, "hej"), NOT_OK);
    ASSERT_EQUAL(remove_key(temp_config_file, "test_key1"), OK);
    ASSERT_EQUAL(remove_key(temp_config_file, "test_key1"), NOT_OK);

    // Check contents of config file
    std::ifstream infile(temp_config_file);
    std::string line;

    std::getline(infile, line);
    ASSERT_STRING_EQUAL(line, "test_key path/for/test");
    std::getline(infile, line);
    ASSERT_STRING_EQUAL(line, "test_key2 path/for/test2");
    std::getline(infile, line);
    ASSERT_STRING_EQUAL(line, "");

    remove(temp_config_file.c_str());
}

TEST(get_key_list)
{
    std::string const temp_config_file = "temp.config";
    std::ofstream outfile(temp_config_file, std::ios::app);
    std::string output_str;

    // Test getting paths from keys
    outfile << "test_key" << " " << "path/for/test" << std::endl;
    outfile << "test_key1" << " " << "path/for/test1" << std::endl;

    ASSERT_EQUAL(get_key_list(temp_config_file, output_str), OK);
    ASSERT_STRING_EQUAL(output_str, "test_key test_key1");

    // Test faulty config file
    ASSERT_EQUAL(get_key_list("", output_str), NOT_OK);

    outfile << "hej" << " " << "" << std::endl;

    ASSERT_EQUAL(get_key_list(temp_config_file, output_str), NOT_OK);

    remove(temp_config_file.c_str());
}


int main(int argc, char *argv[])
{
    std::cout << "Running jump_dir tests..." << std::endl;
    RUN_UNITTESTS();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
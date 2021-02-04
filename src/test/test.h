#include <list>
#include <string>
#include <iostream>
#include <sstream>

// Unittest function pointer type
typedef void (*unittest_fp)();

class Unittest;

// List containing all unittests
std::list<Unittest> unittest_list;

// Contains info about a unittest
class Unittest
{
    public:
        Unittest(unittest_fp const fp, std::string const name) :
        fp{fp},
        name{name}
        {
        }

        void run() const
        {
            (*fp)();
        }

    unittest_fp const fp;
    std::string const name;
};

// Adds unittest to list
class UnittestDeclaration
{
    public:
        UnittestDeclaration(unittest_fp const fp, std::string const name)
        {
            unittest_list.push_back(Unittest{fp, name});
        }
};

// This macro creates a function with the name test_##test_name()
// Then it calls the constructor of the class Unittest which adds that
// unittest to a list
#define TEST(test_name) \
void test_##test_name(); \
UnittestDeclaration unittest_declaration_##test_name(test_##test_name, "test_"#test_name); \
void test_##test_name() \

static bool unittest_failed = false;
static std::stringstream error_message;

class UnittestHandler
{
    public:
        // Runs all unittests in unittest_list
        void run_unittests()
        {
            bool any_unittest_failed = false;

            std::cout << "Running unittests..." << std::endl;
            for (auto const unittest : unittest_list)
            {
                std::cout << "Running " << unittest.name << "...";
                unittest.run();

                if (unittest_failed)
                {
                    std::cout << set_text_red << "FAIL" << set_text_white << std::endl;
                    std::cout << error_message.str();
                    unittest_failed = false;
                    error_message.str("");
                    any_unittest_failed = true;
                }
                else
                {
                    std::cout << set_text_green << "OK" << set_text_white << std::endl;
                }
            }

            if (any_unittest_failed)
            {
                std::cout << set_text_red << "Unittests failed!" << set_text_white << std::endl;
            }
            else
            {
                std::cout << set_text_green << "All unittests passed!" << set_text_white << std::endl;
            }
        }

    private:
        // Colours
        std::string const set_text_red = "\033[1;31m";
        std::string const set_text_green = "\033[1;32m";
        std::string const set_text_white = "\033[0m";

} unittest_handler;

#define RUN_UNITTESTS() (unittest_handler.run_unittests())

void assert_condition(bool const cond, uint32_t const line_nbr, std::string const condition_string)
{
    if (!cond)
    {
        unittest_failed = true;
        error_message << "Failing assert at line " << line_nbr << ":" << std::endl;
        error_message << "    " << condition_string << std::endl << std::endl;
    }
}

#define ASSERT_WRAPPER(cond) (assert_condition(cond, __LINE__, #cond))

// Asserts
#define ASSERT_TRUE(cond) (ASSERT_WRAPPER(cond))
#define ASSERT_FALSE(cond) (ASSERT_WRAPPER(!(cond)))
#define ASSERT_EQUAL(a, b) (ASSERT_WRAPPER(a == b))
#define ASSERT_STRING_EQUAL(a, b) (ASSERT_WRAPPER(a.compare(b) == 0))

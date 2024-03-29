#include <iostream>
#include <list>
#include <sstream>
#include <string>

class AssertionHandler
{
    public:
        void assert_condition(bool const cond, uint32_t const line_nbr, std::string const& condition_string)
        {
            if (!cond)
            {
                unittest_failed = true;
                error_message << "Failing assert at line " << line_nbr << ":" << std::endl;
                error_message << "    " << condition_string << std::endl << std::endl;
            }
        }

        void assert_string_equal(std::string const& str1, std::string const& str2, uint32_t const line_nbr)
        {
            if (str1 != str2)
            {
                unittest_failed = true;
                error_message << "Failing assert at line " << line_nbr << ". Asserting strings equal:" << std::endl;
                error_message << "    " << str1 << " == " << str2 << std::endl << std::endl;
            }
        }

        bool get_unittest_failed() const
        {
            return unittest_failed;
        }

        std::string get_error_message()
        {
            return error_message.str();
        }

    private:
        bool unittest_failed = false;
        std::stringstream error_message;

};

// Contains info about a unittest
class Unittest
{
    public:
        // Unittest function pointer type
        typedef void (*FunctionPointer)(AssertionHandler&);

        struct Status
        {
            bool unittest_failed;
            std::string error_message;
        };

        Unittest(FunctionPointer const function_pointer, std::string name) :
        function_pointer{function_pointer},
        name{std::move(name)}
        {
        }

        Status run() const
        {
            AssertionHandler assertion_handler{};
            function_pointer(assertion_handler);

            bool const unittest_failed = assertion_handler.get_unittest_failed();
            std::string const error_message = assertion_handler.get_error_message();
            return Status{unittest_failed, error_message};
        }

        std::string get_name() const
        {
            return name;
        }

    private:
        FunctionPointer const function_pointer;
        std::string const name;
};

// Singleton class which handles the execution and output of all unittests
class UnittestHandler
{
    public:
        void add_unittest(Unittest const& unittest)
        {
            unittest_list.push_back(unittest);
        }

        // Runs all unittests in unittest_list
        void run_unittests()
        {
            bool any_unittest_failed = false;

            std::cout << "Running unittests..." << std::endl;
            for (Unittest const& unittest : unittest_list)
            {
                std::cout << "Running " << unittest.get_name() << "...";
                Unittest::Status status = unittest.run();

                if (status.unittest_failed)
                {
                    std::cout << set_text_red << "FAIL" << set_text_white << std::endl;
                    std::cout << status.error_message;
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
        // List containing all unittests
        std::list<Unittest> unittest_list;

        // Colours
        std::string const set_text_red = "\033[1;31m";
        std::string const set_text_green = "\033[1;32m";
        std::string const set_text_white = "\033[0m";

} unittest_handler;

// Adds unittest to list in unittest_handler
class UnittestDeclaration
{
    public:
        UnittestDeclaration(Unittest::FunctionPointer const fp, std::string const& name)
        {
            unittest_handler.add_unittest(Unittest{fp, name});
        }
};

// This macro creates a function with the name test_##test_name()
// Then it calls the constructor of the class UnittestDeclaration which adds that
// unittest to a list in unittest_handler
#define TEST(test_name) \
void test_##test_name(AssertionHandler &assertion_handler); \
UnittestDeclaration unittest_declaration_##test_name(test_##test_name, "test_"#test_name); \
void test_##test_name(AssertionHandler &assertion_handler) \

#define RUN_UNITTESTS() (unittest_handler.run_unittests())

#define ASSERT_WRAPPER(cond) (assertion_handler.assert_condition(cond, __LINE__, #cond))

// Asserts
#define ASSERT_TRUE(cond) (ASSERT_WRAPPER(cond))
#define ASSERT_FALSE(cond) (ASSERT_WRAPPER(!(cond)))
#define ASSERT_EQUAL(a, b) (ASSERT_WRAPPER((a) == (b)))
#define ASSERT_STRING_EQUAL(a, b) (assertion_handler.assert_string_equal(a, b, __LINE__))

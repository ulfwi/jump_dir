#include <list>
#include <string>

// Unittest function pointer type
typedef void (*unittest_fp)();

class Unittest;

// List containing all unittests
std::list<Unittest> unittest_list;

// The constructor of this class adds itself to the list of unittests
class Unittest
{
    public:
        Unittest(unittest_fp const fp, std::string const name) :
        fp{fp},
        name{name}
        {
            unittest_list.push_back(*this);
        }

        void run() const
        {
            (*fp)();
        }

    unittest_fp const fp;
    std::string const name;
};

// This macro creates a function with the name test_##test_name()
// Then it calls the constructor of the class Unittest which adds that
// unittest to a list
#define TEST(test_name) \
void test_##test_name(); \
Unittest unittest_##test_name(test_##test_name, "test_"#test_name); \
void test_##test_name() \

bool unittest_failed = false;

// Runs all unittests in unittest_list
void RUN_UNITTESTS()
{
    // Colours
    std::string const set_text_red = "\033[1;31m";
    std::string const set_text_green = "\033[1;32m";
    std::string const set_text_white = "\033[0m";

    std::cout << "Running unittests..." << std::endl;
    for (auto const unittest : unittest_list)
    {
        std::cout << "Running " << unittest.name << "...";
        unittest.run();

        if (unittest_failed)
        {
            std::cout << set_text_red << "FAIL" << set_text_white << std::endl;
            unittest_failed = false;
        }
        else
        {
            std::cout << set_text_green << "OK" << set_text_white << std::endl;
        }
    }
    std::cout << "All tests passed!" << std::endl;
}

void assert_condition(bool cond)
{
    if (!cond)
    {
        unittest_failed = true;
    }
}

// Asserts
#define ASSERT_TRUE(cond) (assert_condition(cond))
#define ASSERT_FALSE(cond) (assert_condition(!(cond)))
#define ASSERT_EQUAL(a, b) (assert_condition(a == b))
#define ASSERT_STRING_EQUAL(a, b) (assert_condition(a.compare(b) == 0))

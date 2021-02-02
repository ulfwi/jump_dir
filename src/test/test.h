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

// Runs all unittests in unittest_list
void RUN_UNITTESTS()
{
    for (auto const unittest : unittest_list)
    {
        std::cout << "Running " << unittest.name << "..." << std::endl;
        unittest.run();
    }
}

// Asserts
#define ASSERT_TRUE(cond) (assert(cond))
#define ASSERT_FALSE(cond) (assert(!(cond)))
#define ASSERT_EQUAL(a, b) (assert(a == b))
#define ASSERT_STRING_EQUAL(a, b) (assert(a.compare(b) == 0))

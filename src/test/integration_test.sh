
TEST_DIR="$(dirname "$(readlink -f "$0")")"

setup_test()
{
    # Import the commands and change the config file
    source /home/s0001191/repos/jump_dir/jump_dir.sh
    JD_CONFIG="$TEST_DIR/test_config.config"
}

test_jd_list()
(
    setup_test

    expected_output=$'hej hoppsan\nman kan\npictures /home/s0001191/Pictures'
    actual_output=$(jd list)

    if [ "$actual_output" ==  "$expected_output" ]; then
        echo "Test test_jd_list passed"
    else
        echo "Test test_jd_list failed"
    fi
)

test_jd()
(
    setup_test

    # Run command to test
    jd pictures

    expected_dir="/home/s0001191/Pictures"
    actual_dir=$PWD

    if [ "$actual_dir" ==  "$expected_dir" ]; then
        echo "Test test_jd passed"
    else
        echo "Test test_jd failed"
    fi
)

echo "Running integration tests..."
test_jd_list
test_jd

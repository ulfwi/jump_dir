
TEST_DIR="$(dirname "$(readlink -f "$0")")"

setup_test()
{
    # Import the jd commands
    source /home/s0001191/repos/jump_dir/jump_dir.sh

    # Change the config file
    JD_CONFIG="$TEST_DIR/test_config.config"

    # Create config file
    touch $JD_CONFIG
}

teardown_test()
{
    # Remove config file
    rm $JD_CONFIG
}

test_jd_list()
(
    setup_test

    expected_output=$'hej hoppsan\nman kan'

    echo "$expected_output" >> $JD_CONFIG

    # Run command to test
    actual_output=$(jd list)

    if [ "$actual_output" ==  "$expected_output" ]; then
        echo "Test test_jd_list passed"
    else
        echo "Test test_jd_list failed"
    fi

    teardown_test
)

test_jd()
(
    setup_test

    echo "pictures /home/s0001191/Pictures" >> $JD_CONFIG

    # Run command to test
    jd pictures

    expected_dir="/home/s0001191/Pictures"
    actual_dir=$PWD

    if [ "$actual_dir" ==  "$expected_dir" ]; then
        echo "Test test_jd passed"
    else
        echo "Test test_jd failed"
    fi

    teardown_test
)

echo "Running integration tests..."
test_jd_list
test_jd

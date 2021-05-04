
TEST_DIR="$(dirname "$(readlink -f "$0")")"

setup_test()
{
    # Import the jd commands
    source /home/s0001191/repos/jump_dir/jump_dir.sh

    # Change the config file
    JD_CONFIG="$TEST_DIR/test_config.config"

    # Create config file
    touch $JD_CONFIG

    # Save name of function
    TESTNAME=${FUNCNAME[1]}
}

teardown_test()
{
    # Remove config file
    rm $JD_CONFIG
}

expect_eq()
(
    printf "Test $TESTNAME"
    if [ "$1" ==  "$2" ]; then
        printf $'\033[1;32m passed \033[0m\n'
    else
        printf $'\033[1;31m failed \033[0m\n'
    fi 
)

test_jd_list()
(
    setup_test

    echo $'hej hoppsan\nman kan' >> $JD_CONFIG

    # Run command to test
    actual_output=$(jd list)

    expected_output=$'Key                 Path\n'
    expected_output="$expected_output"$'-------             -------\n'
    expected_output="$expected_output"$'hej                 hoppsan\n'
    expected_output="$expected_output"$'man                 kan'

    expect_eq "$actual_output" "$expected_output"

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

    expect_eq "$actual_dir" "$expected_dir"

    teardown_test
)

test_jd_add()
(
    setup_test

    expected_output="hejsan hoppsan"

    # Run command to test
    discard_output=$(jd add hejsan hoppsan)

    actual_output=$(jd list)

    expect_eq "$actual_dir" "$expected_dir"

    teardown_test
)

test_jd_add_default()
(
    setup_test

    expected_output="hejsan $PWD"

    # Run command to test
    discard_output=$(jd add hejsan)

    actual_output=$(jd list)

    expect_eq "$actual_dir" "$expected_dir"

    teardown_test
)

test_jd_default()
(
    setup_test

    # Run command to test
    jd

    expected_dir=$HOME
    actual_dir=$PWD

    expect_eq "$actual_dir" "$expected_dir"

    teardown_test
)

test_jd_list_empty()
(
    setup_test

    # Run command to test
    actual_output=$(jd list)
    
    expected_output=$'Key                 Path\n'
    expected_output="$expected_output"$'-------             -------'

    expect_eq "$actual_output" "$expected_output"

    teardown_test
)

echo "Running integration tests..."
test_jd_list
test_jd
test_jd_add
test_jd_add_default
test_jd_default
test_jd_list_empty

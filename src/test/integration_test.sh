
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

    echo $'hej hoppsan\nman kan' >> $JD_CONFIG

    # Run command to test
    actual_output=$(jd list)

    expected_output=$'Key                 Path\n'
    expected_output="$expected_output"$'-------             -------\n'
    expected_output="$expected_output"$'hej                 hoppsan\n'
    expected_output="$expected_output"$'man                 kan'

    printf "Test ${FUNCNAME[0]}"
    if [ "$actual_output" ==  "$expected_output" ]; then
        printf $'\033[1;32m passed \033[0m\n'
    else
        printf $'\033[1;31m failed \033[0m\n'
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

    printf "Test ${FUNCNAME[0]}"
    if [ "$actual_dir" ==  "$expected_dir" ]; then
        printf $'\033[1;32m passed \033[0m\n'
    else
        printf $'\033[1;31m failed \033[0m\n'
    fi

    teardown_test
)

test_jd_add()
(
    setup_test

    expected_output="hejsan hoppsan"

    # Run command to test
    discard_output=$(jd add hejsan hoppsan)

    actual_output=$(jd list)

    printf "Test ${FUNCNAME[0]}"
    if [ "$actual_dir" ==  "$expected_dir" ]; then
        printf $'\033[1;32m passed \033[0m\n'
    else
        printf $'\033[1;31m failed \033[0m\n'
    fi

    teardown_test
)

test_jd_default()
(
    setup_test

    # Run command to test
    jd

    expected_dir=$HOME
    actual_dir=$PWD

    printf "Test ${FUNCNAME[0]}"
    if [ "$actual_dir" ==  "$expected_dir" ]; then
        printf $'\033[1;32m passed \033[0m\n'
    else
        printf $'\033[1;31m failed \033[0m\n'
    fi

    teardown_test
)

test_jd_list_empty()
(
    setup_test

    # Run command to test
    actual_output=$(jd list)
    
    expected_output=$'Key                 Path\n'
    expected_output="$expected_output"$'-------             -------'

    printf "Test ${FUNCNAME[0]}"
    if [ "$actual_output" ==  "$expected_output" ]; then
        printf $'\033[1;32m passed \033[0m\n'
    else
        printf $'\033[1;31m failed \033[0m\n'
    fi

    teardown_test
)

echo "Running integration tests..."
test_jd_list
test_jd
test_jd_add
test_jd_default
test_jd_list_empty

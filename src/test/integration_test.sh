
TEST_DIR="$(dirname "$(readlink -f "$0")")"

test_jd_list()
(
source /home/s0001191/repos/jump_dir/jump_dir.sh

JD_CONFIG="$TEST_DIR/test_config.config"

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
source /home/s0001191/repos/jump_dir/jump_dir.sh

JD_CONFIG="$TEST_DIR/test_config.config"

expected_dir="/home/s0001191/Pictures"

jd pictures

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

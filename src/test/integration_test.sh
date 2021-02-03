
TEST_DIR="$(dirname "$(readlink -f "$0")")"

test_jd_list()
(
source /home/s0001191/repos/jump_dir/jump_dir.sh

JD_CONFIG="$TEST_DIR/test_config.config"

expected_output=$'hej hoppsan\nman kan'

actual_output=$(jd list)

if [ "$actual_output" ==  "$expected_output" ]; then
    echo "Test test_jd_list passed"
else
    echo "Test test_jd_list failed"
fi
)

echo "Running integration tests..."
test_jd_list

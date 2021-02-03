
test_jd_list()
(
source /home/s0001191/repos/jump_dir/jump_dir.sh

JD_CONFIG="test_config.config"

expected_output=$'hej hoppsan\nman kan'

actual_output=$(jd list)

if [ "$actual_output" ==  "$expected_output" ]; then
    echo "test passed"
else
    echo "test failed"
fi
)

test_jd_list

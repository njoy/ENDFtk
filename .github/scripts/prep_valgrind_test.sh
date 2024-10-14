#! /bin/bash
echo "
check_return_code() {
        if [ \$? -ne 0 ]; then
                echo \"Memory leak detected. Test Failed...\"
                exit 1
        fi
} 

" > test_valgrind.sh

find . -iname "*.test" -type f | while IFS= read -r line; do
	dirname=$(dirname "$line")
	realname=$(basename "$line")
	echo "cd ${dirname}; valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=1 ./${realname}; check_return_code; cd -" >> test_valgrind.sh
done

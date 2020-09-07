#!/bin/bash

check_result() {
    local test_name=$1
    local test_result=$2
    outcomes=("PASS" "FAIL")
    printf "%s\t%s\n" $test_name ${outcomes[$test_result]}
}

run_test() {
    local test_name=$1

    ./masmbin tests/$test_name.asm test_results/$test_name.out
    diff -s -w tests/$test_name.golden test_results/$test_name.out > test_results/$test_name.test
    check_result $test_name $?
}

rm -rf test_results
mkdir -p test_results

test_names=("add" "and")

for t in ${test_names[@]}; do
    run_test $t
done

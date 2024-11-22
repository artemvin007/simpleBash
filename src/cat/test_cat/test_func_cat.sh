#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a test1=(
"VAR test_cat/test_case_cat.txt"
)

declare -a tests=(
"VAR test_cat/test_case_cat.txt test_cat/test_3_cat.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > test_s21_cat.log
    cat $t > test_sys_cat.log
    DIFF_RES="$(diff -s test_s21_cat.log test_sys_cat.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_cat.log and test_sys_cat.log are identical" ]
    then
      (( SUCCESS++ ))
        echo "failed: $FAIL succes: $SUCCESS count: $COUNTER success cat $t"
    else
      (( FAIL++ ))
        echo "failed: $FAIL succes: $SUCCESS count: $COUNTER fail cat $t"
    fi
    rm test_s21_cat.log test_sys_cat.log
}

for var1 in b e n s t
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

for var1 in b e n s t
do
    for i in "${test1[@]}"
    do
        var="-$var1"
        testing $i
    done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"

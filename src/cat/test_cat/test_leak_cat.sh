#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
RESULT=0
DIFF_RES=""

declare -a tests=(
"VAR test_cat/test_case_cat.txt"
"VAR test_cat/no_file.txt"
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    leaks -quiet -atExit -- ./s21_cat $t > test_s21_cat.log
    leak=$(grep -A100000 leaks test_s21_cat.log)
    (( COUNTER++ ))
    if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
    then
      (( SUCCESS++ ))
        echo "failed: $FAIL succes: $SUCCESS count: $COUNTER success cat $t"
    else
      (( FAIL++ ))
        echo "failed: $FAIL succes: $SUCCESS count: $COUNTER fail cat $t"
    fi
    rm test_s21_cat.log
}

# 1 параметр
for var1 in b e n s t
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"

FUNC_SUCCESS=0
FUNC_FAIL=0
COUNTER=0
DIFF=""

declare -a flags=(
"-i"
"-v"
"-c"
"-l"
"-n"
"-e"
)

declare -a files=(
#"s21_greptest1.txt"
"test_grep/s21_greptest1.txt test_grep/s21_greptest2.txt"
)

declare -a file1=(
#"s21_greptest1.txt"
"test_grep/s21_greptest1.txt"
)

for opt1 in "${flags[@]}"
    do
    for file in "${files[@]}"
    do
        options="$opt1 lorem $file "
        ./s21_grep $options > s21_grep_testing.log
        grep $options > system_grep_testing.log
        DIFF="$(diff -s s21_grep_testing.log system_grep_testing.log)"
        (( COUNTER++ ))
        if [ "$DIFF" == "Files s21_grep_testing.log and system_grep_testing.log are identical" ]
        then
            (( FUNC_SUCCESS++ ))
            echo "grep $options FUNCTIONALITY SUCCESS $COUNTER"
        else
            (( FUNC_FAIL++ ))
            echo "grep $options FUNCTIONALITY FAIL $COUNTER"
        fi
        rm s21_grep_testing.log system_grep_testing.log
    done
done

for opt1 in "${flags[@]}"
    do
    options="$opt1 lorem $file1"
    ./s21_grep $options > s21_grep_testing.log
    grep $options > system_grep_testing.log
    DIFF="$(diff -s s21_grep_testing.log system_grep_testing.log)"
    (( COUNTER++ ))
    if [ "$DIFF" == "Files s21_grep_testing.log and system_grep_testing.log are identical" ]
    then
        (( FUNC_SUCCESS++ ))
        echo "grep $options FUNCTIONALITY SUCCESS $COUNTER"
    else
        (( FUNC_FAIL++ ))
        echo "grep $options FUNCTIONALITY FAIL $COUNTER"
    fi
    rm s21_grep_testing.log system_grep_testing.log
done

echo "FAIL: $FUNC_FAIL"
echo "SUCCESS: $FUNC_SUCCESS"
echo "ALL: $COUNTER"
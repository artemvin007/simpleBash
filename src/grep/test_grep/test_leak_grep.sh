UCCESS=0
FAIL=0
COUNTER=0
LEAK=""

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
        leaks -quiet -atExit -- ./s21_grep $options > test_s21_grep.log
        LEAK=$(grep -A100000 leaks test_s21_grep.log)
        (( COUNTER++ ))
        if [[ $LEAK == *"0 leaks for 0 total leaked bytes"* ]]
        then
        (( SUCCESS++ ))
            echo "failed: $FAIL succes: $SUCCESS count: $COUNTER success grep $options"
        else
        (( FAIL++ ))
            echo "failed: $FAIL succes: $SUCCESS count: $COUNTER fail grep $options"
        fi
        rm test_s21_grep.log
    done
done

for opt1 in "${flags[@]}"
do
    options="$opt1 lorem $file1 "
    leaks -quiet -atExit -- ./s21_grep $options > test_s21_grep.log
    LEAK=$(grep -A100000 leaks test_s21_grep.log)
    (( COUNTER++ ))
    if [[ $LEAK == *"0 leaks for 0 total leaked bytes"* ]]
    then
    (( SUCCESS++ ))
        echo "failed: $FAIL succes: $SUCCESS count: $COUNTER success grep $options"
    else
    (( FAIL++ ))
        echo "failed: $FAIL succes: $SUCCESS count: $COUNTER fail grep $options"
    fi
    rm test_s21_grep.log
done

echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
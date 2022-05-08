set -e

while :
do
    python3 gen.py > data.in
    time ./fast.out < data.in > fast.ans
    time ./slow.out < data.in > slow.ans
    diff fast.ans slow.ans
    echo $?
done

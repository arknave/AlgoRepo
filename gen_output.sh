for input in data/secret/*.in; do
    output="${input%.in}.ans"
    echo "$input"
    python3 submissions/accepted/arknave.py < "$input" > "$output"
done

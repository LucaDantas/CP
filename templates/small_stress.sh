for i in $(seq 1 10); do echo "Running test ${i}..."; ./gen > gerador; ./sol < gerador > out1; ./slow < gerador > out2; diff -w out1 out2 || break ; done

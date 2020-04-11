for((i = 1; ; ++i)); do
	echo $i
	./gen $i > in2
	./arcoll < in2 > out1
	./comp < in2 > out2
	diff -w out1 out2 || break
done

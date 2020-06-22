#!/bin/bash

trap "trap - SIGTERM && kill -- -$$" SIGINT SIGTERM EXIT

if [ -z $1 ];
then
  echo "Please give problem name";
  exit 1;
fi;

p=$1;
gen=gen;
slow=slow;

shift;
if [ ! -z $1 ];
then
  n=$1;
  shift;
  if [ ! -z $1 ];
  then
    k=$1;
  else
    k=4;
  fi;
else
  n=10;
  k=4;
fi;

make "$p" & make "$gen" & make "$slow" & wait;

test=test;
mkdir -p ${test?};
rm test/*;

for t in $(seq 1 $n);
do
  test "$(jobs | wc -l)" -ge $k && wait -n || true;
  {
    echo "Running test $t...";

    input_gen=${test?}/${t?}_gen.in;
    out=${test?}/${t?}_$p.out;
    out_slow=${test?}/${t?}_slow.out;

    ./"$gen" > ${input_gen?};
    ./"$slow" < ${input_gen?} > ${out_slow?} & ./"$p" < ${input_gen?} > ${out?} & wait;
    if ! diff --brief --ignore-space-change ${out_slow?} ${out?} &>/dev/null;
    then
      echo [1m[31m"Test $t failed"[0m;
      exit 0;
    fi;
    rm ${input_gen?} ${out?} ${out_slow?};
    echo [1m[32m"Test $t passed"[0m;
  } &
done;

wait;

echo "Done";
exit 0;

#! /bin/sh

if [ $# -ne 1 ]; then
  echo "usage: $0 FILE";
  exit 1;
fi

INPUTFILE="$1"
OUTPUTFILE=`mktemp`

for c in $(seq 1 `grep -c "^processor" /proc/cpuinfo`); do
  echo "${c} threads:";

  echo "filter sharpen 3x3"
  for i in $(seq 1 10); do
    ./conv sharpen $c "$INPUTFILE" "$OUTPUTFILE" | grep "^convolution"
  done

  echo "filter unsharp 5x5"
  for i in $(seq 1 10); do
    ./conv unsharp $c "$INPUTFILE" "$OUTPUTFILE" | grep "^convolution"
  done

  echo -e "\n";
done

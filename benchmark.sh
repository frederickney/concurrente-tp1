#! /bin/sh

for c in $(seq 1 `grep -c "^processor" /proc/cpuinfo`); do
  echo "${c} threads:";

  for i in $(seq 1 10); do
    ./conv unsharp $c image.ppm image-out.ppm | grep "^convolution"
  done

  echo -e "\n";
done

#!/bin/bash

for i in {1..1000}; do
  echo "Iteration $i"
  ./flush_-O3
done

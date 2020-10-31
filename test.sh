#!/bin/bash
if [ "$#" -ne 1 ]
then
  echo "Must supply the tree root name"
  exit 1
fi
cd $1
for i in inputs/*
do
  echo "===================="
  echo "Testing: $i"
  echo "Output/Errors: "
	./bin/mail-in <$i
  echo "===================="
done


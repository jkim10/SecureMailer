#!/bin/bash
if [ "$#" -ne 1 ]
then
  echo "Must supply tree name"
  exit 1
fi
rm -rf "$1"
mkdir "$1"
cd $1
mkdir bin mail inputs tmp
while read p; do
  mkdir "./mail/$p"
done < ../mailbox_names.txt
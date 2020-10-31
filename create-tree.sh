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
declare -a arr=("addleness" "analects" "annalistic" "anthropomorphologically" "blepharosphincterectomy" "corector" "durwaun" "dysphasia" "encampment" "endoscopic" "exilic" "forfend" "gorbellied" "gushiness" "muermo" "neckar" "outmate" "outroll" "overrich" "philosophicotheological" "pockwood" "polypose" "refluxed" "reinsure" "repine" "scerne" "starshine" "unauthoritativeness" "unminced" "unrosed" "untranquil" "urushinic" "vegetocarbonaceous" "wamara" "whaledom")
for p in "${arr[@]}"
do
  mkdir "./mail/$p"
done
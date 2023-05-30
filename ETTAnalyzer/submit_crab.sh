#!/bin/bash

for i in {-6..6}
do
   {
   export DELAY=$i
   crab submit CrabConfig_12_3_0.py
   } &
done
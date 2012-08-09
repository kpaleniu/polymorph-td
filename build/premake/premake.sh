#!/bin/bash

TARGETS="gmake vs2010 xcode4"

for target in $TARGETS; do
	premake $target
done

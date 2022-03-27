#!/bin/bash

if (( $# == 1 ))
then
	diff ../../.pre_requisites pre_requisite_detectors/build-debug-text.c.test
	if (( $? != 0))
	then
		touch ../../.pre_requisites
		make -C ../../ $1
		cat pre_requisite_detectors/build-debug-text.c.test > ../../.pre_requisites
	else
		echo "Already \"made with debug.\""
	fi
else
	echo "ERROR: Please specify only one argument."
fi

#!/bin/bash


# https://stackoverflow.com/a/246128/16586661
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

if (( $# == 1 ))
then
	diff ${SCRIPT_DIR}/../../.pre_requisites ${SCRIPT_DIR}/pre_requisite_detectors/build-debug-text.c.test
	if (( $? != 0))
	then
		touch ../../.pre_requisites
		make -C ../../ $1
		cat ${SCRIPT_DIR}/pre_requisite_detectors/build-debug-text.c.test > ${SCRIPT_DIR}/../../.pre_requisites
	else
		echo "Already \"made with debug.\""
	fi
else
	echo "ERROR: Please specify only one argument."
fi

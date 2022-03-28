#!/bin/bash

# https://stackoverflow.com/a/246128/16586661
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

file_pre_requisites="${SCRIPT_DIR}/../../.pre_requisites"
file_build_debug_text="${SCRIPT_DIR}/pre_requisite_detectors/build-debug-text.c.test"

echo ${SCRIPT_DIR}

#pwd

diff $file_build_debug_text $file_pre_requisites
if (($? != 0))
then
	cat $file_build_debug_text > $file_pre_requisites
fi

#!/bin/bash

file_pre_requisites="../../.pre_requisites"
file_build_debug_text="pre_requisite_detectors/build-debug-text.c.test"

diff $file_build_debug_text $file_pre_requisites
if (($? != 0))
then
	cat $file_build_debug_text > $file_pre_requisites
fi

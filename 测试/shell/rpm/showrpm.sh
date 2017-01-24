#!/bin/bash

for rpm in $@; do
if [ -r $rpm ]; then
	echo "========== $rpm =========="
	rpm -qip $rpm
else
	echo "ERROR:cannot read file $rpm"
fi
done

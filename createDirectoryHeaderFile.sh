#!/bin/bash

script=${2:-$(pwd)/$0}

cd $1

fls=$(find . -maxdepth 1 -type f -not -name \. | grep -o [^/]*\.h$)
drs=$(find . -maxdepth 1 -type d -not -name \. | grep -o [^/]*$)

echo "$drs" | xargs -I %% $script %% $script

outFile=$1".h"
echo "Wrote \"$outFile\""

echo '#pragma once' > $outFile
echo '' >> $outFile
	echo "$drs" | xargs -I %% echo '#include "%%/%%.h"' >> $outFile
echo '' >> $outFile
	echo "$fls" | xargs -I %% echo '#include "%%"' >> $outFile

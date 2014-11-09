#!/bin/bash

outFile="ComponentEnums.h"
echo $outFile
echo '#pragma once' > $outFile
echo '' >> $outFile
echo 'enum ComponentType {' >> $outFile

componentTypes=$(find Nano/Components/ |
	egrep '\.h$' |
	xargs -I %% egrep -o 'class [a-zA-Z]+(? : public Component)' -- %% |
	egrep -o ' [^ ]+ :' |
	egrep -o '[a-zA-Z]+')

echo "$componentTypes" | xargs -I %% echo '%%,' >> $outFile
echo '};' >> $outFile

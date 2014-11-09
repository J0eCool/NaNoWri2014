#!/bin/bash

componentTypes=$(find Nano/Components/ |
	egrep '\.h$' |
	xargs -I %% egrep -o 'class [a-zA-Z]+ : public Component' -- %% |
	egrep -o ' [^ ]+ :' |
	egrep -o '[a-zA-Z]+')

outPath="Nano/Generated"
mkdir -p $outPath
outFile="$outPath/ComponentEnums.h"
echo '#pragma once' > $outFile
echo '' >> $outFile
echo '#include <string>' >> $outFile
echo '#include <map>' >> $outFile
echo '#include <Nano/Components/Components.h>' >> $outFile
echo '' >> $outFile

# echo 'enum ComponentType {' >> $outFile

# echo "$componentTypes" | xargs -I %% echo '	%%,' >> $outFile

# echo '};' >> $outFile
# echo '' >> $outFile

echo 'Component* CreateComponentWithName(std::string name) {' >> $outFile

echo "$componentTypes" | xargs -I %% echo '	if (name == "%%") { return new %%; }' >> $outFile

echo '	return nullptr;' >> $outFile
echo '}' >> $outFile
echo '' >> $outFile

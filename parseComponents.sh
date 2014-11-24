#!/bin/bash

componentTypes=$(find Nano/ |
	egrep '\.h$' |
	xargs -I %% egrep -o 'class [a-zA-Z]+ : public Component' -- %% |
	egrep -o ' [^ ]+ :' |
	egrep -o '[a-zA-Z]+')

outPath="Nano/Generated"
mkdir -p $outPath



outFile="$outPath/ComponentEnums.h"

echo '#pragma once' > $outFile
echo '' >> $outFile
echo '#include <Nano/Engine/Util/Util.h>' >> $outFile
echo '#include <typeinfo>' >> $outFile
echo '' >> $outFile
echo 'enum ComponentType {' >> $outFile
echo '	CT_INVALID,' >> $outFile
	echo "$componentTypes" | xargs -I %% echo '	CT_%%,' >> $outFile
echo '	CT_COUNT,' >> $outFile
echo '};' >> $outFile
echo '' >> $outFile
echo 'class Component;' >> $outFile
echo '' >> $outFile
echo 'ComponentType GetComponentType(const std::type_info *type);' >> $outFile
echo 'ComponentType GetComponentType(String name);' >> $outFile
echo 'Component* CreateComponentWithName(String name);' >> $outFile
echo 'Component* CloneComponentWithType(Component* base, ComponentType type);' >> $outFile



outFile="$outPath/ComponentEnums.cpp"

echo '#include "ComponentEnums.h"' > $outFile
echo '' >> $outFile
echo '#include <Nano/Engine/Util/Util.h>' >> $outFile
echo '#include <Nano/Components/Components.h>' >> $outFile
echo '' >> $outFile
echo 'ComponentType GetComponentType(const std::type_info *type) {' >> $outFile
	echo "$componentTypes" | xargs -I %% echo '	if (type == &typeid(%%)) { return CT_%%; }' >> $outFile
echo '	return CT_INVALID;' >> $outFile
echo '}' >> $outFile
echo '' >> $outFile
echo 'ComponentType GetComponentType(String name) {' >> $outFile
	echo "$componentTypes" | xargs -I %% echo '	if (name == "%%") { return CT_%%; }' >> $outFile
echo '	return CT_INVALID;' >> $outFile
echo '}' >> $outFile
echo '' >> $outFile
echo 'Component* CreateComponentWithName(String name) {' >> $outFile
	echo "$componentTypes" | xargs -I %% echo '	if (name == "%%") { return new %%; }' >> $outFile
echo '	return nullptr;' >> $outFile
echo '}' >> $outFile
echo '' >> $outFile
echo 'Component* CloneComponentWithType(Component* base, ComponentType type) {' >> $outFile
echo '	Component *cmp = nullptr;' >> $outFile
	echo "$componentTypes" | xargs -I %% echo '	if (type == CT_%%) { cmp = new %%; memcpy(cmp, base, sizeof(%%)); }' >> $outFile
echo '	return cmp;' >> $outFile
echo '}' >> $outFile

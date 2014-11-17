#!/bin/bash

componentTypes=$(find Nano/ |
	egrep '\.h$' |
	xargs -I %% egrep -o 'class [a-zA-Z]+ : public Component' -- %% |
	egrep -o ' [^ ]+ :' |
	egrep -o '[a-zA-Z]+')

files=$(echo "$componentTypes" | xargs -I %% find Nano/ -name "%%.h")

parseLoadArgs () {
	class=$(basename $1 | grep -o '^[^\.]*')
	line=$(grep '//\$\$' "$1" | grep -o '[^/$]*$')
	if [ ! -z "$line" ]; then
		echo ""
		echo "void $class::Load(std::vector<std::string> const& args) {"
		IFS='|' read -ra args <<< "$line"
		argn=0
		for i in "${args[@]}"; do
			IFS=':' read -ra kv <<< "$i"
			echo "	${kv[0]} = Parse${kv[1]}(args[$argn]);"
			let "argn += 1"
		done
		echo "}"
	fi
}
export -f parseLoadArgs

outFile="Nano/Generated/ComponentLoading.cpp"

echo "#include <Nano/Components/Components.h>" > $outFile
echo "#include <Nano/Engine/Engine.h>" >> $outFile
echo "$files" | xargs -I %% bash -c 'parseLoadArgs %%' >> $outFile

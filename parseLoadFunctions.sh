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
		echo "void $class::LoadArg(std::string const& key, std::string const& val) {"
		IFS='|' read -ra args <<< "$line"
		startElse=""
		for i in "${args[@]}"; do
			IFS=':' read -ra kv <<< "$i"
			key="${kv[0]}"
			stripKey=$(echo "$key" | grep -o '[^_]*')
			line="if (key == \"$stripKey\") { $key = Parse${kv[1]}(val); }"
			[ ! -z "$startElse" ] && line="else $line"
			startElse="yeah"
			echo "	$line"
		done
		echo "	else { Log(\"ERROR: $class: Invalid argument: Key=\", key, \", Val=\", val); }"
		echo "}"
	fi
}
export -f parseLoadArgs

outFile="Nano/Generated/ComponentLoading.cpp"
echo "Wrote \"$outFile\""

echo "#include <Nano/Components/Components.h>" > $outFile
echo "#include <Nano/Engine/Engine.h>" >> $outFile
echo "$files" | xargs -I %% bash -c 'parseLoadArgs %%' >> $outFile

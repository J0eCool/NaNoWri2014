#!/bin/bash

find . | egrep '\.(h|cpp)$' | xargs cat | wc -l

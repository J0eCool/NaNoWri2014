#!/bin/bash

cd Nano/
drs=$(find . -maxdepth 1 -type d -not -name \. | grep -o [^/]*$)

echo "$drs" | xargs -I %% ../createDirectoryHeaderFile.sh %%

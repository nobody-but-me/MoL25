
#!/usr/bin/env bash

if [ "$(type -t ./build/bin/mol)" = "file" ]; then
    echo -e "\n[INFO]: RUNNING..."
    
    cd ./build/bin/
    
    ./mol
    
    cd ..
else
    echo -e "[ERROR]: COULD NOT RUN ENGINE: EXECUTABLE DOES NOT EXIST OR HAS SOME ERROR. \n"
fi

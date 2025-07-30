
#!/usr/bin/env bash

echo -e "[CONFIG]: Are you generating ninja files? (y or n)(DEFAULT: n)"
read -p " > " build
echo -e "[CONFIG]: Do you want to run the project right after building it? (y or n)(DEFAULT: y)"
read -p " > " run

echo -e "[INFO]: CREATING BUILD FOLDER..."
mkdir -p ./build && cd ./build

if [ "$build" = "y" ]; then
    echo -e "[INFO]: GENERATING NINJA FILES..."
    cmake .. -G Ninja
fi

echo -e "[INFO]: BUILDING..."
ninja

cd ..

if  [ "$run" != "n" ]; then
    echo -e "\n--------------------------------------------------"
    ./run.sh
fi


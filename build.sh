
#!/usr/bin/env bash

echo -e "[CONFIG]: Are you generating ninja files? (DEFAULT: n)"
read -p "    (y or n): " build
echo -e "[CONFIG]: Do you want to run the project right after building it? (DEFAULT: y)"
read -p "    (y or n): " run

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


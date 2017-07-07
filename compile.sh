#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "This script must be run as root."
  exit
fi

base_dir=$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)

if [[ $1 == "--release" ]]; then
  build_type=Release
else
  build_type=Debug
fi

# Build the infrastructure code
mkdir -p $base_dir/bin/main-computer/infrastructure
cd $base_dir/bin/main-computer/infrastructure
cmake -DCMAKE_BUILD_TYPE=$build_type $base_dir/src/main-computer/infrastructure && make

# Make the cognition script symlink in bin, since it's interpreted
mkdir -p $base_dir/bin/main-computer/cognition
ln -sf $base_dir/src/main-computer/cognition/main.py $base_dir/bin/main-computer/cognition/cognition.py

# Build and load the microcontroller code
cd $base_dir/src/microcontroller
mkdir -p $base_dir/bin/microcontroller
rm -f $base_dir/bin/microcontroller/code.*
make OUTPUT=$base_dir/bin/microcontroller && make up OUTPUT=$base_dir/bin/microcontroller


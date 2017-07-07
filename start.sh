#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "This script must be run as root."
  exit
fi

cd $(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)

echo "Starting..."

bin/main-computer/infrastructure/infrastructure &
python bin/main-computer/cognition/cognition.py &

echo "Running."

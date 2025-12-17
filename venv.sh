#!/bin/bash

ESPHOME_CACHE_VIRTUAL=~/.cache/esphome/
ESPHOME_CACHE=$(readlink -f $ESPHOME_CACHE_VIRTUAL)
ESPHOME_VENV="$ESPHOME_CACHE/venv"
ESPHOME_BUILD_PATH="$ESPHOME_CACHE/build"

python_bin="python3"

if [[ ! -f  "$ESPHOME_VENV/bin/activate" ]]; then
    "$python_bin" -m pip install --upgrade virtualenv
    "$python_bin" -m virtualenv "$ESPHOME_VENV"
fi

# shellcheck source=/home/marcel/.cache/esphome/venv/bin/activate
source "${ESPHOME_VENV}/bin/activate"
(
    cd produktion || return
    rm ../include
    ln -s include ../include
    cd ..
)

ESPHOME_VERSION=$("$python_bin" -m esphome --version | awk '{print $2}')
echo "ESPhome version: $ESPHOME_VERSION"

#"$python_bin" -m pip install --upgrade "esphome>=2025.11.1" pip cairosvg "ruamel.yaml.clib>=0.2.14"
"$python_bin" -m pip install --upgrade "esphome==2025.11.5" pip cairosvg
#export ESPHOME_BUILD_PATH

echo "Use virtual evironment at: $ESPHOME_VENV"
#echo "Set buildpath for esphome to: $ESPHOME_BUILD_PATH"

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then

  export ESPHOME_BUILD_PATH
  export ESPHOME_VENV
  export ESPHOME_CACHE

  ESPHOME_NEW_VERSION=$("$python_bin" -m esphome --version | awk '{print $2}')
  if [ "$ESPHOME_VERSION" != "$ESPHOME_NEW_VERSION" ]; then
    echo "ESPhome was updated to version: $ESPHOME_NEW_VERSION"
    echo "Cleaning all builds and pio..."
    "$python_bin" -m esphome clean-all
  fi

  if [ -z "$1" ]; then
    bash
  else
    "$python_bin" -m esphome "$@"
  fi
fi
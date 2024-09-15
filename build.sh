set -e

export ROOT_DIR=$(pwd)
export BIN_DIR=$ROOT_DIR/bin

mkdir -p $BIN_DIR
cd $BIN_DIR
cmake ../
cmake --build .
cpack .

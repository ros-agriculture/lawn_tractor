# A docker build script. Run this from one directory above the directory this script is in (in other words, the root of the lawn_tractor repo)
git submodule update --init --recursive
docker build . -t rosagriculture/lawn_tractor:latest

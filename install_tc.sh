#!/bin/bash
echo "Installing tools for the gcc cross compiler" \
     "https://wiki.wxwidgets.org/Cross-Compiling_Under_Linux"


echo "##################### git submodule ######################"
git submodule update --recursive

echo "################# Install prerequisites ##################"
#sudo apt-get -y install gcc gperf bison flex gawk  libtool automake libncurses5-dev texinfo

echo "##################### cross-ng ######################"
# instructions from https://github.com/crosstool-ng/crosstool-ng
cd toolchain/crosstool-ng
./bootstrap
./configure --prefix=$HOME/.local
 make -j && make install

echo -ne "\n\nif [ -d \"$HOME/.local/bin\" ]; then\n    PATH=\"$HOME/.local/bin:$PATH\"\nfi" >> ~/.profile
source ~/.profile

ct-ng list-samples
echo "Go To compiler and choose 4.8"
ct-ng x86_64-w64-mingw32 menuconfig
echo "echo installing and downloading lasts 40 minutes"
ct-ng build # lasts 40 minutes...

export PATH="${PATH}:${HOME}/x-tools/x86_64-w64-mingw32/bin"

echo "##################### Flex ######################"
cd ../flex/
sh autogen.sh
./configure ./configure --host=x86_64-w64-mingw32 --prefix=$home/x-tools
make -j

echo "##################### Bison 3.0.4 ######################"
cd ..
wget http://ftp.gnu.org/gnu/bison/bison-3.0.4.tar.xz && tar -xf bison-3.0.4.tar.xz
rm -f bison-3.0.4.tar.xz
cd bison-3.0.4 && ./configure --host=x86_64-w64-mingw32 --prefix=$home/x-tools
make -j


echo "##################### WxWidgets ######################"
cd ../wxWidgets/
mkdir wxwidgets_mingw && cd wxwidgets_mingw && ../configure --host=x86_64-w64-mingw32 --disable-shared --enable-unicode --target=x86_64-w64-mingw32 
 && make -j

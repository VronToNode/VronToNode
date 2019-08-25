#!/bin/bash
# create multiresolution windows icon
#mainnet
ICON_SRC=../../src/qt/res/icons/vrontonode.png
ICON_DST=../../src/qt/res/icons/vrontonode.ico
convert ${ICON_SRC} -resize 16x16 vrontonode-16.png
convert ${ICON_SRC} -resize 32x32 vrontonode-32.png
convert ${ICON_SRC} -resize 48x48 vrontonode-48.png
convert vrontonode-16.png vrontonode-32.png vrontonode-48.png ${ICON_DST}
#testnet
ICON_SRC=../../src/qt/res/icons/vrontonode_testnet.png
ICON_DST=../../src/qt/res/icons/vrontonode_testnet.ico
convert ${ICON_SRC} -resize 16x16 vrontonode-16.png
convert ${ICON_SRC} -resize 32x32 vrontonode-32.png
convert ${ICON_SRC} -resize 48x48 vrontonode-48.png
convert vrontonode-16.png vrontonode-32.png vrontonode-48.png ${ICON_DST}
rm vrontonode-16.png vrontonode-32.png vrontonode-48.png

#!/bin/bash

set -e

# Set your target directories
FFMPEG_DIR="$HOME/goinfre/ffmpeg_build"
mkdir -p "$FFMPEG_DIR"

# Versions
FFMPEG_VERSION="6.1.1"

# Clean old sources
rm -rf "$HOME/goinfre/ffmpeg_build"
mkdir "$HOME/goinfre/ffmpeg_build"
cd "$HOME/goinfre/ffmpeg_build"


cd "$HOME/goinfre/ffmpeg_build"
echo "==> Downloading and building FFmpeg..."
curl -LO https://ffmpeg.org/releases/ffmpeg-$FFMPEG_VERSION.tar.gz
tar xzf ffmpeg-$FFMPEG_VERSION.tar.gz
cd ffmpeg-$FFMPEG_VERSION

./configure \
  --prefix="$FFMPEG_DIR" \
  --pkg-config-flags="--static" \
  --extra-libs="-lpthread -lm" \
  --enable-nonfree \
  --enable-gpl \
  --disable-debug \
  --disable-doc \
  --enable-static \
  --disable-shared \
  --disable-programs \
  --enable-shared

make -j$(nproc)
make install

echo "✅ Done! FFmpeg  installed."


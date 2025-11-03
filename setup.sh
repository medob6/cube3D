#!/bin/bash

set -e

# Set your target directories
OPENSSL_DIR="$HOME/goinfre/openssl"
FFMPEG_DIR="$HOME/goinfre/ffmpeg_build"
mkdir -p "$OPENSSL_DIR" "$FFMPEG_DIR"

# Versions
OPENSSL_VERSION="1.1.1w"
FFMPEG_VERSION="6.1.1"

# Clean old sources
rm -rf /tmp/ffmpeg_build
mkdir /tmp/ffmpeg_build
cd /tmp/ffmpeg_build

echo "==> Downloading and building OpenSSL..."
curl -LO https://www.openssl.org/source/openssl-$OPENSSL_VERSION.tar.gz
tar xzf openssl-$OPENSSL_VERSION.tar.gz
cd openssl-$OPENSSL_VERSION

./Configure linux-x86_64 --prefix=$OPENSSL_DIR no-shared no-tests
make -j$(nproc)
make install_sw  # installs headers, libs, and pkgconfig

# Export pkg-config path
export PKG_CONFIG_PATH="$OPENSSL_DIR/lib/pkgconfig"
export LD_LIBRARY_PATH="$OPENSSL_DIR/lib:$LD_LIBRARY_PATH"

cd /tmp/ffmpeg_build
echo "==> Downloading and building FFmpeg..."
curl -LO https://ffmpeg.org/releases/ffmpeg-$FFMPEG_VERSION.tar.gz
tar xzf ffmpeg-$FFMPEG_VERSION.tar.gz
cd ffmpeg-$FFMPEG_VERSION

./configure \
  --prefix="$FFMPEG_DIR" \
  --pkg-config-flags="--static" \
  --extra-cflags="-I$OPENSSL_DIR/include" \
  --extra-ldflags="-L$OPENSSL_DIR/lib" \
  --extra-libs="-lpthread -lm" \
  --enable-openssl \
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

echo "✅ Done! FFmpeg and OpenSSL installed."


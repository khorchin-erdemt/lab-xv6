FROM debian:trixie-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN rm -f /etc/apt/sources.list.d/debian.sources && cat <<EOF > /etc/apt/sources.list
deb http://mirrors.huaweicloud.com/debian/ trixie main contrib non-free non-free-firmware
deb-src http://mirrors.huaweicloud.com/debian/ trixie main contrib non-free non-free-firmware
deb http://mirrors.huaweicloud.com/debian/ trixie-updates main contrib non-free non-free-firmware
deb-src http://mirrors.huaweicloud.com/debian/ trixie-updates main contrib non-free non-free-firmware
deb http://mirrors.huaweicloud.com/debian/ trixie-backports main contrib non-free non-free-firmware
deb-src http://mirrors.huaweicloud.com/debian/ trixie-backports main contrib non-free non-free-firmware
deb http://mirrors.huaweicloud.com/debian-security trixie-security main contrib non-free non-free-firmware
deb-src http://mirrors.huaweicloud.com/debian-security trixie-security main contrib non-free non-free-firmware
EOF

RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential clang-format gcc-riscv64-linux-gnu gdb-multiarch git python3 qemu-system && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

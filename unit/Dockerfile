FROM archlinux

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm reflector
RUN reflector --sort rate --connection-timeout 1 --save /etc/pacman.d/mirrorlist --score 5
RUN pacman -S --noconfirm eigen
RUN pacman -S --noconfirm git
RUN pacman -S --noconfirm base-devel
RUN pacman -S --noconfirm opencv
RUN pacman -S --noconfirm spdlog
RUN pacman -S --noconfirm qt6-base
RUN pacman -S --noconfirm sudo
RUN pacman -S --noconfirm libxkbcommon
RUN pacman -S --noconfirm libx11
RUN cd /opt && git clone --recursive https://github.com/stevenlovegrove/Pangolin
RUN pacman -S --noconfirm cmake glew eigen libjpeg libpng openexr libtiff ffmpeg lz4 zstd catch2 libdc1394
RUN pacman -S --noconfirm wayland-protocols
RUN cd /opt/Pangolin && mkdir build && cd build && cmake .. && cmake --build .

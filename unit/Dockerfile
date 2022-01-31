FROM archlinux

RUN pacman -S eigen git base-devel opencv spdlog qt6-base -y
RUN cd /opt/ && git clone https://aur.archlinux.org/pangolin-git.git && cd pangolin-git && makepkg -si -y


FROM ubuntu

ENV TZ=America/Los_Angeles
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update
RUN apt-get install libeigen3-dev git libopencv-dev libspdlog-dev --no-install-recommends -y

RUN apt-get --no-install-recommends install -y ca-certificates
RUN git clone --recursive https://github.com/stevenlovegrove/Pangolin.git
RUN apt-get install -y libgl1-mesa-dev libwayland-dev libxkbcommon-dev wayland-protocols libegl1-mesa-dev libc++-dev libglew-dev libeigen3-dev cmake libjpeg-dev libpng-dev libavcodec-dev libavutil-dev libavformat-dev libswscale-dev libavdevice-dev --no-install-recommends
RUN apt-get install -y build-essential libcurl4-openssl-dev --no-install-recommends
RUN cd Pangolin && mkdir build && cd build && \ 
    cmake .. && \
    cmake --build .

# syntax=docker/dockerfile:1.4

## README: 
# docker build -t fuzix:rpipico .
#
# Running the build container:
# `docker run fuzix:rpipico`
# This is the minimum command needed to build fuzix for Pi Pico at this point
# but this will only be useful to prove that this image can, no mounted volumes
# means no easy way to get the build out.
# 
# Instead I recommend:
# `docker run -v $(pwd):/workspace/FUZIX fuzix:rpipico`
# Which will use the current working directory (presumably a git repo of FUZIX)
# as the volume that this container will use for the build root.
# Thus, the container will build within your local repo and artifacts will
# all be local.
# 
# To debug your docker-based build environment:
# `docker run -it -v $(pwd):/workspace/FUZIX fuzix:rpipico /bin/bash`
# Will drop you into a shell in the container.
# 

FROM ubuntu:24.10

RUN <<EOF
apt-get update
apt upgrade -y
apt-get install -y \
    git \
    build-essential \
    byacc \
    gcc-arm-none-eabi \
    cmake \
    python3

update-alternatives --set yacc /usr/bin/byacc
mkdir -p /workspace
cd /workspace;
mkdir -p /workspace

if [ ! -d "FUZIX" ]; then
    echo "FUZIX directory does not exist. Cloning..."
    git clone https://github.com/EtchedPixels/FUZIX.git
elif [ -z "$(ls -A FUZIX)" ]; then
    echo "FUZIX directory is empty. Cloning..."
    rm -rf FUZIX  # Ensure we remove the empty directory before cloning
    git clone https://github.com/EtchedPixels/FUZIX.git
else
    echo "FUZIX directory already exists and is not empty. Skipping clone."
fi
EOF

WORKDIR /workspace/FUZIX

# We make to prove that we now can.
#    ... it also 'caches' the pi-sdk that's auto-downloaded if missing.
RUN make TARGET=rpipico
# We clean to clear out our build
# Commented out so I can build once and speed up my life.
# RUN make clean
# Only porcelain if you want to break builds on dirty cleans.
RUN git status #--porcelain
# Removing `n` will actually clear the repo
#   - good for distributing images, bummer for local builds
#   ... and since I'm not distributing images, it stays.
RUN git clean -fdn

# Set the default command but allow overriding it
ENTRYPOINT ["/bin/bash", "-c", "make TARGET=rpipico"]

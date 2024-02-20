# Use the base image with essential packages
FROM archlinux:base-devel

ARG TOOLS_PATH=/opt/gcc-arm-none-eabi
ARG ARM_VERSION=12.3.rel1

# Install necessary packages
RUN pacman -Syu --noconfirm --needed \
  base-devel \
  make cmake ninja \
  git gnupg \
  python \
  python-pip \
  python-virtualenv  # Ensure virtualenv is installed

# Create and activate a virtual environment
# Using /opt/venv for the virtual environment location
RUN python -m virtualenv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

# Install compiledb in the virtual environment
RUN pip install compiledb

# Get ARM Toolchain
RUN mkdir -p ${TOOLS_PATH} \
    && curl -Lo gcc-arm-none-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/${ARM_VERSION}/binrel/arm-gnu-toolchain-${ARM_VERSION}-x86_64-arm-none-eabi.tar.xz" \
    && tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C ${TOOLS_PATH} \
    && rm gcc-arm-none-eabi.tar.xz \
    && rm ${TOOLS_PATH}/*.txt \
    && rm -rf ${TOOLS_PATH}/share/doc

# Add Toolchain to PATH
ENV PATH="$PATH:${TOOLS_PATH}/bin"

# Set the working directory
WORKDIR /project

# Copy your project files into the container
COPY . .

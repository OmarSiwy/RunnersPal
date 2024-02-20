#!/bin/bash
install_st_flash_mac() {
    # Check if Homebrew is installed
    if ! command -v brew &> /dev/null; then
        echo "Homebrew not found, installing now..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi

    # Install st-flash using Homebrew
    echo "Installing st-flash using Homebrew..."
    brew install stlink
}

flash_elf() {
    ELF_FILE="./build/PathRememberingRobot.bin" # Update this path to your .elf file

    if [ ! -f "$ELF_FILE" ]; then
        echo "Error: ELF file not found at $ELF_FILE"
        exit 1
    fi

    echo "Flashing $ELF_FILE to the device..."
    st-flash --connect-under-reset --reset write "$ELF_FILE" 0x8000000
}

# Detect the OS
OS="`uname`"
case $OS in
  'Linux')
    OS='Linux'
    echo "Detected Linux"
    # Run Docker to build and flash
    docker-compose up build-and-flash
    ;;
  'Darwin') 
    OS='macOS'
    echo "Detected macOS"
    # Run Docker to build only
    docker-compose up build-only
    # Check if st-flash is installed
    if ! command -v st-flash &> /dev/null; then
        install_st_flash_mac
    fi
    # Flash the .elf file
    flash_elf
    ;;
  *) ;;
esac

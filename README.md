# hasher-cli

A simple command-line tool that calculates the SHA-256 hash of files using the OpenSSL EVP API.

## Requirements

This program requires the OpenSSL development headers to be installed on your system.
Debian / Ubuntu / Mint (APT)

sudo apt install libssl-dev

Fedora / RHEL / CentOS (DNF)

sudo dnf install openssl-devel

Arch Linux / Manjaro (Pacman)

sudo pacman -S openssl

## Build

To compile the program, simply run:

make

## Usage

Provide the path to the file you want to hash as an argument:

./hasher-cli <filename>

## Example

./hasher-cli image.png

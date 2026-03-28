# Use the official CachyOS base image
FROM cachyos/cachyos:latest

# Initialize keys and install IDE agent dependencies
# MARK: Added ca-certificates to fix connection issues and paru for AUR support
RUN pacman-key --init && \
    pacman-key --populate archlinux cachyos && \
    pacman -Sy --noconfirm cachyos-keyring archlinux-keyring && \
    pacman -Syu --noconfirm && \
    pacman -S --noconfirm \
    # IDE Agent Essentials:
    git tar openssh nodejs npm \
    # Basic build tools (needed for agent extensions):
    base-devel \
    # Your requested tools:
    # MARK: Added ca-certificates here for SSL/TLS connectivity
    fish sudo binutils grep wget ca-certificates paru \
    gperf cmake python3 python-pip 

# MARK: Commented out 'espdev' to replace with requested 'espidf' account
# RUN useradd -m -G wheel -s /usr/bin/fish espdev
RUN useradd -m -G wheel -s /usr/bin/fish espidf

# MARK: Commented out 'espdev' password removal to apply to 'espidf'
# RUN passwd -d espdev
RUN passwd -d espidf

# Ensure the wheel group can use sudo without a password
RUN echo "%wheel ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/wheel

# MARK: Added execution of paru to install 'eim'. 
# This is run as the 'espidf' user because paru (and its build process) should not run as root.
RUN sudo -u espidf paru -S --noconfirm eim

# Switch to the new user
# USER espdev   <-- Commented out old user
USER espidf
# ENV USER=espdev <-- Commented out old env
ENV USER=espidf
# ENV HOME=/home/espdev <-- Commented out old env
ENV HOME=/home/espidf
# WORKDIR /home/espdev <-- Commented out old path
WORKDIR /home/espidf

# Start with fish shell
CMD ["/usr/bin/fish"]
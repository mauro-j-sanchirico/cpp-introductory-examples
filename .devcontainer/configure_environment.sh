# =============================================================================
# configure_environment.sh
#
# Description:
#
# Configuration script to set up a development environment with basic C++ and
# Python tooling.
#
# Usage:
#
# bash ./configure_environment.sh
#
# =============================================================================

# ===================
# Basic configuration
# ===================

source .devcontainer/user_info.sh

# ==========================
# Basic package installation
# ==========================

echo "Installing basic packages..."

sudo apt-get -y update \
&& sudo DEBIAN_FRONTEND=noninteractive apt-get install -yq curl vim git npm lshw build-essential make cmake gdb valgrind cppcheck \
&& sudo apt-get clean

if [ $? -eq 0 ]; then
    echo "Basic packages installed!"
else
    echo "Failed to install basic packages."
    exit 1
fi

# ===================
# Python installation
# ===================

echo "Installing Python..."

sudo apt update && sudo apt upgrade -y \
&& sudo apt install software-properties-common -y \
&& sudo add-apt-repository ppa:deadsnakes/ppa -y \
&& sudo apt update \
&& sudo apt install -y python3.12 python3.12-venv python3.12-dev \
&& sudo apt install -y python3-pip

if [ $? -eq 0 ]; then
    echo "Python installed!"
else
    echo "Failed to install Python."
    exit 1
fi

echo "Linking pip to pip3..."
sudo update-alternatives --install /usr/bin/pip pip /usr/bin/pip3 1

echo "Linking python3 to Python3.12..."
python3_location="/usr/bin/python3"
python312_location="/usr/bin/python3.12"
sudo update-alternatives --install "$python3_location" python3 "$python312_location" 1 \
&& sudo update-alternatives --set python3 "$python312_location"

# ==========================
# Permissions configuration
# ==========================

echo "Changing ownership of user files in workspace to user group..."

find . \
    -mindepth 1 -maxdepth 1 \
    -type f \
    -exec chown "$user_name":"$group_name" {} ';' \
&& find . \
    -mindepth 1 -maxdepth 1 -type d \
    -not \( -name '.venv' -o -name '.git' -o -name '.devcontainer' \) \
    -exec chown -R "$user_name":"$group_name" {} ';'

if [ $? -eq 0 ]; then
    echo "Success!"
else
    echo "Failed to change ownership."
    exit 1
fi

echo "Changing ownership of .git files to user group..."

git_ownership_command="sudo chown -R $user_name:$group_name .git"
if git_ownership_command; then
    echo "Successfully changed ownership of .git files"
else
    echo "Failed to change ownership of .git files. This is likely due to the"
    echo "permissions configuration of the host machine. One the host machine,"
    echo "open permissions on .git in the host machine using:"
    echo "chmod -R 755 .git"
fi

# ==========================
# Extra package installation
# ==========================

# Install extra packages needed here

# =====================
# Account configuration
# =====================

echo "Getting convenient bash shortcuts..."

add_aliases() {
    touch $developer_home/.bashrc
    file_name=$(basename "$1")
    curl -o "$developer_home/$file_name" $1
    echo "source $developer_home/$file_name" >> "$developer_home/.bashrc"
}

add_aliases $command_line_aliases_file
add_aliases $git_aliases_file
add_aliases $poetry_aliases_file

echo "source $developer_home/.bashrc" >> "$developer_home/.bash_profile"
echo "source $developer_home/.bashrc" >> "$developer_home/.profile"

# ===================
# Poetry installation
# ===================

echo "Installing Poetry..."

poetry_install_command="curl -sSL https://install.python-poetry.org | python3 -"
bash -c "$poetry_install_command"

if "$poetry_command" --version &>/dev/null; then
    echo "Poetry installed!"
else
    echo "Failed to install Poetry."
fi

echo "Adding Poetry to path..."

echo "export PATH=\"$developer_home/$poetry_dir:\$PATH\"" >> $developer_home/.bashrc

# ===============
# Status messages
# ===============

echo "Success!"
exit 0
#!/bin/bash
clear

# Create logs directory if it doesn't exist
mkdir -p logs

# Generate timestamped log filename
TIMESTAMP=$(date +"%Y%m%d_%H%M%S")
LOG_DIR="logs"

# Function to check if pwndbg is installed
check_pwndbg() {
    if [ -d "$HOME/.gdbinit-pwndbg" ] || [ -f "$HOME/.gdbinit.d/pwndbg" ] || grep -q "pwndbg" "$HOME/.gdbinit" 2>/dev/null; then
        echo "Using pwndbg for enhanced debugging..."
        PWNDBG_INSTALLED=1
    else
        echo "pwndbg not detected, using standard gdb..."
        PWNDBG_INSTALLED=0
    fi
}

# Function to check if valgrind is installed
check_valgrind() {
    if command -v valgrind &> /dev/null; then
        echo "Valgrind is available for memory debugging..."
        VALGRIND_INSTALLED=1
    else
        echo "Valgrind not detected. Install with 'sudo dnf install valgrind' (Fedora) or 'sudo apt install valgrind' (Ubuntu)"
        VALGRIND_INSTALLED=0
    fi
}

# Function to launch gdb with appropriate flags and log output
launch_gdb() {
    local binary=$1
    local log_file="${LOG_DIR}/gdb_${TIMESTAMP}_$(basename ${binary}).log"
    local history_file="${LOG_DIR}/gdb_history_${TIMESTAMP}_$(basename ${binary})"
    
    echo "GDB output will be saved to: ${log_file}"
    echo "GDB history will be saved to: ${history_file}"
    
    # Create GDB script for logging
    local gdb_script="${LOG_DIR}/gdb_script_${TIMESTAMP}.gdb"
    echo "set logging on ${log_file}" > "$gdb_script"
    echo "set logging redirect on" >> "$gdb_script"
    echo "set pagination off" >> "$gdb_script"
    echo "set history filename ${history_file}" >> "$gdb_script"
    echo "set history save on" >> "$gdb_script"
    
    # Run GDB with script
    if [ "$PWNDBG_INSTALLED" -eq 1 ]; then
        # For pwndbg, we'll use a different approach due to its interactive nature
        # We'll use tee to capture the output while still allowing interactive use
        script -q -c "gdb -q -x $gdb_script $binary" /dev/null | tee "$log_file"
    else
        script -q -c "gdb -x $gdb_script $binary" /dev/null | tee "$log_file"
    fi
    
    echo "Debug session logged to ${log_file}"
    echo "GDB command history saved to ${history_file}"
}

# Function to launch valgrind with appropriate options and log output
launch_valgrind() {
    local binary=$1
    local log_file="${LOG_DIR}/valgrind_${TIMESTAMP}_$(basename ${binary}).log"
    local valgrind_options="--leak-check=full --show-leak-kinds=all -s --track-origins=yes --log-file=${log_file}"
    
    echo "Valgrind output will be saved to: ${log_file}"
    
    # Run valgrind with output to both console and log file
    valgrind $valgrind_options "$binary" 2>&1 | tee -a "$log_file"
    
    echo "Valgrind session logged to ${log_file}"
}

# Function to run custom command with logging
run_custom_command() {
    local cmd=$1
    local log_file="${LOG_DIR}/custom_${TIMESTAMP}.log"
    
    echo "Command output will be saved to: ${log_file}"
    
    # Run the command and tee output to log file
    eval "$cmd" 2>&1 | tee "$log_file"
    
    echo "Command output logged to ${log_file}"
}

# Check for debugging tools
check_pwndbg
check_valgrind

# Run premake to generate build files
echo "Generating build files with premake..."
cd build
./premake5 gmake2 --cc=gcc
cd ..

# Build configuration selection
echo "Select build configuration:"
echo "1) Debug (recommended for debugging)"
echo "2) Release"
echo
read -p "Enter configuration number [1]: " config_choice
config_choice=${config_choice:-1}

case $config_choice in
    1)
        BUILD_CONFIG="debug_x64"
        BUILD_DIR="Debug"
        ;;
    2)
        BUILD_CONFIG="release_x64"
        BUILD_DIR="Release"
        ;;
    *)
        echo "Invalid choice, using Debug configuration"
        BUILD_CONFIG="debug_x64"
        BUILD_DIR="Debug"
        ;;
esac

# Build the project with the selected configuration
echo "Building Idleizer with $BUILD_CONFIG configuration..."
make config=$BUILD_CONFIG

# Choose what to debug
echo
echo "Idleizer - Debug Mode ($BUILD_CONFIG)"
echo "Choose what to debug:"
echo "1) Mine Hunter"
echo "2) (C)ookie Clicker"
echo "3) Custom Binary"
echo
read -p "Enter choice [1]: " target_choice
target_choice=${target_choice:-1}

# Choose debugging tool
echo
echo "Choose debugging tool:"
echo "1) GDB/pwndbg (for step debugging, breakpoints, memory inspection)"
if [ "$VALGRIND_INSTALLED" -eq 1 ]; then
    echo "2) Valgrind (for memory leak detection, access errors)"
fi
echo "3) Custom Command"
echo
read -p "Enter debugging tool [1]: " tool_choice
tool_choice=${tool_choice:-1}

# Execute based on choices
case $target_choice in
    1) # Mine Hunter
        echo "Building Mine Hunter..."
        make config=$BUILD_CONFIG MineHunter
        cd examples/MineHunter
        
        # Update log path to be relative to current directory
        LOG_DIR="../../logs"
        mkdir -p "$LOG_DIR"
        
        case $tool_choice in
            1) # GDB
                echo "Starting GDB with Mine Hunter..."
                launch_gdb "./MineHunter"
                ;;
            2) # Valgrind
                if [ "$VALGRIND_INSTALLED" -eq 1 ]; then
                    echo "Starting Valgrind with Mine Hunter..."
                    launch_valgrind "./MineHunter"
                else
                    echo "Valgrind not installed. Using GDB instead."
                    launch_gdb "./MineHunter"
                fi
                ;;
            3) # Custom Command
                echo "Enter custom debugging command (e.g., 'gdb ./MineHunter' or 'valgrind ./MineHunter'):"
                read -p "> " custom_cmd
                run_custom_command "$custom_cmd"
                ;;
            *)
                echo "Invalid choice, using GDB."
                launch_gdb "./MineHunter"
                ;;
        esac
        ;;
      2) # (C)ookie Clicker
        echo "Building CookieClicker..."
        make config=$BUILD_CONFIG CookieClicker 
        cd examples/CookieClicker
        
        # Update log path to be relative to current directory
        LOG_DIR="../../logs"
        mkdir -p "$LOG_DIR"
        
        case $tool_choice in
            1) # GDB
                echo "Starting GDB with Cookie Clicker..."
                launch_gdb "./CookieClicker"
                ;;
            2) # Valgrind
                if [ "$VALGRIND_INSTALLED" -eq 1 ]; then
                    echo "Starting Valgrind with Cookie Clicker..."
                    launch_valgrind "./CookieClicker"
                else
                    echo "Valgrind not installed. Using GDB instead."
                    launch_gdb "./CookieClicker"
                fi
                ;;
            3) # Custom Command
                echo "Enter custom debugging command (e.g., 'gdb ./CookieClicker' or 'valgrind ./CookieClicker'):"
                read -p "> " custom_cmd
                run_custom_command "$custom_cmd"
                ;;
            *)
                echo "Invalid choice, using GDB."
                launch_gdb "./CookieClicker"
                ;;
        esac
        ;;
        
       
    3) # Custom Binary
        echo "Enter path to binary to debug (relative to project root):"
        read -p "> " binary_path
        
        if [ ! -f "$binary_path" ]; then
            echo "Error: File not found: $binary_path"
            exit 1
        fi
        
        case $tool_choice in
            1) # GDB
                echo "Starting GDB with $binary_path..."
                launch_gdb "$binary_path"
                ;;
            2) # Valgrind
                if [ "$VALGRIND_INSTALLED" -eq 1 ]; then
                    echo "Starting Valgrind with $binary_path..."
                    launch_valgrind "$binary_path"
                else
                    echo "Valgrind not installed. Using GDB instead."
                    launch_gdb "$binary_path"
                fi
                ;;
            3) # Custom Command
                echo "Enter custom debugging command:"
                read -p "> " custom_cmd
                run_custom_command "$custom_cmd"
                ;;
            *)
                echo "Invalid choice, using GDB."
                launch_gdb "$binary_path"
                ;;
        esac
        ;;
        
    *)
        echo "Invalid choice, exiting."
        exit 1
        ;;
esac

# Display log summary
echo
echo "=== Debugging Session Summary ==="
echo "Logs are available in the ${LOG_DIR} directory:"
ls -la ${LOG_DIR}/ | grep ${TIMESTAMP}
echo "Use 'cat [logfile]' to view a log file."
echo "GDB history files are also saved in the ${LOG_DIR} directory for reference."

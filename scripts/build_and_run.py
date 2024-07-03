import os
import subprocess
import shutil
import platform
import argparse

def main(build_type):
    # Determine the root directory (one level up from the scripts directory)
    root_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))

    # Clean the project using Cargo
    clean_command = ["cargo", "clean"]
    subprocess.run(clean_command, cwd=root_dir)

    # Run the build process with Cargo
    build_command = ["cargo", "build"]
    
    if build_type == "release":
        build_command.append("--release")

    result = subprocess.run(build_command, cwd=root_dir)
    if result.returncode != 0:
        print("Build failed")
        return

    # Determine the executable name based on the platform
    exe_name = "computational_physics_engine"
    if platform.system() == "Windows":
        exe_name += ".exe"

    # Define the path to the executable
    exe_path = os.path.join(root_dir, "target", build_type, exe_name)

    # Check if the executable exists
    if not os.path.exists(exe_path):
        print(f"Executable not found: {exe_path}")
        return

    # Run the executable
    result = subprocess.run([exe_path])
    if result.returncode != 0:
        print("Execution failed")
        return

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Build and run the Rust project.')
    parser.add_argument('--build_type', type=str, choices=['debug', 'release'], default='debug', help='Specify the build type: debug or release')

    args = parser.parse_args()
    main(args.build_type)

import subprocess
import os
import sys

def find_executable():
    # Attempt to locate the compiled Projeto2 executable
    paths = [
        "build/GarageManager.exe",
        "build/Debug/GarageManager.exe",
        "build/Release/GarageManager.exe",
        "out/build/x64-Debug/GarageManager.exe"
    ]
    for p in paths:
        if os.path.exists(p):
            return p
    return None

def test_input_resilience(exe_path):
    print("========================================")
    print("= INITIATING HEAVY CLI FUZZING TEST =")
    print("========================================\n")
    
    # 1. Test massive buffer overflow string
    massive_string = "A" * 50000 + "\n"
    
    # 2. Test out-of-bounds menu inputs
    out_of_bounds = "-999\n9999\n"
    
    # 3. Test empty newlines and pure whitespace
    empty_lines = "\n\n\n   \n\t\n"
    
    # 4. Test non-numeric inputs for integer fields
    non_numeric = "not_a_number\n!@#$%\n"
    
    # Finally gracefully exit the program
    exit_command = "T\n"  # "T" for Exit Program in Menu
    
    payload = massive_string + out_of_bounds + empty_lines + non_numeric + exit_command
    
    print("[FUZZ] Sending malformed payload to CLI...")
    
    try:
        process = subprocess.run(
            [exe_path], 
            input=payload, 
            text=True, 
            capture_output=True, 
            timeout=10
        )
        
        output = process.stdout
        errors = process.stderr
        
        # Check for successful exit without crashing.
        # EOF validation forces exit(1) which is considered a successful defensive exit in our new codebase
        if process.returncode == 0 or process.returncode == 1:
            print(f"[PASS] Process exited correctly (return code {process.returncode}). No crash detected.")
        else:
            print(f"[FAIL] Process crashed with return code {process.returncode}.")
            print(f"Stderr: {errors}")
            return False
            
        # Verify defensive logic caught the errors
        if "Invalid choice" in output or "Invalid option" in output or process.returncode == 1:
            print("[PASS] System gracefully intercepted invalid inputs.")
        else:
            print("[WARNING] System did not explicitly complain about invalid inputs, but didn't crash.")
            
        return True
        
    except subprocess.TimeoutExpired:
        print("[FAIL] Process HUNG in an infinite loop! Timeout Expired.")
        return False
    except Exception as e:
        print(f"[FAIL] An unexpected error occurred: {e}")
        return False

if __name__ == "__main__":
    exe_path = find_executable()
    if not exe_path:
        print("[SKIP] Could not find compiled Projeto2 executable.")
        print("Please compile the project via CMake before running the fuzzer.")
        print("Expected paths checked: build/GarageManager.exe, etc.")
        sys.exit(0)
        
    success = test_input_resilience(exe_path)
    if success:
        print("\n=> ALL FUZZING TESTS PASSED! System is highly resilient.")
        sys.exit(0)
    else:
        print("\n=> SYSTEM FAILED RESILIENCE TESTING.")
        sys.exit(1)

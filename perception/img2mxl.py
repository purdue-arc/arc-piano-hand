import subprocess
import os 
# Define the command
command = r'C:\\"Program Files"\\Audiveris\\bin\\Audiveris.bat -batch -output "C:\\Users\\anish\\OneDrive\\Desktop" -export -- "C:\\Users\\anish\\OneDrive\\Desktop\\twinkleDPI.pdf"'
#command = ["C:\\'Program Files\'\\Audiveris\\bin\\Audiveris.bat", "-batch", "-output", "C:\\Users\\anish\\OneDrive\\Desktop","-export","--","C:\\Users\\anish\\OneDrive\\Desktop"]
#command = r'ls'
# Run the command in the terminal
#process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

# Wait for the process to finish and get the output and errors
#output, error = process.communicate()
#subprocess.run(["ls", "-l"])    
os.system(command)
# Print the output and errors
#if output:
 #   print("Success")
#if error:
 #   print("Failed")

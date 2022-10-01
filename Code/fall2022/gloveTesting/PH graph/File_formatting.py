import matplotlib.pyplot as plt

# with open('Arduino_Outputs') as f:
#     lines = f.readlines()

# Cleans an unprocessed line from the output and adds it to its data
def add_data(input):
    # Remove '\n'
    # lines = input.split("\\n")
    # cleaned_lines = []
    # Remove 'b's
    # for line in lines:
    # cleaned_line = input.replace("b\'","")
    # cleaned_line = input.replace("\\n'","")
    cleaned_line = input[2:-3]
    
    if(len(cleaned_line) <= 5):
        return ["n", 999999999]
    # Not sure what this does
    # while cleaned_lines[0][0:1] != "R":
    #     cleaned_lines.pop(0)
    # Take substrings of the values to include only the numbers
        # Converted values
    # print(cleaned_line)
    if (cleaned_line[0] == "C"):
        cleaned_line = cleaned_line[17:].strip()
        #if cleaned_line.isdigit():
        
        new_line = cleaned_line.replace(".","")
        if new_line.isnumeric():
            print("test",cleaned_line)
            cleaned_line = float(cleaned_line)
            return ["c", cleaned_line]
    # Raw values
    elif cleaned_line[0] == "R":
        cleaned_line = cleaned_line[10:].strip()
        #if cleaned_line.isdigit():
        if cleaned_line.isdecimal():
            cleaned_line = float(cleaned_line)
            return ["r", cleaned_line]
    return ["n", 999999999]
        


# Make a graph using the values
def make_graph():  
    timelist = range(0, len(converted_readings))
    timelist = [time/3 for time in timelist]
    plt.plot(timelist, converted_readings)
    #Graph of converted values vs. time
    plt.xlabel("time")
    plt.ylabel("converted values")
    plt.title('time vs. converted values')
    plt.legend()
    plt.show()
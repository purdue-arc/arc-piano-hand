import matplotlib.pyplot as plt

# with open('Arduino_Outputs') as f:
#     lines = f.readlines()

raw_readings = []
converted_readings = []  

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
        return
    # Not sure what this does
    # while cleaned_lines[0][0:1] != "R":
    #     cleaned_lines.pop(0)

    # Take substrings of the values to include only the numbers
        # Converted values
    # print(cleaned_line)
    if (cleaned_line[0] == "C"):
        cleaned_line = cleaned_line[17:].strip()
        print(cleaned_line)
        if cleaned_line.isdigit():
            cleaned_line = float(cleaned_line)
            converted_readings.append(cleaned_line)
    # Raw values
    else:
        cleaned_line = cleaned_line[10:].strip()
        if cleaned_line.isdigit():
            cleaned_line = float(cleaned_line)
            raw.append(cleaned_line)
        


# Make a graph using the values
def make_graph():  
    timelist = range(0, len(converted))
    timelist = [time/3 for time in timelist]
    plt.plot(timelist, converted)

    #Graph of converted values vs. time
    plt.xlabel("time")
    plt.ylabel("converted values")
    plt.title('time vs. converted values')
    plt.legend()
    plt.show()
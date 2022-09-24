import matplotlib.pyplot as plt

with open('Arduino_Outputs') as f:
    lines = f.readlines()

# Remove \n 
a = lines[0].split("\\n")
p = []
# Remove 'b's
for i in a:
    p.append(i.replace("\'b\'",""))
while p[0][0:1] != "R":
    p.pop(0)

raw = []
converted = []    
for i in range(0,len(p)):
    #converted
    if (i % 2 == 1):
        p[i] = p[i][17:].strip()
        converted.append(p[i])
    #raw
    else:
        p[i] = p[i][10:].strip()
        raw.append(p[i])

# Convert raw
k = 0
for i in raw:
    if (not i.isdigit()):
        raw.pop(k)
        k += 1

# Convert converted
k = 0
for i in converted:
    if (not i.isdigit()):
        converted.pop(k)
        k += 1

print(raw)
print(converted)

converted = [float(convert) for convert in converted]

timelist = range(0, len(converted))
timelist = [time/3 for time in timelist]
plt.plot(timelist, converted)
  
#Graph of converted values vs. time
plt.xlabel("time")
plt.ylabel("converted values")
plt.title('time vs. converted values')
plt.legend()
plt.show()
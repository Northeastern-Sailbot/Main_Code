import csv
import math


# Calculate mean of the values
def mean(values):
        size = len(values)
        sum = 0.0
        for n in range(0, size):
                sum += values[n]
        return sum / size;

# Calculate standard deviation
def SD(values, _mean):
    size = len(values)
    sum = 0.0
    for n in range(0, size):
        sum += ((values[n] - _mean)**2)
    return math.sqrt((1.0/(size-1))*(sum))


filename = 'Charles River Data/Community Boating 2013.04.04_10.csv'

wind = list()
histo = [0 for i in range(360)]
n = 0
maxv = -1000000
minv = 999999999999

with open(filename, 'rb') as csvfile:
    csvreader = csv.reader(csvfile, delimiter=',',quotechar='"')
    for row in csvreader:
        n += 1
        angle = math.radians(float(row[12]))
        angle_deg = int(float(row[12]))
        histo[int(angle_deg/4)] += 1
        mag = float(row[10])
        xx = -mag * math.sin(angle)
        yy = -mag * math.cos(angle)
        minv = min(minv, mag)
        maxv = max(maxv, mag)
        #print str(xx) + ', ' + str(yy)
        wind += [[xx,yy]]

xs = [x[0] for x in wind]
ys = [y[1] for y in wind]
means = [mean(xs),mean(ys)]
sds = [SD(xs,means[0]),SD(ys,means[1])]
histo = [float(f)/float(n) for f in histo]
print means
print sds
print histo
print str(maxv) + ', ' + str(minv)
# Wind direction: Where it originates from, degrees clockwise from N

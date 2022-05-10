from math import ceil
import sys
if len(sys.argv) <= 1:
    output = '''
    Failed to parse file as none were specified, please pass the file to analyse.
    Usage:
        python3 procedural_python_example.py <name of file>
    '''
    print(output)
    sys.exit(-1)

print('Loading file and counting lines')
with open(str(sys.argv[1]), 'r') as inf:
    counts = {}
    total_number = 0
    for line in inf:
        data = str(line).replace('\n','')
        if data in counts:
            counts[data] = counts[data] + 1
            total_number = total_number + 1
        else:
            counts[data] = 0
            total_number = total_number + 1

print(counts)
min_k = ''
min_v = sys.maxsize
max_k = ''
max_v = 0
print('Finding max, min & general distribution')
for k,v in counts.items():
    distribution = ( v / total_number ) * 100
    if v < min_v:
        min_k = k
        min_v = v
    if v > max_v:
        max_k = k
        max_v = v
    print(f"Value: {k} \n\t\t distribution: {distribution}%")

print(f"Max value: {max_k} count: {max_v}")
print(f"Min value: {min_k} count: {min_v}")


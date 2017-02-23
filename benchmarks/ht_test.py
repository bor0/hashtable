ht = {}

with open("strings.txt", "r") as ins:
    for line in ins:
        ht[line] = line

print(ht['pffevnoghq\n']);

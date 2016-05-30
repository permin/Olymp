def check_units_number(bit_count, d):
    for k in range(2, d + 1):
        if d % k == 0:
            if (bit_count - 1) % k == 0:
                return k
    for k in range(2, d):
        if (d - 1) % k == 0:
            if bit_count % k == 0:
                return k
    return None

for i in range(2, 14, 2):
    print "%d:" % i,
    for d in range(2, 11, 2):
        print check_units_number(i, d),
    print

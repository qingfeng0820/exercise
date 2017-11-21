def answer(n, b):
    # your code here
    r = n
    base_convert = "0123456789ABCDEFHIJKLMNOPQRSTUVWZXY"
    l = len(n)
    loops = []
    while r not in loops:
        loops.append(r)
        x = int(''.join(sorted(r, reverse=True)), b)
        y = int(''.join(sorted(r)), b)
        r_num = x - y
        if r_num == 0:
            return 1
        if b != 10:
            new_num_str = ""
            while r_num != 0:
                remainder = r_num % b
                if 36 > remainder > 9:
                    remainder_string = base_convert[remainder]
                elif remainder >= 36:
                    remainder_string = "(" + str(remainder) + ")"
                else:
                    remainder_string = str(remainder)
                new_num_str = remainder_string + new_num_str
                r_num = r_num / b
            r = new_num_str
        else:
            r = str(r_num)
        k = l - len(r)
        r = '0' * k + r
    return len(loops) - loops.index(r)


if __name__ == "__main__":
    print answer("2222", 3)

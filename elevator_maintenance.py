def answer(l):
    # your code here
    tmp_list = [x.split(".") for x in l]
    tmp_int_list = [map(int, y) for y in tmp_list]
    sorted_int_list = sorted(tmp_int_list)
    return [".".join(str(a) for a in z) for z in sorted_int_list]


if __name__ == "__main__":
    print answer(["1.1.2", "1.0", "1.3.3", "1.0.12", "1.0.2"])
    print answer(["1.11", "2.0.0", "1.2", "2", "0.1", "1.2.1", "1.1.1", "2.0"])
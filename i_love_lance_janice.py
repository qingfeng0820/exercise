def answer(s):
    # your code here
    ret = ''
    for c in s:
        n = ord(c)
        if 97 <= n <= 122:
            n = 219 - n
            ret += str(unichr(n))
        else:
            ret += c
    return ret

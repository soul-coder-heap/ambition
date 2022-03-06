#!/usr/bin/env python
# coding=utf-8

def solution():
    d = dict()
    ll = list()
    count = 0
    while True:
        l = input()
        if l == "1":
            break
        a,b = map(int, l.split(",")[0:2])
        string = l.split(",")[2:][0]
        li = eval(string)
        li_ = list(map(int,li))
        d[a] = b
        for i in li_:
            ll.append(i)
    for k,v in d.items():
        count += v
    for i in ll:
        #count += d[i]
        pass
    print(count)

solution()

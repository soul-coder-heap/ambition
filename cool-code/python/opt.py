def opr():
    N = int(input())
    l = list(map(int, input().split()))
    same = True
    for i in range(N):
        if i == 0:
            continue
        if l[i] > l[i - 1]:
            if l[i] / l[i - 1] % 2 == 0:
                continue
            else:
                same = False
                break
        if l[i] < l[i - 1]:
            if l[i - 1] / l[i] % 2 == 0:
                continue
        else:
            same = False
            break
    if same:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    opr()

def getMaxColors(prices,money):
    max_cnt = 0
    window = []
    sums = 0
    for m in prices:

        window.append(m)
        sums += m
        if sums <= money:
            max_cnt = max(max_cnt,len(window))
        while sums > money:
            sums -= window[0]
            window = window[1:]

    return max_cnt

prices = [2,3,5,1,1,1,1,1,1,1,2,1]
money = 7
print(getMaxColors(prices,money))
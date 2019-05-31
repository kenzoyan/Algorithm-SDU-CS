
# 给定某条路径，计算它的成本
def distcal(path, dist):
    
    sum_dist = 0 
    for j in range(0, len(path) - 1):
        di = dist[int(path[j]) - 1][int(path[j + 1]) - 1]  
        sum_dist = sum_dist + di  #
    di = dist[int(path[len(path) - 1]) - 1][path[0] - 1]  # 最后一个城市回到初始城市的成本
    sum_dist = sum_dist + di
    return sum_dist  


# 递归构造所有可能路径
def perm(l):  # 构造路径（城市列表）
    if (len(l)) <= 1:  # 只有一个城市，选择这个城市
        return [l]
    r = []  # 空列表
    for i in range(len(l)):  # 对每个城市，构建不包括这个城市的所有可能序列
        s = l[:i] + l[i + 1:]  # 去除当前城市的列表
        p = perm(s)  # 调用自身，构造不包含这个城市的序列
        for x in p:
            r.append(l[i:i + 1] + x)  # 将序列和该城市合并，得到完整的序列
    return r


if __name__ == '__main__':
    
    nums=int(input('city_nums='))
    
    city = [i+1 for i in range(nums)]
    
    dist = [[0]*nums]*nums        #初始化二维数组
    for i in range(nums):
        dist[i] = input().split(" ")       #输入二维数组，同行数字用空格分隔，不同行则用回车换行
        dist[i] = [int(j) for j in dist[i]]    

    for i in range(0, nums):
        print(dist[i][:])

    print('=============')

    allpath = perm(city)  #产生所有可能的路径

    optimal = 1000000 

    index = 1

    for i in range(0, len(allpath)):
        pd = distcal(allpath[i], dist)
        if pd < optimal:  # 比较是否总成本更低，如果是替换最优解
            optimal = pd
            index = i
        # print(pd)

    print(optimal)
    print(allpath[index])

'''
    0 3 3 2 6
    3 0 7 3 2
    3 7 0 2 5
    2 3 2 0 3
    6 2 5 3 0
'''
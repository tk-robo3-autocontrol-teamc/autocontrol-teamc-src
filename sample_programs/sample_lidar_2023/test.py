f = open('test.txt', 'r', encoding='UTF-8')

datalist = f.readlines()
for i in range(0, 10):
    print(datalist[i].split()[0], datalist[i].split()[1])


def hashf(szword):
    w = szword.lower()
    g = 31
    hash = 0
    for c in w:
        if c.isalpha():
            hash =(g * hash + (ord(c) - ord('a'))) & 0xffffffff
        else:
            break    
    return hash    
    
def main():
    hist = [0] * 65535
    with open('f:/cs50/pset5/speller/dictionaries/large','r') as szDict:
        word_list = szDict.readlines()
        for word in word_list:
            ndx = hashf(word) % 65521
            hist[ndx] += 1
    print(hist) 
    for i in range(20):
        print(i,hist.count(i))
    
      
if __name__ == '__main__':
    main()
# dna.py
# k. r. bergerstock @ 2020.11.17

import sys
import csv
import difflib

def main(argv):
    if len(argv) < 2:
        sys.stderr.write('insufficient number of arguments\n')
        sys.stderr.write('usage: "database file" "sequence file"\n')
        exit(-1)
    try:
        with open(argv[1],'r') as seq_file:
            sequence = seq_file.readline()
    except:
        sys.stderr.write(f'no sequence file named {argv[1]}\n')
        exit(-2)
    
    try:
        db = {}
        idx = 0
        with open(argv[0],'r') as db_file:
            reader = csv.reader(db_file, delimiter=',')
            for row in reader:
                db[row[0]] = row[1:]
    except:        
        sys.stderr.write(f'no data base file named {argv[0]}\n')
        exit(-3)
    found = []
    for name in db :
        if name != 'name':
            fnd = []
            seq = ''
            row = db[name]
            n = len(row)      
            for i in range(n):
                seq = db['name'][i] * int(db[name][i])
                # f = seq in sequence
                g = sequence.count(seq)
                p = sequence.find(seq)
                q = sequence.rfind(seq)
                fnd.append(g == 1 and p == q)
            if False in fnd:
                pass
            else:
                print(f'{name} matches {argv[1]}')
                exit(0)
    print(f'no match found for {argv[1]}')            
    return 0            

if __name__ == "__main__":
    main(sys.argv[1:])    
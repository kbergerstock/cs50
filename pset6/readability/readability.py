# readability.py
#
# Keith R Bergerstock
# date: 2020.11.16

import sys

def inputString(prompt):
    """ returns a string from stdin """
    sys.stdout.write(prompt)
    sys.stdout.flush()
    tstr = sys.stdin.readline()
    return tstr.rstrip()

def calc_colman_laiu(sentences, words, letters):
    L = letters / words * 100.0
    S = sentences / words * 100.0
    return 0.0588 * L - 0.296 * S - 15.8


def count_characters(text):
    letters = 0
    words = 0
    sentences = 0
    t = ''
    for c in text:
        if c.isalpha():
            letters += 1
        elif c == '!' or c == '?' or c == '.':
            sentences += 1
            words  += 1
        elif c == ';' or c == ',':
            words += 1
        elif c == ' ' and t.isalpha():
            words += 1
        # store this pass to be used by the next pass            
        t = c    

    # print('sentences ',sentences)        
    # print(' words    ',words)
    # print('letters   ',letters)
    cl = calc_colman_laiu(sentences, words, letters)
    return int(cl + 0.5)


def main():
    txt = inputString("TEXT:")
    grade = count_characters(txt)
    if grade < 1:
        print('Before Grade 1')
    elif grade >= 16:    
        print('Grade 16+')
    else:
        print(f"Grade {grade} ")    


if __name__ == "__main__":
    main()

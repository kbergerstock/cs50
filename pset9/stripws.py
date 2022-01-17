# function to strip white space from the end of lines in text or source files
# K. R. Bergerstock
# @ july, 2018

import os
import sys
import string

__author__ = "k. r. bergerstock"
def copy_file(sf, df):
    with open(df,'w') as fp_out:
        with open(sf,'r') as fp_in:
            for line in fp_in:
                fp_out.write(line.rstrip())
                fp_out.write('\n')
      

#parameters are a list of files to be processed
def main(file_list):
    # sf === source file
    # df === destination file
    for sf in file_list: 
        tf = os.path.split(sf)
        if not tf[0] and os.path.isfile(tf[1]):           
            df = 'ws_' + tf[1]
            os.rename(sf,df)
            copy_file(df, sf)
        else:
            print(sf,' is not a valid file')    
        
if __name__ == "__main__": 
    main(sys.argv[1:])

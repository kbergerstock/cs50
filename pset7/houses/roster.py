# roster.py
#
# (cs50) pset7 houses
# k r bergerstock

import sqlite3 as sql
import sys


def output_row(row):
    if row[2] == None:
        result = f"{row[1]} {row[3]}, born {row[5]}\n"
    else:
        result = f"{row[1]} {row[2]} {row[3]}, born {row[5]}\n" 
    sys.stdout.write(result)    


def main(argv):
    if len(argv) < 1:
        sys.stderr.write('insufficient number of arguments\n')
        sys.stderr.write('usage: roster <string>house" \n')
        exit(-1)
        
    xmd = f"select * from students where house='{argv[0]}' order by last, first" 
    try:
        db = sql.connect('students.db')
        cursor = db.cursor()
        cursor.execute(xmd)
        results = cursor.fetchall()
        for row in results:
            output_row(row)
        db.close()    

    except:
        sys.stderr.write('unable to open "students.db" data base\n')
        exit(-3)
        
        
if __name__ == "__main__":
    main(sys.argv[1:])        
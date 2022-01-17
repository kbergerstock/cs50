# # import.py
# (cs50) pset7 houses
# k r bergerstock

import csv
import sqlite3 as sql
import sys


def create_sql_cmd(row):
    """ create the sql insert command """
    name = row[0]
    house = row[1]
    year = row[2]
    # skip over column headers
    if name == 'name':
        cmd = None
    else:
        n = name.split()
        first = n[0]
        if len(n) < 3:
            middle = ''
            last = n[1]
            cmd = "insert into students (first,last,house,birth) values('{0}','{1}','{2}',{3})".format(
                first, last, house, year)
        else:
            middle = n[1]
            last = n[2]
            cmd = "insert into students (first,middle,last,house,birth) values('{0}','{1}','{2}','{3}',{4})".format(
                first, middle, last, house, year)
    return cmd


def main(argv):
    if len(argv) < 1:
        sys.stderr.write('insufficient number of arguments\n')
        sys.stderr.write('usage: "file.csv" \n')
        exit(-1)

    try:
        db = sql.connect('students.db')
        cursor = db.cursor()

    except:
        print('unable to open "students.db" data base')
        exiit(-3)

    try:
        with open(argv[0], 'r') as raw:
            reader = csv.reader(raw, delimiter=',')
            # process the csv file
            for row in reader:
                cmd = create_sql_cmd(row)
                # if the return value is null skip executing the cmd
                if cmd:
                    cursor.execute(cmd)
                    db.commit()
    except:
        sys.stderr.write(f'{argv[0]} csv file not found.\n')

    db.close()


if __name__ == "__main__":
    main(sys.argv[1:])
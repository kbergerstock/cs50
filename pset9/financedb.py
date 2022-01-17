## access for finance db using sqlite 3
## for pset7
## keith r bergerstock

from os import write
import time
from werkzeug.security import check_password_hash, generate_password_hash
import sqlite3
import iexapis

ACTION_NONE = 0
ACTION_BUY  = 1
ACTION_SELL = 2

ERR_MSGS = (
                'ok',                               #0
                'Data base / connection err',       #1
                'No user record loaded.',           #2
                'Uninitialized data base name',     #3
                'Unable to connect to data base',   #4
                "BAD user Id (0) ZERO",             #5
                'password does not match',          #6
                'Insufficient funds to purchase shares', #7
                'Insufficient shares owned for sell request', #8
                'ILLEGAL ACTION !',                 #9
                'nothing to buy',                   #10
                'sql error : ',                     #11
)

def format_proper_name(t):
    if t[0] and t[1] and t[2]:
        return f"{t[0]} {t[1]} {t[2]}"
    elif t[0] and t[2]:
        return f"{t[0]} {t[2]}"
    else:
        return "missing name"


# sqlite3 access class for finace db
class financeDB:

    def reset_err(self):
        self.err = 0
        self.sqlerr = ''


    def __init__(self,filename):
        self.__file_name__ = filename
        self.__user_id__ = 0
        self.__user_name__ = ''
        self.__user_proper_name__ = ''
        self.__user_cash__ =  0.0
        self.__portfolio__ = []
        cmd = "select count(username) from users"
        rows = self.fetch(cmd)
        if int(rows[0][0]) == 0:
            HASH = generate_password_hash('x11klown',salt_length=23)
            cmd = f"insert into users (user_id,username,hash,cash) VALUES (1001,'KEITH','{HASH}',0.00)"
            self.write(cmd)
            cmd = "insert into names (user_id,first,middle,last) values (1001,'KEITH','R','BERGERSTOCK')"
            self.write(cmd)


    def user_id(self):
        return self.__user_id__

    def user_name(self):
        return self.__user_name__

    def user_proper_name (self):
        return self.__user_proper_name__

    def user_cash_balance(self):
        return self.__user_cash__

    def get_user_portfolio(self):
        return self.__portfolio__

    def get_last_error(self):
        if self.err == 11:
            return self.sqlerr
        else:
            return ERR_MSGS[self.err]


    def fetch(self,cmd):
        try:
            self.reset_err()
            # open connection to data base
            db = sqlite3.connect(self.__file_name__)
            c = db.cursor()
            c.execute(cmd)
            # retrieve the records
            rows = c.fetchall()
            db.close()
            return rows

        except sqlite3.Error as sqz:
            self.err = 11
            self.sqlerr = sqz
            print(sqz)
            print(cmd)
            return None


    def write(self,cmd):
        try:
            self.reset_err()
            # open connection to data base
            db = sqlite3.connect(self.__file_name__)
            c = db.cursor()
            c.execute(cmd)
            db.commit()
            db.close()
            return True

        except sqlite3.Error as sqz:
            self.err = 11
            self.sqlerr = sqz
            print(sqz)
            print(cmd)
            return None


    def get_user_id(self,user_name):
        """ retrieves the user id for a given unique user name """
        cmd = f"SELECT user_id,hash,cash FROM users where username = '{user_name}'"
        rows =  self.fetch(cmd)
        if rows:
            # return the tupple of the response
            return rows[0]
        return (0,'USER NOT FOUND',0.0)


    def get_proper_name(self,user_id):
        """ retrives the proper name of the user from the name table """
        cmd = f"SELECT first, middle, last FROM names WHERE user_id = {user_id}"
        rows = self.fetch(cmd)
        if rows:
            return rows[0]
        return ('USER ID','NOT','FOUND')

    def login(self, user_name, user_password):
        """ performs verifaction of an attempted login """
        self.reset_err()
        # Ensure username exists and password is correct
        t = self.get_user_id(user_name)
        if int(t[0]) > 1000:
            if check_password_hash(t[1], user_password):
                self.__user_id__ = int(t[0])
                self.__user_name__ = user_name
                self.__user_proper_name__ = format_proper_name(self.get_proper_name(int(t[0])))
                self.__user_cash__ = t[2]
                return True
            else:
                self.err = 6
                return False
        self.err = 5
        return False


    def logout(self):
        """ close data base and clear record """
        # reset the user data to none
        self.__user_id__ = 0
        self.__user_name__ = ''
        self.__user_proper_name__ = ''
        self.__user_cash__  = 0
        self.__portfolio__ = []


    def __register__(self, user_name, password):
        """ function to write new user to db """
        # detemine if a record exists for given user
        t = self.get_user_id(user_name)
        if int(t[0]) == 0:
            # no user in data base matches given user
            # so register the new user
            hash = generate_password_hash(password,salt_length  = 23)
            cmd = f"INSERT into users (username, hash) values ('{user_name}','{hash}')"
            return self.write(cmd)
        return False


    def register(self, user, pswd, first, middle, last):
        """ function to register new users """
        if not self.__register__(user, pswd):
            return False
        t = self.get_user_id(user)
        if not self.insert_proper_name(int(t[0]), first, middle, last):
            return False
        return True


    def insert_proper_name(self, user_id, first, middle, last):
        if user_id > 1000:
            cmd = f"INSERT into names (user_id, first, middle, last) values ({user_id},'{first}','{middle}','{last}')"
            return self.write(cmd)
        return False


    def update_symbol(self, data):
        """ add new symbol to symbols table """
        cmd = f"select count(symbol) from symbols where symbol = '{data[0]}'"
        rows = self.fetch(cmd)
        if int(rows[0][0]) == 0:
            cmd = f"""INSERT into symbols (symbol, company, exchange, type) values
                    ('{data[0]}','{data[1]}','{data[2]}','{data[3]}')"""
            if not self.write(cmd):
                return  False
        cmd = f"select count(symbol) from stocks where symbol = '{data[0]}' and user_id = {self.user_id()}"
        rows =  self.fetch(cmd)
        if int(rows[0][0]) == 0:
            cmd = f"insert into stocks (symbol, user_id) values('{data[0]}',{self.user_id()})"
            return self.write(cmd)
        else:
            return int(rows[0][0]) == 1
        return False

    def update_stocks(self, stock_list):
        if stock_list:
            for stock in stock_list:
                self.update_symbol(stock)

    def update_quote_price(self):
        ''' function  to update the price field in stocks table '''
        cmd =  f"select symbol, shares from stocks where user_id = {self.user_id()} "
        stock_list = self.fetch(cmd)
        t = []
        if stock_list and self.user_id() > 1000:
            for stock in stock_list:
                price = iexapis.lookup(stock[0])
                shares = stock[1]
                cmd = f"""update stocks set price = { price['price'] }
                        where symbol = '{stock[0]}' and user_id = {self.user_id()}"""
                t.append(self.write(cmd))
                if shares > 0:
                    value = shares * price['price']
                    cmd = f"""update stocks set value = { value }
                            where symbol = '{stock[0]}' and user_id = {self.user_id()}"""
                    t.append(self.write(cmd))
            return all(t)
        return False

    def read_portfolio(self):
        ''' function to read the contents for the portfolio table '''
        self.__portfolio__ = []
        cmd = f"""select stocks.symbol, symbols.company, shares, invested,price ,value from stocks
                    inner join symbols on stocks.symbol = symbols.symbol where user_id = {self.user_id()}"""
        self.__portfolio__ = self.fetch(cmd)
        return self.__portfolio__

    def update_history(self, symbol, action, shares, price):
        ''' function to update the history table '''
        cmd = f"""INSERT INTO history (user_id, tdate, symbol,action,price,shares,cost) values
                ({self.user_id()},tbd,'{symbol}','{action}',{price},{shares},{shares * price})"""
        return self.write(cmd)

    def uppdate_shares(self,symbol,shares,price):
        '''fuction to update the shares in the stock table '''
        cmd = f"""select shares, invested from stocks where user_id = {self.user_id()} and symbol = {symbol}"""
        stock = self.fetch(cmd)
        if not stock:
            return False
        invested = shares * price + stock[0][1]
        shares += stock[0][0]

        cmd =f"""update stocks set shares = { shares } where 
                   where user_id = {self.user_id()} and symbol = {symbol}"""
        self.write(cmd)
        cmd =f"""update stocks set invested = { invested } where 
                   where user_id = {self.user_id()} and symbol = {symbol}"""
        self.write(cmd)

    def buy_stock(self, symbol, shares, price):
        # make sure there is enough cash on hand to purchase  the requested stock
        if price * shares > self.user_cash_balance():
            return False
        if not self.update_history(symbol,"bought",shares,price):
            return False

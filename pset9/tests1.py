import unittest
import time
from werkzeug.security import check_password_hash, generate_password_hash
from financedb import financeDB, format_proper_name
import iexapis

class TestsFinanceDB(unittest.TestCase):

    def setUp(self):
        self.db = financeDB('finance.db')

    def test__KEITH(self):
        t = self.db.get_user_id('KEITH')
        self.assertEqual(t[0],1001)

    def test__login_countdown(self):
        self.assertTrue(self.db.login('countdown','klown'))

    def test__keith_r_bergerstock(self):
        t = self.db.login('countdown','klown')
        rv = self.db.get_proper_name(self.db.user_id())
        self.assertEqual(format_proper_name(rv),"Keith R Bergerstock")
        self.assertEqual(self.db.user_cash_balance(),10000)

    def test__logff_countdown(self):
        self.db.logout()
        self.assertEqual(self.db.user_id(),0)

    def test__login_tarzan(self):
        self.assertTrue(self.db.login('tarzan','tantor'))
        self.assertEqual(self.db.user_proper_name(),"Lord John Greystoke")

    def test__logff_tarzan(self):
        self.db.logout()
        self.assertEqual(self.db.user_id(),0)

    def test__tarzan_write_agilent(self):
        self.assertTrue(self.db.login('tarzan','tantor'))
        data =  ('A', 'Agilent Technologies Inc.', 'NEW YORK STOCK EXCHANGE, INC.', 'cs')
        self.assertTrue(self.db.update_symbol(data))

    def test__countdown_read_portfolio(self):
        self.assertTrue(self.db.login('countdown','klown'))
        t = self.db.read_portfolio()
        s = iexapis.search(t,'IBM')
        self.assertEqual(s[0],'IBM')

    def test__search_for_symbol(self, symbol = ''):
        stock_list = iexapis.fetch_symbols()
        t = iexapis.search(stock_list,'NOC')
        self.assertEqual(t[0],'NOC')

    def tearDown(self):
         self.db.logout()

if __name__ =="__main__":
    unittest.main()


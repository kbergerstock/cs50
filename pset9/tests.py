import unittest
import time
from werkzeug.security import check_password_hash, generate_password_hash
from financedb import financeDB, format_proper_name

class TestsFinanceDB(unittest.TestCase):
    """ run this file on a new data base or after you have used
    the create schema sql comand to populate the data base
    with minimun functionality """

    def setUp(self):
        self.db = financeDB('finance.db')

    def test__a_keith(self):
        self.db = financeDB('finance.db')
        t = self.db.get_user_id('keith')
        self.assertEqual(t[0], 0)

    def test__a_KEITH(self):
        t = self.db.get_user_id('KEITH')
        self.assertEqual(t[0],1001)

    def test__b_cregister_countdown(self):
        self.assertTrue(self.db.register('countdown','klown','Keith','R','Bergerstock'))

    def test__b_register_tarzan(self):
        self.assertTrue(self.db.register('tarzan','tantor','Lord','John','Greystoke'))

    def test__b_register_grue(self):
        self.assertTrue(self.db.register('grue','zork','great','underground','empire'))

    def test__c_missing_name(self):
        self.assertEqual(format_proper_name(('','','')),"missing name")

    def test__c_chuck_henry(self):
        self.assertEqual(format_proper_name(('Charles','','Henry')),"Charles Henry")

    def test__d_countdown(self):
        t = self.db.get_user_id('countdown')
        self.assertGreater(t[0], 1000)

    def test__d_countdown_psd(self):
        t = self.db.get_user_id('countdown')
        self.assertTrue(check_password_hash(t[1],'klown'))

    def test__e_tarzan(self):
        t = self.db.get_user_id('tarzan')
        self.assertGreater(t[0], 1000)

    def test__e_tarzan_psd(self):
        t = self.db.get_user_id('tarzan')
        self.assertTrue(check_password_hash(t[1],'tantor'))

    def test__f_zork(self):
        t = self.db.get_user_id('grue')
        self.assertGreater(t[0], 1000)

    def test__f_zork_psd(self):
        t = self.db.get_user_id('grue')
        self.assertTrue(check_password_hash(t[1],'zork'))

    def test__g_login_countdown(self):
        self.assertTrue(self.db.login('countdown','klown'))

    def test__g_keith_r_bergerstock(self):
        t = self.db.login('countdown','klown')
        rv = self.db.get_proper_name(self.db.user_id())
        self.assertEqual(format_proper_name(rv),"Keith R Bergerstock")
        self.assertEqual(self.db.user_cash_balance(),10000)

    def test__g_logff_countdown(self):
        self.db.logout()
        self.assertEqual(self.db.user_id(),0)

    def test__h_login_tarzan(self):
        self.assertTrue(self.db.login('tarzan','tantor'))
        self.assertEqual(self.db.user_proper_name(),"Lord John Greystoke")

    def test__h_logff_tarzan(self):
        self.db.logout()
        self.assertEqual(self.db.user_id(),0)

    def test__j_write_agilent(self):
        self.assertTrue(self.db.login('countdown','klown'))
        data =  ('A', 'Agilent Technologies Inc.', 'NEW YORK STOCK EXCHANGE, INC.', 'cs')
        self.assertTrue(self.db.update_symbol(data))

    def tearDown(self):
         self.db.logout()

if __name__ =="__main__":
    unittest.main()


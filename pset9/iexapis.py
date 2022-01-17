# fetch symbols
import os
import requests
import urllib.parse

from flask import redirect, render_template, request, g
from functools import wraps


__api_key__ = "pk_34cf6f3b055e41ae89c7461648ffed73"
__stocks__ = []

def api_call(token):
    # Contact API
    try:
        response = requests.get(token)
        response.raise_for_status()
    except requests.RequestException:
        return None
    try:
        # Parse response
        return response.json()
    except (KeyError, TypeError, ValueError):
        return None


def fetch_symbols():
    # Contact API
    if not __stocks__:
        # the api call only needs to be called once to fill  the __stocks__ list
        token = f"https://cloud.iexapis.com/beta/ref-data/symbols?token={__api_key__}"

        stock_list = api_call(token)
        if stock_list:
            for stock in stock_list:
                t = (stock['symbol'],stock['name'],stock['exchangeName'], stock['type'])
                __stocks__.append(t)
    return __stocks__

def lookup(symbol):
    """Look up the quote for symbol."""

    token = f"https://cloud-sse.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={__api_key__}"
    quote = api_call(token)
    if quote  and symbol == quote["symbol"]:
        return {"symbol": quote["symbol"], "price": float(quote["latestPrice"])}
    return None

def search(stock_list,symbol):
    low = 0
    hi = len(stock_list)
    while hi - low > 1:
        mid = (low + hi)//2
        if stock_list[mid][0] == symbol:
            return stock_list[mid]
        elif stock_list[mid][0] > symbol:
            hi = mid
        else:
            low = mid
    if stock_list[hi][0] == symbol:
        return stock_list[hi]
    return False

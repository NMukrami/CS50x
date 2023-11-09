import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # get user stocks that they have in db
    user_stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        session["user_id"],
    )

    # get and check how much cash the user currently has in db
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[
        0
    ]["cash"]

    # loop through user stocks
    for stock in user_stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["total_shares"]
        user_cash += stock["value"]

    # render page
    return render_template(
        "index.html",
        stocks=user_stocks,
        cash=db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0][
            "cash"
        ],
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # user route through "GET"
    if request.method == "GET":
        return render_template("buy.html")

    # user route through "POST"
    else:
        # get user input
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("Invalid symbol")

        # check the number to be a positive int.
        elif not shares.isdigit():
            return apology("Invalid share")

        # check if stock/quote is not available or blank input
        elif lookup(symbol) == None:
            return apology("Invalid symbol")

        else:
            # stock current price
            stock_price = lookup(symbol)["price"]

            # total price of stock
            total_price = float(shares) * float(stock_price)

            # get and check how much cash the user currently has in db
            user_cash = float(
                db.execute(
                    "SELECT cash FROM users WHERE id = :user_id",
                    user_id=session["user_id"],
                )[0]["cash"]
            )

            # check if the user has enough money to pay the stock
            if user_cash < total_price:
                return apology("Not enough money to pay")

            else:
                # user current money after pay the stock
                user_current_money = user_cash - total_price

                # update user current money into db
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    user_current_money,
                    session["user_id"],
                )

                # update user transactions into a new table in the db.
                db.execute(
                    "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                    session["user_id"],
                    symbol,
                    shares,
                    stock_price,
                )

                # print notification after buy in page
                flash(
                    f" Successfuly bought {shares} shares of {symbol} for {usd(total_price)}"
                )

                return redirect("/")

                # new table for user purchases in db
                # CREATE TABLE transactions (
                #     id INTEGER PRIMARY KEY AUTOINCREMENT,
                #     user_id INTEGER NOT NULL,
                #     symbol TEXT NOT NULL,
                #     shares INTEGER NOT NULL,
                #     price NUMERIC NOT NULL,
                #     timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
                #     FOREIGN KEY (user_id) REFERENCES users(id)
                # );


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get user info from table transactions
    user_transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
        session["user_id"],
    )

    # render html
    return render_template("history.html", transactions=user_transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # user route through "GET"
    if request.method == "GET":
        return render_template("quote.html")

    # user route through "POST"
    else:
        # get symbol value and use the lookup function to get stock/quote info.
        symbol = lookup(request.form.get("symbol"))

        # check if stock/quote is not available or empty
        if symbol == None:
            return apology("Invalid symbol")

        # render data into html page
        else:
            return render_template("quoted.html", quote=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # user route through "GET"
    if request.method == "GET":
        return render_template("register.html")

    # user route through "POST"
    else:
        # get and check username was submitted by the user
        if not request.form.get("username"):
            return apology("Enter username")

        # get and check the password and confirmation was submitted by the user
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Enter password")

        # check the password and confirmation if they are not the same.
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password does not match")

        else:
            try:
                # insert a new user and password(hash password) into db.
                session["user_id"] = db.execute(
                    "INSERT INTO users (username, hash) VALUES(?, ?)",
                    request.form.get("username"),
                    generate_password_hash(request.form.get("password")),
                )
                return redirect("/")

            except:
                # check if the user name already exists in db.
                return apology("Username is already taken")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # get user stocks that they have in db
    user_stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares From transactions WHERE user_id = ?",
        session["user_id"],
    )

    # user route via "GET"
    if request.method == "GET":
        return render_template("sell.html", stocks=user_stocks)

    # user route via "POST"
    else:
        # get user input
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        for stock in user_stocks:
            if stock["total_shares"] < shares:
                return apology("Not enough shares")

            else:
                # stock’s current price
                stock_price = lookup(symbol)["price"]

                # total price of stock
                total_price = float(shares) * float(stock_price)

                # check how much cash the user currently has in db
                user_cash = float(
                    db.execute(
                        "SELECT cash FROM users WHERE id = ?", session["user_id"]
                    )[0]["cash"]
                )

                # user current money after sell the stock
                user_current_money = user_cash + total_price

                # update user current money into db
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    user_current_money,
                    session["user_id"],
                )

                # update user transactions into a new table(transactions) in the db.
                db.execute(
                    "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                    session["user_id"],
                    symbol,
                    shares,
                    stock_price,
                )

                # print notification after buy in page
                flash(
                    f"Successfully sold {shares} shares of {symbol} for {usd(total_price)}"
                )

                return redirect("/")

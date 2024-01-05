import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///casemaker.db")


@app.route("/")
@login_required
def index():
    # Redirect to indext.html
    return render_template("index.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Logged in.')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password was submitted
        elif not request.form.get("confirmation") == request.form.get("password"):
            return apology("passwords don't match", 400)

        # Query database for username to confirm
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensures the username has not been picked.
        if len(rows) == 1:
            return apology("username already taken", 400)
        else:
            password = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), password)
            # Remember which user has logged in
            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('Logged in.')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/play", methods=["GET", "POST"])
@login_required
def play():
    """Show game taking place"""
    # Gets all info for return
    if request.method == "POST":
        # Ensures a valid game is chosen
        j = 0
        for i in range(len(db.execute("SELECT * FROM games WHERE user_id = ?", session["user_id"]))):
            if (request.form.get("game")) == db.execute("SELECT game_name FROM games WHERE user_id = ?", session["user_id"])[i]['game_name']:
                j = 1
        if j == 0:
            return apology("invalid game", 400)
        # Grabs the current frames of the game that exist.
        game = db.execute("SELECT gameid FROM games WHERE user_id = ? and game_name = ?", session["user_id"], request.form.get("game"))[0]['gameid']
        frames = db.execute("SELECT * FROM frames WHERE game_id = ?", game)
        if frames == []:
            return apology("no frames", 400)
        return render_template("play.html", frames = frames)
    else:
        if db.execute("SELECT game_name FROM games WHERE user_id = ?", session["user_id"]):
            games = db.execute("SELECT game_name FROM games WHERE user_id = ?", session["user_id"])
            redir = 'play'
            return render_template("pickgame.html", games=games, redir=redir)
        else:
            flash('No games to play! Make games by clicking "make" in the top bar.')
            return redirect(url_for('index'))


@app.route("/edit", methods=["GET", "POST"])
@login_required
def edit():
    """Allows user to create frames"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensures a valid game is chosen
        j = 0
        for i in range(len(db.execute("SELECT * FROM games WHERE user_id = ?", session["user_id"]))):
            if (request.form.get("game")) == db.execute("SELECT game_name FROM games WHERE user_id = ?", session["user_id"])[i]['game_name']:
                j = 1
        if j == 0:
            return apology("invalid game", 400)
        # Grabs the current frames of the game that exist.
        game = db.execute("SELECT gameid FROM games WHERE user_id = ? and game_name = ?", session["user_id"], request.form.get("game"))[0]['gameid']

        frames = db.execute("SELECT * FROM frames WHERE game_id = ?", int(game))
        # Get a list of names of all current roles in the database accessible for use.
        d = db.execute("SELECT DISTINCT name FROM characters WHERE position = 'defense'")
        defenses = []
        for i in range(len(d)):
            defenses.append(d[i]['name'])

        p = db.execute("SELECT DISTINCT name FROM characters WHERE position = 'prosecution'")
        prosecutors = []
        for i in range(len(p)):
            prosecutors.append(p[i]['name'])

        j = db.execute("SELECT DISTINCT name FROM characters WHERE position = 'judge'")
        judges = []
        for i in range(len(j)):
            judges.append(j[i]['name'])

        w = db.execute("SELECT DISTINCT name FROM characters WHERE position = 'witness'")
        witnesses = []
        for i in range(len(w)):
            witnesses.append(w[i]['name'])
        c = db.execute("SELECT DISTINCT name, pose FROM characters")
        positions = db.execute("SELECT DISTINCT position FROM characters")
        # Redirect to the index
        return render_template("edit.html", frames=frames, witnesses=witnesses, defenses=defenses, prosecutors=prosecutors, judges=judges, c=c, positions=positions, game = game)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        if db.execute("SELECT game_name FROM games WHERE user_id = ?", session["user_id"]):
            games = db.execute("SELECT game_name FROM games WHERE user_id = ?", session["user_id"])
            redir = 'edit'
            return render_template("pickgame.html", games=games, redir=redir)
        else:
            flash('No games! Make games by clicking "make" in the top bar.')
            return redirect("/")


@app.route("/save", methods=["POST"])
@login_required
def save():
    # Retrieves data
    frames = request.form.getlist('frame')
    position = request.form.getlist('position')
    character = request.form.getlist('character')
    poses = request.form.getlist('pose')
    dialogue = request.form.getlist('dialogue')
    game = int(request.form.get('game_id'))
    # Ensure valid game id
    ug = db.execute("SELECT gameid FROM games WHERE user_id = ?", session["user_id"])
    k = 0
    for i in range(len(ug)):
        if ug[i]['gameid'] != game:
            k = k + 1
        if k == len(ug):
            return apology("error: invalid gameid", 400)
    # Ensures equal amount of information retrieved for each frame.
    if not len(frames) == len(position) == len(character) == len(poses) == len(dialogue):
        return apology("error: not all date retrieved", 400)
    # Ensures frames are in order
    for i in range(len(frames)):
        x = i + 1
        if x != int(frames[i]):
            return apology("error: out of order frames", 400)
    # Ensures character information lines up
    for i in range(len(frames)):
        p = db.execute("SELECT DISTINCT position FROM characters")
        f = 0
        for j in range(len(p)):
            if position[i] != p[j]['position']:
                f = f + 1
            if f == len(p):
                return apology("error: invalid position", 400)
        c = db.execute("SELECT DISTINCT name FROM characters WHERE position = ?", position[i])
        f = 0
        for l in range(len(c)):
            if character[i] != c[l]['name']:
                f = f + 1
            if f == len(c):
                return apology("error: invalid character", 400)
        p = db.execute("SELECT pose FROM characters WHERE name = ?", character[i])
        f = 0
        for m in range(len(p)):
            if poses[i] != p[m]['pose']:
                f = f + 1
            if f == len(p):
                return apology("error: invalid pose", 400)
        # Ensures dialogue is proper limit.
        if len(dialogue[i]) > 160:
            return apology("error: phrase too long", 400)
    db.execute("DELETE FROM frames WHERE game_id = ?", game)
    for i in range(len(frames)):
        db.execute("INSERT INTO frames (game_id, frame, position, character, pose, dialogue) VALUES (?, ?, ?, ?, ?, ?)", game, int(frames[i]), position[i], character[i], poses[i], dialogue[i])
    return redirect("/edit")


@app.route("/create", methods=["GET", "POST"])
@login_required
def create():
    """Allows user to create new games"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensures that a name is given.
        if not request.form.get("game"):
            return apology("must have a game name", 400)
        # Ensures the character length isn't too long.
        if len(request.form.get("game")) > 50:
            return apology("name length too long", 400)
        # Confirms that there isn't a game with that same name already.
        if db.execute("SELECT game_name FROM games WHERE user_id = ? AND game_name = ?", session["user_id"], request.form.get("game")):
            return apology("game with game name already exists", 400)
        # Update the value of cash and shares in response to how many were sold.
        db.execute("INSERT INTO games (game_name, user_id) VALUES (?, ?)", request.form.get("game"), session["user_id"])
        # Redirect to the index
        flash('Created!')
        return redirect("/edit")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("create.html")
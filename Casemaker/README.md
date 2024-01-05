## CaseMaker
CaseMaker is designed as a simple fan project of the series Ace Attorney, a videogame franchise by Capcom where the player plays a defense attorney named Phoenix Wright and attempts to solve dramatic court cases.  My goal with this project was to allow fans of the series to replicate sequences from the courtroom on a website, allowing them to make Phoenix Wright and his cast of friends and enemies go through dialogue and perhaps play out cases of their own.  The series was inspired by when I was younger and constantly was looking for a way to do this without finding anything developed.  Nowdays, there are a couple of incredibly designed websites and programs that allow you to do that, but I wanted to try my hand at constructing my own from scratch.

## Background
The Ace Attorney series falls into the genre of a visual novel; the game is mostly clicking through the characters saying dialogue. Typically, during the courtroom sections, there are four main "locations" of the characters: the defense's bench, the prosecution bench, the witness stand, and the judge.  The main trials of the game have the defense attorney trying to parse out the real killer while contending with the prosecution and witness often disrupting them. Visually, as characters speak the visuals shift to their side of the courtroom, with each character having a variety of poses (sprites) to represent their current feeling.  This forms the basis for CaseMaker's design and implementation.  The website assumes the user's familiarity with the series with all of these basic features, since the website is designed for use by fans of the series; for instance, that you aware that characters have poses and are in parts of the courtroom.

## Running
Just like in finance, CaseMaker is a website built in flask and can be run through CS50's code space.  After the file is in one's codespace:

Start Flask's built-in web server (within `finalproject/`):

```
$ flask run
```

Visit the URL outputted by `flask` to see the CaseMaker website.

Additionally, CaseMaker makes use of a `casemaker.db`, which can be found in the finalproject folder. Right clicking it allows you to click `Open in phpLiteAdmin`, which allows you (on the second click) to see the database and its contents.

## Details
In terms of the website itself, the program is fairly straightforward in usage:

When a user first gets onto the site, they will be asked to log in, just like in `finance` or in any other sort of website.  Once the user has logged in, they have a variety of pages to go to. `Create` allows user to make a `game`, which is what they'll be able to edit and play once the project has been fleshed out. `Edit` is where the user actually inputs their game's information; they can input their dialogue and what character is saying it, as well as the character's expression.  They can add as many additional frames as they want. Ultimately, `Edit` is where the user makes their case, which they can play on the `Play` pages. `Play` shows the visual of what the user inputted, and the user can proceed through all the frames of the story at their own pace.

Again, the program should be able to adjust relatively simply to user input.  For instance, the expressions and positions specific characters line up (i.e. Phoenix Wright is a defense attorney so he can't be in a position other than defense) will automatically adjust as the user switches up data, as well as the limit on the characters of dialogue a user can input.  Unless someone is actively malicious and deletes code (which the program is prepared to prevent against harming the website overall), a user shouldn't be able to make a mistake.  If they do, the program will alert them to the problem and move on.

## Credit
All of the sprites I used for this project were made by Capcom and all rights belong to them.

https://youtu.be/_ZY3_hnNh7U
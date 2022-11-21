# patro
This is a terminal based patro app. It uses an array of nepali month lengths to calculate and convert AD to BS and vice-versa.

#### Install
1. `$ make`
2. Copy `build/main` to executable directory or create an alias. <br>
  example: `alias miti='.../build/main'` in  your `.bashrc` or `.bash_aliases` file.

#### Usage
This program is terminal based, so the textual alignment may not the same in different systems.
* `$ miti`  <br>
  displays today's miti
* `$ miti ad <miti>` <br>
  converts given miti to AD <br>
  example: `$ miti ad 2070-5-1` <br>
* `$ miti bs <date>` <br>
  converts given date to BS <br>
  example: `$ miti bs 2013-8-17` <br>
* `$ miti patro <year> <month>` <br>
  displays Nepali calendar for given <year> and <month> <br>
  example: `$ miti patro 2079 8` <br>
 

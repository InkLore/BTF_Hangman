# Batchelorean Logic Presents: Hangman

from random import choice

# Section One: Variables and Functions

# Initilizes Global Game Variables (seperated by when they need to be called)

___GAMESTATUS___ = "boot"

def chooseword():
	wordbank = []
	word = "Captain Picard"  # as homage to the test code
	x = input("Pick a category: Smash Characters (1), Minecraft Blocks (2), Random Words (3): ")
	if x not in "1234567890":
		return chooseword()
	if int(x) == 1:
		with open('wordbanksmashchr.txt', 'r', encoding = 'utf8') as f:
			for line in f:
				wordbank.append(line[:-1])
		word = choice(wordbank)
		return word.lower()
	elif int(x) == 2:
		with open('wordbankmcblocks.txt', 'r', encoding = 'utf8') as f:
			for line in f:
				wordbank.append(line[:-1])
		word = choice(wordbank)
		return word.lower()
	elif int(x) == 3:
		with open('wordbankother.txt', 'r', encoding = 'utf8') as f:
			for line in f:
				wordbank.append(line[:-1])
		word = choice(wordbank)
		return word.lower()
	elif int(x) == 4: #test words
		word = "Jack-O-Lantern"
		return word.lower()

def guess_and_chech():
	global MASTERWORD
	global WRONGGUESS
	global tguess
	global wguess
	global rguess
	alphabet = "abcdefghijklmnopqrstuvwxyz"
	cguess = str(input("Pick a letter: ")) #Current Guess
	cguess = cguess.lower()
	if cguess not in alphabet:
		guess_and_chech()
	elif cguess in tguess:
		guess_and_chech()
	elif cguess in MASTERWORD:
		tguess = tguess + list(cguess)
		rguess = rguess + list(cguess)
		return
	else:
		tguess = tguess + list(cguess)
		wguess = wguess + list(cguess)
		WRONGGUESS += 1
		return

def printman():
	global GUESSWORD
	global WRONGGUESS
	global wguess
	global rguess
	global remaining_letters
	GUESSWORD = MASTERWORD
	for x in rguess:
		remaining_letters = remaining_letters.replace(str(x), '')
	#print("Remaining Letters: " + remaining_letters)
	for y in remaining_letters:
		GUESSWORD = GUESSWORD.replace(y, '_')
	spb = " " * (WRONGGUESS)
	spa = " " * (DIFFICULTY - WRONGGUESS)
	print(spb + r"       '0 -,--     " + spa + r"                      ")
	print(spb + r"   ,____|/_____,   " + spa + r"                      ")
	print(spb + r" /' ___ ___ __  ', " + spa + r"                      ")
	print(spb + r" | |   |   |  |  \ " + spa + r"  ,    ___            ")
	print(spb + r" |  ``` ``` ``   | " + spa + r" \ `<'__\''>,__       ")
	print(spb + r" |       *       } " + spa + r"  |   __________''`,, ")
	print(spb + r" `()-----------()' " + spa + r"  `-()-----------()'  ")
	print("_" * 80)
	print(' ' + '"' + GUESSWORD + '"' + ' ')
	print(f"Wrong Guesses: {wguess}")
	#print("Right Guesses: " + str(rguess) + " and total Guesses: " + str(tguess))

def difficulty():
	DPREP = str(input("Easy, Medium, or Hard: ")).lower()
	if DPREP[0] not in "emh":
		return difficulty()
	if DPREP[0] == "e":
		return 15
	elif DPREP[0] == "m":
		return 10
	elif DPREP[0] == "h":
		return 5
	else:
		difficulty()

#Section Two: Boot Sequence

#Boot art
print("\n")
print(r" |````\     /\     /````\ |    /   ```|``` /````\  ```|``` |    | |````` ")
print(r" |    |    /  \    |      |   /       |    |    |     |    |    | |      ")
print(r" |----<   /----\   |      |--\        |    |    |     |    |----| |----- ")
print(r" |    |  /      \  |      |   \       |    |    |     |    |    | |      ")
print(r" |____/ /        \ \____/ |    \      |    \____/     |    |    | |_____ ")
print("\n")
print(r" |`````` |    | ```|``` |    | |````\  |`````  ")
print(r" |       |    |    |    |    | |    |  |       ")
print(r" |----   |    |    |    |    | |----/  |-----  ")
print(r" |       |    |    |    |    | |    \  |       ")
print(r" |       \____/    |    \____/ |     \ |_____  ")
print("\n")
print(r" |    |     /\     |\    | /````\ |\    /|     /\     |\    |")
print(r" |    |    /  \    | \   | |      | \  / |    /  \    | \   |")
print(r" |----|   /----\   |  \  | |      |  \/  |   /----\   |  \  |")
print(r" |    |  /      \  |   \ | |   `| |      |  /      \  |   \ |")
print(r" |    | /        \ |    \| \____/ |      | /        \ |    \|")
print("\n")

DIFFICULTY = int(difficulty())

#___GAMESTATUS___ = input("One Player Game or Two Player Game?: ")
MASTERWORD = chooseword()
GUESSWORD = MASTERWORD
WRONGGUESS = 0
remaining_letters = "abcdefghijklmnopqrstuvwxyz"
tguess = [] #All guesses
wguess = [] #Wrong Guess
rguess = [] #Right Guess

#Secion Three: The Game itself

___GAMESTATUS___ = "play"

#       Begin Game Loop

print('\n')

while True:
	guess_and_chech()
	print('\n' * 20)
	printman()
	if WRONGGUESS == DIFFICULTY:
		___GAMESTATUS___ = "lose"
		break
	if GUESSWORD == MASTERWORD:
		___GAMESTATUS___ = "win"
		break

#Win/Lose Outcomes

print('\n' * 20)
if ___GAMESTATUS___ == "win":
	print(r"                                      \   / /```\ |   |  |  ||  | ``|`` |\   |")
	print(r"    , ,                                \ /  |   | |   |  \  ||  /   |   | \  |")
	print(r"  ,\   /,```````````````````````````    |   |   | |   |   \ /\ /    |   |  \ |")
	print(r" \   X   / ,,,,,,,,,,,,,,,,,,,,,,,,,,   |   \___/ \___/    |  |   __|__ |   \|")
if ___GAMESTATUS___ == "lose":
	print(r"    '0'   \   / /```\ |   |  |    /```\ /```' |```")
	print(r"  |  |/    \ /  |   | |   |  |    |   | |___  |___")
	print(r"  |'/|      |   |   | |   |  |    |   |     | |   ")
	print(r"  | / \     |   \___/ \___/  |___ \___/ .___/ |___")
	print('\n')
	print('The word was: ' + MASTERWORD)

print('\n')

___GAMESTATUS___ = str(input("Would you like to play again? [Yes] [No] ")).lower()
if ___GAMESTATUS___[0] == 'y':
	exec(open('./Hangman_1P.py').read())

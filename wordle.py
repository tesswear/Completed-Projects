import random
import string

def AlphabetizeLetters(letter_set):
    organized_letter_set = ','.join(sorted(letter_set))
    return organized_letter_set

given_list = open('/Users/tesswear/Downloads/five-letter-words.csv', mode='r', encoding='utf-8-sig')
contents = given_list.read()
split_list = contents.split('\n')

solution = random.choice(split_list).upper()

alphabet = string.ascii_uppercase
alphabet_list = []
for letter in alphabet:
    alphabet_list.append(letter)

incorrect_letters_list = []

number_of_guesses = 0
for guess_number in range(6):
    guess = input('Guess a word! ').upper()
    if guess == solution:
        print('Correct!')
        break
    number_of_guesses += 1
    print('Incorrect.', (6 - number_of_guesses), 'guesses remaining')
    correct_letters = {
        letter for letter, correct in zip(solution, guess) if letter == correct
    }
    misplaced_letters = set(solution) & set(guess) - correct_letters
    incorrect_letters_set = set(guess) - set(solution)
    for letter in incorrect_letters_set:
        incorrect_letters_list.append(letter)
    remaining_letters = set(alphabet_list) - set(incorrect_letters_list)
    print('Correct letters: ', AlphabetizeLetters(correct_letters))
    print('Misplaced letters: ', AlphabetizeLetters(misplaced_letters))
    print('Incorrect letters: ', AlphabetizeLetters(incorrect_letters_list))
    print('Remaining letters: ', AlphabetizeLetters(remaining_letters))

print('The word was ' + solution + '!')
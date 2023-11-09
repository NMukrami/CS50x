# TODO


def main():
    text = input("Text: ").lower()

    # create var
    letters = get_letter(text)
    words = get_word(text)
    sentences = get_sentence(text)

    # math
    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    # print grade
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


# check alphabet in text using isalpha()
def get_letter(text):
    letter = 0

    for char in text:
        if char.isalpha():
            letter += 1
    return letter


# check whitespace in text using isalpha()ef get_word(text):
def get_word(text):
    word = 1

    for char in text:
        if char.isspace():
            word += 1
    return word


# check symbol in text (!, ?, .)
def get_sentence(text):
    sentence = 0

    for char in text:
        if char == "!" or char == "?" or char == ".":
            sentence += 1
    return sentence


if __name__ == "__main__":
    main()

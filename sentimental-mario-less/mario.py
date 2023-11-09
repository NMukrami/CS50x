# TODO


def main():
    # ask user input, if not valid re-prompt again, if valid exit loop
    while True:
        try:
            height = int(input("Height: "))

            # positive integer between 1 and 8,
            if 1 <= height <= 8:
                mario(height)  # call mario func
                break  # break the loop

        except:
            continue


def mario(height):
    for row in range(height):
        for column in range(height):
            if row + column >= height - 1:  # print # without \n
                print("#", end="")

            else:  # print whitespace \n
                print(" ", end="")

        print()  # print new line


if __name__ == "__main__":
    main()

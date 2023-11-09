# TODO
def main():
    # ask user for input
    name = input("What is your name?\n")
    # create var
    name = hello(name)
    # print var
    print(name)


# create function hello and return the value
def hello(name):
    name = f"hello, {name}"
    return name


if __name__ == "__main__":
    main()

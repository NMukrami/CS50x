# TODO


def main():
    coins = 0
    while True:
        try:
            change_owed = float(input("Change owed: "))

            # if not grater than 0 re-prompt again
            if change_owed > 0:
                cents = round(change_owed * 100)

                # loop
                while cents > 0:
                    # quarters
                    if cents >= 25:
                        cents -= 25
                        coins += 1

                    # dimes
                    elif cents >= 10:
                        cents -= 10
                        coins += 1

                    # nickels
                    elif cents >= 5:
                        cents -= 5
                        coins += 1

                    # pennies
                    elif cents >= 1:
                        cents -= 1
                        coins += 1

                print(coins)
                break  # exit loop

        except:
            continue


if __name__ == "__main__":
    main()

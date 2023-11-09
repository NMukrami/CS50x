import csv
import sys


def main():
    # TODO: Check for command-line usage
    csv_, txt = argv_checker()  # check argv

    # TODO: Read database file into a variable
    db = []
    # read database file
    with open(csv_, "r") as file:
        reader = csv.DictReader(file)  # convert to dict
        for row in reader:
            db.append(row)  # append to db

    # TODO: Read DNA sequence file into a variable
    # TODO: Find longest match of each STR in DNA sequence
    # read file squence
    with open(txt, "r") as file:
        sequences_file = file.read()  # conver to list

    # create var dict
    STR = {}
    sequences = list(db[0].keys())[1:]
    # iterate over STR in db
    for key in sequences:
        STR[key] = longest_match(sequences_file, key)  # update sequence STR

    # TODO: Check database for matching profiles
    # check if person have same STR repeats
    for row in db:
        match = 0
        for key in sequences:
            if int(row[key]) == STR[key]:
                match += 1
            if match == len(sequences):
                print(row["name"])
                exit()

    print("No Match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def argv_checker():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    else:
        return sys.argv[1], sys.argv[2]


if __name__ == "__main__":
    main()

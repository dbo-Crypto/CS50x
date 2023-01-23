# TODO
def main():
    # while loop to reprompt if the format of input is invalid
    while True:
        try:
            height = int(input("Height: "))
            if height > 0 and height < 9:
                break
            else:
                pass
        except ValueError:
            print("That's not an integer!")
    # Execute row function
    row(height)


def row(n):
    i = 1
    n = int(n)
    while i < n+1:
        print(" " * (n-i) + "#" * (i))
        i += 1


if __name__ == "__main__":
    main()

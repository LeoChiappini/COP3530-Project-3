


def splitString(input_string):
    # Split the input string at the colon ":" character
    parts = input_string.split(":", 1)  # Using 1 as the second parameter to only split at the first occurrence

    # Extract the two parts
    first_part = parts[0].strip()  # Remove leading and trailing whitespaces
    second_part = parts[1].strip() if len(parts) > 1 else ''  # Check if there is a second part

    return first_part, second_part



def main():

    file_path = "english_dictionary.txt" # File path to the dictionary text file

    # Declares variables needed to process the text file
    line = ""
    word = ""
    definition = ""

    # Open the file and read each line
    try:
        with open(file_path, 'r') as file:
            #for line in file: # Use for the entire file
            for i in range(10): # Use for smaller range for testing purposes
                line = file.readline()
                word, definition = splitString(line)

                print("Word: " + word)
                print("Definition: " + definition)
                print("")

    except FileNotFoundError:
        print("File not found")

    except Exception as ex:
        print("An undefined error has occured")



if __name__ == '__main__':
    main()
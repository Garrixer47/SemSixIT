def count_word_frequencies(filename):
    word_freq = {}
    
    # Open the file in read mode
    with open(filename, 'r') as file:
        # Read each line in the file
        for line in file:
            # Split the line into words
            words = line.strip().split()
            
            # Count the frequency of each word
            for word in words:
                if word in word_freq:
                    word_freq[word] += 1
                else:
                    word_freq[word] = 1
    
    return word_freq

# Prompt the user to enter the file path
filename = input("Enter the file path: ")

# Call the function to count word frequencies
word_frequency = count_word_frequencies(filename)

# Print the word frequencies
for word, freq in word_frequency.items():
    print(f"{word}: {freq}")

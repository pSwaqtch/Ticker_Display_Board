def copy_lines_between(input_file):
    with open(input_file, 'r') as file:
        lines = file.readlines()

    if len(lines) < 11:
        print("File does not have enough lines.")
        return

    lines_to_copy = [lines[i] for i in range(1, len(lines), 11)]  # Get 2, 13, 25, 38, ...

    for i, line_to_copy in enumerate(lines_to_copy):
        insertion_index = 10 + i * 12  # Insert at 10, 22, 34, 49, ...
        lines.insert(insertion_index, line_to_copy)

    with open(input_file, 'w') as file:
        file.writelines(lines)

    print(f"Content copied from lines 2, 13, 25, 38, ... inserted between lines 10, 22, 34, 49, ... in the file.")

# Replace 'input_file.txt' with the path to your file
copy_lines_between('example_output.txt')

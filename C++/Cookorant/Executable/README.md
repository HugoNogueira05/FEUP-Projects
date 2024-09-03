# Valorant Comp Maker
### The executable

To run the program correctly you will need to follow two steps:

> 💡 **Tip:** These steps are specified in greater detail in the main README file

1. **First**, you need to download the executable and place it inside a directory of your choosing.

2. **Second**, you will need to add 2 files to the same directory as the executable:
    - `agents.txt` file
    - `questions.txt` file

> **Note:** These files will be read during the execution, so make sure the files follow the correct structure. For more details, refer to the main README file.

After following the steps mentioned above, you just need to double-click the executable and it's done!

### Errors

During the execution of the program, you may run into some errors:
These errors will always be related to the reading of the needed data files. Here is an example of an error and how to fix it:

1. The window closes instantly after answering the secondary playstyle question.
    - **Solution:** This error occurs because the file `agents.txt` is not being read correctly. This could be because of two reasons:
        1. The file is not in the correct directory:
            - Please make sure that the file is placed in the same directory as the executable itself, do not use any extra directories.
        2. The file is not correctly named:
            - By design, I decided not to give the user an option to provide the program the name of the file, so, the file needs to be named exactly "agents.txt" or "questions.txt". Anything else will result in the file not being read correctly.

> ⚠️ **Warning:** File names are case sensitive! A file named "Agents.txt" is different from a file called "agents.txt". Please ensure that the file names are always lowercase when running the program to avoid errors.
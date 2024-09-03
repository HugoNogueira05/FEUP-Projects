<h1 align="center" style="margin-bottom: 0;">Valorant Comp Maker</h1>
<h3 align="center" style="margin-top: 0;">The executable</h3>

<div style="background: #F9F1F1; padding: 20px; border-radius: 10px; color: black;">
  <p> To run the program correctly you will need to follow two steps:</p>
   
> 💡 **Tip:** These steps are specified in greater detail in the main README file
- First you need to download the executable and place it inside a directory of your choosing

- Second you will need to add 2 files to the same directory of the executable:
    1. agents.txt file
    2. questions.txt file
    > **Note:** This files will be the ones read during the execution so make sure the files follow the correct structure for more details refer to the main README file.

After following the steps mentioned above you just need to double click the executable and it's done!
</div>


<h3 align="center" style="margin-top: 15;">Errors</h3>
<div style="background: #F9F1F1; padding: 20px; border-radius: 10px; color: black;">

### During the execution of the program you may run into some errors:
This errors will always be related to the reading of the needed data files, here is an example of an error and how to fix it:
1. The window closes instantly after answering the secondary playstyle question.
    - Solution : This error occurs because the file agents.txt is not being read correctly, this could be because of 2 reasons: <br>
        1. The file is not in the correct directory:
            - Please make sure that the file is placed in the same directory as the executable itself, do not use any extra directories.
        2. The file is not correctly named: <br>
            - By design, I decided not to give the user an option to provide the program the name of the file, so, the file needs to be named exaclty "agents.txt" or "questions.txt" anything else will result in the file not being read correctly. 

> ⚠️ **Warning:** File names are case sensitive! A file named "Agents.txt" is diferent from a file called "agents.txt" , please ensure that the file names are always lowercase when running the program to avoid errors.

</div>
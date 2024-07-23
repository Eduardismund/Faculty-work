# Shell Script Tasks

## Mursa

1. **Write a shell script that will receive as command line arguments a list of possible files or usernames:**
    - If the argument indicates the name of an existing file (recursive), it will store in a file named `file-reports.info` the full path of the file, its size, and the last modified date.
    - If the argument indicates the name of an existing username (you can use `/etc/passwd`), it will store in a file named `user-reports.info` the username and its group.
    - If neither a file nor a user is found with the value of the argument, the script will store the values in a file named `errors-report.info`.
    - At the end, the script will print an info message indicating the percentage of arguments that were files, usernames, or none of them.

    Note: `file-reports.info`, `user-reports.info`, and `errors-report.info` must be created if they do not exist.

## idk

2. **Sa se scrie un script care numara cate fisiere cu extensia *.txt din directorul curent contin TOATE cuvintele date ca parametri. Se vor efectua toate validarile necesare!**

## Brad

3. **Write a shell script that receives command line arguments as follows:**
    - The first argument is a file containing text.
    - The second argument is a string.
    - The third argument is an email address.
    - The rest of the arguments are also email addresses.
    - For each email address received as an argument, except the third argument, the script will generate a file named `message-<email address here>`. Each file created will contain the following:
      ```
      From: <insert email received as the third argument here>
      To: <insert email address here>
      <insert the text from the file received as the first argument here>

      Delivered on <day>/<month>/<year>
      ```
      - The day, month, and year are taken from the system's current time.
    - After creating the files, the script will group all the files in directories. Each directory will be named after the domains of the email addresses given as arguments (the domain of an email address is the part that comes after @, e.g., yahoo.com, gmail.com, scs.ubbcluj.ro).
    - The following commands can be used to solve this problem: `while`, `for`, `mv`, `date`, `cut`.

## Boian

4. **(RETAKE) Scrieti un script Shell care afiseaza comenzile din PATH similare argumentelor primite in linia de comanda, cautand in directoarele din PATH comenzile ale caror nume includ valoarea argumentului.**

5. **Sa se afiseze ordonate descrescator dupa dimensiune toate fisierele din /tmp a carei dimensiune inmultita cu 1000000 este mai mare decat numarul i-node-ului acelui fisier. Folositi comanda `stat` pentru a afla numarul i-nod-ului (Inode).**

-------- SIVAGAMINATHAN SIVASANKARAN ------


Initially learned GIT using Windows using Youtube tutorial 
** URL not provided here **


UBUNTU
installed VM for ubuntu 64 bit and worked on it with GIT bash

GIT 
created account in Github. 
Created repositories and played with it for sometime.

GIT BASH
downloaded git bash, from git-scm.com/downloads
for ubuntu the command is $sudo apt-get install git
This is like a command line tool, you can use to add username, email and master/branch etc 

CODE
Code is the exact one from the lecture, no modifications were done

COMPILE
Created a file named myinfo.c using VIM editer, vi was hard to manage
Created an output file named myinfo.txt 
Copied the code into the file myinfo.c
Compile using command : gcc -o myinfo myinfo.c
Run the code using : ./myinfo
use echo to copy contents of it to myinfo.txt 
echo ./myinfo >> myinfo.txt
./myinfo >> myinfo.txt 2>&1 

TO GIT
to push code or commit to git, we need to add files 
Set path and directory in git bash 
clone the repository first, using git clone "URL"
we worked on the code only this path under a new folder "hw1"
now use add commands to add the files
git add hw1
git add myinfo.txt
git add myinfo.c

Dont need to add the object file myinfo, we are going to remove it using rm myinfo 

Now use git commit 
git commit -m "any message you would like to say"

all changes get commited
now use git push

git push -u origin master

All changes are available in the git repository


-- Complete the assignment with a README.txt file -- 
-- ASSIGNMENT 1 REQUIREMENTS COMPLETE -- 


# knowledgeIsland
A git repo

# Why git?
Git is a useful tool for team collaboration in all sorts of programming projects.
If you haven't used git before, it's a really good chance to learn how to as it's a tool used in almost all programming projects these days.
Get out of your comfort zone now and you'll be glad you did in a year or sooner.

# If you don't have git on your computer
First check. In terminal:
> git --version
Should give: git version 1.9.3 (Apple Git-50) or something
If it says unknown command - you don't have git.

Then simply go to: https://mac.github.com/ (for Mac)
And install it.
You don't really need the GUI but if you feel like using it - you can of course.
It's easy to do everything in the Terminal as described below

## How to use our repository (repo)

To clone this repo go to terminal and navigate to where you want 
to put it by using 

> cd ./Documents/University.... 
(to whatever folder you normally put your work in)
Note: Don't cd to the Dropbox folder!

Now we clone the repository. Cloning is where you copy the set of files
from the repository onto your local computer. This is achieved by executing 
the following line:

> git clone git@github.com:swiftpantha/knowledgeIsland.git

That might not work since it's an SSH connection.
However when installing git you have got your key (I did), try and locate it.

Go to your user home folder, then open
> pico .ssh/github_rsa.pub
(you can use vim/gedit or whatever text editor you use)
Does the file exist?
If not, refer to this guide on how to create an SSH key for git OR ask Moss or Anton
https://help.github.com/articles/generating-ssh-keys/

Now that you have the SSH key, do the following commands:
> eval "$(ssh-agent -s)"
> ssh-add ~/.ssh/github_rsa
The last one may promt for a password. You've created it with your SSH key. 
If you don't know it, use Spotlight to open Keychain Access
Search for "ssh" or "github" and then right click and choose "copy password to clipboard". 
It will prompt for your system password, enter it and you have your SSH key pass in the clipboard
Now go back to terminal and CMD+V the password

Now your SSH key should have been added to your session.

Go back to the repository folder:
> cd ./Documents/University....

Try cloning again:
> git clone git@github.com:swiftpantha/knowledgeIsland.git

If that didn't work still, contact Anton or Moss

If that worked, OK, so now you've got a copy of all the files. Awesome!!!!!

So why is this so much better? Well the idea is that we actually have branches
branches are identical copies of the master where you can work on one version
of the code to fix one specific thing.

Think of it like this there is a master branch, this branch should
always only have perfect working code. 

You can see the status:
> git status
And see the log of changes:
> git log

Now say you want to fix an issue or work on something in the system

Create a new branch from master by doing the following:

> git checkout -b moss-fixing-failed-log-2

The -b tells git to create a new branch and that branch is called  
moss-fixing-failed-log-2 Now anything I do only makes changes to code on
that branch. So say I find the problem and figured out how to fix it. I have changed the code.
I can now type:

> git status

That'll tell me which files I ended up changing. Now we want to tell git
to add those changes. This is done with:

> git add -A 
to add all files changed
OR:
> git add [filename]
where [filename] is the file you want to add out of those you've changed

Usually you'd use -A version

Now those changes are staged and we're ready to update that branch for everyone!
We do this by commiting the changes. Every commit must include a message about
the changes you made. This is done with:

> git commit -m "Made changes to the testGame.c to include the failed test"
(obviously replace the message in the quotes with an appropriate msg)

Awesome, now we've commited that change we want to push it we can do that with:

> git push origin moss-fixing-failed-log-2 

Now everyone in the team can see that branch online and we can merge it to master, that fix is 
now applied to the production code and the production code has remained 
working at all times. You can also see that all four of us can be working on
the same file at the same time without causing conflicts.
And if there are any conflicts during the merge to the master branch - they are easy to resolve all in one go.

Another useful command is:

> git diff master 

This will give you a line by line of what is different in your code compared to the current master code.


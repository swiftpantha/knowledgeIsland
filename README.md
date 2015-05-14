
# knowledgeIsland
A git repo 

##Git new starters guide!!!

To clone this repo go to terminal and navigate to where you want 
to put it by using 

cd ./Documents/University.... or whatever folder

you normally put your work in. 

Now we clone the repository. Cloning is where you copy the set of files
fro the repository onto your local computer. This is executed by executing 
the following line

git clone git@github.com:swiftpantha/knowledgeIslandAI.git

Ok, so now you've got a copy of all the files. Awesome!!!!!

So why is this so much better? Well the idea is that we actually have branches
branches are identical copies of the master where you can work on one version
of the code to fix one specific thing.

Think of it like this there is a master branch, this branch should
always only have perfect working code. Now say we want to fix an issue

we create a new branch from master by doing the following

git checkout -b moss-fixing-failed-log-2

The -b tells git to create a new branch and that branch is called  
moss-fixing-failed-log-2 Now anything I do only makes changes to code on
that branch. So say I find the problem and figure out how to fix it.
I can now got 

git status

That'll tell me which files I ended up changing. Now we want to tell git
to add those changes. This is done with

git add -A 

Now those changes are staged and we're ready to update that branch for everyone!
We do this by commiting the changes. Every commit must include a message about
the changes you made. This is done with

git commit -m "Made changes to the testGame.c to include the failed test, which
was causing a seg fault by trying to build an arc on a nulls tring path"

Awesome, now we've commited that change we want to push it we can do that with

git push origin moss-fixing-failed-log-2 

Now everyone can see that branch and we can merge it to master, that fix is 
now applied to the production code and the production code has remained 
working at all times. You can also see that all four of us can be working on
the same file at the same time without causing conflicts.

Other cool commands are

git diff master 

This will give you a line by line of what is different to the current master code.


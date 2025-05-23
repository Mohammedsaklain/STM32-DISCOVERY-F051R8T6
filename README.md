

### Usefull git Commands
* Accidentally deleted files and pushed to remote repo, then follow this<br>
1. Find the correct Commit you want to go, with the command
```
    git log --oneline --all
```
2. Once you have the good Commit hash(like 1d0b403), reset your local branch to that commit:
```
    git reset --hard 1d0b403
```
3. Then force push to the remote<br>
```
    git push --force origin <your branch name>
```
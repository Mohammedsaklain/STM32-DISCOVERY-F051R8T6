## Unit testing using Unity framework

Unity is a Unit testing framework written in C.<br>

1. I've created a symbolic link(symlink) for Unity folder, inorder reduce project size (rather copying the whole Unity structure & pasting it)<br>
2. To creat symlink on windows
```
mklink [options] <LinkName> <Target>
mklink /D Unity D:source\directory\place
ex: mklink /D Unity D:\C_C++_FILES\STM32\STM32_TOOLS\Unity
```

3.  mklink  - Command to create symbolic link<br>
    /D      - Specifies to create directory symbolic link(or default file symbolic link)<br>
    Unity   - Name of the new symbolic link<br>
    target  - target path from to create symlink<br>

# Hello Miyoo Project

This project is for getting started with developing CPP+SDL apps for the MiyooMini devices. 
This repo contains a simple "Hello World" application for the Miyoo Mini. The application displays the text "Hello Miyoo" in the center of the screen.

There are plenty of comments in both versions of the .cpp for users to get familiar with the SDL functions. Hope it helps!!

### Preview
![image](https://github.com/Yorisoft/HelloMiyoo/assets/27126548/91dd9b6c-4be8-4467-adb9-a976d1ed9fc6)


## Instructions

### Compiling on Windows Visual Studio

1. Open the `HelloMiyoo` folder located in the `Source/VisualStudio` directory. In there you will find a project solution for opening in Visual Studios. 
2. Configure Visual Studios with SDL and SDL_ttf libraries and include directories.
3. Compile and run the program.

### Compiling on Union-miyoomini-toolchain

1. Clone and start the docker container for the union-miyoomini-toolchain. 
   - For instructions on how to get started union-miyoomini-toolchain please refer to their github READ.me 
   - [union-miyoomini-toolchain](https://github.com/MiyooMini/union-toolchain/tree/main)
2. Transfer the contents `workspace` folder from the `Source/Union-miyoomini-toolchain` directory of this repo to the development environment `/workspace`. 
   - Optionally you could just replace the `workspace` folder with the one from this repo. 
3. Compile the HelloMiyoo program using the provided CMakeList and Toolchain files:
     ```
        cd build
        cmake .. -DCMAKE_TOOLCHAIN_FILE=../Toolchain.cmake
        make
     ```
4. The binary should be located in `workspace/build/HelloMiyoo`

### Transferring the App to the Miyoo Mini Device

1. Connect the Miyoo Mini device to your computer.
  - Refer to the OnionOS wiki for the various ways to do this, e.i: FTP, Webserver, Samba, etc..
2. Transfer the `HelloMiyoo` folder found in the `App` directory of this repo to the device. Place the `HelloMiyoo` in `/mnt/SDCARD/App` folder of the miyoo mini.
3. On the miyoo mini device, navigate to your Apps list. Refresh your App list by bringing up and exiting the 'search' function - pressing `x`
4. Navigate to the HelloMiyoo app and launch it. 

## Additional Information

### Directory Structure

The project has the following directory structure:
```
- HelloMiyoo
    - App
      - HelloMiyoo
    - Source
        - VisualStudio
            - HelloMiyoo
        - Union-miyoomini-toolchain
            - workspace
```

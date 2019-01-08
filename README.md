# Suit
This app will keep track of all the __HR__ components of the company, storing in a database name, surname, birth date and some other basic informations of the candidate.

## Setup the environment
In order to avoid several possible issues during the setup, it is highly recommended to work on Linux.\
If you are not on Linux, you can setup a virtual machine, otherwise you can directly jump [here](https://github.com/lt-scuolalavoro/suit#install-gcc-and-libmysqlclint).
### 1. Setup the virtual machine 
#### Download required resources
1. Download and install [Virtual Box](https://www.virtualbox.org/wiki/Downloads).
2. Download [Ubuntu ISO](https://www.ubuntu.com/download/desktop).
#### Create the virtual machine
1. Open VirtualBox and click New. A new window will come out.
3. In the name field type "Ubuntu".
4. Choose "Linux" as Type and "Ubuntu (64-bit)" as Version.
3. Set the RAM size (at least 4096MB if possible) and click Next.
4. Set the Disk size (20GB are enough) and then click Create.
5. On VirtualBox main window, select the new Ubuntu virtual machine and click START.
6. Pick the ISO previously downloaded.
6. Finish the installation as normal installation.
7. Restart the virtual machine.

### 2. Install gcc and libmysqlclient
In the Ubuntu terminal:
```
sudo apt install gcc
sudo apt-get install libmysqlclient-dev
```

### 3. Install your favorite editor/IDE
You can find the most popular editors in the **Ubuntu Software Center**.

## Clone the repository
```
git clone https://github.com/lt-scuolalavoro/suit.git
```
## Compile and run
In __suit__ folder:
1. Compile:\
```gcc -o bin/suit src/candidates.c```    
2. Run:\
```bin/suit```
## Useful docs 
* [MySQL C](https://docs.google.com/document/d/1XyP09J5EF2wkSpmlwJ9Ew7IGDa0sb1mDyL_xx6XuTk8/edit) - MySQL C API programming tutorial
 
## Built with
* C

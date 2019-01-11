# Suit
This app will keep track of all the __HR__ components of the company, storing in a database name, surname, birth date and some other basic informations of the candidate.

## Index
* [Environment setup](https://github.com/lt-scuolalavoro/suit#environment-setup)
* [Clone the repository](https://github.com/lt-scuolalavoro/suit#clone-the-repository)
* [Compile and run](https://github.com/lt-scuolalavoro/suit#compile-and-run)

## Environment setup
In order to avoid several possible issues during the setup, it is highly recommended to work on Linux.\
If you are not on Linux, you can create a virtual machine, otherwise you can directly jump [here](https://github.com/lt-scuolalavoro/suit#2-install-gcc-and-libmysqlclient).
### 1. Set the virtual machine up 
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

_You can leave the default values for the options not mentioned in these steps._

##### Now you should open this readme file in your virtual machine, so you can easily click on the links or copy and paste the commands.
### 2. Install gcc, libmysqlclient and mysql client
In the Ubuntu terminal:
```
sudo apt install gcc
sudo apt-get install libmysqlclient-dev
sudo apt install mysql-client-core-5.7   
sudo apt install mariadb-client-core-10.1
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

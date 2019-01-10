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

### 2. Install gcc and libmysqlclient
In the Ubuntu terminal:
```
sudo apt install gcc
sudo apt-get install libmysqlclient-dev
```
### 3. Install XAMPP
#### 1. Download the installation package from [here](https://www.apachefriends.org/it/download.html).
#### 2. Make the installation package executable
Move to the Downloads folder by using the following command:
```
$ cd /home/[username]/Downloads
```
The installation package you downloaded needs to be made executable before it can be used further.

Run the following command for this purpose:
```
$ chmod 755 [package name]
```
Example:
```
$ chmod 755 xampp-linux-x64-7.2.10-0-installer.run
```
#### 3. Run the Setup Wizard
Run the following command in order to launch the graphical setup wizard:
```
$ sudo ./[package name]

```
#### 4. Finish the installation
#### 5. Install net-tools
You need net-tools in order to use XAMPP. Run the following command to install the package:
```
$ sudo apt install net-tools
```
#### 6. Run XAMPP
You can run XAMPP through the terminal entering the following command:
```
$ sudo /opt/lampp/lampp start
```
Note: you have to sttart XAMPP every time you restart the system.

#### 7. Verify installation
After you have installed and run XAMPP, you should verify that it works correctly. To do so, enter the following URL in your browser:
```
http://localhost/dashboard/
```
If you've done everything correctly you should see this page:
![XAMPP Dashboard](https://vitux.com/wp-content/uploads/2018/10/word-image-14-768x369.png)

You can access phpmyadmin to manage the database at `http://localhost/phpmyadmin/`.

### 4. Install your favorite editor/IDE
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

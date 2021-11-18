# IndividualAssignment
Individual Assignment - DayTime Protocol
Author - Muhammad 'Asif Danial Bin Mohd Shahir

Before running daytime.out make sure to enable linux daytime server as below:

1.check whether /etc/xinetd.d/daytime file exists or not. if exists goto step 3, if not goto step 2
2.Install xinetd by using this command
#apt-get install xinetd
or
#sudo apt-get install xinetd
3.Then edit the config file in /etc/xinetd.d
#vim /etc/xinetd.d/daytime
in this file change disabe = no in tcp section (or if u want in udp section)
4.then execute command
#invoke-rc.d xinetd reload

# snmp
Tango device server for SNMP

## building
git clone --recursive http://github.com/ELETTRA-SincrotroneTrieste/snmp.git  
cd snmp  
git config --local include.path ../.gitconfig  
rm src/\*Class.cpp  
git checkout -f src/\*Class.cpp  
make
